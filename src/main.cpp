#include "config.h"

// Матрица расположения вершин треугольника
GLfloat points[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f};

// Матрица цвета треугольника
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,  // Red
    0.5f, 1.0f, 0.0f,  // Green
    0.0f, 0.0f, 1.0f}; // Blue

// Вершинный шейдер
const char *vertex_shader =
    "#version 460\n"
    "layout(location = 0) in vec3 vertex_position;"
    "layout(location = 1) in vec3 vertex_color;"
    "out vec3 color;"
    "void main() {"
    "   color = vertex_color;"
    "   gl_Position = vec4(vertex_position, 1.0);}";

// Фрагментный шейдер
const char *fragment_shader =
    "#version 460\n"
    "in vec3 color;"
    "out vec4 frag_color;"
    "void main(){"
    "   frag_color = vec4(color, 1.0);}";

// Переменные разрешения экрана
int g_windowSizeWidth = 640;
int g_windowSizeHeight = 480;

// Callback функция изменения разрешения окна
void glfwWindowSizeCallBack(GLFWwindow *pWindow, int width, int height)
{
    g_windowSizeWidth = width;
    g_windowSizeHeight = height;
    glViewport(0, 0, g_windowSizeWidth, g_windowSizeHeight);
}

// Callback функция закрытия окна
void glfwKeyCallBack(GLFWwindow *pWindow, int key, int scancode, int action, int mode)
{
    // Закрытие окна
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
}

int main()
{

    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Проверка инициализации библиотеки
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << '\n';
        return -1;
    }

    // Проверка на соотвествие версии 4.6 cntxt
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Установка в Core профиль, да бы авойдить старые функции OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создание окна
    GLFWwindow *pWindow = glfwCreateWindow(g_windowSizeWidth, g_windowSizeHeight, "LAND_OUT", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << '\n';
        glfwTerminate();
        return -1;
    }

    // Регистрация callback функции изменения размера окна
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallBack);

    // Регистрация callback функции закрытия окна
    glfwSetKeyCallback(pWindow, glfwKeyCallBack);

    // Контекст текущего окна
    glfwMakeContextCurrent(pWindow);

    // Проверка инициализации glad
    if (!gladLoadGL())
    {
        std::cout << "Cant load Glad!" << '\n';
        return -1;
    }

    // GPU
    std::cout << "Renderer is -> " << glGetString(GL_RENDERER) << '\n';
    // Вывод текущей версии OpenGl
    std::cout << "OpenGL version is -> " << glGetString(GL_VERSION) << '\n';

    // Установка цвета окна
    glClearColor(0, 0, 0, 1);

    // Идентефикация шейдера вершин
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    // Идентефикация фрагментного шейдера
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    // Генерация программы шейдеров
    GLuint shader_program = glCreateProgram();

    // Прикрепление шейдеров к shader_program
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);

    // Линковка программы шейдеров
    glLinkProgram(shader_program);

    // Освобождение памяти.
    glDeleteShader(fs);
    glDeleteShader(vs);

    // Создание VertexBufferObject
    GLuint points_VBO = 0;
    glGenBuffers(1, &points_VBO);                                           // Генерация идентефикатора для points_vbo
    glBindBuffer(GL_ARRAY_BUFFER, points_VBO);                              // Подключение буфера в память GPU, так же делаем его текущим
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW); // Заполнение буфера информацией из массива точек

    // Создание VBO для цветов
    GLuint colors_VBO = 0;
    glGenBuffers(1, &colors_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors, GL_STATIC_DRAW);

    // Создание объекта VA(array)O, указания обработки VBO объектов.
    GLuint vao = 0;
    glGenVertexArrays(1, &vao); // Генерация
    glBindVertexArray(vao);     // Установка сгенерированного VertexArrayObject в текущий

    // Передача данных из буфера VBO в вершинный шейдер OpenGL
    glEnableVertexAttribArray(0);                                // Подключение 0-й позиции шейдера layout(0) -> vertex_shader
    glBindBuffer(GL_ARRAY_BUFFER, points_VBO);                   // Переключение буфера
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Интерпритация байтов

    // Передача из VBO в фрагментный шейдер OpenGL
    glEnableVertexAttribArray(1);                                // layout(1) -> color_shader
    glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);                   // Переключение буфера
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Интерпритация сырых байтов

    // Основной цикл
    while (!glfwWindowShouldClose(pWindow))
    {
        // glClear в данном случае заливка только буфера цвета
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Свап фронт/бэк буферов
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    // Освобождение ресурсов GLFW и закрытие окон
    glfwTerminate();
    return 0;
}
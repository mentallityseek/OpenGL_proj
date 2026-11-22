#include "config.h"

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

    // Основной цикл
    while (!glfwWindowShouldClose(pWindow))
    {
        // glClear в данном случае заливка только буфера цвета
        glClear(GL_COLOR_BUFFER_BIT);
        // Свап фронт/бэк буферов
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
    }

    // Освобождение ресурсов GLFW и закрытие окон
    glfwTerminate();
    return 0;
}
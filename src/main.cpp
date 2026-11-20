#include "config.h"

int main()
{
    // Проверка инициализации библиотеки
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << '\n';
        return -1;
    }

    // Проверка на соотвествие версии 4.6 cntx
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Установка в Core профиль, да бы авойдить старые функции OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создание окна
    GLFWwindow *pWindow = glfwCreateWindow(640, 480, "LAND_OUT", nullptr, nullptr);

    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << '\n';
        glfwTerminate();
        return -1;
    }

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
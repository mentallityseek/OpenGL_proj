#include "config.h"


int main()
{
    setlocale(LC_ALL, "Russian");

    GLFWwindow *window;

    if(!glfwInit())
    {
        std::cout << "GLFW couldnt start!" << '\n';
        return -1;
    }

    window = glfwCreateWindow(800, 600, "Main Window", 0, 0);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
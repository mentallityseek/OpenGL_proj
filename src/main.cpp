#include "config.h"


int main()
{
    GLFWwindow *window;


    if (!glfwInit())
        return -1;

    //Создание окна
    window = glfwCreateWindow(640, 480, "LAND_OUT", 0, 0);
    if (!window){
        glfwTerminate();
        return -1;
    }

    //Контекст текущего окна
    glfwMakeContextCurrent(window);

    //Проверка инициализации glad
    if(!gladLoadGL()){
        std::cout << "Cant load Glad!" << '\n';
        return -1;
    }

    std::cout << "OpenGL version is -> " << GLVersion.major << '.' << GLVersion.minor << '\n';

    //Установка цвета окна
    glClearColor(0, 0, 0, 1);


    
    while (!glfwWindowShouldClose(window)){
        //glClear в данном случае заливка только буфера цвета
        glClear(GL_COLOR_BUFFER_BIT);
        //Свап фронт/бэк буферов
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Освобождение ресурсов GLFW и закрытие окон
    glfwTerminate();
    return 0;
}
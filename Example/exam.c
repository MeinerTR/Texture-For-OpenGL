#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

unsigned char *CWD;
GLFWwindow *Window;

unsigned int SCR_W = 640,
             SCR_H = 480;

#define ERROR(MSG) {perror(#MSG), exit(-1);}

#include "Headers/Texture.h"

void Reshape(GLFWwindow* Window, const unsigned int NEW_W, const unsigned int NEW_H) {
    SCR_W = NEW_W; SCR_H = NEW_H;
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glViewport(0, 0, SCR_W, SCR_H);
    glOrtho(0, SCR_W, SCR_H, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glfwSwapBuffers(Window);
}

void HandleKeyboard(GLFWwindow* window, const unsigned int Key, const unsigned int STAT, const unsigned int A, const unsigned int M) {
    if (A == 1) {
        if (Key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(Window, 1);
        }
    }
}

void InitOpenGL() {
    if (!glfwInit()) ERROR(Unable to init glfw!)
    Window = glfwCreateWindow(
        SCR_W, SCR_H, "Hello, World!", 
        NULL, NULL); if (!Window)
    ERROR(Unable to create glfw window!)
    glfwMakeContextCurrent(Window);

    glEnable(GL_POINTS); glViewport(0, 0, SCR_W, SCR_H);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    SetDefaultColor(0, 0.6, 0, 0);
    glPointSize(20.0f); glOrtho(0, SCR_W, SCR_H, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();

    glfwSetInputMode(Window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(Window, HandleKeyboard);
    // glfwSetInputMode(Window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    // glfwSetMouseButtonCallback(Window, HandleMouse);
    glfwSetFramebufferSizeCallback(Window, Reshape);
}

int main(void) { InitOpenGL();
    if (!(CWD = getcwd(NULL, 0)))
    ERROR(Unable to get the CWD!)
    glClear(GL_COLOR_BUFFER_BIT);
    unsigned int *ASD = Texture(
        CWD, "trying.font", 16, 16
    ); ChangeScaleTo(5.0f, SCR_W, SCR_H);
    DisplayTexture(ASD, 0, 0, 16, 16);
    free(ASD); glfwSwapBuffers(Window);
    while (!glfwWindowShouldClose(Window)) {
        glfwPollEvents();                  }
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int SCR_W = 640,
             SCR_H = 480;

#include <GLFW/glfw3.h>

#define PIX_W 16
#define PIX_H 16

GLFWwindow *Window;
static unsigned char *CWD;

static unsigned int
    CurrColor = 2;
unsigned int *Pixs,
        CurrPic = 0;

#include "Headers/Texture.h"
#include "Headers/UI.h"

static bool
    Grids = True;

void AppendTo(unsigned char *_CWD, const unsigned char *FName) {
    unsigned char DIR[100];
    sprintf(DIR, "%s/%s", _CWD, FName);
    FILE *File = fopen(DIR, "ab");
    fwrite(Pixs, sizeof(unsigned int), (PIX_W * PIX_H), File);
    fputc('\n', File);
    fclose(File);
}
void SaveToFile(unsigned char *_CWD, const unsigned char *FName) {
    unsigned char DIR[100];
    sprintf(DIR, "%s/%s", _CWD, FName);
    FILE *File = fopen(DIR, "wb+");
    fwrite(Pixs, sizeof(unsigned int), (PIX_W * PIX_H), File);
    fclose(File); File = fopen(DIR, "a");
    fputc('\n', File); fclose(File);
}
void LoadFromFile(unsigned char *_CWD, const unsigned char *FName) {
    unsigned char DIR[100];
    sprintf(DIR, "%s/%s", _CWD, FName);
    FILE *File = fopen(DIR, "rb");
    if (!File) {SaveToFile(_CWD, FName);}
    fread(Pixs, sizeof(unsigned int), (PIX_W * PIX_H), File);
    fclose(File);
}
void DisplayCanvas() {
    glClear(GL_COLOR_BUFFER_BIT);
    unsigned int CurrX = 0, CurrY = 0, Counter = 0,
                            XLength = (SCR_W / PIX_W),
                            YLength = (SCR_H / PIX_H);
    glBegin(GL_QUADS);
    for (unsigned int Idx = 0; Idx < (PIX_W * PIX_H); Idx++) {
        if (Counter == PIX_W) { Counter = 0;
            CurrY += YLength; CurrX = 0;   }
        if (Pixs[Idx] == 0) { /* Is there anything to do? */
        } else { if (Pixs[Idx] == 1) { glColor4f(0.0f, 0.0f, 0.0f, 1.0f);}
            else if (Pixs[Idx] == 2) { glColor4f(1.0f, 1.0f, 1.0f, 1.0f);}
            else if (Pixs[Idx] == 3) { glColor4f(1.0f, 0.0f, 0.0f, 1.0f);}
            else if (Pixs[Idx] == 4) { glColor4f(0.0f, 1.0f, 0.0f, 1.0f);}
            else if (Pixs[Idx] == 5) { glColor4f(0.0f, 0.0f, 1.0f, 1.0f);}
            glVertex2i(CurrX, CurrY); glVertex2i(CurrX+XLength, CurrY);
            glVertex2i(CurrX+XLength, CurrY+YLength); glVertex2i(CurrX, CurrY+YLength);
        } CurrX += XLength; Counter++;
    } glEnd(); if (Grids == True) {DrawGrids();}
    glFlush(); glfwSwapBuffers(Window);
}
void Reshape(GLFWwindow* Window, int NEW_W, int NEW_H) {
    SCR_W = NEW_W; SCR_H = NEW_H;
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glViewport(0, 0, SCR_W, SCR_H);
    glOrtho(0, SCR_W, SCR_H, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glfwSwapBuffers(Window);
}
void HandleKeyboard(GLFWwindow* window, const unsigned int Key, const unsigned int STAT, const unsigned int A, const unsigned int M) {
    if (A == 1) {
        if (Key == GLFW_KEY_0) {CurrColor = 0;}
        else if (Key == GLFW_KEY_1) {CurrColor = 1;}
        else if (Key == GLFW_KEY_2) {CurrColor = 2;}
        else if (Key == GLFW_KEY_3) {CurrColor = 3;}
        else if (Key == GLFW_KEY_4) {CurrColor = 4;}
        else if (Key == GLFW_KEY_5) {CurrColor = 5;}
        else if (Key == GLFW_KEY_6) {CurrColor = 6;}
        else if (Key == GLFW_KEY_ESCAPE) { free(Pixs);
            glfwSetWindowShouldClose(Window, 1);
        } if (M == 2) {
            if (Key == GLFW_KEY_C) {
                const unsigned int PixsLen = (PIX_W * PIX_H);
                for (unsigned int Idx = 0; Idx < PixsLen; Idx++) { 
                    Pixs[Idx] = CurrColor; } DisplayCanvas();
            } else if (Key == GLFW_KEY_S) {
                SaveToFile(CWD, "trying.font");
            } else if (Key == GLFW_KEY_G) {
                if (Grids == True) {Grids = False;} else {Grids = True;}
                DisplayCanvas();
                CurrPic = 0;
            } else if (Key == GLFW_KEY_A) {
                AppendTo(CWD, "trying.font");
                CurrPic = 0;
            } else if (Key == GLFW_KEY_F) {
                glClear(GL_COLOR_BUFFER_BIT);
                unsigned int *_Pixs = GetTexture(
                    CWD, "trying.font", CurrPic
                ); ChangeScaleTo(CurrPic + 3, SCR_W, SCR_H);
                DisplayTexture(_Pixs, 5, 5, 16, 16);
                CurrPic++; free(_Pixs); glfwSwapBuffers(Window);
            }
        }
    }
}
static void HandleMouse(GLFWwindow* window, const unsigned int Button, const unsigned int STAT, const unsigned int WTH) {
    if (STAT == GLFW_PRESS) { double posX, posY;
        glfwGetCursorPos(Window, &posX, &posY);
        const unsigned int PosX = posX, PosY = posY;
        for (unsigned int CurrY = 0; CurrY < PIX_H+1; CurrY++) {
            if (PosY < (CurrY * (SCR_H / PIX_H))) {
                for (unsigned int CurrX = 0; CurrX < PIX_W+1; CurrX++) {
                    if (PosX < (CurrX * (SCR_W / PIX_W))) {
                        Pixs[((CurrY-1) * PIX_H) + (CurrX - 1)] = CurrColor;
                        DisplayCanvas(); return;
                    }
                }
            }
        }
    }
}
void InitOpenGL() {
    if (!glfwInit()) ERROR(Unable to init glfw!)
    Window = glfwCreateWindow(SCR_W, SCR_H, "MeinTexture", NULL, NULL);
    if (!Window) ERROR(Unable to create glfw window!) glfwMakeContextCurrent(Window);

    glEnable(GL_POINTS); glViewport(0, 0, SCR_W, SCR_H);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    SetDefaultColor(0, 0.6, 0, 0);
    glPointSize(20.0f); glOrtho(0, SCR_W, SCR_H, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();

    glfwSetInputMode(Window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(Window, HandleKeyboard);
    glfwSetInputMode(Window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetMouseButtonCallback(Window, HandleMouse);
    glfwSetFramebufferSizeCallback(Window, Reshape);
    Pixs = (unsigned int *) calloc (
        (PIX_W * PIX_H), sizeof(unsigned int)
    );
}
int main(void) { InitOpenGL();
    if (!(CWD = getcwd(NULL, 0))) ERROR(Unable to get current work directory!)
    LoadFromFile(CWD, "trying.font"); DisplayCanvas();
    while (!glfwWindowShouldClose(Window)) {
        glfwWaitEvents();} glfwTerminate();}

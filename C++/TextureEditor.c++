#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define I int
#define C char
#define V void
#define B bool
#define S static

#define CC const char
#define UI unsigned int
#define CUI const unsigned int
#define UC unsigned char
#define CUC const unsigned char
#define CI const int

#include "Headers/Prefs.h"
#include <GLFW/glfw3.h>

class Canvas {
    public:
        std::string Name;
        UI W, H, *Pixs, CurrColor;
}; GLFWwindow *Window;

#define W_PIX TheCanvas.W
#define H_PIX TheCanvas.H

S std::vector<Canvas> Canvases;
S UI CurrCanvas = 0, PIX_W, PIX_H, SCR_W, SCR_H,
    W_SCR = (SCR_W / 2), H_SCR = (SCR_H / 2);
S Canvas TheCanvas; UI CurrColor = 0;

#include "Headers/Display.h"

#define ERROR(MSG, PTH) {std::cout << MSG << PTH << std::endl; return false;}

S V New(CUI _W, CUI _H, std::string _Name) {
    CurrCanvas++; W_PIX = _W; H_PIX = _H; 
    TheCanvas.Name = _Name;
    if (TheCanvas.Pixs) {free(TheCanvas.Pixs);}
    TheCanvas.Pixs = (UI *) calloc ((_W * _H) * 3, 4);
    PIX_W = (SCR_W / _W); PIX_H = (SCR_H / _H); 
    Canvases.push_back(TheCanvas); Display.Update();      
}

S Canvas Read(CC *Path) { Canvas Output;
    std::ifstream File(Path, std::ios::in | std::ios::binary);
    File.read((C *) &Output, sizeof(Canvas));
    File.close(); return Output;
}

S V Load(CC *Path) {
    Canvas TheCanvas = Read(Path); 
    CurrCanvas++;
    PIX_W = (SCR_W / W_PIX);
    PIX_H = (SCR_H / H_PIX);
    Canvases.push_back(TheCanvas);
    Display.Update();      
}

S V Write(Canvas TheCanvas, CC *Path) {
    std::ofstream File(Path, std::ios::out | std::ios::binary);
    File.write((C *) &TheCanvas, sizeof(Canvas));
    File.close();
}

#include "Headers/Inputs.h"

#include "Headers/Init.h"

int main(void) { INIT Init;
    if (!Init.ThePrefs() | !Init.OpenGL()) {
        glfwTerminate(); return -1;
    } New(16, 16, "White Space"); CurrCanvas--;
    while (!glfwWindowShouldClose(Window)) {
        glfwPollEvents();
    } glfwTerminate();
    return 0;
}
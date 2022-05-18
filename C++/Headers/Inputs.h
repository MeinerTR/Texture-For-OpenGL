void Reshape(GLFWwindow* Window, CI NEW_W, CI NEW_H) {
    SCR_W = NEW_W; SCR_H = NEW_H;
    W_SCR = (NEW_W / 2);
    H_SCR = (SCR_H / 2);
    PIX_W = (SCR_W / W_PIX);
    PIX_H = (SCR_H / H_PIX);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glViewport(0, 0, NEW_W, NEW_H);
    glOrtho(0, NEW_W, NEW_H, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    Display.Update(); glfwSwapBuffers(Window);
}

void Keyboard(GLFWwindow* window, CI Key, CI STAT, CI A, CI M) {
    printf("%i %i %i\n", STAT, A, M);
    if (A == 1) {
        if (M == 1) { if (Key == GLFW_KEY_F5) {
            glfwSwapBuffers(Window);
        } else if (Key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(Window, 1);
        } } else {
            if (Key == GLFW_KEY_0) { CurrColor = 0; }
            else if (Key == GLFW_KEY_1) { CurrColor = 1; }
            else if (Key == GLFW_KEY_2) { CurrColor = 2; }
            else if (Key == GLFW_KEY_3) { CurrColor = 3; }
            else if (Key == GLFW_KEY_4) { CurrColor = 4; }
            else if (Key == GLFW_KEY_5) { CurrColor = 5; }
        }
    }
}

void Mouse(GLFWwindow* window, CI Button,  CI STAT, CI WTH) {
    if (STAT == GLFW_PRESS) { double PosX, PosY;
        glfwGetCursorPos(Window, &PosX, &PosY); UI Curr = 0;
        for (UI CurrY = 0; CurrY < (SCR_H + 1); CurrY += PIX_H) {
            for (UI CurrX = 0; CurrX < (SCR_W + 1); CurrX += PIX_W) {
                if (CurrY > PosY) { if (CurrX > PosX) {
                    Curr = (Curr - (CurrY / PIX_H) - (W_PIX + 1)) * 3;
                    switch (CurrColor) {
                        case (0): { TheCanvas.Pixs[Curr] = 4;
                            TheCanvas.Pixs[Curr + 1] =     0;
                            TheCanvas.Pixs[Curr + 2] =     4;

                        } case (1): {TheCanvas.Pixs[Curr] =  0;
                            TheCanvas.Pixs[Curr + 1] =       0;
                            TheCanvas.Pixs[Curr + 2] =       0;

                        } case (2): { TheCanvas.Pixs[Curr] = 1;
                            TheCanvas.Pixs[Curr + 1] =       0;
                            TheCanvas.Pixs[Curr + 2] =       0;

                        } case (3): { TheCanvas.Pixs[Curr] = 0;
                            TheCanvas.Pixs[Curr + 1] =       1;
                            TheCanvas.Pixs[Curr + 2] =       0;

                        } case (4): { TheCanvas.Pixs[Curr] = 0;
                            TheCanvas.Pixs[Curr + 1] =       0;
                            TheCanvas.Pixs[Curr + 2] =       1;

                        } case (5): { TheCanvas.Pixs[Curr] = 1;
                            TheCanvas.Pixs[Curr + 1] =       1;
                            TheCanvas.Pixs[Curr + 2] =       1;
                        }
                    } Display.Update(); return; }
                } Curr++;
            }
        }
    }
}
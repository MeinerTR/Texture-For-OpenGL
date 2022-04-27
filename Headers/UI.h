 
void DrawGrids() {
    glBegin(GL_LINES); unsigned int CurrCLR = 1;
    for (unsigned int Y = 0; Y < PIX_H; Y++) {
        for (unsigned int X = 0; X < PIX_W; X++) {
            CurrCLR++; if (CurrCLR == 7) {CurrCLR = 1;}
            ChangeColorTo(CurrCLR);
            glVertex2i((SCR_W / PIX_W) * X, 0);
            glVertex2i((SCR_W / PIX_W) * X, SCR_H);
        } CurrCLR++; if (CurrCLR == 7) {CurrCLR = 1;}
        ChangeColorTo(CurrCLR);
        glVertex2i(0, (SCR_H / PIX_H) * Y);
        glVertex2i(SCR_W, (SCR_H / PIX_H) * Y);
    } glEnd();}

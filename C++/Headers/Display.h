class DISPLAY {
    public:
        V Update(V);
        V Grids(V);
        V ShowCurrImg(V);
}; DISPLAY Display;

V DISPLAY::Grids(V) { glBegin(GL_LINES);
    for (UI CurrX = 0; CurrX < W_PIX; CurrX++) {
        CUI X = (CurrX * PIX_W);
        glVertex2i(X, 0);
        glVertex2i(X, SCR_H);
    } for (UI CurrY = 0; CurrY < H_PIX; CurrY++) {
        CUI Y = (CurrY * PIX_H);
        glVertex2i(0, Y);
        glVertex2i(SCR_W, Y);
    } glEnd();
}

V DISPLAY::Update(V) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(PIX_W); UI Curr = 0;
    for (UI CurrY = 0; CurrY < H_PIX; CurrY++) {
        for (UI CurrX = 0; CurrX < W_PIX; CurrX++) {
            UI Current = (Curr * 3); 
            if (TheCanvas.Pixs[Current] != 4) {
                glColor3f(TheCanvas.Pixs[Current],
                    TheCanvas.Pixs[Current + 1]  , 
                    TheCanvas.Pixs[Current + 2] );
                
            }
            // printf("%i %i %i\n", TheCanvas.Pixs[Current],
            // TheCanvas.Pixs[Current + 1], TheCanvas.Pixs[Current + 2]);
        Curr++; }
    } glPointSize(PIX_W); Grids();
    glfwSwapBuffers(Window);
}

V DISPLAY::ShowCurrImg(V) {

}
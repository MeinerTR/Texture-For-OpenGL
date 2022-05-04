static float Scale = 1.0f,
    _R__ = 0.0f, _G__ = 0.0f,
    _B__ = 0.0f, _A__ = 0.0f;

typedef enum {True, False} bool;

void SetDefaultColor(const float R, const float G, const float B, const float A) {
    glClearColor(R, G, B, A); _R__ = R; _G__ = G; _B__ = B; _A__ = A;
}
void ChangeColorTo(const unsigned int CLR) {
    if (CLR == 0) { glColor4f(_R__, _G__, _B__, _A__);
    } else { if (CLR == 1) { glColor4f(0.0f, 0.0f, 0.0f, 1.0f);}
        else if (CLR == 2) { glColor4f(1.0f, 1.0f, 1.0f, 1.0f);}
        else if (CLR == 3) { glColor4f(1.0f, 0.0f, 0.0f, 1.0f);}
        else if (CLR == 4) { glColor4f(0.0f, 1.0f, 0.0f, 1.0f);}
        else if (CLR == 5) { glColor4f(0.0f, 0.0f, 1.0f, 1.0f);}
        else if (CLR == 6) { glColor4f(1.0f, 0.0f, 0.0f, 1.0f);}
    } /* So much colors ;) */ }
unsigned int Len(const unsigned char *STR) {
    unsigned char CHR = 0; unsigned int Output = 0;
    while (CHR != '\n') {CHR = STR[Output];
        Output++;} return Output;
}
unsigned int *GetTexture(unsigned char *_CWD, const unsigned char *FName, const unsigned int TheLine) {
    unsigned char DIR[Len(_CWD) + Len(FName)]; char CHR;
    sprintf(DIR, "%s/%s", _CWD, FName);
    FILE *File = fopen(DIR, "rb");
    unsigned int *Output = (unsigned int *) calloc (
        1024, sizeof(unsigned int)              );
    fseek(File, 1025 * TheLine, SEEK_CUR);
    fread(Output, sizeof(unsigned int), 1024, File);
    fclose(File); return Output;
}
void ChangeScaleTo(const float _Scale, const unsigned int __SCR_W, const unsigned int __SCR_H) {
    glMatrixMode(GL_PROJECTION); glLoadIdentity();

    Scale = _Scale; glPointSize(_Scale);
    glOrtho(0, __SCR_W, __SCR_H, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}
unsigned int *Texture(const unsigned char *_CWD, const unsigned char *FName, const unsigned int LenX, const unsigned int LenY) {
    unsigned char DIR[100];
    unsigned int *Output;
    sprintf(DIR, "%s/%s", _CWD, FName);
    FILE *File = fopen(DIR, "rb"); char CHR;
    Output = (unsigned int *) calloc (
        (LenX * LenY), sizeof(unsigned int) );
    fread(Output, sizeof(unsigned int), (LenX * LenY), File);
    fclose(File); return Output;
}
void DisplayTexture(unsigned int *TextureArray, const unsigned int PosX, const unsigned int PosY, const unsigned int LenX, const unsigned int LenY) {
    glBegin(GL_POINTS); unsigned int Idx = 0;
    for (unsigned int CurrY = PosY; CurrY < (PosY + (LenY * Scale)); CurrY += Scale) {
        for (unsigned int CurrX = PosX; CurrX < (PosX + (LenX * Scale)); CurrX += Scale) {
            ChangeColorTo(TextureArray[Idx]);
            glVertex2i(CurrX, CurrY); Idx++;
        }
    } glEnd(); glFlush();
}

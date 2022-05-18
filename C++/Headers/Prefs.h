#ifndef PREFS_H
#define PREFS_H

class Prefs {
    public:
        int CurrLine = 0;
        std::string Path;
        std::string CurrKey;
        std::string STR(std::string Key);
        int INT(std::string Key);
        void Change(std::string Key, std::string Value);
};

#define prefNULL 0
#define prefPATH 1
#define prefFIND 2
#define prefTYPE 3

std::string Prefs::STR(std::string Key) { CurrKey = Key;
    if (Path.length() == 0) {throw 0;}
    FILE *File = fopen(Path.c_str(), "r");
    if (File == NULL) {throw 1;} CurrLine = 0;
    std::string Output = ""; char CHR;
    unsigned int Pos = 0, Status = 1;
    while (CHR != -2) { CHR = fgetc(File);
        if (CHR == '\n') {
            if (Status == 2) {
                fclose(File);
                return Output;
            } Status = 1; Pos = 0;
        } else if (CHR == EOF) {
            if (Status == 2) {
                fclose(File);
                return Output;
            } CHR = -2;
        } else {
            if (Status == 1) {
                if (CHR != Key[Pos]) {
                    Status = 0;
                } if (CHR == ' ') {
                    if (Pos == Key.length()) {
                        Status = 2;
                    } 
                } Pos++;
            } else if (Status == 2) {
                Output += CHR;
            }
        }
    } fclose(File); throw 2;
}

int Prefs::INT(std::string Key) { CurrKey = Key;
    if (Path.length() == 0) {throw 0;}
    FILE *File = fopen(Path.c_str(), "r");
    if (File == NULL) {throw 1;} CurrLine = 0;
    std::string Output = ""; char CHR;
    unsigned int Pos = 0, Status = 1;
    while (CHR != -2) { CHR = fgetc(File);
        if (CHR == '\n') { CurrLine++;
            if (Status == 2) {
                fclose(File);
                try {
                    int CopyCat = stoi(Output);
                    return CopyCat;
                } catch (std::invalid_argument F) {
                    throw 3;
                } } Status = 1; Pos = 0;
        } else if (CHR == EOF) { CurrLine++;
            if (Status == 2) {
                fclose(File);
                try {
                    int CopyCat = stoi(Output);
                    return CopyCat;
                } catch (std::invalid_argument F) {
                    throw 3;
                } } CHR = -2;
        } else {
            if (Status == 1) {
                if (CHR != Key[Pos]) {
                    Status = 0;
                } if (CHR == ' ') {
                    if (Pos == Key.length()) {
                        Status = 2;
                    } 
                } Pos++;
            } else if (Status == 2) {
                Output += CHR;
            }
        }
    } fclose(File); throw 2;
}

void Prefs::Change(std::string Key, std::string Value) {
    CurrKey = Key; if (Path.length() == 0) {throw 0;}
    FILE *File = fopen(Path.c_str(), "r"), *Hi = fopen("OOPSIE.VIRUS", "w");
    if (File == NULL) {throw 1;} fclose(Hi); std::string Line;
    Hi = fopen("OOPSIE.VIRUS", "a"); char CHR; int Curr = 0; bool
    Ins = false, Any = false; while (CHR != -2) { CHR = fgetc(File);
        if (CHR == '\n') {
            if (Ins) { fprintf(Hi, "%s %s\n", Key.c_str(), Value.c_str()); Any = true;
            } else { fputs(Line.c_str(), Hi); fputc('\n', Hi);
            } Ins = false; Line.clear(); Curr = 0;
        } else if (CHR == EOF) {
            if (Ins) { fprintf(Hi, "%s %s", Key.c_str(), Value.c_str()); Any = true;
            } else { fputs(Line.c_str(), Hi); } CHR = -2;
        } else { if (Ins == true) { continue; }
            if (CHR != Key[Curr]) {
                if (CHR == ' ') { if (Curr == Key.length()) {
                        Ins = true; } else { Ins = false;   }
                }
            } Line += CHR; Curr++;
        }
    } fclose(File); fclose(Hi); remove(Path.c_str()); 
    if (Any == false) {throw 2;} rename("OOPSIE.VIRUS", Path.c_str());
}

#endif
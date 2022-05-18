class INIT {
    public:
        B OpenGL(V);
        B ThePrefs(V);
};

B INIT::OpenGL(V) {
    if (!glfwInit()) ERROR("Unable to init glfw!", ' ')
    Window = glfwCreateWindow(SCR_W, SCR_H, "TextureEditor", NULL, NULL);
    if (!Window) ERROR("Unable to create glfw window!", ' ')
    glfwMakeContextCurrent(Window);
    
    glMatrixMode(GL_PROJECTION);
    glPointSize(PIX_W); glOrtho(0, SCR_W, SCR_H, 0, 0, 1);
    glViewport(0, 0, SCR_W, SCR_H); glMatrixMode(GL_MODELVIEW);

    glfwSetInputMode(Window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(Window, Keyboard);
    // glfwSetInputMode(Window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetMouseButtonCallback(Window, Mouse);
    glfwSetFramebufferSizeCallback(Window, Reshape); return true;
}

B INIT::ThePrefs(V) {
    Prefs Settings; Settings.Path = "Settings.prefs";
    try {
        SCR_W = Settings.INT("WIDTH"); W_SCR = (SCR_W / 2);
        SCR_H = Settings.INT("HEIGHT"); H_SCR = (SCR_H / 2);
    } catch (int ERRCODE) {
        switch (ERRCODE) {
            case (prefNULL): ERROR("\"Prefs.Path\" is NULL!", ' ')
            case (prefPATH): ERROR("Unable to open!: ", Settings.Path)
            case (prefFIND): ERROR("Unable to find WIDTH or HEIGHT!: ", Settings.Path);
            case (prefTYPE): ERROR("Expected integer at WIDTH or HEIGHT!: ", Settings.Path);
        }
    }
    return true;
}
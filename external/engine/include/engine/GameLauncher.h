#pragma once
#include "engine/GameCore.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class GameLauncher
{
public:
    GameLauncher(GameCore* instance);
    ~GameLauncher() {}

    void Launch();
    void SetCursorMode(int mode);
protected:
    inline static GameCore* game_instance = nullptr;
    GLFWwindow* window = nullptr;

    void init_glfw();
    void init_glad();
    void init_opengl();
    void end();

    friend void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};
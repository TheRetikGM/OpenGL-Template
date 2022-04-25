#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/*
*  Simple keyboard interface wrapper for checking key presses.
*/
class InputInterface
{
public:
    InputInterface(bool* pKeys, bool* pKeysProcessed, bool* pMouseButtons, bool* pMouseButtonsPressed) 
        : pKeys(pKeys)
        , pKeysProcessed(pKeysProcessed)
        , pMouseButtons(pMouseButtons)
        , pMouseButtonsPressed(pMouseButtonsPressed)
        , vMousePosition(glm::vec2(0.0f))
    {}

    // Checks ifs key was pressed (will return true only once until it is released).
    inline bool Pressed(int key)
    {
        if (pKeys[key] && !pKeysProcessed[key])
        {
            pKeysProcessed[key] = true;
            return true;
        }
        return false;
    }
    // Checks if key is being held.
    inline bool Held(int key)
    {
        return pKeys[key];
    }

    inline bool MousePressed(int key)
    {
        if (pMouseButtons[key] && !pMouseButtonsPressed[key])
        {
            pMouseButtonsPressed[key] = true;
            return true;
        }
        return false;
    }
    inline bool MouseHeld(int key)
    {
        return pMouseButtons[key];
    }
    const glm::vec2& GetMousePos() { return vMousePosition; }

protected:
    bool* pKeys;
    bool* pKeysProcessed;
    bool* pMouseButtons;
    bool* pMouseButtonsPressed;
    glm::vec2 vMousePosition;

    friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    friend void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/GameLauncher.h"
#include "engine/DebugColors.h"

inline float get_time_from_start()
{
    return float(glfwGetTime());
}

GameLauncher::GameLauncher(GameCore* instance)
{
    game_instance = instance;
    init_glfw();
    init_glad();
    init_opengl();
    game_instance->GetTimeFromStart = &get_time_from_start;
}

void GameLauncher::Launch()
{
    try
    {
        game_instance->InitEngine();
        game_instance->Init();

        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        while (!glfwWindowShouldClose(window) && game_instance->Run)
        {
            float currentFrame = (float)glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            // Poll events like key presses, mouse event, ...
            glfwPollEvents();

            game_instance->ProcessInput();
            game_instance->Update(deltaTime);

            // Set window title
            glfwSetWindowTitle(window, game_instance->WindowTitle.c_str());

            // Clear default framebuffer and render game scene.
            glClearColor(game_instance->BackgroundColor.r, game_instance->BackgroundColor.g, game_instance->BackgroundColor.b, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            game_instance->Render();

            // Swap back and front buffers.
            glfwSwapBuffers(window);
        }
        if (!game_instance->Run)
            glfwSetWindowShouldClose(window, true);
    }
    catch (const std::exception& e)
    {
        std::cerr << DC_ERROR " " << e.what() << std::endl;
    }
    end();
}
void GameLauncher::SetCursorMode(int mode)
{
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}
void GameLauncher::init_glfw()
{
    /* Initialize glfw and create window*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(game_instance->Width, game_instance->Height, game_instance->WindowTitle.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSwapInterval(1);
}
void GameLauncher::init_glad()
{
    /* Load GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("GameLauncher::init_glad(): Failed to initialize GLAD.");
    }
}
void GameLauncher::init_opengl()
{
    // OpenGL configuration
    glViewport(0, 0, game_instance->Width, game_instance->Height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST | GL_CULL_FACE);
}
void GameLauncher::end()
{
    game_instance->Delete();
    game_instance->DeleteEngine();
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	GameLauncher::game_instance->Width = width;
	GameLauncher::game_instance->Height = height;
	GameLauncher::game_instance->OnResize();
    GameLauncher::game_instance->_onResize();
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{		
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			GameLauncher::game_instance->Keys[key] = true;
		else if (action == GLFW_RELEASE)
		{
			GameLauncher::game_instance->Keys[key] = false;
			GameLauncher::game_instance->KeysProcessed[key] = false;
		}
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	GameLauncher::game_instance->ProcessMouse(float(xpos), float(ypos));
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	GameLauncher::game_instance->ProcessScroll((float)yoffset);
}
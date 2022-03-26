#include <engine/Engine.h>
#include <vector>

unsigned int SCREEN_WIDTH = 800;
unsigned int SCREEN_HEIGHT = 600;

class Game : public GameCore
{
public:
	Game(unsigned int width, unsigned int height) : GameCore(width, height) {}

	void Init()
	{
		text_renderer->Load(ASSETS_DIR "fonts/DejaVuSansCondensed.ttf", 20);
		BackgroundColor = glm::vec3(0.0f);
	}
	void Delete()
	{
		GameCore::Delete();
	}

	void ProcessInput()
	{
		if (Input->Pressed(GLFW_KEY_ESCAPE))
			Exit();
	}
	void Update(float dt)
	{
	}
	void Render()
	{
		text_renderer->RenderText("Hello, Engine!", 10.0f, 10.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	}
};

int main()
{
	GameCore* game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);
	GameLauncher launcher(game);
	launcher.Launch();

	delete game;
	return 0;
}

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
		text_renderer->Load(ASSETS_DIR "fonts/DejaVuSansCondensed.ttf", 64);
		BackgroundColor = glm::vec3(0.0f);

		ResourceManager::LoadTexture(ASSETS_DIR "awesomeface.png", true, "awesome_face");
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
		std::string str = "Hello, Engine!";
		glm::vec2 str_size = text_renderer->GetStringSize(str);
		glm::vec2 center = glm::vec2(float(Width), float(Height)) * 0.5f;
		text_renderer->RenderText(str, center.x - str_size.x * 0.5f, center.y - str_size.y * 0.5f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		sprite_renderer->RenderSprite(
			ResourceManager::GetTexture("awesome_face"),
			glm::vec2(10.0f, 10.0f),
			glm::vec2(100.0f, 100.0f),
			0.0f,
			glm::vec3(1.0f)
		);
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

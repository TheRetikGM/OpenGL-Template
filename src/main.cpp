#include <engine/Engine.h>
#include <vector>

unsigned int SCREEN_WIDTH = 800;
unsigned int SCREEN_HEIGHT = 600;

class Game : public GameCore
{
	bool render_face = true;
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
		static std::string str = "Hello, Engine!";
		glm::vec2 str_size = text_renderer->GetStringSize(str);
		glm::vec2 center = glm::vec2(float(Width), float(Height)) * 0.5f;
		static glm::vec3 vTextColor{ 1.0f, 0.0f, 0.0f };
		text_renderer->RenderText(str, center.x - str_size.x * 0.5f, center.y - str_size.y * 0.5f, 1.0f, vTextColor);

		Texture2D& awesome_face = ResourceManager::GetTexture("awesome_face");
		if (render_face)
			sprite_renderer->RenderSprite(
				awesome_face,
				glm::vec2(10.0f, 10.0f),
				glm::vec2(100.0f, 100.0f),
				0.0f,
				glm::vec3(1.0f)
			);

		ImGui::Begin("Hello from ImGui!");
		ImGui::Text("This is OpenGL-Template demo application.");
		ImGui::Checkbox("Render awesome face", &this->render_face);
		ImGui::ColorEdit3("Background color", 
			(float*)((void*)&BackgroundColor), 
			ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs
		);
		ImGui::ColorEdit3("Text color", 
			(float*)((void*)&vTextColor), 
			ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueBar
		);
		ImGui::InputText("Hello text", &str);
		ImGui::Image(
			(void*)awesome_face.ID,
			ImVec2{ 0.25f *  (float)awesome_face.Width, 0.25f * (float)awesome_face.Height }
		);
		ImGui::Dummy(ImVec2(10.0f, 10.0f));
		if (ImGui::Button("Exit"))
			Exit();
		ImGui::End();
	}
};

int main()
{
	GameCore* game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);
	GameLauncher launcher(game);
	launcher.GuiTheme = ImGuiTheme::dark;
	launcher.Init().Launch();

	delete game;
	return 0;
}

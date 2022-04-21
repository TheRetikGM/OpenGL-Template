#include <engine/Engine.h>
#include <vector>

unsigned int SCREEN_WIDTH = 800;
unsigned int SCREEN_HEIGHT = 600;

class Game : public GameCore
{
	std::shared_ptr<Framebuffer> fbo = nullptr;
	
public:
	Game(unsigned int width, unsigned int height) : GameCore(width, height) {}

	void Init()
	{
		ResourceManager::LoadTexture(ASSETS_DIR "awesomeface.png", true, "face");

		fbo = Framebuffer::Create2DBasicFramebuffer(Width, Height);
	}
	void Delete()
	{
		GameCore::Delete();
		fbo->Delete();
	}
	void ProcessInput()
	{
		if (Input->Pressed(GLFW_KEY_ESCAPE))
			Exit();
	}
	float rotation = 0.0f;
	void Update(float dt)
	{
		rotation += 90.0f * dt;
		if (rotation > 360.0f)
			rotation -= 360.0f;
	}
	void Render()
	{
		fbo->Bind();
		fbo->Clear();
		glm::vec2 face_size = glm::vec2(float(this->Width) / 10.0f, float(Height) / 5.0f);
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 5; y++)
			{
				basic_renderer->RenderShape(br_Shape::circle_empty, glm::vec2(x * face_size.x, y * face_size.y), face_size, 0.0f, glm::vec3(1.0f));
				sprite_renderer->RenderSprite(ResourceManager::GetTexture("face"), glm::vec2(x * face_size.x, y * face_size.y), face_size, rotation, 
					glm::vec3(glm::abs( ((x + 1) * (y + 1) / (50.0f)) * glm::sin(glfwGetTime())), (x + 1) * (y + 1) / (50.0f) *  glm::abs(glm::cos(glfwGetTime())),  std::pow((x + 1) * (y + 1) / (50.0f), 2) * glm::abs(glm::cos(glfwGetTime()) * glfwGetTime()))
				);
			}
		}
		fbo->Unbind();

		static float size[2] = {497.0f, 200.0f};

		ImGui::Begin("Texture test");
		ImGui::SliderFloat("Size", size, 50.0f, 600.0f);
		ImGui::Image((ImTextureID)(intptr_t(fbo->GetColorAttachmentID(0))), ImVec2(size[0] * (Width / float(Height)), size[0]), ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Text(("Rotation: " + std::to_string(rotation)).c_str());
		if (ImGui::Button("Exit"))
			Exit();
		ImGui::End();
	}
	void OnResize()
	{
		fbo->Resize(Width, Height);
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

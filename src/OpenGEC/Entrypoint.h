#pragma once
#include "Application.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Opengl.h"
#include "Serialization.h"
#include "Compiler.h"

#define NAME "OpenGEC"
#define EDITOR true

static Camera camera;
int WinMain() {

	bool sflag = false;

	float sizeo[2] = { 0,0 };
	float position[2] = { 0,0 };
	float csizeo[2] = { 0,0 };
	float cposition[2] = { 0,0 };

	int index = -1;

	if (!glfwInit()) {
		std::cerr << "Failed to initalize GLFW!" << std::endl;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* m_window = glfwCreateWindow(1000, 1000, NAME, NULL, NULL);

	if (m_window == NULL) {
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_window);

	bool show = true;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Application::Start();

	Script script("res/main.lua");

	script.Run();

	script.Start();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	while (!glfwWindowShouldClose(m_window)) {

		ImGui_ImplOpenGL3_NewFrame();

		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Show GUIS



		float bcol[4];
#ifdef EDITOR
		ImGui::Begin("Background", &show);

		Color color = Binary::Deserialize();
		bcol[0] = color.getRed();
		bcol[1] = color.getGreen();
		bcol[2] = color.getBlue();

		ImGui::ColorPicker3("Color", bcol);
		ClearColor(bcol[0], bcol[1], bcol[2]);
		Binary::Serialize(bcol);
		ImGui::End();

		char* buf = new char(1024);
		const GLubyte* vendor = glGetString(GL_VENDOR);
		const GLubyte* renderer = glGetString(GL_RENDERER);

		ImGui::Begin("Renderering", &show);
		ImGui::Text("Driver:");
		ImGui::Text((const char*)vendor);
		ImGui::Text("\n");
		ImGui::Text("Model:");
		ImGui::Text((const char*)renderer);
		ImGui::Text("\n");
		ImGui::Text("FPS:");
		std::string f = std::to_string(io.Framerate) + " FPS";
		ImGui::Text(f.c_str());
		ImGui::End();

		ImGui::Begin("Scene", &show);
		TexturedQuad* quad = new TexturedQuad(vec2(0,0),vec2(0,0),Texture()," " );
		TexturedQuad* cquad = new TexturedQuad(vec2(0, 0), vec2(0, 0), Texture(), " ");
		const char* name = " ";

		for (auto i = quads.begin(); i != quads.end(); ++i) {
			quad = *i;
			if (ImGui::Button(quad->getName(), ImVec2(100, 20))) {

				csizeo[0] = quad->getSize().x;
				csizeo[1] = quad->getSize().y;

				cposition[0] = quad->getPosition().x;
				cposition[1] = quad->getPosition().y;

				name = quad->getName();

				sflag = true;
			}
		}
		ImGui::End();

		ImGui::Begin("Properties", &show);

		for (int i = 0; i < names.size(); i++) {
			if (names[i] == name) {
				index = i;
				break;
			}
		}
		DeserializeObjects();
		if (index != -1) {
			ImGui::Text(quads[index]->getName());
			ImGui::DragFloat2("Position", cposition);
			ImGui::Text("\n");
			ImGui::DragFloat2("Size", csizeo);

			quads[index]->setPosition(vec2(cposition[0], cposition[1]));
			quads[index]->setSize(vec2(csizeo[0], csizeo[1]));


		}
		ImGui::End();
		SerializeObjects();
#else
		Color color = Binary::Deserialize();
		bcol[0] = color.getRed();
		bcol[1] = color.getGreen();
		bcol[2] = color.getBlue();
		ClearColor(bcol[0], bcol[1], bcol[2]);
		DeserializeObjects();
#endif // EDITOR

		camera.UpdateQuads();



		Application::HandleInput(m_window);
		script.HandleInput(m_window);

		Application::Update();

		script.Update();

		glClear(GL_COLOR_BUFFER_BIT);
		for (auto i = quads.begin(); i != quads.end(); ++i) {
			TexturedQuad* fquad = *i;
			TexturedQuad rquad(fquad->getSize(),fquad->getPosition(),fquad->getTexture(),fquad->getName());
			QuadRenderer::RenderQuad(rquad);
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();
	glfwTerminate();
}
#pragma once
#include "Application.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Opengl.h"
#include "Serialization.h"
#include <sol/sol.hpp>

static Camera camera;
int main() {

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
	GLFWwindow* m_window = glfwCreateWindow(800, 800, "OpenGEC", NULL, NULL);

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

	sol::state lua;
	lua.open_libraries();

	lua.set("KEY_1", KEY_1);
	lua.set("KEY_2", KEY_2);
	lua.set("KEY_3", KEY_3);
	lua.set("KEY_4", KEY_4);
	lua.set("KEY_5", KEY_5);
	lua.set("KEY_6", KEY_6);
	lua.set("KEY_7", KEY_7);
	lua.set("KEY_8", KEY_8);
	lua.set("KEY_9", KEY_9);
	lua.set("KEY_0", KEY_0);

	lua.set("KEY_Q", KEY_Q);
	lua.set("KEY_W", KEY_W);
	lua.set("KEY_E", KEY_E);
	lua.set("KEY_R", KEY_R);
	lua.set("KEY_T", KEY_T);
	lua.set("KEY_Y", KEY_Y);
	lua.set("KEY_U", KEY_U);
	lua.set("KEY_I", KEY_I);
	lua.set("KEY_O", KEY_O);
	lua.set("KEY_P", KEY_P);

	lua.set("KEY_A", KEY_A);
	lua.set("KEY_S", KEY_S);
	lua.set("KEY_D", KEY_D);
	lua.set("KEY_F", KEY_F);
	lua.set("KEY_G", KEY_G);
	lua.set("KEY_H", KEY_H);
	lua.set("KEY_J", KEY_J);
	lua.set("KEY_K", KEY_K);
	lua.set("KEY_L", KEY_L);

	lua.set("KEY_Z", KEY_Z);
	lua.set("KEY_X", KEY_X);
	lua.set("KEY_C", KEY_C);
	lua.set("KEY_V", KEY_V);
	lua.set("KEY_B", KEY_B);
	lua.set("KEY_N", KEY_N);
	lua.set("KEY_M", KEY_M);

	lua.set("KEY_CRTL", KEY_CRTL);
	lua.set("KEY_SHIFT", KEY_SHIFT);
	lua.set("KEY_SPACE", KEY_SPACE);

	for (auto i = quads.begin(); i != quads.end(); ++i) {
		TexturedQuad* quad = *i;
		lua.set(quad->getName(), quad);
	}

	lua.new_usertype<glm::vec2>("vec2", "x", &glm::vec2::x, "y", &glm::vec2::y);
	lua.set_function("setPosition", &TexturedQuad::setPosition);

	lua.script_file("res/main.lua");

	lua["Start"]();

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

		camera.UpdateQuads();



		Application::HandleInput(m_window);
		lua["HandleInput"](Input::CheckKey(m_window));

		Application::Update();

		lua["Update"]();

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
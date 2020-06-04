#pragma once
#include <sol/sol.hpp>
#include "Opengl.h"

class Script{
private:
	sol::state lua;
	const char* path;
public:
	Script(const char* path) {
		this->path = path;
	}
	void Run(){
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
		lua.set_function("getPosition", &TexturedQuad::getPosition);
		lua.set_function("setSize", &TexturedQuad::setSize);
		lua.set_function("getSize", &TexturedQuad::getSize);
		lua.set_function("setName", &TexturedQuad::setName);
		lua.set_function("getName", &TexturedQuad::getName);

		lua.script_file(this->path);
	}
	void Start() {
		lua["Start"]();
	}
	void HandleInput(GLFWwindow* m_window) {
		lua["HandleInput"](Input::CheckKey(m_window));
	}
	void Update() {

		lua["Update"]();
	}
};
#pragma once
#include <string>
#include <ostream>
#include <iostream>

#include <fstream>
#include <nlohmann\json.hpp>
#include "Opengl.h"
using namespace std;

using namespace std;
using namespace nlohmann;

class Binary {
public:
	static json& Serialize(float col[3]) {
		json j;
		j["Red"] = col[0];
		j["Green"] = col[1];
		j["Blue"] = col[2];

		ofstream of("C:/Appdata/OpenGEC/Editor/b.bin");
		of << j;
		return j;
	}
	static json& SerializeQuad(TexturedQuad* quad) {
		json j;

		string name = quad->getName();
		float sizex = quad->getSize().x;
		float sizey = quad->getSize().y;

		float posx = quad->getPosition().x;
		float posy = quad->getPosition().y;
		string path = quad->getTexture().getPath();

		string base = "C:/Appdata/OpenGEC/Editor/" + name + ".bin";

		ofstream of(base);

		j["Texture"] = path;

		j["X"] = posx;
		j["Y"] = posy;

		j["SizeX"] = sizex;
		j["SizeY"] = sizey;

		j["Name"] = name;

		of << j;
		return j;
	}
	static TexturedQuad* DeserializeQuad(TexturedQuad* quad) {
		string name = quad->getName();
		string base = "C:/Appdata/OpenGEC/Editor/" + name + ".bin";
		ifstream is(base);
		json j = j.parse(is);

		auto sizex = j["SizeX"].get<float>();
		auto sizey = j["SizeY"].get<float>();

		auto posx = j["X"].get<float>();
		auto posy = j["Y"].get<float>();

		auto path = j["Texture"].get<string>();

		auto names = j["Name"].get<string>();

		return new TexturedQuad(vec2(sizex , sizey), vec2(posx, posy), Texture(path.c_str()), names.c_str());

	}
	static Color& Deserialize() {

		json j;
		ifstream is("C:/Appdata/OpenGEC/Editor/b.bin");

		is >> j;

		Color color = Color(
			j["Red"].get<float>(),
			j["Green"].get<float>(),
			j["Blue"].get<float>()
		);
		return color;
	}
};
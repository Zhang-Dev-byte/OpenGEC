#pragma once
#include <irrKlang/irrKlang.h>
using namespace irrklang;

class Sound {
private:
	ISoundEngine* engine;
	const char* path;
	bool looped;
public:
	Sound(const char* path,bool looped = false) {
		this->engine = createIrrKlangDevice();
		this->path = path;
		this->looped = looped;
	}
	void Play() {
		engine->play2D(path, this->looped);
	}
};
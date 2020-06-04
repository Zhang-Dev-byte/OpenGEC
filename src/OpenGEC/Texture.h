#pragma once
#include <glad/glad.h>
#include "stb_image.h"
#include <iostream>

class Texture
{
private:
	unsigned char* data;
	unsigned int id;
	int width;
	int height;
	int nrChannels;
    const char* path;

public:
    const char* getPath() {
        return this->path;
    }
	Texture() {

	}
    Texture(const char* path, bool hasAlpha = false) {
        this->path = path;
        glGenTextures(1, &this->id);
        glBindTexture(GL_TEXTURE_2D, this->id);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        this->data = stbi_load(path, &this->width, &this->height, &this->nrChannels, 0);
        if (this->data)
        {
            if (hasAlpha) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->data);
            }
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(this->data);
	}
};
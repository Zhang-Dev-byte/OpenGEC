#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include <glm/glm.hpp>
#include <Texture.h>
#include <vector>

using namespace glm;
using namespace std;

static void InitOpenGL() {
	if (!glfwInit()) {
		std::cerr << "Failed to initalize GLFW!" << std::endl;
	}
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#define KEY_1 GLFW_KEY_1
#define KEY_2 GLFW_KEY_2
#define KEY_3 GLFW_KEY_3
#define KEY_4 GLFW_KEY_4
#define KEY_5 GLFW_KEY_5
#define KEY_6 GLFW_KEY_6
#define KEY_7 GLFW_KEY_7
#define KEY_8 GLFW_KEY_8
#define KEY_9 GLFW_KEY_9
#define KEY_0 GLFW_KEY_0

#define KEY_Q GLFW_KEY_Q
#define KEY_W GLFW_KEY_W
#define KEY_E GLFW_KEY_E
#define KEY_R GLFW_KEY_R
#define KEY_T GLFW_KEY_T
#define KEY_Y GLFW_KEY_Y
#define KEY_U GLFW_KEY_U
#define KEY_I GLFW_KEY_I
#define KEY_O GLFW_KEY_O
#define KEY_P GLFW_KEY_P

#define KEY_A GLFW_KEY_A
#define KEY_S GLFW_KEY_S
#define KEY_D GLFW_KEY_D
#define KEY_F GLFW_KEY_F
#define KEY_G GLFW_KEY_G
#define KEY_H GLFW_KEY_H
#define KEY_J GLFW_KEY_J
#define KEY_K GLFW_KEY_K
#define KEY_L GLFW_KEY_L

#define KEY_Z GLFW_KEY_Z
#define KEY_X GLFW_KEY_X
#define KEY_C GLFW_KEY_C
#define KEY_V GLFW_KEY_V
#define KEY_B GLFW_KEY_B
#define KEY_N GLFW_KEY_N
#define KEY_M GLFW_KEY_M

#define KEY_CRTL GLFW_KEY_LEFT_CONTROL
#define KEY_SPACE GLFW_KEY_SPACE
#define KEY_SHIFT GLFW_KEY_LEFT_SHIFT
}
static void ClearColor(float Red, float Green, float Blue) {
	glClearColor(Red, Green, Blue, 1.0f);
 }
class Color {
public:
    Color() {

    }
    Color(float red, float green, float blue){
        this->r = red;
        this->g = green;
        this->b = blue;
    }
    float getRed() {
        return this->r;
    }
    float getGreen() {
        return this->g;
    }
    float getBlue() {
        return this->b;
    }
private:
    float r;
    float g;
    float b;
};
class Quad{
public:
    Quad() {

    }
    Quad(vec2 size, vec2 position, Color color, const char* name){
        this->color = color;
        this->size = size;
        this->pos = position;
        this->name = name;
    }
    vec2 getPosition() {
        return this->pos;
    }
    vec2 getSize() {
        return this->size;
    }
    Color getColor() {
        return this->color;
    }
    void setPosition(vec2 value) {
        this->pos = value;
    }
    void setSize(vec2 value) {
        this->size = value;
    }
    void setColor(Color value) {
        this->color = value;
    }
private:
    vec2 pos;
    vec2 size;
    Color color;
    const char* name;
};
class TexturedQuad{
public:
    TexturedQuad() {

    }
    TexturedQuad(vec2 size, vec2 position, Texture texture, const char* name) {
        this->texture = texture;
        this->size = size;
        this->pos = position;
        this->name = name;
    }
    vec2 getPosition() {
        return this->pos;
    }
    vec2 getSize() {
        return this->size;
    }
    Texture getTexture() {
        return this->texture;
    }
    void setPosition(vec2 value) {
        this->pos = value;
    }
    void setSize(vec2 value) {
        this->size = value;
    }
    void setTexture(Texture value) {
        this->texture = value;
    }
    const char* getName() {
        return this->name;
    }
    void setName(const char* value) {
        this->name = value;
    }
private:
    vec2 pos;
    vec2 size;
    Texture texture;
    const char* name;
};
#include "Serialization.h"

static vector<const char*> names;
static vector<TexturedQuad*> quads;

static void AddObject(TexturedQuad* quad) {

    quads.push_back(quad);
    names.push_back(quad->getName());
}
static void SerializeObjects() {
    for (auto i = quads.begin(); i != quads.end(); ++i) {
        TexturedQuad* quad = *i;
        Binary::SerializeQuad(quad);
    }
}
static void DeserializeObjects() {
    for (auto i = quads.begin(); i != quads.end(); ++i) {
        TexturedQuad* quad = *i;
        TexturedQuad& quadr = *quad;

        TexturedQuad* quadq = &quadr;
        quadq = Binary::DeserializeQuad(&quadr);

        quadr.setPosition(quadq->getPosition());
        quadr.setSize(quadq->getSize());
    }
}

class Camera {
public:
    vec2 getVelocity() {
        return this->velocity;
    }
    void setVelocity(vec2 value) {
        this->velocity = value;
    }
    void UpdateQuads() {
        for (auto i = quads.begin(); i != quads.end(); ++i) {
            TexturedQuad* quad = *i;
            quad->setPosition(quad->getPosition() - this->velocity);
        }
    }
private:
    vec2 velocity;
};

class QuadRenderer {
public:
    //TODO: Move in seperate .h and .cpp files
    static void RenderQuad(vec2 pos,vec2 size,Color color) {
        pos /= 1000;
        size /= 1000;
        float vertices[] = {
         pos.x + size.x,  pos.y + size.y, 0.0f,  // top right
         pos.x + size.x, pos.y - size.y, 0.0f,  // bottom right
         pos.x - size.x, pos.y - size.y, 0.0f,  // bottom left
         pos.x - size.x,  pos.y + size.y, 0.0f   // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
        Shader shader("res/quad.vs", "res/quad.fs");
        shader.use();
        shader.setFloat("r", color.getRed());
        shader.setFloat("g", color.getGreen());
        shader.setFloat("b", color.getBlue());
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    static void RenderQuad(Quad quad) {
        vec2 pos = quad.getPosition();
        pos /= 800;
        vec2 size = quad.getSize();
        size /= 800;
        Color color = quad.getColor();
        float vertices[] = {
         pos.x + size.x,  pos.y + size.y, 0.0f,  // top right
         pos.x + size.x, pos.y - size.y, 0.0f,  // bottom right
         pos.x - size.x, pos.y - size.y, 0.0f,  // bottom left
         pos.x - size.x,  pos.y + size.y, 0.0f   // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
        Shader shader("res/quad.vs", "res/quad.fs");
        shader.use();
        shader.setFloat("r", color.getRed());
        shader.setFloat("g", color.getGreen());
        shader.setFloat("b", color.getBlue());
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    static void RenderQuad(TexturedQuad quad) {
        vec2 pos = quad.getPosition();
        pos /= 1000;
        vec2 size = quad.getSize();
        size /= 1000;
        
        float vertices[] = {
         pos.x + size.x,  pos.y + size.y, 0.0f,  1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
         pos.x + size.x, pos.y - size.y, 0.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
         pos.x - size.x, pos.y - size.y, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
         pos.x - size.x,  pos.y + size.y, 0.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
        };
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
        Shader shader("res/textured.vs", "res/textured.fs");
        shader.setInt("ourTexture", 0);
        shader.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};

class Input {
public:
    static bool GetKey(GLFWwindow* window, int key) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            return true;
        }
        else {
            return false;
        }
    }
    static int CheckKey(GLFWwindow* window) {
        if (glfwGetKey(window, KEY_1) == GLFW_PRESS) {
            return KEY_1;
        }
        if (glfwGetKey(window, KEY_2) == GLFW_PRESS) {
            return KEY_2;
        }
        if (glfwGetKey(window, KEY_3) == GLFW_PRESS) {
            return KEY_3;
        }
        if (glfwGetKey(window, KEY_4) == GLFW_PRESS) {
            return KEY_4;
        }
        if (glfwGetKey(window, KEY_5) == GLFW_PRESS) {
            return KEY_5;
        }
        if (glfwGetKey(window, KEY_6) == GLFW_PRESS) {
            return KEY_6;
        }
        if (glfwGetKey(window, KEY_7) == GLFW_PRESS) {
            return KEY_7;
        }
        if (glfwGetKey(window, KEY_8) == GLFW_PRESS) {
            return KEY_8;
        }
        if (glfwGetKey(window, KEY_9) == GLFW_PRESS) {
            return KEY_9;
        }
        if (glfwGetKey(window, KEY_0) == GLFW_PRESS) {
            return KEY_0;
        }
        if (glfwGetKey(window, KEY_Q) == GLFW_PRESS) {
            return KEY_Q;
        }
        if (glfwGetKey(window, KEY_W) == GLFW_PRESS) {
            return KEY_W;
        }
        if (glfwGetKey(window, KEY_E) == GLFW_PRESS) {
            return KEY_E;
        }
        if (glfwGetKey(window, KEY_R) == GLFW_PRESS) {
            return KEY_R;
        }
        if (glfwGetKey(window, KEY_T) == GLFW_PRESS) {
            return KEY_T;
        }
        if (glfwGetKey(window, KEY_Y) == GLFW_PRESS) {
            return KEY_Y;
        }
        if (glfwGetKey(window, KEY_U) == GLFW_PRESS) {
            return KEY_U;
        }
        if (glfwGetKey(window, KEY_I) == GLFW_PRESS) {
            return KEY_I;
        }
        if (glfwGetKey(window, KEY_O) == GLFW_PRESS) {
            return KEY_O;
        }
        if (glfwGetKey(window, KEY_P) == GLFW_PRESS) {
            return KEY_P;
        }
        if (glfwGetKey(window, KEY_A) == GLFW_PRESS) {
            return KEY_A;
        }
        if (glfwGetKey(window, KEY_S) == GLFW_PRESS) {
            return KEY_S;
        }
        if (glfwGetKey(window, KEY_D) == GLFW_PRESS) {
            return KEY_D;
        }
        if (glfwGetKey(window, KEY_F) == GLFW_PRESS) {
            return KEY_F;
        }
        if (glfwGetKey(window, KEY_G) == GLFW_PRESS) {
            return KEY_G;
        }
        if (glfwGetKey(window, KEY_H) == GLFW_PRESS) {
            return KEY_H;
        }
        if (glfwGetKey(window, KEY_J) == GLFW_PRESS) {
            return KEY_J;
        }
        if (glfwGetKey(window, KEY_K) == GLFW_PRESS) {
            return KEY_K;
        }
        if (glfwGetKey(window, KEY_L) == GLFW_PRESS) {
            return KEY_L;
        }
        if (glfwGetKey(window, KEY_Z) == GLFW_PRESS) {
            return KEY_Z;
        }
        if (glfwGetKey(window, KEY_X) == GLFW_PRESS) {
            return KEY_X;
        }
        if (glfwGetKey(window, KEY_C) == GLFW_PRESS) {
            return KEY_C;
        }
        if (glfwGetKey(window, KEY_V) == GLFW_PRESS) {
            return KEY_V;
        }
        if (glfwGetKey(window, KEY_B) == GLFW_PRESS) {
            return KEY_B;
        }
        if (glfwGetKey(window, KEY_N) == GLFW_PRESS) {
            return KEY_N;
        }
        if (glfwGetKey(window, KEY_M) == GLFW_PRESS) {
            return KEY_M;
        }
        if (glfwGetKey(window, KEY_CRTL) == GLFW_PRESS) {
            return KEY_CRTL;
        }
        if (glfwGetKey(window, KEY_SPACE) == GLFW_PRESS) {
            return KEY_SPACE;
        }
        if (glfwGetKey(window, KEY_SHIFT) == GLFW_PRESS) {
            return KEY_SHIFT;
        }
        return NULL;
    }
};
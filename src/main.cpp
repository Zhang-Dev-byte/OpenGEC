#include "OpenGEC.h"

TexturedQuad quad;
TexturedQuad quad1;
TexturedQuad quad2;


float col[3];
float sizeo[2];
float position[2];

void Application::HandleInput(GLFWwindow* window)
{
    InitOpenGL();
    if (Input::GetKey(window, KEY_A)) {
        printf("Hello");
    }
}
void Application::Update()
{
}
void Application::Start()
{
    InitOpenGL();
    quad = TexturedQuad(vec2(1000.0f, 100.0f), vec2(0.0f, 0.0f), Texture("res/h.jpg"),"Quad");
    quad1 = TexturedQuad(vec2(100.0f, 100.0f), vec2(0.0f, 0.0f), Texture("res/h.jpg"), "Quadg");
    quad2 = TexturedQuad(vec2(200.0f, 100.0f), vec2(0.0f, 0.0f), Texture("res/h.jpg"), "Quadgg");

    AddObject(&quad);
    AddObject(&quad1);
    AddObject(&quad2);

}
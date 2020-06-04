cmake_minimum_required(VERSION 3.10)

project(OpenGEC)

add_executable(OpenGEC src/main.cpp src/OpenGEC.h src/OpenGEC/glad/glad.c src/OpenGEC/glad/glad.h src/OpenGEC/KHR/khrplatform.h src/OpenGEC/sol/sol.hpp src/OpenGEC/sol/forward.hpp src/OpenGEC/Application.h src/OpenGEC/Audio.h src/OpenGEC/Entrypoint.h src/OpenGEC/imconfig.h src/OpenGEC/imgui.cpp src/OpenGEC/imgui.h src/OpenGEC/imgui_demo.cpp src/OpenGEC/imgui_draw.cpp src/OpenGEC/imgui_impl_glfw.cpp src/OpenGEC/imgui_impl_glfw.h src/OpenGEC/imgui_impl_opengl3.cpp src/OpenGEC/imgui_impl_opengl3.h src/OpenGEC/imgui_internal.h src/OpenGEC/imgui_widgets.cpp src/OpenGEC/imstb_rectpack.h src/OpenGEC/imstb_textedit.h src/OpenGEC/imstb_truetype.h src/OpenGEC/Opengl.h src/OpenGEC/Serialization.h src/OpenGEC/Shader.h src/OpenGEC/stb_image.h src/OpenGEC/Texture.h)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
add_compile_definitions(STB_IMAGE_IMPLEMENTATION)
target_link_directories(  OpenGEC PUBLIC "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/lib/")
target_link_libraries(OpenGEC glfw3.lib)
target_link_libraries(OpenGEC irrklang.lib)
target_link_libraries(OpenGEC lua53.lib)
target_include_directories(OpenGEC PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/src/OpenGEC"
                          )
						  
target_compile_features(OpenGEC PRIVATE cxx_std_17)
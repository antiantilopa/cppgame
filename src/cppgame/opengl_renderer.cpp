#include "include/opengl_renderer.h"

namespace CppGame {

Window OpenGLRenderer::init(int width, int height, std::string title) {
    CoreGeometry::init();
    window = Window(width, height, title.c_str());

    Draw3D::init(window);
    Draw2D::init(window);

    glfwSwapInterval(1);
    return window;
}

void OpenGLRenderer::predraw() {
    window.fill(64, 0, 64, 255);
}

void OpenGLRenderer::postdraw() {
    if (glGetError() == GL_INVALID_OPERATION){
        std::cout << "this is written once btw flag 1\n";
        throw std::runtime_error("FUCK!!!!");
    }

    window.flip();
    if (glGetError() == GL_INVALID_OPERATION){
        std::cout << "FVCK\n";
    }
}
}

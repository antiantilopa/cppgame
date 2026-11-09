#include "include/opengl_renderer.h"

namespace CppGame {

OpenGLRenderer::OpenGLRenderer(int width, int height, std::string title) // class being virtual fuckery
    : window(OpenGLRenderer::init(width, height, title)),
      screen(OpenGLRenderer::init_screen()) {}


Window& OpenGLRenderer::init(int width, int height, std::string title) {
    CoreGeometry::init();
    Window& window = *new Window(width, height, title.c_str());
    window.setAsMain();
    Draw3D::init();
    Draw2D::init();

    glfwSwapInterval(1);
    return window;
}

Texture& OpenGLRenderer::init_screen(){
    Texture& screen = *new Texture(Window::window_ptr->width, Window::window_ptr->height);
    FBO* fbo_ptr = new FBO();
    fbo_ptr->bindTexture(screen);
    CoreGeometry::fbo_ptr = fbo_ptr;
    return screen;
}

void OpenGLRenderer::preupdate() {

}

void OpenGLRenderer::postupdate() {

}

void OpenGLRenderer::predraw() {
    window.fill(0, 0, 0, 0);
    CoreGeometry::fbo_ptr->setup();
}

void OpenGLRenderer::postdraw() {
    if (glGetError() == GL_INVALID_OPERATION){
        std::cout << "open gl error\n";
        throw std::runtime_error("FUCK!!!!");
    }

    CoreGeometry::fbo_ptr->unbind();
    Draw2D::texture(0, 0, screen, nullptr, 1, nullptr);



    window.flip();
    if (glGetError() == GL_INVALID_OPERATION){
        std::cout << "window flip failed\n";
    }
}
}

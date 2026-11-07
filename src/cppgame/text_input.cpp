#include "include/text_input.h"

namespace CppGame{

UIntToVoidFunc TextInput::onCharTyped = 0;

void TextInput::init(){
    Window::checkWindow();
    glfwSetCharCallback(Window::window_ptr->window, CharCallback);
}

void TextInput::CharCallback(GLFWwindow* window, unsigned int key){
    if (onCharTyped != nullptr){
        onCharTyped(key);
    }
}

void TextInput::setOnCharCallback(UIntToVoidFunc onCharCallback){
    TextInput::onCharTyped = onCharCallback;
}


}
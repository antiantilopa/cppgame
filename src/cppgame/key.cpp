#include "include/key.h"

namespace CppGame {

std::map<int, bool> Key::isPressing{};
std::map<int, VoidFunc> Key::onPressing{};
std::map<int, VoidFunc> Key::onClick{};
std::map<int, VoidFunc> Key::onHold{};
std::map<int, VoidFunc> Key::onRelease{};
IntToVoidFunc Key::onClickDefault = 0;
IntToVoidFunc Key::onHoldDefault = 0;
IntToVoidFunc Key::onReleaseDefault = 0;
IntIntToVoidFunc Key::onUndefinedKeyAction = 0;

void Key::init(){
    Window::checkWindow();
    glfwSetKeyCallback(Window::window_ptr->window, keyCallback);
}

void Key::update(){
    for (const auto& [key, value] : isPressing)
        if (value && Key::onPressing.count(key) && Key::onPressing[key] != nullptr)
            Key::onPressing[key]();
}

void Key::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_PRESS){ // click
        if (onClick.count(key) && onClick[key] != nullptr)
            onClick[key]();
        if (onClickDefault != nullptr)
            onClickDefault(key);
        if (isPressing.count(key))
            Key::isPressing[key] = true;
    }
    if (action == GLFW_REPEAT){ // hold
        if (onHold.count(key) && onHold[key] != nullptr)
            onHold[key]();
        if (onHoldDefault != nullptr)
            onHoldDefault(key);
    }
    if (action == GLFW_RELEASE){ // release
        if (onRelease.count(key) && onRelease[key] != nullptr)
            onRelease[key]();
        if (onReleaseDefault != nullptr)
            onReleaseDefault(key);
        if (isPressing.count(key))
            Key::isPressing[key] = true;
    }
    if (onUndefinedKeyAction != nullptr)
        onUndefinedKeyAction(key, action);
}
void Key::setOnPressing(int key, VoidFunc onClick){ Key::onPressing[key] = onClick; Key::isPressing[key] = isPressed(key);}
void Key::setOnClick(int key, VoidFunc onClick){ Key::onClick[key] = onClick; }
void Key::setOnHold(int key, VoidFunc onHold){ Key::onHold[key] = onHold; }
void Key::setOnRelease(int key, VoidFunc onRelease){ Key::onRelease[key] = onRelease; }
void Key::setOnClick(IntToVoidFunc onClick){ Key::onClickDefault = onClick; }
void Key::setOnHold(IntToVoidFunc onHold){ Key::onHoldDefault = onHold; }
void Key::setOnRelease(IntToVoidFunc onRelease){ Key::onReleaseDefault = onRelease; }
void Key::setOnUndefinedKeyAction(IntIntToVoidFunc onUndefinedKeyAction){ Key::onUndefinedKeyAction = onUndefinedKeyAction; }

bool Key::isPressed(int key){
    return glfwGetKey(Window::window_ptr->window, key) == GLFW_PRESS;
}
bool Key::anyPressed(int* keys, int lenght){
    for (int* i = keys; i < keys + lenght; i++)
        if (isPressed(*i))
            return true;
    return false;
}
bool Key::allPressed(int* keys, int lenght){
    for (int* i = keys; i < keys + lenght; i++)
        if (!isPressed(*i))
            return false;
    return true;
}

}
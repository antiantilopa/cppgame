#include "include/mouse.h"

namespace CppGame {

    
IntIntToVoidFunc Mouse::onUndefinedButton = 0;
VoidFunc Mouse::onClick[3] = {0, 0, 0};
VoidFunc Mouse::onRelease[3] = {0, 0, 0};
ULLToVoidFunc Mouse::onDoubleClick[3] = {0, 0, 0};
ULLToVoidFunc Mouse::onHold[3] = {0, 0, 0};
DoubleDoubleToVoidFunc Mouse::onScroll = 0;

bool Mouse::button_states[3] = {false, false, false};
unsigned long long Mouse::ticks_timer[3] = {0, 0, 0};
unsigned long long Mouse::minimal_hold_ticks = ULLONG_MAX;
unsigned long long Mouse::maximal_ticks_between_double_click = 0;

const int glfw_button_order_to_cppgame_order[3] = {0, 2, 1}; 

void Mouse::init(){
    Window::checkWindow();
    glfwSetMouseButtonCallback(Window::window_ptr->window, mouseButtonCallback);
    glfwSetScrollCallback(Window::window_ptr->window, scrollCallback);
}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
    if (button >= 3 || button < 0){
        onUndefinedButton(button, action);
    }
    int index = glfw_button_order_to_cppgame_order[button];
    if (action == GLFW_RELEASE){
        if (onRelease[index] != nullptr){
            onRelease[index]();}}
    else if (Mouse::ticks_timer[index] <= Mouse::maximal_ticks_between_double_click){
        if (onDoubleClick[index] != nullptr){
            onDoubleClick[index](Mouse::ticks_timer[index]);}}
    else{
        if (onClick[index] != nullptr){
            onClick[index]();}}

    Mouse::button_states[index] = (action == GLFW_PRESS);
    Mouse::ticks_timer[index] = 0;
}

void Mouse::scrollCallback(GLFWwindow* window, double x_offset, double y_offset){
    onScroll(x_offset, y_offset);
}

void Mouse::update(){
    for (char i = 0; i < 3; i++){
        if (
            (minimal_hold_ticks != ULLONG_MAX) &&
            (Mouse::button_states[i] == PRESSED) && 
            (Mouse::ticks_timer[i] >= minimal_hold_ticks) &&
            (onHold[i] != nullptr)
        )
            onHold[i](Mouse::ticks_timer[i]);
        Mouse::ticks_timer[i]++;
    }
}

bool Mouse::isPressed(int key){ return Mouse::button_states[key] == 1; }
bool Mouse::isReleased(int key){ return Mouse::button_states[key] == 0; }

// sets minimal ticks needed to hold a button to call onHold
void Mouse::setMinimalHoldTicks(unsigned long long minimal_hold_ticks){
    Mouse::minimal_hold_ticks = minimal_hold_ticks;
}

// sets maximal ticks needed to not press a button to call onDouble click
void Mouse::setMaximalTicksBetweenDoubleClick(unsigned long long maximal_ticks_between_double_click){
    Mouse::maximal_ticks_between_double_click = maximal_ticks_between_double_click;
}

void Mouse::setOnLeftClick(VoidFunc onLeftClick){ Mouse::onClick[0] = onLeftClick; }
void Mouse::setOnMiddleClick(VoidFunc onMiddleClick){ Mouse::onClick[1] = onMiddleClick; }
void Mouse::setOnRightClick(VoidFunc onRightClick){ Mouse::onClick[2] = onRightClick; }
void Mouse::setOnLeftRelease(VoidFunc onLeftRelease){ Mouse::onRelease[0] = onLeftRelease; }
void Mouse::setOnMiddleRelease(VoidFunc onMiddleRelease){ Mouse::onRelease[1] = onMiddleRelease; }
void Mouse::setOnRightRelease(VoidFunc onRightRelease){ Mouse::onRelease[2] = onRightRelease; }
void Mouse::setOnLeftDoubleClick(ULLToVoidFunc onLeftDoubleClick){ Mouse::onDoubleClick[0] = onLeftDoubleClick; }
void Mouse::setOnMiddleDoubleClick(ULLToVoidFunc onMiddleDoubleClick){ Mouse::onDoubleClick[1] = onMiddleDoubleClick; }
void Mouse::setOnRightDoubleClick(ULLToVoidFunc onRightDoubleClick){ Mouse::onDoubleClick[2] = onRightDoubleClick; }
void Mouse::setOnLeftHold(ULLToVoidFunc onLeftHold){ Mouse::onHold[0] = onLeftHold; }
void Mouse::setOnMiddleHold(ULLToVoidFunc onMiddleHold){ Mouse::onHold[1] = onMiddleHold; }
void Mouse::setOnRightHold(ULLToVoidFunc onRightHold){ Mouse::onHold[2] = onRightHold; }
void Mouse::setOnScroll(DoubleDoubleToVoidFunc onScroll){ Mouse::onScroll = onScroll; }
void Mouse::setOnUndefinedButton(IntIntToVoidFunc OnUndefinedButton){ Mouse::onUndefinedButton = onUndefinedButton; }

void Mouse::hid(){
    glfwSetInputMode(Window::window_ptr->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Mouse::capture(){
    glfwSetInputMode(Window::window_ptr->window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
}

void Mouse::disable(){
    glfwSetInputMode(Window::window_ptr->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Mouse::enable(){
    glfwSetInputMode(Window::window_ptr->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

template<typename T>
void Mouse::getPosition(T* x, T* y) {
    double x_pos, y_pos;
    glfwGetCursorPos(Window::window_ptr->window, &x_pos, &y_pos);
    
    *x = (T) Mode::x_sign * (x_pos - Mode::ox * Window::window_ptr->width / 2);
    *y = -((T) Mode::y_sign * (y_pos - Mode::oy * Window::window_ptr->height / 2));
}

template void Mouse::getPosition<int>(int* x, int* y);
template void Mouse::getPosition<float>(float* x, float* y);
template void Mouse::getPosition<double>(double* x, double* y);

template<typename T>
T* Mouse::getPosition(){
    double x_pos, y_pos;
    glfwGetCursorPos(Window::window_ptr->window, &x_pos, &y_pos);
    T* position = new T[2];
    position[0] = (T) Mode::x_sign * (x_pos - Mode::ox * Window::window_ptr->width / 2);
    position[1] = -((T) Mode::y_sign * (y_pos - Mode::oy * Window::window_ptr->height / 2));
    return position;
}

template int* Mouse::getPosition<int>();
template float* Mouse::getPosition<float>();
template double* Mouse::getPosition<double>();

template<typename T>
void Mouse::getPosition(T* position){
    double x_pos, y_pos;
    glfwGetCursorPos(Window::window_ptr->window, &x_pos, &y_pos);
    position[0] = (T) Mode::x_sign * (x_pos - Mode::ox * Window::window_ptr->width / 2);
    position[1] = -((T) Mode::y_sign * (y_pos - Mode::oy * Window::window_ptr->height / 2));
}

template void Mouse::getPosition<int>(int* position);
template void Mouse::getPosition<float>(float* position);
template void Mouse::getPosition<double>(double* position);

template<typename T>
void Mouse::setPosition(T x, T y){
    double x_pos = (double)(x * Mode::x_sign + Mode::ox * Window::window_ptr->width / 2);
    double y_pos = (double)(-y * Mode::y_sign + Mode::oy * Window::window_ptr->height / 2);
    glfwSetCursorPos(Window::window_ptr->window, x_pos, y_pos);
}

template void Mouse::setPosition<int>(int x, int y);
template void Mouse::setPosition<float>(float x, float y);
template void Mouse::setPosition<double>(double x, double y);

template<typename T>
void Mouse::setPosition(T* position){
    double x_pos = (double)(position[0] * Mode::x_sign + Mode::ox * Window::window_ptr->width / 2);
    double y_pos = (double)(-position[1] * Mode::y_sign + Mode::oy * Window::window_ptr->height / 2);
    glfwSetCursorPos(Window::window_ptr->window, x_pos, y_pos);
}

template void Mouse::setPosition<int>(int* position);
template void Mouse::setPosition<float>(float* position);
template void Mouse::setPosition<double>(double* position);
}
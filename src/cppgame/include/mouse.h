#pragma once
#include "cppgame.h"

namespace CppGame{

typedef void(*voidFunc)();
typedef void(*intintToVoidFunc)(int, int);
typedef void(*doubledoubleToVoidFunc)(double, double);
typedef void(*ullToVoidFunc)(unsigned long long);

class Mouse{
protected:
    static intintToVoidFunc onUndefinedButton; // arguments - button id, action
    static voidFunc onClick[3];
    static voidFunc onRelease[3];
    static ullToVoidFunc onDoubleClick[3];    // argument - ticks between clicks
    static ullToVoidFunc onHold[3];           // argument - ticks of holding
    static doubledoubleToVoidFunc onScroll;   // arguments - horizontal and vertical scroll offset. horizontal works only from touchpad scroll
    static bool button_states[3];
    static unsigned long long ticks_timer[3];
    static unsigned long long minimal_hold_ticks;
    static unsigned long long maximal_ticks_between_double_click;
    static void mouseButtonCallback(GLFWwindow* window, int key, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double x_offset, double y_offset);
public:
    static void init(); // should be called after a window was created
    static void update(); // have to be called every tick

    // sets minimal ticks needed to hold a button to call onHold
    static void setMinimalHoldTicks(unsigned long long minimal_hold_ticks); 

    // sets maximal ticks needed to not press a button to call onDouble click
    static void setMaximalTicksBetweenDoubleClick(unsigned long long maximal_ticks_between_double_click); 

    static void setOnLeftClick(voidFunc onLeftClick);
    static void setOnMiddleClick(voidFunc onMiddleClick);
    static void setOnRightClick(voidFunc onRightClick);
    static void setOnLeftRelease(voidFunc onLeftRelease);
    static void setOnMiddleRelease(voidFunc onMiddleRelease);
    static void setOnRightRelease(voidFunc onRightRelease);
    static void setOnLeftDoubleClick(ullToVoidFunc onLeftDoubleClick);
    static void setOnMiddleDoubleClick(ullToVoidFunc onMiddleDoubleClick);
    static void setOnRightDoubleClick(ullToVoidFunc onRightDoubleClick);
    static void setOnLeftHold(ullToVoidFunc onLeftHold);
    static void setOnMiddleHold(ullToVoidFunc onMiddleHold);
    static void setOnRightHold(ullToVoidFunc onRightHold);
    static void setOnScroll(doubledoubleToVoidFunc onScroll);
    static void setOnUndefinedButton(intintToVoidFunc OnUndefinedButton);

    static void hid(); // makes cursor hidden
    static void disable(); // makes cursor hidden and disables movement
    static void capture(); // makes cursor visible but does not let cursor leave the window
    static void enable(); // makes cursor normal

    static bool isPressed(int key);
    static bool isReleased(int key);

    template<typename T>
    static void getPosition(T* x, T* y);
    template<typename T>
    static T* getPosition(); // creates new obhect on heap! needs deleting
    template<typename T>
    static void getPosition(T* position); // position has to be array of at least size 2.

    template<typename T>
    static void setPosition(T x, T y);
    template<typename T>
    static void setPosition(T* position); // position has to be array of at least size 2.

    const static inline int LEFT = 0;
    const static inline int MIDDLE = 1;
    const static inline int RIGHT = 2;

    const static inline int RELEASED = 0;
    const static inline int PRESSED = 1;
};

}
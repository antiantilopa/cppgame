#pragma once
#include "cppgame.h"

namespace CppGame{

typedef void(*VoidFunc)();
typedef void(*IntIntToVoidFunc)(int, int);
typedef void(*DoubleDoubleToVoidFunc)(double, double);
typedef void(*ULLToVoidFunc)(unsigned long long);

class Mouse{
protected:
    static IntIntToVoidFunc onUndefinedButton; // arguments - button id, action
    static VoidFunc onClick[3];
    static VoidFunc onRelease[3];
    static ULLToVoidFunc onDoubleClick[3];    // argument - ticks between clicks
    static ULLToVoidFunc onHold[3];           // argument - ticks of holding
    static DoubleDoubleToVoidFunc onScroll;   // arguments - horizontal and vertical scroll offset. horizontal works only from touchpad scroll
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

    static void setOnLeftClick(VoidFunc onLeftClick);
    static void setOnMiddleClick(VoidFunc onMiddleClick);
    static void setOnRightClick(VoidFunc onRightClick);
    static void setOnLeftRelease(VoidFunc onLeftRelease);
    static void setOnMiddleRelease(VoidFunc onMiddleRelease);
    static void setOnRightRelease(VoidFunc onRightRelease);
    static void setOnLeftDoubleClick(ULLToVoidFunc onLeftDoubleClick);
    static void setOnMiddleDoubleClick(ULLToVoidFunc onMiddleDoubleClick);
    static void setOnRightDoubleClick(ULLToVoidFunc onRightDoubleClick);
    static void setOnLeftHold(ULLToVoidFunc onLeftHold);
    static void setOnMiddleHold(ULLToVoidFunc onMiddleHold);
    static void setOnRightHold(ULLToVoidFunc onRightHold);
    static void setOnScroll(DoubleDoubleToVoidFunc onScroll);
    static void setOnUndefinedButton(IntIntToVoidFunc OnUndefinedButton);

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
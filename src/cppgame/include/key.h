#pragma once

#include "cppgame.h"
#include <map>

namespace CppGame {

typedef void(*VoidFunc)();
typedef void(*IntToVoidFunc)(int);
typedef void(*IntIntToVoidFunc)(int, int);

class Key{
    static std::map<int, bool> isPressing; // only for those keys that are to be checked if they are pressed. only for those from onPressed
    static std::map<int, VoidFunc> onPressing; // 'pressing' will be registered the same moment a key is pressed and held
    static std::map<int, VoidFunc> onClick; // 'click' registeres only once the key is pressed
    static std::map<int, VoidFunc> onHold; // 'hold' will be registered a little after the 'pressing'
    static std::map<int, VoidFunc> onRelease; // 'click' registeres only once the key is released
    static IntToVoidFunc onClickDefault;
    static IntToVoidFunc onHoldDefault;
    static IntToVoidFunc onReleaseDefault;
    static IntIntToVoidFunc onUndefinedKeyAction; //  this will process every key action pair.
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
    static void init(); // should be called after a window was created
    static void update(); // have to be called every tick

    static void setOnUndefinedKeyAction(IntIntToVoidFunc onUndefinedKeyAction);
    static void setOnPressing(int key, VoidFunc onClick);
    static void setOnClick(int key, VoidFunc onClick);
    static void setOnHold(int key, VoidFunc onHold);
    static void setOnRelease(int key, VoidFunc onRelease);
    static void setOnClick(IntToVoidFunc onClick);
    static void setOnHold(IntToVoidFunc onHold);
    static void setOnRelease(IntToVoidFunc onRelease);

    static bool isPressed(int key);
    static bool anyPressed(int* keys, int lenght);
    static bool allPressed(int* keys, int lenght);
};

}
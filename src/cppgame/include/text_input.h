#pragma once
#include "cppgame.h"

namespace CppGame{

typedef void(*UIntToVoidFunc)(unsigned int);

class TextInput{
protected:
    static UIntToVoidFunc onCharTyped; // arguments - button id, action
    static void CharCallback(GLFWwindow* window, unsigned int key); // key is in UTF-32, thus key is in unsigned int
public:
    static void init(); // should be called after a window was created.
    static void setOnCharCallback(UIntToVoidFunc onCharCallback);
};

}
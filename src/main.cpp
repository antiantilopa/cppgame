#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <chrono>

#include "cppgame/include/cppgame.h"
#include "cppgame/include/VAO.h"
#include "cppgame/include/VBO.h"
#include "cppgame/include/EBO.h"
#include "cppgame/include/window.h"
#include "cppgame/include/shader.h"

int WIDTH = 800;
int HEIGHT = 600;

int offset[] = {0, 0};
int x, y;

int main(){
    CppGame::init();
    Window window = Window(WIDTH, HEIGHT, "title");
    
    CppGame::Draw::init(window);

    Mode::setOrigin(Mode::ORIGIN_CENTER);
    Mode::setDirection(Mode::DIRECTION_DOWN_RIGHT);

    std::cout << (int)Mode::ox << " " << (int)Mode::oy << " " << (int)Mode::x_sign << " " << (int)Mode::y_sign << "\n";
    std::cout << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";
    
    CppGame::Mouse::setPosition(0, 0);
    while (!window.exitPressed()){
        // clear all events 
        glfwPollEvents();
        
        // sets background color for clear or swap
        window.fill(64, 0, 64, 255);
        
        CppGame::Mouse::getPosition(&x, &y);
        std::cout << "Mouse position: " << x << " " << y << "\n";
        offset[0] += x;
        offset[1] += y;

        CppGame::Draw::rect(offset[0], offset[1], 100, 100, 255, 0, 0, 10);
        CppGame::Draw::line(offset[0] + 50, offset[1] + 50, offset[0] - 50, offset[1] - 50, 0, 0, 0, 10);
        CppGame::Draw::line(offset[0] + 50, offset[1] - 50, offset[0] - 50, offset[1] + 50, 200, 200, 200, 10);

        CppGame::Mouse::setPosition(0, 0);
        // swaps two image buffers.
        window.flip();
    }

    // we need to terminate glfw
    glfwTerminate();

    // Actually, it is not nessecary to clean-up, but it is recomneded.
    return 0;
}
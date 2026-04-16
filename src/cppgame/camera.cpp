#include "include/camera.h"
#include "include/cppgame.h"
#include <iostream>

Camera* Camera::main_camera_ptr = nullptr;

const float half_pi = 1.5707964f;

Camera::Camera(){
    this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->right = glm::vec3(-1.0f, 0.0f, 0.0f);
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->near_plane = 0.01f;
    this->far_plane = 100.0f;
    this->fov = half_pi / 2; // 45 degrees
    this->min_pitch = glm::radians(5.0f);
    this->const_up = true;
    this->proj = glm::perspective(fov, CppGame::window_ptr->aspect, near_plane, far_plane);
    this->updated = true;
    Camera::main_camera_ptr = this;
}
Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up, float near_plane, float far_plane, float fov, bool const_up){
    this->forward = forward;
    this->up = up;
    this->right = glm::cross(forward, up);
    this->position = position;
    this->near_plane = near_plane;
    this->far_plane = far_plane;
    this->fov = fov;
    this->const_up = const_up;
    this->proj = glm::perspective(fov, CppGame::window_ptr->aspect, near_plane, far_plane);
    this->updated = true;
    Camera::main_camera_ptr = this;
}

Camera::~Camera(){
    std::cout << "Camera destroyed" << std::endl;
}

void Camera::setMatrixUniform(Shader& shader, const char* uniform_name){
    if (updated){
        view = glm::lookAt(position, position + forward, up);
        proj_times_view = proj * view;
        updated = false;
        shader.setUniformMatrix(uniform_name, proj_times_view);
    }
}

void Camera::setForward(glm::vec3 new_forward, glm::vec3 new_up){
    forward = glm::normalize(new_forward);
    if (const_up){
        updated = true;
        return;
    }
    if (new_up == glm::vec3(0.0f)){
        if (glm::dot(up, forward) != 0.0f){
            std::cerr << "ERROR: old up forward is not perpendicular to forward\nERROR: WHICH IS RIDICULUS!!!";
            throw "floating point ahh error";
        }
        updated = true;
        return;
    }
    if (glm::dot(new_up, forward) != 0.0f){
        std::cerr << "ERROR: new up forward is not perpendicular to forward";
        throw "(!) maybe (!) floating point ahh error";
    }
    up = glm::normalize(new_up);
    updated = true;
}
void Camera::updateOrientation(float rotx, float roty, float rotz){
    if (rotx == 0.0f && roty == 0.0f && (rotz == 0 || const_up)){
        // some optimization here
        return;
    }
    if (updated){
        right = glm::normalize(glm::cross(forward, up));
    }
    updated = true;
    if (!const_up){
        forward = glm::rotate(forward, glm::radians(roty), up);
        forward = glm::rotate(forward, glm::radians(rotx), right);
        up = glm::rotate(up, glm::radians(rotx), right);
        up = glm::rotate(up, glm::radians(rotz), forward);
        right = glm::normalize(glm::cross(forward, up));
        return;
    }
    forward = glm::rotate(forward, glm::radians(roty), up);
    forward = glm::rotate(forward, glm::radians(rotz), forward);
    glm::vec3 new_forward = glm::rotate(forward, glm::radians(rotx), right);
    if (abs(glm::angle(new_forward, up) - half_pi) <= half_pi - min_pitch){
        forward = new_forward;
    }
}
void Camera::setPosition(glm::vec3 new_pos){
    position = new_pos;
    updated = true;
}
void Camera::updatePosition(glm::vec3 offset){
    position += offset;
    updated = true;
}

void Camera::setNearPlane(float value){
    near_plane = value;
    this->proj = glm::perspective(fov, CppGame::window_ptr->aspect, near_plane, far_plane);
    updated = true;
}
void Camera::setFarPlane(float value){
    far_plane = value;
    this->proj = glm::perspective(fov, CppGame::window_ptr->aspect, near_plane, far_plane);
    updated = true;
}
void Camera::setFov(float value){
    fov = value;
    this->proj = glm::perspective(fov, CppGame::window_ptr->aspect, near_plane, far_plane);
    updated = true;
}

glm::vec3 Camera::getForward(){
    return forward;
}

glm::vec3 Camera::getUp(){
    return up;
}

glm::vec3 Camera::getRight(){
    if (updated){
        right = glm::normalize(glm::cross(forward, up));
    }
    return right;
}

glm::vec3 Camera::getPos(){
    return position;
}

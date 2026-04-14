#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/ext/scalar_constants.hpp"
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <stb/stb_image.h>

#include "shader.h"
#include "cppgame.h"

// since there is gonna be only one camera, it can store up to megabyte of data, if it makes it time efficient enough
class Camera{
protected:
    glm::vec3 forward; // normalized
    glm::vec3 up; // normalized, if const_up, always perpendicular to forward
    glm::vec3 right; // normalized, equal to norm(forward x up)
    glm::vec3 position; // position of camera
    glm::mat4 view; // (!) changes only when setMatrixUniform is called and updated is true (!)
    glm::mat4 proj; // changes every time near_plane, far_plane, or fov changes. presumably they change not so frequent
    glm::mat4 proj_times_view; // stores proj * view for optimization
    float near_plane; // more than 0
    float far_plane; // more that near plane
    float fov; // in radians
    bool updated; // check if any above was changed, so when view or right are used, they are calculated once
public:
    static Camera* main_camera_ptr;
    float min_pitch; // in radians. does nothing if not const_up
    bool const_up; // if true, up vector stays always <0, 1, 0>

    Camera();
    Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up, float near_plane, float far_plane, float fov, bool const_up); // (!) forward and up are expected to be normalized
    ~Camera();
    void setMatrixUniform(Shader& shader, const char* uniform_name);
    void setForward(glm::vec3 new_forward, glm::vec3 new_up = glm::vec3(0));
    void updateOrientation(float rotx, float roty, float rotz = 0);
    void setPosition(glm::vec3 new_position);
    void updatePosition(glm::vec3 offset);
    void setNearPlane(float);
    void setFarPlane(float);
    void setFov(float);
    glm::vec3 getUp();
    glm::vec3 getForward();
    glm::vec3 getRight();
};

#endif
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gfx/Window.h>
#include <gfx/Resource.h>
#include <Settings.h>

#include <models/Model.h>




class Camera {
private:
    Camera() = delete;
    Camera(const Camera &) = delete;
    ~Camera() {}
public:
    static void startup(float fov = 45);
    static void Update(const glm::vec3& position);
    static const glm::vec3& Right();
    static const glm::vec3& Direction();
    static void handle_mouse(float dx, float dy, float delta_time);
    static void wrap_coords(float ix, float iy, float& ox, float& oy);
};

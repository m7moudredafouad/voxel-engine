#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gfx/Window.h>
#include <gfx/Resource.h>
#include <Settings.h>




class Camera {
private:
    Camera() = delete;
    Camera(const Camera &) = delete;
    ~Camera() {}
public:
    static void startup(float fov = 45);
    static void Update();
    static const glm::vec3 & Position();
    static void handle_keys(uint32_t key, float delta_time);
    static void handle_mouse(float dx, float dy, float delta_time);
    static void wrap_coords(float ix, float iy, float& ox, float& oy);
};

#include "Camera.h"
#include <utils/cmath.h>

glm::mat4 view, proj;
static glm::vec3 position, direction, up, right;
static float pitch, yaw, fov, aspect, znear, zfar;

static float velocity = 140.0f;
static float mouse_sensitivity = 1.0f;

void Camera::startup(float fov_) {
    fov = fov_;
    aspect = Window::ratio();
    znear = 0.01f;
    zfar = 1000.0f;
    yaw = 0.0f;
    pitch = 0.0f;

    position = glm::vec3(0.0f, BLOCK_SIZE, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    Camera::Update();
}

void Camera::handle_keys(uint32_t key, float delta_time) {
    auto old_y = position.y;

    if (key == GLFW_KEY_A)
        position += right * velocity * delta_time;

    if (key == GLFW_KEY_D)
        position -= right * velocity * delta_time;

    if (key == GLFW_KEY_W)
        position += direction * velocity * delta_time;

    if (key == GLFW_KEY_S)
        position -= direction * velocity * delta_time;

    position.y = old_y;

}

void Camera::handle_mouse(float dx, float dy, float delta_time) {

  dx *= mouse_sensitivity * delta_time;
  dy *= mouse_sensitivity * delta_time;

  yaw += dx;
  pitch += dy;
}

void Camera::Update() {
    pitch = saturate(pitch, -PI_2+0.1f, PI_2-0.1f);

    yaw = (yaw < 0 ? TAU : 0.0f) + fmodf(yaw, TAU);

    direction = {cosf(pitch) * sinf(yaw), sinf(pitch), cosf(pitch) * cosf(yaw) };
    direction = glm::normalize(direction);

    right = glm::cross({ 0.0f, 1.0f, 0.0f }, direction);
    up = glm::cross(direction, right);

    view = glm::lookAt(position, position+direction, up);
    proj = glm::perspective(fov, aspect, znear, zfar);


    Resource::useShader(ShaderEnum::BASIC)
                .setUniform("view", view)
                .setUniform("projection", proj);
}

const glm::vec3& Camera::Position() {
    return position;
}


void Camera::wrap_coords(float ix, float iy, float& ox, float& oy) {
    static float max_offset_x = BLOCK_WIDTH * GAME_WIDTH - WINDOW_WIDTH / 2;
    static float max_offset_y = BLOCK_HEIGHT * GAME_HEIGHT - WINDOW_HEIGHT / 2;
    if (ix < WINDOW_WIDTH / 2) ox = WINDOW_WIDTH / 2;
    if (iy < WINDOW_HEIGHT / 2) oy = WINDOW_HEIGHT / 2;
    if (ix > max_offset_x) ox = max_offset_x;
    if (iy > max_offset_y) oy = max_offset_y;
}
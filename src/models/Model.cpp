#include "Model.h"

float max_player_x = BLOCK_WIDTH * GAME_WIDTH - BLOCK_WIDTH;
float max_player_y = BLOCK_HEIGHT * GAME_HEIGHT - BLOCK_HEIGHT;

/***Model*************************************/
Model::Model(float x, float y, float z, float size, glm::vec4 color)
    : Model(x, y, z, size, size, size, true, color) {}

Model::Model(float x, float y, float z, float size, bool isActive, glm::vec4 color)
    : Model(x, y, z, size, size, size, isActive, color) {}

Model::Model(float x, float y, float z, float width, float height, float depth, bool isActive, glm::vec4 color)
    : m_pos(x, y, z), m_delta(0, 0, 0), m_size(width, height, depth), m_angle(0), m_is_active(isActive), m_color(color) {}


bool Model::in_window() {
    return !(m_pos.x <= 0.5f || m_pos.x >= Window::width() - 0.5f ||
        m_pos.y <= 0.5f || m_pos.y >= Window::height() - 0.5f);
}

void Model::wrap_coords() {
    float ix = this->m_pos.x;
    float iy = this->m_pos.y;

    if (ix < 0) m_pos.x = 0;
    if (iy < 0) m_pos.y = 0;
    if (ix > max_player_x) m_pos.x = max_player_x;
    if (iy > max_player_y) m_pos.y = max_player_y;
}

void Model::translate() {
    //float delta = Window::delta_time();
    float delta = 1;

    m_pos.x += m_delta.x * delta;
    m_pos.y += m_delta.y * delta;
    m_pos.z += m_delta.z * delta;

    //this->wrap_coords();
}

bool Model::collides(const Model& other) {
    if (other.m_is_active == false) return false;
    float this_width = -0.1f + m_size.x / 2, other_width = other.m_size.x / 2;
    float this_height = -0.1f + m_size.y / 2, other_height = other.m_size.y / 2;
    float this_depth = -0.1f + m_size.z / 2, other_depth = other.m_size.z / 2;

    bool col_x = ((m_pos.x + this_width) >= (other.m_pos.x - other_width))
        && ((m_pos.x + this_width) <= (other.m_pos.x + other_width));

    col_x = col_x || ((m_pos.x - this_width) >= (other.m_pos.x - other_width))
        && ((m_pos.x - this_width) <= (other.m_pos.x + other_width));

    bool col_y = ((m_pos.y + this_height) >= (other.m_pos.y - other_height))
        && ((m_pos.y + this_height) <= (other.m_pos.y + other_height));

    col_y = col_y || ((m_pos.y - this_height) >= (other.m_pos.y - other_height))
        && ((m_pos.y - this_height) <= (other.m_pos.y + other_height));

    bool col_z = ((m_pos.z + this_depth) >= (other.m_pos.z - other_depth))
        && ((m_pos.z + this_depth) <= (other.m_pos.z + other_depth));

    col_z = col_z || ((m_pos.z - this_depth) >= (other.m_pos.z - other_depth))
        && ((m_pos.z - this_depth) <= (other.m_pos.z + other_depth));

    return col_x && col_y && col_z;
}
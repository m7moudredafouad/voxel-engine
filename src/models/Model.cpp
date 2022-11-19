#include "Model.h"

float max_player_x = BLOCK_WIDTH * GAME_WIDTH - BLOCK_WIDTH;
float max_player_y = BLOCK_HEIGHT * GAME_HEIGHT - BLOCK_HEIGHT;

/***Model*************************************/
Model::Model(float x, float y, float z, float size, glm::vec4 color)
    : Model(x, y, z, size, size, size, color) {}

Model::Model(float x, float y, float z, float width, float height, float depth, glm::vec4 color)
    : m_pos(x, y, z), m_delta(0, 0, 0), m_size(width, height, depth), m_angle(0), m_color(color) {}


void Model::set_position(const glm::vec3& pos) { 
    m_pos = { pos.x - BLOCK_SIZE, pos.y - BLOCK_SIZE, pos.z - BLOCK_SIZE };
}


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
    float this_width = -0.1f + m_size.x / 2, other_width = other.m_size.x / 2;
    float this_height = -0.1f + m_size.y / 2, other_height = other.m_size.y / 2;

    bool col_x = ((m_pos.x + this_width) >= (other.m_pos.x - other_width))
        && ((m_pos.x + this_width) <= (other.m_pos.x + other_width));

    col_x = col_x || ((m_pos.x - this_width) >= (other.m_pos.x - other_width))
        && ((m_pos.x - this_width) <= (other.m_pos.x + other_width));

    bool col_y = ((m_pos.y + this_height) >= (other.m_pos.y - other_height))
        && ((m_pos.y + this_height) <= (other.m_pos.y + other_height));

    col_y = col_y || ((m_pos.y - this_height) >= (other.m_pos.y - other_height))
        && ((m_pos.y - this_height) <= (other.m_pos.y + other_height));

    return col_x && col_y;
}
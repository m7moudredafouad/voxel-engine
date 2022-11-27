#pragma once

#include "./model_utils.h"

class Model {
    glm::vec3   m_pos;  /*x, y, z*/
    glm::vec3   m_delta /*dx, dy, dz*/;
    glm::vec3   m_size /*width, height, depth*/;
    float       m_angle, m_jump_height;
    bool        m_is_active;
    sColor   m_color;
public:

    Model(float x, float y, float z, float size, sColor color = { 0xFF, 0xFF, 0xFF, 0xFF });
    Model(float x, float y, float z, float size, bool isActive, sColor color = { 0xFF, 0xFF, 0xFF, 0xFF });
    Model(float x, float y, float z, float width, float height, float depth, bool isActive, sColor color = { 0xFF, 0xFF, 0xFF, 0xFF });

    /***Getters***************************************/
    bool isActive() const { return m_is_active; }
    const sColor & color() const { return m_color; }
    glm::vec3 get_size() const { return m_size; }
    glm::vec3 get_position() const { return m_pos; }
    std::vector<int> get_voxel_position() const { 
        return 
        {
                (int)std::floor(m_pos.x / m_size.x),
                (int)std::floor((m_pos.y / m_size.y)),
                (int)std::floor(m_pos.z / m_size.z)
        };
    }


    /***Setters***************************************/
    void set_position(const glm::vec3& pos) { m_pos = pos; }

    /***Behavior**************************************/
    void jump() { m_jump_height = JUMP_HEIGHT; }

    void handle_jump(bool collided_top, bool collided_bottom);
    bool in_window();
    void wrap_coords();
    void translate();
    bool collides(const Model& other);
};


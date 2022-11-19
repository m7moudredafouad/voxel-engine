#pragma once

#include "./model_utils.h"

class Model {
    glm::vec3   m_pos,  /*x, y, z*/
                m_delta /*dx, dy, dz*/,
                m_size /*width, height, depth*/;

    float m_angle;
    bool m_is_active;
    glm::vec4 m_color;
public:

    Model(float x, float y, float z, float size, glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
    Model(float x, float y, float z, float size, bool isActive, glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });
    Model(float x, float y, float z, float width, float height, float depth, bool isActive, glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f });

    /***Getters***************************************/
    const glm::vec4 & color() const { return m_color; }
    glm::vec3 get_size() const { return m_size; }
    glm::vec3 get_position() const { return m_pos; }
    bool isActive() const { return m_is_active; }

    /***Setters***************************************/
    void set_position(const glm::vec3& pos) { 
        //m_pos = { pos.x - BLOCK_SIZE, pos.y - BLOCK_SIZE, pos.z - BLOCK_SIZE };
        m_pos = pos;
    }

    /***Behavior**************************************/
    bool in_window();
    void wrap_coords();
    void translate();
    bool collides(const Model& other);
};


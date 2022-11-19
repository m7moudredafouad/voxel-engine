#pragma once

#include <memory>
#include <vector>
#include <models/Model.h>
#include <gfx/Resource.h>
#include "../gfx/Buffers.h"
#include <world/world_utils.h>


struct BufferLayout {
    uint32_t length, type, normalize;
};


template <class vertex_t, class index_t>
class Chunkmesh {
private:
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo, m_ibo;

    std::vector<Model> m_object;
    std::vector<vertex_t> m_vertex;
    std::vector<index_t> m_index;

    uint32_t m_shape[3];

    ShaderEnum m_shader;
    size_t m_size, m_idx_per_vertex;
    bool m_updated_buffers;

public:
    Chunkmesh(std::shared_ptr<VertexBuffer> vb, std::shared_ptr<VertexBuffer> ib);
    Chunkmesh(size_t vbo_max_size, size_t ibo_max_size);
    ~Chunkmesh() {}

    /***Drawer****************************************/
    void Render();
    void layout(std::vector<BufferLayout> layout) const;

    /***Getters***************************************/
    size_t size() const { return m_size; }
    Model& object(size_t i) {
        ASSERT(i <= m_size, "MESH::index is out of range");
        return m_object[i];
    }

    /***Setters***************************************/
    void shader(ShaderEnum shader) { this->m_shader = shader; }
    void push(Model obj);
    void remove(size_t i);

    /***Behavior**************************************/
    void translate(size_t i);
    bool check_collision(Model player, eCollisionDir dir);
};

template <class vertex_t, class index_t>
Chunkmesh<vertex_t, index_t>::Chunkmesh(std::shared_ptr<VertexBuffer> vb,
    std::shared_ptr<VertexBuffer> ib) :
    m_vao(std::shared_ptr<VertexArray>(new VertexArray)),
    m_vbo(vb),
    m_ibo(ib),
    m_size(0), m_idx_per_vertex(sizeof(index_t) / sizeof(uint32_t)), m_updated_buffers(false) {   }

template <class vertex_t, class index_t>
Chunkmesh<vertex_t, index_t>::Chunkmesh(size_t vbo_max_size, size_t ibo_max_size) :
    Chunkmesh(
        std::shared_ptr<VertexBuffer>(new VertexBuffer(GL_ARRAY_BUFFER, vbo_max_size)),
        std::shared_ptr<VertexBuffer>(new VertexBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_max_size))
    ) {   }

/***Drawer****************************************/
template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::Render() {
    if (m_size == 0) return;

    //TODO: Check if dynamic or static buffers
    Resource::useShader(m_shader);
    if (m_updated_buffers) {
        m_vbo->bindData(m_vertex, true);
        m_ibo->bindData(m_index, true);
        m_updated_buffers = false;
    }

    m_vao->bind();
    m_vbo->bind();
    m_ibo->bind();

    //GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    //std::cout << m_ibo->length() << ", " << m_vbo->length() << std::endl;
    if (m_idx_per_vertex == 1) {
        GLCall(glDrawElements(GL_POINTS, m_ibo->length(), GL_UNSIGNED_INT, 0));
    }
    else if (m_idx_per_vertex == 2) {
        GLCall(glDrawElements(GL_LINE, m_ibo->length() * 2, GL_UNSIGNED_INT, 0));
    }
    else {
        GLCall(glDrawElements(GL_TRIANGLES, m_ibo->length() * m_idx_per_vertex, GL_UNSIGNED_INT, 0));
    }
}

template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::layout(std::vector<BufferLayout> layouts) const {
    size_t stride = 0, offset = 0;
    for (auto& element : layouts) {
        stride += sizeofGlType(element.type) * element.length;
    }

    this->m_vao->bind();
    this->m_vbo->bind();
    for (size_t i = 0; i < layouts.size(); ++i) {

        auto& element = layouts[i];

        GLCall(glEnableVertexAttribArray(i));

        GLCall(glVertexAttribPointer(
            i, element.length, element.type, element.normalize, stride, reinterpret_cast<const void*>(offset)
        ));
        offset += element.length * sizeofGlType(element.type);

    }
}

/***Setters***************************************/
template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::push(Model obj) {
    m_object.push_back(obj);
    m_vertex.push_back(vertex_t(obj));

    index_t i = m_size++;
    m_index.push_back(i);
    m_updated_buffers = true;
};

template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::remove(size_t i) {
    ASSERT(i <= m_size, "MESH::index is out of range");
    m_size--;

    m_object.erase(m_object.begin() + i);
    m_vertex.erase(m_vertex.begin() + i);
    m_index.pop_back();
    m_updated_buffers = true;
}

/***Behavior**************************************/
template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::translate(size_t i) {
    ASSERT(i <= m_size, "MESH::index is out of range");
    m_vertex[i].translate(m_object[i]);
    m_updated_buffers = true;
}

template <class vertex_t, class index_t>
bool Chunkmesh<vertex_t, index_t>::check_collision(Model player, eCollisionDir dir) {
    glm::vec3 player_pos = player.get_position();
    glm::vec3 player_size = player.get_size();

    // TODO
    glm::vec3 idx = {   std::round(player_pos.x / player_size.x),
                        std::round(player_pos.y / player_size.y),
                        std::round(player_pos.y / player_size.z)
                    };

    player.translate();
    int idx = getBlockIndex(x, y);

    if (dir & eCollisionDir::LEFT) {
        idx = getBlockIndex(x - 1, y);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::RIGHT) {
        idx = getBlockIndex(x + 1, y);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::TOP) {
        idx = getBlockIndex(x, y + 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::BOTTOM) {
        idx = getBlockIndex(x, y - 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::BOTTOM_LEFT) {
        idx = getBlockIndex(x - 1, y - 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::TOP_LEFT) {
        idx = getBlockIndex(x - 1, y + 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::BOTTOM_RIGHT) {
        idx = getBlockIndex(x + 1, y - 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    if (dir & eCollisionDir::TOP_RIGHT) {
        idx = getBlockIndex(x + 1, y + 1);
        if (idx > -1 && player.collides(block->object(idx))) return true;
    }

    return false;
}
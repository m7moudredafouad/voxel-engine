#pragma once

#include <memory>
#include <vector>
#include <models/Model.h>
#include <gfx/Resource.h>
#include <gfx/Buffers.h>
#include <world/world_utils.h>


struct BufferLayout {
    uint32_t length, type, normalize;
};

// ! Layout is x, z, y
template <class vertex_t, class index_t>
class Chunkmesh {
private:
    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo, m_ibo;

    std::vector<Model> m_object;
    std::vector<vertex_t> m_vertex;
    std::vector<index_t> m_index;
    ShaderEnum m_shader;

    Shape m_shape;

    size_t m_size, m_idx_per_vertex;
    bool m_updated_buffers;

private:
    void load();
public:
    /***Constructors**********************************/
    Chunkmesh(size_t max_size, const std::vector<int>& shape);
    Chunkmesh( std::shared_ptr<VertexBuffer> vb,
               std::shared_ptr<VertexBuffer> ib,
               const std::vector<int>& shape);
    ~Chunkmesh() {}

    /***Drawer****************************************/
    void Render();
    void layout(std::vector<BufferLayout> layout) const;

    /***Getters***************************************/
    size_t size() const { return m_size; }
    bool exist(size_t i) {
        return i < m_size;
    }
    Model& object(size_t i) {
        ASSERT(i < m_size, "MESH::index is out of range");
        m_updated_buffers = true;
        return m_object[i];
    }

    int in_bound(const Model& player) {
        glm::vec3 pos = player.get_position();
        int idx = m_shape.at({
                int(std::floor(pos.x / BLOCK_WIDTH)),
                int(std::floor(pos.z / BLOCK_DEPTH)),
                int(std::floor(pos.y / BLOCK_HEIGHT)),
            });
        return idx != -1;
    }

    /***Setters***************************************/
    void shader(ShaderEnum shader) { this->m_shader = shader; }
    void push(Model obj);
    void remove(size_t i);
    void deactivate(size_t i) {
        if (i >= m_shape.get_max_size()) return;

        m_object[i].deactivate();
        m_updated_buffers = true;
    }

    /***Behavior**************************************/
    bool check_collision(Model player, eCollisionDir y_dir);
    bool deactivate_if_contains(Model model);
};

/***Constructors**********************************/
template <class vertex_t, class index_t>
Chunkmesh<vertex_t, index_t>::Chunkmesh(size_t max_size, const std::vector<int>& shape) :
    Chunkmesh(
        std::shared_ptr<VertexBuffer>(new VertexBuffer(GL_ARRAY_BUFFER, sizeof(vertex_t) * max_size)),
        std::shared_ptr<VertexBuffer>(new VertexBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_t) * max_size)),
        shape
    ) {   }

template <class vertex_t, class index_t>
Chunkmesh<vertex_t, index_t>::Chunkmesh(
    std::shared_ptr<VertexBuffer> vb,
    std::shared_ptr<VertexBuffer> ib,
    const std::vector<int>& shape) :
    m_vao(std::shared_ptr<VertexArray>(new VertexArray)),
    m_vbo(vb),
    m_ibo(ib),
    m_shader(ShaderEnum::NONE),
    m_shape(shape),
    m_size(0), m_idx_per_vertex(sizeof(index_t) / sizeof(uint32_t)), m_updated_buffers(false) {   }


/***Drawer****************************************/
template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::Render() {
    if (m_size == 0) return;

    //TODO: Check if dynamic or static buffers
    Resource::useShader(m_shader);
    if (m_updated_buffers) {
        this->load();
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

/***Getters***************************************/

/***Setters***************************************/
template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::push(Model obj) {
    if (m_object.size() >= m_shape.get_max_size()) return;
    m_object.push_back(obj);
    if (obj.isActive()) {
        m_size++;
        m_updated_buffers = true;
    }
};

template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::remove(size_t i) {
    ASSERT(i <= m_size, "MESH::index is out of range");
    m_object.erase(m_object.begin() + i);
    m_size--;
    m_updated_buffers = true;
}

template <class vertex_t, class index_t>
void Chunkmesh<vertex_t, index_t>::load() {
    
    static int directions[][3] = {
        {1, 0, 0},
        {-1, 0, 0},
        {0, 1, 0},
        {0, -1, 0},
        {0, 0, 1},
        {0, 0, -1},
    };

    m_vertex.clear();
    m_index.clear();


    
    int idx = 0;
    for (int i = 0; i < m_object.size(); i++) {
        if (!m_object[i].isActive()) continue;

        auto idx_vec = m_shape.at(i);
        bool are_surrounding_active = true;
        for (auto dir : directions) {
            for(int x = 0; x < idx_vec.size(); x++) idx_vec[x] += dir[x];

            auto tmp_idx = m_shape.at(idx_vec);
            if (tmp_idx == -1 || tmp_idx >= m_object.size()) {
                are_surrounding_active = false;
                break;
            }

            are_surrounding_active &= m_object[tmp_idx].isActive();

            if (!are_surrounding_active) break;
            for (int x = 0; x < idx_vec.size(); x++) idx_vec[x] -= dir[x];
        }

        if (are_surrounding_active) continue;

        m_vertex.push_back(vertex_t(m_object[i]));
        m_index.push_back(idx++);
    }

    m_vbo->bindData(m_vertex, true);
    m_ibo->bindData(m_index, true);
}

/***Behavior**************************************/
template <class vertex_t, class index_t>
bool Chunkmesh<vertex_t, index_t>::check_collision(Model player, eCollisionDir y_dir) {
    if (!player.isActive()) return false;
    
    static int directions[][2] = {
        {0, 0},
        {0, 1},
        {0, -1},
        {1, 0},
        {1, 1},
        {1, -1},
        {-1, 0},
        {-1, 1},
        {-1, -1}
    };

    player.translate();

    // Poition of the player in the Array
    // TODO: Need fix here, Shouldn't depend on player size
    glm::vec3 pos = player.get_position();
    glm::vec3 size = player.get_size();

    // TODO: The whole chunk should have the same dimensions
    // Do I need to add this as a variable ?
    int y = std::floor(pos.y / BLOCK_HEIGHT) + static_cast<int>(y_dir);

    for (const auto & dir : directions) {
        int idx = m_shape.at({  // check collision in the same location of the player
                int(std::round((pos.x/ BLOCK_WIDTH) + (dir[0] * 0.5f))),
                int(std::round((pos.z/ BLOCK_DEPTH) + (dir[1] * 0.5f))),
                y
            });

        if (idx > -1 && player.collides(m_object[idx])) return true;

    }

    return false;
}

template <class vertex_t, class index_t>
bool Chunkmesh<vertex_t, index_t>::deactivate_if_contains(Model model) {
    if (!model.isActive()) return false;

    glm::vec3 pos = model.get_position();
    
    int idx = m_shape.at({  // check collision in the same location of the player
            int(std::round(pos.x / BLOCK_WIDTH)),
            int(std::round(pos.z / BLOCK_DEPTH)),
            int(std::round(pos.y / BLOCK_HEIGHT))
    });

    if (idx > -1 && m_object[idx].isActive()) {
        this->deactivate(idx);
        return true;
    }

    return false;
}

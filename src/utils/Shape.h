#pragma once

#include <vector>
#include "error.h"
class Shape {
private:
	std::vector<int> m_shape, m_stride;
    uint32_t m_dims, m_max_size;
public:
    Shape(uint32_t num_dims, uint32_t dim_size) : Shape(std::vector<int>(num_dims, dim_size)) {}

    Shape(const std::vector<int> & shape) : m_dims(shape.size()) {
        ASSERT(m_dims != 0, "Shape must have at least 1 dimension");
        m_shape = std::vector<int>(m_dims, 0);
        m_stride = std::vector<int>(m_dims, 1);

        m_shape[m_dims-1] = shape[m_dims-1];
        for (int i = m_dims - 2; i >= 0; i--) {
            m_shape[i] = shape[i];
            m_stride[i] = m_stride[i + 1] * m_shape[i + 1];
        }

        m_max_size = m_shape[0] * m_stride[0];
        
        /*m_stride[0] = shape.y * shape.z;
        m_stride[1] = shape.z;
        m_stride[2] = 1;*/
    }

    int32_t at(const std::vector<int>& idx_in_dims) const {
        ASSERT(idx_in_dims.size() == m_dims, "Shape::at::Dimensions are not the same");

        int32_t idx = 0;

        for (int i = 0; i < m_dims; i++) {
            if (idx_in_dims[i] < 0 || idx_in_dims[i] >= m_shape[i]) return -1;

            idx += (idx_in_dims[i] * m_stride[i]);
        }

        return (idx < m_max_size) ? idx : -1;
    }
};

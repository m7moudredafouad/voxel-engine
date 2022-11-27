#pragma once
#include "world_utils.h"
#include "geometric_utils.h"
#include <models/model_utils.h>


/** Square Positions
 * 0 ------------- 1
 * |               |
 * |               |
 * |               |
 * |               |
 * 2 ------------- 3
 * 0, 3, 2
 * 0, 1, 3
*/
struct sSquareIndex {
    uint32_t pos[INDEX_PER_SQUARE];
    sSquareIndex(uint32_t i) : pos{ 0, 2, 3, 0, 3, 1 } {
        for (uint32_t& x : pos) {
            x += i * 4;
        }
    }
};

/** Cube Positions
 *    7 ------------ 6   
 *  /               /
 * 3 ------------- 2
 * |               |
 * |               |
 * |  4----------- | 5 
 * | /             |/
 * 0 ------------- 1
 * 
*/

struct sCubeIndex {
    uint32_t pos[INDEX_PER_CUBE];
    sCubeIndex(uint32_t i) : pos{ 1, 0, 3, 1, 3, 2,
                                4, 5, 6, 4, 6, 7,
                                5, 1, 2, 5, 2, 6,
                                0, 4, 7, 0, 7, 3,
                                2, 3, 7, 2, 7, 6,
                                5, 4, 0, 5, 0, 1,
    } {
        for (uint32_t& x : pos) {
            x += i * 8;
        }
    }
};

/***Vertex******************************/
struct sSpaceVertex {
    glm::vec3 coord;
    sColor color;
};

/***Geometric**************************/
class Geometric {
public:
    void translate(Model& obj);
};

/***Square******************************/
class Square : public Geometric {
    sSpaceVertex points[VERTEX_PER_SQUARE];
public:
    Square(const Model& obj);
    void translate(Model& obj);
};

/***Cube********************************/
class Cube : public Geometric {
    sSpaceVertex points[VERTEX_PER_CUBE];
public:
    Cube(const Model& obj);
    void translate(Model& obj);
};
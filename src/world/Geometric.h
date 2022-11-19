#pragma once
#include "world_utils.h"
#include "geometric_utils.h"


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
 * 0, 3, 2, 0, 1, 3
 * 4, 7, 6, 4, 5, 7
 * 
 * 0, 5, 1, 0, 4, 1
 * 2, 7, 3, 2, 6, 3
 * 
 * 4, 2, 6, 4, 0, 2
 * 1, 5, 7, 1, 7, 3
*/

struct sCubeIndex {
    uint32_t pos[INDEX_PER_CUBE];
    sCubeIndex(uint32_t i) : pos{ 1, 0, 3, 1, 3, 2, // north (-z)
                                4, 5, 6, 4, 6, 7, // south (+z)
                                5, 1, 2, 5, 2, 6, // east (+x)
                                0, 4, 7, 0, 7, 3, // west (-x)
                                2, 3, 7, 2, 7, 6, // top (+y)
                                5, 4, 0, 5, 0, 1, // bottom (-y)
    } {
        for (uint32_t& x : pos) {
            x += i * 8;
        }
    }
};

/***Vertex******************************/
struct sSpaceVertex {
    glm::vec3 coord;
    glm::vec4 color;
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
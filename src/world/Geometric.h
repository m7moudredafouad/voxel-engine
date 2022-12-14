#pragma once
#include "world_utils.h"
#include <models/model_utils.h>

//#define VERTEX_PER_CUBE   (8)
#define VERTEX_PER_CUBE   (24)
//#define INDEX_PER_SQUARE   (6)
#define INDEX_PER_CUBE   (36)

/***Faces*******************************/\
enum eFace {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    FRONT = 4,
    BACK = 5
};

/***Vertex******************************/
struct sVertex {
    glm::vec3 coord;
    sColor color;
    float face;
    sVertex(glm::vec3 coord = {0.0f, 0.0f, 0.0f}, sColor color = {0,0,0,0}, float face = 0.0) : coord(coord), color(color), face(face) {}
};

/***Geometric**************************/
class Geometric {
public:
};

/***Cube********************************/
struct sCubeIndex {
    uint32_t pos[INDEX_PER_CUBE];
    sCubeIndex(uint32_t idx);
};

class Cube : public Geometric {
    sVertex points[VERTEX_PER_CUBE];
public:
    Cube(const Model& obj);
};
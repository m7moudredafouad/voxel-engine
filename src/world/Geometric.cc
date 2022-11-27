#include "Geometric.h"

/***Cube********************************/
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

const static uint32_t CUBE_IDX[] = {
    1, 0, 3, 1, 3, 2,
    4, 5, 6, 4, 6, 7,
    5, 1, 2, 5, 2, 6,
    0, 4, 7, 0, 7, 3,
    2, 3, 7, 2, 7, 6,
    5, 4, 0, 5, 0, 1,
};

const static int32_t CUBE_POINTS[][3] = {
    {-1, -1, -1}, // 0
    { 1, -1, -1}, // 1
    { 1,  1, -1}, // 2
    {-1,  1, -1}, // 3

    {-1, -1,  1}, // 4
    { 1, -1,  1}, // 5
    { 1,  1,  1}, // 6
    {-1,  1,  1}, // 7
};

//const static uint32_t CUBE_IDX[] = {
//    0, 1, 2, 2, 3, 0,
//};
//
//const static int32_t CUBE_POINTS[][3] = {
//        {-1, -1, -1},
//        { 1, -1, -1},
//        { 1,  1, -1},
//        {-1,  1, -1},
//
//        {-1, -1,  1},
//        { 1, -1,  1},
//        { 1,  1,  1},
//        {-1,  1,  1},
//
//        {-1,  1,  1},
//        {-1,  1, -1},
//        {-1, -1, -1},
//        {-1, -1,  1},
//
//        {1,  1,  1},
//        {1,  1, -1},
//        {1, -1, -1},
//        {1, -1,  1},
//
//        {-1, -1, -1},
//        { 1, -1, -1},
//        { 1, -1,  1},
//        {-1, -1,  1},
//
//        {-1,  1, -1},
//        { 1,  1, -1},
//        { 1,  1,  1},
//        {-1,  1,  1},
//};
//
//const static eFace CUBE_FACE[] = {
//      BACK, BACK, BACK, BACK,
//      FRONT, FRONT, FRONT, FRONT,
//      LEFT, LEFT, LEFT, LEFT,
//      RIGHT, RIGHT, RIGHT, RIGHT,
//      DOWN, DOWN, DOWN, DOWN,
//      UP, UP, UP, UP,
//};

sCubeIndex::sCubeIndex(uint32_t idx) {
    // pos[x] = (Point index in square + Square index in Cube) + Cube index in world
    //int x = 0;
    //for (size_t i = 0; i < INDEX_PER_SQUARE; i++) {
    //    for (size_t j = 0; j < INDEX_PER_SQUARE; j++) {
    //        pos[x++] = (CUBE_IDX[j] + 4*i)  + idx * VERTEX_PER_CUBE;
    //    }
    //}

    for (size_t i = 0; i < INDEX_PER_CUBE; i++) {
            pos[i] = CUBE_IDX[i] + idx * VERTEX_PER_CUBE;
    }
}

Cube::Cube(const Model& obj) {

    const sColor color = obj.color();
    glm::vec3 obj_size = obj.get_size();
    glm::vec3 obj_pos = obj.get_position();

    for (size_t i = 0; i < VERTEX_PER_CUBE; i++) {
        points[i].color = color;
        //points[i].face = static_cast<uint32_t>(CUBE_FACE[i]);
        points[i].coord.x = obj_pos.x + CUBE_POINTS[i][0] * obj_size.x * 0.5f;
        points[i].coord.y = obj_pos.y + CUBE_POINTS[i][1] * obj_size.y * 0.5f;
        points[i].coord.z = obj_pos.z + CUBE_POINTS[i][2] * obj_size.z * 0.5f;
    }
}
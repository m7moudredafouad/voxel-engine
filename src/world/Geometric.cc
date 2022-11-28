#include "Geometric.h"

/***Cube********************************/
/** Cube Positions
 *    3 ------------ 2
 *  /               /
 * 7 ------------- 6
 * |               |
 * |               |
 * |  0----------- | 1
 * | /             |/
 * 4 ------------- 5
 *
*/

//const static uint32_t CUBE_IDX[] = {
//    1, 0, 3, 1, 3, 2,
//    4, 5, 6, 4, 6, 7,
//    5, 1, 2, 5, 2, 6,
//    0, 4, 7, 0, 7, 3,
//    2, 3, 7, 2, 7, 6,
//    5, 4, 0, 5, 0, 1,
//};
//
//const static int32_t CUBE_POINTS[][3] = {
//    {-1, -1, -1}, // 0
//    { 1, -1, -1}, // 1
//    { 1,  1, -1}, // 2
//    {-1,  1, -1}, // 3
//
//    {-1, -1,  1}, // 4
//    { 1, -1,  1}, // 5
//    { 1,  1,  1}, // 6
//    {-1,  1,  1}, // 7
//};

const static uint32_t CUBE_IDX[] = {
    0, 1, 2, 0, 2, 3,   // FRONT
    4, 6, 5, 4, 7, 6,   // BACK

    8, 9, 10, 8, 10, 11,   // RIGHT
    12, 14, 13, 12, 15, 14,   // LEFT

    16, 17, 18, 16, 18, 19,   // UP
    20, 22, 21, 20, 23, 22,   // DOWN
};

const static int32_t CUBE_POINTS[][3] = {
        {-1, -1,  1}, // 0
        { 1, -1,  1}, // 1
        { 1,  1,  1}, // 2
        {-1,  1,  1}, // 3

        {-1, -1, -1}, // 4
        { 1, -1, -1}, // 5
        { 1,  1, -1}, // 6
        {-1,  1, -1}, // 7

        {1, -1,  1},  // 8
        {1, -1, -1},  // 9
        {1,  1, -1},  // 10
        {1,  1,  1},  // 11

        {-1, -1,  1}, // 12
        {-1, -1, -1}, // 13
        {-1,  1, -1}, // 14
        {-1,  1,  1}, // 15
 
        {-1,  1,  1}, // 16
        { 1,  1,  1}, // 17
        { 1,  1, -1}, // 18
        {-1,  1, -1}, // 19

        {-1, -1,  1}, // 20
        { 1, -1,  1}, // 21
        { 1, -1, -1}, // 22
        {-1, -1, -1}, // 23
};

const static eFace CUBE_FACE[] = {
      FRONT, FRONT, FRONT, FRONT,
      BACK, BACK, BACK, BACK,
      RIGHT, RIGHT, RIGHT, RIGHT,
      LEFT, LEFT, LEFT, LEFT,
      UP, UP, UP, UP,
      DOWN, DOWN, DOWN, DOWN,
};

sCubeIndex::sCubeIndex(uint32_t idx) {
     //pos[i] = Square index in Cube + Cube index in world
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
        points[i].face = static_cast<float>(CUBE_FACE[i]);
        points[i].coord.x = obj_pos.x + CUBE_POINTS[i][0] * obj_size.x * 0.5f;
        points[i].coord.y = obj_pos.y + CUBE_POINTS[i][1] * obj_size.y * 0.5f;
        points[i].coord.z = obj_pos.z + CUBE_POINTS[i][2] * obj_size.z * 0.5f;
    }
}
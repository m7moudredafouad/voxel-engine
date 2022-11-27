#include "Geometric.h"

/***Square******************************/
Square::Square(const Model& obj)
    : points{ 
                {{0 , 1, 0}, obj.color()},
                {{1 , 1, 0}, obj.color()},
                {{0 , 0, 0}, obj.color()},
                {{1 , 0, 0}, obj.color()}
            }
{
    // Size
    glm::vec3 obj_size = obj.get_size();
    for (auto& point : points) {
        point.coord.x *= obj_size.x;
        point.coord.y *= obj_size.y;
    }

    // Translate
    glm::vec3 obj_pos = obj.get_position();

    for (auto& point : points) {
        point.coord.x += obj_pos.x;
        point.coord.y += obj_pos.y;
    }
}

//void Square::translate(Model& obj) {
//    obj.translate();
//    *this = Square(obj);
//}


/***Cube********************************/

Cube::Cube(const Model& obj)
    : points{
            {{-1 , -1, -1}, obj.color()},     // 0
            {{1 , -1, -1}, obj.color()},      // 1
            {{1 , 1, -1}, obj.color()},       // 2
            {{-1 , 1, -1}, obj.color()},      // 3

            {{-1 , -1, 1}, obj.color()},      // 4
            {{1 , -1, 1}, obj.color()},       // 5
            {{1 , 1, 1}, obj.color()},        // 6
            {{-1 , 1, 1}, obj.color()},       // 7
}
{
    // Size
    glm::vec3 obj_size = obj.get_size();
    for (auto& point : points) {
        point.coord.x *= obj_size.x * 0.5f;
        point.coord.y *= obj_size.y * 0.5f;
        point.coord.z *= obj_size.z * 0.5f;
    }

    // Translate
    glm::vec3 obj_pos = obj.get_position();
    for (auto& point : points) {
        point.coord.x += obj_pos.x;
        point.coord.y += obj_pos.y;
        point.coord.z += obj_pos.z;
    }
}

//void Cube::translate(Model& obj) {
//    obj.translate();
//    *this = Cube(obj);
//}
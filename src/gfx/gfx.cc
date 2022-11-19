#include "./gfx.h"

size_t sizeofGlType(uint32_t type) {
    switch (type)
    {
    case GL_FLOAT:
        return sizeof(GLfloat);
    case GL_INT:
    case GL_UNSIGNED_INT:
        return sizeof(GLuint);
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
        return sizeof(GLbyte);

    }
    ASSERT(false, "Provided type is wrong");
    return 0;
}

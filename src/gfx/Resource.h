#pragma once

#include "gfx.h"
#include "Buffers.h"
#include "Shader.h"
#include "Window.h"
#include <unordered_map>

enum ShaderEnum {
    NONE,
    BASIC,
    CIRCLE,
};

/**
 * @brief Singleton Renderer
 * 
 */
class Resource {
private:
    static std::unordered_map<ShaderEnum, Shader *> m_shaders;
    static ShaderEnum m_last_used_shader;

private: // PRIVATE FUNCTIONS
    Resource();
    Resource(const Resource&) = delete;
public:
    static void startup();
    static void shutdown();
    static const Shader & getShader(ShaderEnum shaderName);
    static const Shader & useShader(ShaderEnum shaderName);
    ~Resource() {}

};  // class Renderer







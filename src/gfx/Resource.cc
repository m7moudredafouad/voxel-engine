#include "Resource.h"

ShaderEnum Resource::m_last_used_shader = ShaderEnum::NONE;
std::unordered_map<ShaderEnum, Shader*> Resource::m_shaders = std::unordered_map<ShaderEnum, Shader*>();

void Resource::startup() {
    m_shaders[BASIC] = new Shader("./shaders/basic");
    m_shaders[CIRCLE] = new Shader("./shaders/circle");
}


void Resource::shutdown() {
    for (auto& shader : m_shaders) {
        delete shader.second;
    }
}

const Shader & Resource::getShader(ShaderEnum shaderName) {
    const auto & shader = m_shaders.find(shaderName);
    ASSERT(shader != m_shaders.end(), "Shader was not found");
    return *shader->second;
}

const Shader & Resource::useShader(ShaderEnum shaderName) {
    const auto& shader = getShader(shaderName);
    if(m_last_used_shader == shaderName) return shader;
    shader.bind();
    return shader;
}


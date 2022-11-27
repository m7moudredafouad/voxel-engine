#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;

uniform mat4 projection, view, model;

out vec4 v_Color;

void main() {
    gl_Position = projection * view * vec4(pos, 1.0);
    v_Color = vec4(
        color.x / 255.0, color.y / 255.0, color.z / 255.0, color.w / 255.0
    );
}
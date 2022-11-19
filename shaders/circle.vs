#version 330 core

precision mediump float;

layout (location = 0) in vec2 pos;
layout (location = 1) in float r;
layout (location = 2) in vec4 color;

uniform mat4 projection, view, model;
uniform vec2 resolution;

out vec4 v_Color;
out float radius;
out vec2 pointPos;

void main() {
    gl_Position = projection * vec4(pos, -1.0, 1.0);
    gl_PointSize = 900.0;
    radius = r;
    v_Color  = color;

    vec2 ndcPos = gl_Position.xy / gl_Position.w;
    pointPos    = resolution * (ndcPos * 0.5 + 0.5);
}
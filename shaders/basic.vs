#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;
layout (location = 2) in uint face;

const uint UP = 0U;
const uint DOWN = 1U;
const uint LEFT = 2U;
const uint RIGHT = 3U;
const uint FRONT = 4U;
const uint BACK = 5U;

const vec4 sunlight_color = vec4(0.3, 0.3, 0.3, 0.5);

uniform mat4 projection, view, model;

out vec4 v_Color;

void main() {
    gl_Position = projection * view * vec4(pos, 1.0);

    vec3 light = vec3(
        color.x / 255.0, color.y / 255.0, color.z / 255.0
    ) * color.w / 255.0;

    light = max(vec3(sunlight_color.rgb), light);

    const float min_light = 0.0025;
    light *= vec3(1.0 - min_light);
    light += vec3(min_light);

    if (face == UP) {
        light *= 1.0;
    } else if (face == LEFT || face == RIGHT) {
        light *= 0.8;
    } else if (face == FRONT || face == BACK) {
        light *= 0.6;
    } else {
        light *= 0.5;
    }

    v_Color = vec4(light, 1.0);
    v_Color = vec4(pow(v_Color.rgb, vec3(1.0 / 2.2)), v_Color.a);
}
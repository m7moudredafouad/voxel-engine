#version 330 core

in vec4 v_Color;
in float radius;
in vec2  pointPos;

const float threshold = 2.0;

out vec4 fragment_color;

void main() {
    float dist = distance(pointPos, gl_FragCoord.xy);

    if (dist > radius || dist < radius-threshold) discard;

    float d = dist / radius;

    vec4 color = mix(vec4(0.0), v_Color, step(1.0-threshold, d));

    fragment_color = v_Color;
}

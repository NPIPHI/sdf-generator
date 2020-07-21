#version 300 es

out lowp vec4 Color;

in lowp vec2 UV;

void main() {
    Color = vec4(UV, 1, 1);
}

#version 300 es

in vec2 position;
in vec2 uv;

out vec2 UV;

void main() {
    gl_Position = vec4(position, 0, 1);
    UV = uv;
}

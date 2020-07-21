#version 300 es

in lowp vec2 UV;

layout(location = 0) out lowp vec4 Color;

uniform sampler2D tex;

void main() {
//    Color = vec4(texelFetch(tex, ivec2(0, 0), 0));
    Color = vec4(texture(tex, UV).xyz, texture(tex, UV).w * 0.5 + 0.5);
//    Color = vec4(1);
//    Color = texture(tex, UV);
//    Color= vec4(0.5);
}

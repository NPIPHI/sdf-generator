#version 300 es

in lowp vec2 UV;

layout(location = 0) out mediump vec3 Color;

uniform sampler2D tex;

void main() {
    ivec2 texDimnsions = textureSize(tex, 0);
    ivec2 texel = ivec2(UV * vec2(texDimnsions));
    if(texelFetch(tex, texel, 0).a == 1.f){
        bool onEdge = !(
        texelFetch(tex, texel + ivec2(0, 1), 0).a == 1.f &&
        texelFetch(tex, texel + ivec2(1, 0), 0).a == 1.f &&
        texelFetch(tex, texel + ivec2(-1, 0), 0).a == 1.f &&
        texelFetch(tex, texel + ivec2(0, -1), 0).a == 1.f);
        if(onEdge){
            Color = vec3(UV, 1);
        } else {
            Color = vec3(0, 0, 0);
        }
    } else {
        Color = vec3(0, 0, 0);
    }
}

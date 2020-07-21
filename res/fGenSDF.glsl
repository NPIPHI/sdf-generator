#version 300 es

in lowp vec2 UV;

uniform sampler2D interiorMask;
uniform sampler2D closestTexture;

layout(location = 0) out mediump vec4 Color;

uniform mediump float sdfRadius;

void main() {
    ivec2 texel = ivec2(vec2(textureSize(closestTexture, 0)) * UV);
    mediump vec3 info = texelFetch(closestTexture, texel, 0).xyz;
    mediump float valid = info.z;
    if(valid == 1.f){
        mediump vec2 closestPoint = info.xy;
        mediump float dist = distance(closestPoint, UV);
        Color = vec4(vec3(dist*sdfRadius),1);
    } else {
        Color = vec4(1);
    }
//    lowp float valid = texelFetch(closestTexture, texel, 0).z;
//    Color = vec4(vec3(valid), 1);
}

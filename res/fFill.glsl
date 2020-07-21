#version 300 es

in lowp vec2 UV;

layout(location = 0) out mediump vec3 Color;

uniform sampler2D tex;

uniform int jump;

mediump float valid;
mediump vec2 closest;
mediump float minDist2;

lowp float distance2(mediump vec2 a, mediump vec2 b){
    mediump vec2 dif = a - b;
    return dot(dif, dif);
}

void check(ivec2 loc){
    mediump vec3 info = texelFetch(tex, loc, 0).xyz;
    mediump float dist = distance2(info.xy, UV);
    if(info.z == 1.f && dist < minDist2){
        minDist2 = dist;
        closest = info.xy;
        valid = 1.f;
    }
}

void main() {
    ivec2 texel = ivec2(vec2(textureSize(tex, 0)) * UV);
    mediump vec3 info = texelFetch(tex, texel, 0).xyz;
    closest = info.xy;
    valid = info.z;
    if(valid == 1.f){
        minDist2 = distance2(closest, UV);
    } else {
        minDist2 = 10000000.f;
    }
//    for(int i = -jump; i < jump; i++){
//        check(texel + ivec2(i, jump));
//        check(texel + ivec2(i, -jump));
//        check(texel + ivec2(jump, i));
//        check(texel + ivec2(-jump, i));
//    }
    check(texel + ivec2(-jump, jump));
    check(texel + ivec2(0, jump));
    check(texel + ivec2(jump, jump));
    check(texel + ivec2(-jump, 0));
    check(texel + ivec2(jump, 0));
    check(texel + ivec2(-jump, -jump));
    check(texel + ivec2(0, -jump));
    check(texel + ivec2(jump, -jump));
    Color = vec3(closest, valid);
}

#version 300 es

in lowp vec2 UV;

out lowp vec4 Color;

uniform sampler2D tex;
uniform lowp float threshold;

void main() {
    Color = texture(tex, UV);
//    Color = texture(tex, UV);
//    if(texture(tex, UV).r > threshold){
//        Color = vec4(0, 0, 0, 1);
//    } else {
//        discard;
//    }
}

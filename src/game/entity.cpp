//
// Created by 16182 on 7/17/2020.
//

#include "../gfx/bufferObject.h"
#include "entity.h"

using namespace glm;

void entity::update() {
    vec2 dV = [&] {
        if (position == target_position) {
            return vec2{0};
        } else {
            return glm::normalize(target_position - position) * 0.03f;
        }}();
    velocity += dV;
    velocity *= 0.5;
    position += velocity;
}

void entity::emplaceGeometry(bufferObject<vec3, vec2> &buffer) const {
    vec3 position3 = vec3{position, 0};
    buffer.push_back<0>(position3);
    buffer.push_back<1>(vec2{0, 0});
    buffer.push_back<0>(position3 + vec3{-0.1, 0.1, 0});
    buffer.push_back<1>(vec2{1, 0});
    buffer.push_back<0>(position3 + vec3{0.1, 0.1, 0});
    buffer.push_back<1>(vec2{0, 1});
}

entity::entity(vec2 position): position(position){

}

void entity::moveTo(glm::vec2 target) {
    target_position = target;
}

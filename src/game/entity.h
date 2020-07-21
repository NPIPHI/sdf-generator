#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../gfx/bufferObject.h"

class entity {
public:
    entity(glm::vec2 position);
    void update();
    void emplaceGeometry(bufferObject<glm::vec3, glm::vec2> &buffer) const;
    void moveTo(glm::vec2 target);
private:
    glm::vec2 position;
    glm::vec2 target_position {0};
    glm::vec2 velocity {0};
};
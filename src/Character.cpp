#include "Character.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "config.hpp"
#include <glm/fwd.hpp>

void Character::Start() {
    this->SetDrawable(work_img);
    this->SetPivotToLeftButton();
    this->SetZIndex(UI_Z);
    this->SetPosition({
        CHARACTER_START_INDEX.x * BLOCK_SIZE,
        CHARACTER_START_INDEX.y * BLOCK_SIZE,
    });
}

void Character::Update() {
    auto position = this->GetTransform().translation;
    glm::vec2 force = {0, 0};

    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        force = {force.x, force.y + 1};
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        force = {force.x, force.y - 1};
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        force = {force.x - 1, force.y};
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        force = {force.x + 1, force.y};
    }

    force = Normalize(force);
    glm::vec2 distance = {force.x * MOVE_NUMBER, force.y * MOVE_NUMBER};

    this->SetPosition(CheckMoveRange(position, distance));
}

glm::vec2 Character::Normalize(const glm::vec2 force) {
    if (force.x == 0 && force.y == 0) {
        return force;
    }

    float temp = sqrt(pow(force.x, 2) + pow(force.y, 2));
    return glm::vec2{force.x / temp, force.y / temp};
}

glm::vec2 Character::CheckMoveRange(glm::vec2 position, glm::vec2 distance) {
    glm::vec2 result = position + distance;
    glm::int64 top = MAP_START_INDEX.y * BLOCK_SIZE;
    glm::int64 bottom = (MAP_END_INDEX.y + 1) * BLOCK_SIZE;
    glm::int64 left = MAP_START_INDEX.x * BLOCK_SIZE;
    glm::int64 right = (MAP_END_INDEX.x - 1) * BLOCK_SIZE;

    if ((position + distance).y >= top) {
        LOG_DEBUG("top");
        result.y = position.y + (top - position.y);
    }

    if ((position + distance).y <= bottom) {
        LOG_DEBUG("bottom");
        result.y = position.y + (bottom - position.y);
    }

    if ((position + distance).x <= left) {
        result.x = position.x + (left - position.x);
        LOG_DEBUG("P {}, L {},  result {}", position.x, left, result.x);
    }

    if ((position + distance).x >= right) {
        result.x = position.x + (right - position.x);
        LOG_DEBUG("right");
    }

    return result;
}

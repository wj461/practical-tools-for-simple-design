#include "Character.hpp"
#include "Util/Animation.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "config.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

void Character::Start() {
    // this->SetDrawable(work_img);
    animations.push_back(AddIdle());
    animations.push_back(AddJump());
    animations.push_back(AddSitDown());
    animations.push_back(AddSit());
    animations.push_back(AddSitUp());
    animations.push_back(AddSleep());
    animations.push_back(AddBattle());
    animations.push_back(AddKega());
    this->SetDrawable(animations[Motion::IDLE]);

    this->SetPivotToLeftButton();
    this->SetZIndex(UI_Z);
    this->SetPosition({
        CHARACTER_START_INDEX.x * BLOCK_SIZE,
        CHARACTER_START_INDEX.y * BLOCK_SIZE,
    });
}

std::shared_ptr<Util::Animation> Character::AddIdle() {
    auto IDLE_SPRITES_PATH = CHAR_SPRITES_PATH + "idle/idel";
    return std::make_shared<Util::Animation>(
        std::vector<std::string>{
            IDLE_SPRITES_PATH + "1.png", IDLE_SPRITES_PATH + "2.png",
            IDLE_SPRITES_PATH + "3.png", IDLE_SPRITES_PATH + "4.png",
            IDLE_SPRITES_PATH + "5.png", IDLE_SPRITES_PATH + "6.png",
            IDLE_SPRITES_PATH + "7.png", IDLE_SPRITES_PATH + "8.png"},
        true, 100, true, 0);
}

std::shared_ptr<Util::Animation> Character::AddBattle() {
    auto IDLE_SPRITES_PATH = CHAR_SPRITES_PATH + "battle/battle";
    return std::make_shared<Util::Animation>(
        std::vector<std::string>{
            IDLE_SPRITES_PATH + "1.png", IDLE_SPRITES_PATH + "2.png",
            IDLE_SPRITES_PATH + "3.png", IDLE_SPRITES_PATH + "4.png",
            IDLE_SPRITES_PATH + "5.png", IDLE_SPRITES_PATH + "6.png",
            IDLE_SPRITES_PATH + "7.png", IDLE_SPRITES_PATH + "8.png",
            IDLE_SPRITES_PATH + "9.png", IDLE_SPRITES_PATH + "10.png",
            IDLE_SPRITES_PATH + "11.png", IDLE_SPRITES_PATH + "12.png"},
        true, 100, true, 0);
}

std::shared_ptr<Util::Animation> Character::AddSit() {
    auto IDLE_SPRITES_PATH = CHAR_SPRITES_PATH + "sit/sit";
    return std::make_shared<Util::Animation>(
        std::vector<std::string>{
            IDLE_SPRITES_PATH + "10.png", IDLE_SPRITES_PATH + "11.png",
            IDLE_SPRITES_PATH + "12.png", IDLE_SPRITES_PATH + "13.png",
            IDLE_SPRITES_PATH + "14.png", IDLE_SPRITES_PATH + "15.png"},
        true, 200, true, 0);
}

std::shared_ptr<Util::Animation> Character::AddSitDown() {
    auto IDLE_SPRITES_PATH = CHAR_SPRITES_PATH + "sit/down/sit";
    return std::make_shared<Util::Animation>(
        std::vector<std::string>{
            IDLE_SPRITES_PATH + "1.png", IDLE_SPRITES_PATH + "2.png",
            IDLE_SPRITES_PATH + "3.png", IDLE_SPRITES_PATH + "4.png",
            IDLE_SPRITES_PATH + "5.png", IDLE_SPRITES_PATH + "6.png",
            IDLE_SPRITES_PATH + "7.png", IDLE_SPRITES_PATH + "8.png",
            IDLE_SPRITES_PATH + "9.png"},
        true, 100, false, 0);
}

std::shared_ptr<Util::Animation> Character::AddSleep() {
    auto IDLE_SPRITES_PATH = CHAR_SPRITES_PATH + "sit/sleep/sleep";
    return std::make_shared<Util::Animation>(
        std::vector<std::string>{
            IDLE_SPRITES_PATH + "1.png", IDLE_SPRITES_PATH + "2.png",
            IDLE_SPRITES_PATH + "3.png", IDLE_SPRITES_PATH + "4.png",
            IDLE_SPRITES_PATH + "5.png", IDLE_SPRITES_PATH + "6.png",
            IDLE_SPRITES_PATH + "7.png", IDLE_SPRITES_PATH + "8.png",
            IDLE_SPRITES_PATH + "9.png", IDLE_SPRITES_PATH + "10.png",
            IDLE_SPRITES_PATH + "11.png"},
        true, 200, false, 0);
}

std::shared_ptr<Util::Animation> Character::AddJump() {
    auto IDLE_SPRITES_PATH = CHAR_SPRITES_PATH + "jump/jump";
    return std::make_shared<Util::Animation>(
        std::vector<std::string>{
            IDLE_SPRITES_PATH + "1.png", IDLE_SPRITES_PATH + "2.png",
            IDLE_SPRITES_PATH + "3.png", IDLE_SPRITES_PATH + "4.png"},
        true, 200, false, 0);
}

std::shared_ptr<Util::Animation> Character::AddSitUp() {
    auto IDLE_SPRITES_PATH = CHAR_SPRITES_PATH + "sit/up/sit";
    return std::make_shared<Util::Animation>(
        std::vector<std::string>{
            IDLE_SPRITES_PATH + "16.png", IDLE_SPRITES_PATH + "17.png",
            IDLE_SPRITES_PATH + "18.png", IDLE_SPRITES_PATH + "19.png"},
        true, 200, false, 0);
}
std::shared_ptr<Util::Animation> Character::AddKega() {
    auto IDLE_SPRITES_PATH = CHAR_SPRITES_PATH + "kega/kega";
    return std::make_shared<Util::Animation>(
        std::vector<std::string>{
            IDLE_SPRITES_PATH + "1.png", IDLE_SPRITES_PATH + "2.png",
            IDLE_SPRITES_PATH + "3.png", IDLE_SPRITES_PATH + "4.png"},
        true, 300, true, 0);
}

void Character::Update() {
    MoveFunction();

    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        this->SetDrawable(animations[Motion::BATTLE]);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        this->SetDrawable(animations[Motion::DAMAGE]);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::S)) {
        animations[Motion::SIT_SLEEP]->Reset();
        this->SetDrawable(animations[Motion::SIT_SLEEP]);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::D)) {
        this->SetDrawable(animations[Motion::SIT_DOWN]);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        this->SetDrawable(animations[Motion::SIT_UP]);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        animations[Motion::JUMP]->Play();
        this->SetDrawable(animations[Motion::JUMP]);
    }

    if (animations[Motion::SIT_DOWN]->GetState() ==
            Util::Animation::State::ENDED ||
        animations[Motion::SIT_SLEEP]->GetState() ==
            Util::Animation::State::ENDED) {
        this->SetDrawable(animations[Motion::SIT]);
        animations[Motion::SIT_DOWN]->Reset();
        animations[Motion::SIT_SLEEP]->Reset();
    }

    if (animations[Motion::SIT_UP]->GetState() ==
            Util::Animation::State::ENDED ||
        animations[Motion::JUMP]->GetState() == Util::Animation::State::ENDED) {
        this->SetDrawable(animations[Motion::IDLE]);
        animations[Motion::SIT_UP]->Reset();
        animations[Motion::JUMP]->Reset();
    }
}

void Character::MoveFunction() {
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
        result.y = position.y + (top - position.y);
    }

    if ((position + distance).y <= bottom) {
        result.y = position.y + (bottom - position.y);
    }

    if ((position + distance).x <= left) {
        result.x = position.x + (left - position.x);
    }

    if ((position + distance).x >= right) {
        result.x = position.x + (right - position.x);
    }

    return result;
}

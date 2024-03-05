#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "config.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

enum Motion {
    IDLE,
    IDLE_2,
    WALK_VERTICAL,
    WALK_HORIZONTAL,
    WALK_SLASH,
    JUMP,
    SIT,
    SIT_SLEEP,
    BATTLE,
    DAMAGE
};

class Character : public Util::GameObject {
public:
    void Start();

    void Update();

    glm::vec2 Normalize(const glm::vec2 force);

    glm::vec2 CheckMoveRange(glm::vec2 postion, glm::vec2 distance);

    void SetCharInitPosition(glm::vec2 indexPos) {
        CHARACTER_START_INDEX = indexPos;
    };

private:
    void MoveFunction();

    glm::int64 MOVE_NUMBER = 8;

    glm::vec2 CHARACTER_START_INDEX = {-8, 6};

    std::shared_ptr<Util::Image> work_img =
        std::make_shared<Util::Image>("../assets/sprites/ch.png");

    std::vector<std::shared_ptr<Util::Animation>> animations;

    glm::vec2 MAP_START_INDEX = {floor(MAP_START_POS.x / BLOCK_SIZE) + 1,
                                 floor(MAP_START_POS.y / BLOCK_SIZE) - 1};

    glm::vec2 MAP_END_INDEX = {MAP_START_INDEX.x + MAP_SIZE.x,
                               MAP_START_INDEX.y - MAP_SIZE.y};
};

#endif

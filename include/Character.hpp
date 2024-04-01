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
    // IDLE_2,
    // WALK_VERTICAL,
    // WALK_HORIZONTAL,
    // WALK_SLASH,
    JUMP,
    SIT_DOWN,
    SIT,
    SIT_UP,
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

    std::shared_ptr<Util::Animation> AddIdle();
    std::shared_ptr<Util::Animation> AddBattle();
    std::shared_ptr<Util::Animation> AddKega();
    std::shared_ptr<Util::Animation> AddSitDown();
    std::shared_ptr<Util::Animation> AddSit();
    std::shared_ptr<Util::Animation> AddSitUp();
    std::shared_ptr<Util::Animation> AddSleep();
    std::shared_ptr<Util::Animation> AddJump();

private:
    void MoveFunction();

    glm::int64 MOVE_NUMBER = 8;

    glm::vec2 CHARACTER_START_INDEX = {-8, 6};

    std::vector<std::shared_ptr<Util::Animation>> animations;

    glm::vec2 MAP_START_INDEX = {floor(MAP_START_POS.x / BLOCK_SIZE) + 1,
                                 floor(MAP_START_POS.y / BLOCK_SIZE) - 1};

    glm::vec2 MAP_END_INDEX = {MAP_START_INDEX.x + MAP_SIZE.x,
                               MAP_START_INDEX.y - MAP_SIZE.y};

    std::string CHAR_SPRITES_PATH = "../assets/sprites/Character/ani/";
};

#endif

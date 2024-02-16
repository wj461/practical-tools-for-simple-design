#include "map.hpp"
#include "Block.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "config.hpp"
#include <cmath>
#include <glm/fwd.hpp>
#include <memory>
#include <spdlog/spdlog.h>
#include <vector>

void Map::Start() {
    for (glm::int64 i = 0; i < WINDOW_HEIGHT/16; i++){
        std::vector<int> tempVector;
        for (glm::int64 j = 0; j < WINDOW_WIDTH/16; j++){
            tempVector.push_back(0);
        }
        map.push_back(tempVector);
    }
}

void Map::Update() {
    auto mousePosition = Util::Input::GetCursorPosition();
    glm::vec2 index {mousePosition.x/block_size, mousePosition.y/block_size};

    if (Util::Input::IsLButtonEdge()){
        NewBlock(index);
    }
}

void Map::NewBlock(glm::vec2 index){
    LOG_DEBUG("index {}, {}",index.x, index.y);
    glm::vec2 translation {
    floor(index.x) * block_size,
    floor(index.y) * block_size};
    LOG_DEBUG("index floor {}, {}",translation.x, translation.y);

    auto block = std::make_shared<Block>(translation);
    block->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/block.png"));
    block->SetZIndex(6);
    this->AddChild(block);
}
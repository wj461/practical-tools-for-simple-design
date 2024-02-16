#include "map.hpp"
#include "Block.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <spdlog/spdlog.h>

void Map::Start() {

}

void Map::Update() {
    auto mousePosition = Util::Input::GetCursorPosition();

    if (Util::Input::IsLButtonEdge()){
        LOG_DEBUG("mouseP {}, {}",mousePosition.x, mousePosition.y);
        auto block = std::make_shared<Block>(mousePosition);
        block->SetDrawable(
            std::make_shared<Util::Image>("../assets/sprites/block.png"));
        block->SetZIndex(6);
        this->AddChild(block);
        // block->Draw();
    }
}
#include "map.hpp"
#include "Block.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "config.hpp"
#include <cmath>
#include <glm/detail/qualifier.hpp>
#include <glm/fwd.hpp>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

void Map::Start() {
    LOG_DEBUG("MAP START INDEX {} {}", MAP_START_INDEX.x, MAP_START_INDEX.y);
    LOG_DEBUG("MAP END INDEX {} {}", MAP_END_INDEX.x, MAP_END_INDEX.y);

    for (glm::int64 y = 0; y < MAP_SIZE.y; y++){
        std::vector<glm::int64> tempVector;
        for (glm::int64 x = 0; x < MAP_SIZE.x; x++){
            tempVector.push_back(0);

            glm::vec2 index_pos = {MAP_START_INDEX.x+x ,MAP_START_INDEX.y-y };
            NewBlock(index_pos, 0);
        }
        map.push_back(tempVector);
    }
    LoadMaterial();
}

void Map::Update() {
    auto mouse_position = Util::Input::GetCursorPosition();
    glm::vec2 index_pos {floor(mouse_position.x/BLOCK_SIZE), floor(mouse_position.y/BLOCK_SIZE)};
    int index_map = 1;


    // edit map
    if (Util::Input::IsLButtonEdge() && IsDrawRange(index_pos)){
        NewBlock(index_pos, index_map);
        // map[index_pos.y][index_pos.x] = index_map;
    }

    if (Util::Input::IsLButtonEdge()){
        LOG_DEBUG("mousePos {}, {}", mouse_position.x, mouse_position.y);
        LOG_DEBUG("indexPos {}, {}", index_pos.x, index_pos.y);
        LOG_DEBUG("indexMap {}", index_map);
    }
}

void Map::LoadMaterial(){
    for (unsigned long i = 0; i < material_path.size(); ++i){
        glm::vec2 material_position = {
        LEFT_TOP_POS.x + ((i % MATERIAL_COL_NUM) * BLOCK_SIZE),
        LEFT_TOP_POS.y - (glm::int64(i / MATERIAL_COL_NUM) * BLOCK_SIZE),
        };

        glm::vec2 index_pos {floor(material_position.x/BLOCK_SIZE) +1 , floor(material_position.y/BLOCK_SIZE) - 1};
        NewBlock(index_pos, i);
    }
}

void Map::NewBlock(glm::vec2 indexPos, int indexMap){
    std::string path = "../assets/sprites/" + material_path[indexMap];
    glm::vec2 translation {
    ((floor(indexPos.x) * BLOCK_SIZE)+(float(BLOCK_SIZE)/2)),
    ((floor(indexPos.y) * BLOCK_SIZE)+(float(BLOCK_SIZE)/2))};


    auto block = std::make_shared<Block>(translation);
    block->SetDrawable(
        std::make_shared<Util::Image>(path));
    block->SetZIndex(MAP_Z);
    this->AddChild(block);
}

bool Map::IsDrawRange(glm::vec2 indexPos){
    if (indexPos.x >= MAP_START_INDEX.x &&
    indexPos.x < MAP_END_INDEX.x &&
    indexPos.y <= MAP_START_INDEX.y &&
    indexPos.y > MAP_END_INDEX.y){
        return true;
    }

    return false;
}
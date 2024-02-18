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
#include <unistd.h>
#include <vector>

void Map::Start() {
    LoadMaterial();
    LoadChooseEventFocus();
    LoadChooseToolFocus();
    LoadChooseMaterialFocus();
    LoadEmptyMap();
    LoadToolImage();
}

void Map::Update() {
    auto mouse_position = Util::Input::GetCursorPosition();
    glm::vec2 index_pos {floor(mouse_position.x/BLOCK_SIZE), floor(mouse_position.y/BLOCK_SIZE)};

    //Tool select
    if (Util::Input::IsLButtonEdge()) {
        current_tool = ChooseTool(index_pos);
        LOG_DEBUG("index pos {},{}", index_pos.x, index_pos.y);
    }

    switch (current_tool) {
    case Edit:
        // edit map
        if (Util::Input::IsLButtonDown() && IsEditRange(index_pos)){
            ChangeBlockMaterial(index_pos, current_material_index);
        }
        // chang target material
        else if (Util::Input::IsLButtonEdge()){
            current_material_index = ChooseMaterial(index_pos);
        }
        break;
    case Event:
        if (Util::Input::IsLButtonEdge() && IsEditRange(index_pos)){
            current_event = ChooseEventBlock(index_pos);
        }
        break;
    }

}

void Map::LoadEmptyMap(){
    for (glm::int64 y = 0; y < MAP_SIZE.y; y++){
        std::vector<std::shared_ptr<Block>> tempVector;
        for (glm::int64 x = 0; x < MAP_SIZE.x; x++){
            glm::vec2 index_pos = {MAP_START_INDEX.x+x ,MAP_START_INDEX.y-y };
            tempVector.push_back(NewBlock(index_pos, 0, BlockType::Map_Block));
        }
        map.push_back(tempVector);
    }
}

void Map::LoadMaterial(){
    for (unsigned long i = 0; i < material_path.size(); ++i){
        glm::vec2 material_position = {
        LEFT_TOP_POS.x + ((i % MATERIAL_COL_NUM) * BLOCK_SIZE),
        LEFT_TOP_POS.y - (glm::int64(i / MATERIAL_COL_NUM) * BLOCK_SIZE),
        };

        glm::vec2 index_pos {floor(material_position.x/BLOCK_SIZE) +1 , floor(material_position.y/BLOCK_SIZE) - 1};
        std::string path = "../assets/sprites/" + material_path[i];
        material_image.push_back(std::make_shared<Util::Image>(path));
        NewBlock(index_pos, i, BlockType::Material);
    }
}

void Map::LoadChooseMaterialFocus(){
    auto img = std::make_shared<Util::Image>("../assets/sprites/focus.png");
    material_focus = NewBlock(MATERIAL_START_INDEX, 0, BlockType::Focus, UI_Z, img );
}

void Map::LoadChooseEventFocus(){
    auto img = std::make_shared<Util::Image>("../assets/sprites/current_event.png");
    event_focus = NewBlock(MAP_START_INDEX, 0, BlockType::Focus, UI_Z, img);
    event_focus->SetVisible(false);
}

void Map::LoadChooseToolFocus(){
    auto img = std::make_shared<Util::Image>("../assets/sprites/current_event.png");
    tool_focus = NewBlock(TOOL_START_INDEX, 0, BlockType::Focus, UI_Z, img);
}

void Map::LoadToolImage(){
    std::vector<std::string> tool_img_names = {
    "pan.png","mouse.png"
    };

    for (unsigned long i = 0; i < tool_img_names.size(); ++i){
        auto icon_path = "../assets/sprites/" + tool_img_names[i];
        auto tool_icon =
            std::make_shared<Util::Image>(icon_path);

        auto tool_block = NewBlock(
        {TOOL_START_INDEX.x + i, TOOL_START_INDEX.y},
        0, BlockType::ToolIcon,
        MAP_Z, tool_icon);
        tools.push_back(tool_block);
    }
}

std::shared_ptr<Block> Map::NewBlock(glm::vec2 indexPos, int indexMap, BlockType type, glm::int64 indexZ, std::shared_ptr<Util::Image> img){
    auto block = std::make_shared<Block>();

    if (img != nullptr){
        block->SetDrawable(img);
    }
    else {
        block->SetDrawable(material_image[indexMap]);
    }

    block->SetIndexPostion(indexPos);
    block->SetPivot(BLOCK_PIVOT);
    block->SetZIndex(indexZ);
    block->SetBlockType(type);

    this->AddChild(block);

    return block;
}

bool Map::IsEditRange(glm::vec2 indexPos){
    if (indexPos.x >= MAP_START_INDEX.x &&
    indexPos.x < MAP_END_INDEX.x &&
    indexPos.y <= MAP_START_INDEX.y &&
    indexPos.y > MAP_END_INDEX.y){
        return true;
    }

    return false;
}

std::shared_ptr<Block> Map::FindMapBlockByIndex(glm::vec2 indexPos){
    for (std::vector<std::shared_ptr<Block>> blocks : map ){
        for (std::shared_ptr<Block> block : blocks ){
            if (block->GetIndexPostion() == indexPos){
                return block;
            }
        }
    }
    return nullptr;
}

glm::int64 Map::ChooseMaterial(glm::vec2 indexPos){
    if (glm::int64(indexPos.x - MATERIAL_START_INDEX.x) >= MATERIAL_COL_NUM){
        return current_material_index;
    }

    glm::int64 material_index = 
    (glm::int64(indexPos.x) - MATERIAL_START_INDEX.x) +
    (MATERIAL_COL_NUM * (MATERIAL_START_INDEX.y - (glm::int64(indexPos.y))));

    if (material_index >= glm::int64(material_path.size())){
        return current_material_index;
    }

    material_focus->SetIndexPostion(indexPos);

    return material_index;
}

void Map::ChangeBlockMaterial(glm::vec2 indexPos, int indexMap){
    std::shared_ptr<Block> block = FindMapBlockByIndex(indexPos);
    block->SetIndexMaterial(indexMap, material_image[indexMap]);
}

std::shared_ptr<Block> Map::ChooseEventBlock(glm::vec2 indexPos){
    std::shared_ptr<Block> block = FindMapBlockByIndex(indexPos);

    event_focus->SetIndexPostion(indexPos);

    return block;
}

Tool Map::ChooseTool(glm::vec2 indexPos){
    if (indexPos == TOOL_START_INDEX){
        event_focus->SetVisible(false);
        tool_focus->SetIndexPostion(indexPos);
        return Tool::Edit;
    }
    if (indexPos.x == TOOL_START_INDEX.x +1 && indexPos.y == TOOL_START_INDEX.y){
        event_focus->SetVisible(true);
        tool_focus->SetIndexPostion(indexPos);
        return Tool::Event;
    }

    return  current_tool;
}
#include "map.hpp"
#include "Block.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "WithTextButton.hpp"
#include "config.hpp"
#include <cmath>
#include <ctime>
#include <glm/detail/qualifier.hpp>
#include <glm/fwd.hpp>
#include <memory>
#include <spdlog/details/os.h>
#include <spdlog/fmt/bundled/core.h>
#include <spdlog/spdlog.h>
#include <string>
#include <unistd.h>
#include <vector>

void Map::Start() {
    LoadMaterial();
    LoadChooseEventFocus();
    LoadChooseToolFocus();
    LoadChooseMaterialFocus();
    LoadPageFocus();
    LoadEmptyMap();
    LoadToolImage();
    LoadPageIcon();
}

void Map::Update() {
    auto mouse_position = Util::Input::GetCursorPosition();
    glm::vec2 index_pos {floor(mouse_position.x/BLOCK_SIZE), floor(mouse_position.y/BLOCK_SIZE)};

    //Tool select
    if (Util::Input::IsLButtonEdge()) {
        current_tool = ChooseTool(index_pos);
        current_page_index = ChoosePage(index_pos);
        VisibleCurrentPageMaterial(current_page_index);
        // LOG_DEBUG("index pos {},{}", index_pos.x, index_pos.y);
    }

    switch (current_tool) {
    case Edit:
        // edit map
        if (Util::Input::IsLButtonDown() && IsEditRange(index_pos)){
            ChangeBlockMaterial(index_pos, current_material_index.y);
        }
        // chang target material
        else if (Util::Input::IsLButtonEdge()){
            current_material_index = ChooseMaterial(index_pos, current_page_index);
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
            auto block = NewBlock(index_pos, {0, 0}, BlockType::Map_Block);
            for (unsigned long i = 0; i< material_path.size(); ++i){
                block->CreatNewZBlock();
            }
            block->SetIndexMaterial({0,1}, material_image[0][1]);
            tempVector.push_back(block);
        }
        map.push_back(tempVector);
    }
}

void Map::LoadMaterial(){
    for (unsigned long i = 0; i < material_path.size(); ++i){
        std::vector<std::shared_ptr<Block>> temp;
        std::vector<std::shared_ptr<Util::Image>> temp_img;
        material_image.push_back(temp_img);
        for (unsigned long j = 0; j< material_path[i].size(); ++j){
            glm::vec2 material_position = {
            LEFT_TOP_POS.x + ((j % MATERIAL_COL_NUM) * BLOCK_SIZE),
            LEFT_TOP_POS.y - (glm::int64(j / MATERIAL_COL_NUM) * BLOCK_SIZE),
            };

            glm::vec2 index_pos {floor(material_position.x/BLOCK_SIZE) +1 , floor(material_position.y/BLOCK_SIZE) - 1};
            std::string path = SPRITES_PATH + material_path[i][j].path;
            auto img = std::make_shared<Util::Image>(path);
            temp_img.push_back(img);
            material_image[i] = temp_img;

            auto block = NewBlock(index_pos, {i,j}, BlockType::Material);
            block->SetStand(material_path[i][j].stand);
            temp.push_back(block);
        }
        material_map.push_back(temp);
    }
    VisibleCurrentPageMaterial(0);
}

void Map::LoadChooseMaterialFocus(){
    auto path = SPRITES_PATH + "focus.png";
    auto img = std::make_shared<Util::Image>(path);
    material_focus = NewBlock(MATERIAL_START_INDEX, {0 ,0}, BlockType::Focus, FOCUS_Z, img );
}

void Map::LoadChooseEventFocus(){
    auto path = SPRITES_PATH + "current_event.png";
    auto img = std::make_shared<Util::Image>(path);
    event_focus = NewBlock(MAP_START_INDEX, {0, 0}, BlockType::Focus, FOCUS_Z, img);
    event_focus->SetVisible(false);
}

void Map::LoadChooseToolFocus(){
    auto path = SPRITES_PATH + "current_event.png";
    auto img = std::make_shared<Util::Image>(path);
    tool_focus = NewBlock(TOOL_START_INDEX, {0, 0}, BlockType::Focus, FOCUS_Z, img);
}

void Map::LoadPageFocus(){
    auto path = SPRITES_PATH + "focus24.png";
    auto img = std::make_shared<Util::Image>(path);
    page_focus = NewBlock(MATERIAL_PAGE_START_INDEX, {0, 0}, BlockType::Focus, FOCUS_Z, img);
}

void Map::LoadPageIcon(){
    for (unsigned long i = 0; i<material_image.size(); ++i){
        auto text = std::to_string(i + 1);
        pages.push_back(NewTextButton(
        {MATERIAL_PAGE_START_INDEX.x + i, MATERIAL_PAGE_START_INDEX.y}, 
        text));
    }
}

void Map::LoadToolImage(){
    std::vector<std::string> tool_img_names = {
    "pan.png","mouse.png"
    };

    for (unsigned long i = 0; i < tool_img_names.size(); ++i){
        auto icon_path = SPRITES_PATH + tool_img_names[i];
        std::shared_ptr<Util::Image> tool_icon =
            std::make_shared<Util::Image>(icon_path);

        auto tool_block = NewBlock(
        {TOOL_START_INDEX.x + i, TOOL_START_INDEX.y},
        {0, 0}, BlockType::ToolIcon,
        MAP_Z, tool_icon);
        tools.push_back(tool_block);
    }
}

std::shared_ptr<Block> Map::NewBlock(glm::vec2 indexPos, glm::vec2 indexMap, BlockType type, glm::int64 indexZ, std::shared_ptr<Util::Image> img){
    auto block = std::make_shared<Block>();

    if (img != nullptr){
        block->SetDrawable(img);
    }
    else {
        block->SetDrawable(material_image[indexMap.x][indexMap.y]);
    }

    block->SetIndexPostion(indexPos);
    block->SetPivotToLeftTop();
    block->SetZIndex(indexZ);
    block->SetBlockType(type);

    this->AddChild(block);

    return block;
}

std::shared_ptr<WithTextButton> Map::NewTextButton(glm::vec2 indexPos, std::string text) {
    auto block = std::make_shared<WithTextButton>();
    auto path = SPRITES_PATH + "page2.png";
    auto button_bg = std::make_shared<Util::Image>(path);


    block->SetDrawable(button_bg);

    block->SetIndexPostion(indexPos);
    block->SetPivotToLeftTop();
    block->SetZIndex(UI_Z);
    block->SetBlockType(BlockType::ToolIcon);

    block->Init("../assets/fonts/Inter.ttf", 20);
    block->SetTextPostionToCenter();
    block->SetText(text);

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

glm::vec2 Map::ChooseMaterial(glm::vec2 indexPos, glm::int64 currentPage){
    //width
    if (glm::int64(indexPos.x - MATERIAL_START_INDEX.x) >= MATERIAL_COL_NUM){
        return current_material_index;
    }

    glm::int64 material_index = 
    (glm::int64(indexPos.x) - MATERIAL_START_INDEX.x) +
    (MATERIAL_COL_NUM * (MATERIAL_START_INDEX.y - (glm::int64(indexPos.y))));

    if (material_index >= glm::int64(material_path[currentPage].size()) ||
    material_index < 0){
        return current_material_index;
    }

    material_focus->SetIndexPostion(indexPos);

    return {currentPage, material_index};
}

void Map::ChangeBlockMaterial(glm::vec2 indexPos, int indexMap){
    std::shared_ptr<Block> block = FindMapBlockByIndex(indexPos);
    block->SetIndexMaterial({current_page_index,indexMap},
    material_image[current_page_index][indexMap], 
    material_map[current_page_index][indexMap]->GetStand());
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

glm::int64 Map::ChoosePage(glm::vec2 indexPos){
    glm::int64 index = indexPos.x-MATERIAL_PAGE_START_INDEX.x;

    if (index < glm::int64(material_path.size()) && indexPos.y == MATERIAL_PAGE_START_INDEX.y){
        page_focus->SetIndexPostion(indexPos);
        current_material_index = ChooseMaterial(MATERIAL_START_INDEX, index);
        return index;
    }

    return current_page_index;
}

void Map::VisibleCurrentPageMaterial(glm::int64 currentPage){
    for (auto page : material_map){
        for(auto material : page){
            material->SetVisible(false);
        }
    }

    auto current_page = material_map[currentPage];
    for(auto material : current_page){
        material->SetVisible(true);
    }
}

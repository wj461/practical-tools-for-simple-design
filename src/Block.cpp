#include "Block.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "config.hpp"
#include <glm/fwd.hpp>
#include <memory>


void Block::SetIndexMaterial(glm::vec2 index, std::shared_ptr<Util::Image> material, bool canStand){
    index_material[index.x] = index.y;
    stand = canStand;

    zBlock[index.x]->SetDrawable(material);
}

void Block::SetIndexPostion(glm::vec2 indexPos) {
    glm::vec2 translation {
    (indexPos.x * BLOCK_SIZE),
    (indexPos.y * BLOCK_SIZE)};

    index_pos = indexPos;
    this->SetPosition(translation);
}

void Block::CreatNewZBlock(){
    glm::vec2 translation {
    (index_pos.x * BLOCK_SIZE),
    (index_pos.y * BLOCK_SIZE)};

    auto block =  std::make_shared<Util::GameObject>();
    block->SetDrawable(std::make_shared<Util::Image>("../assets/sprites/Blank.png"));
    block->SetPosition(translation);
    block->SetPivotToLeftTop();
    block->SetZIndex(MAP_Z + zBlock.size()+1);
    zBlock.push_back(block);
    this->AddChild(block);

    index_material.push_back(0);
}
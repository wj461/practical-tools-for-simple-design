#include "Block.hpp"
#include "Util/Image.hpp"
#include "config.hpp"
#include <glm/fwd.hpp>
#include <memory>

void Block::SetIndexMaterial(glm::int64 index, std::shared_ptr<Util::Image> material){
    index_material = index;

    this->SetDrawable(material);
}

void Block::SetIndexPostion(glm::vec2 indexPos) {
    glm::vec2 translation {
    (indexPos.x * BLOCK_SIZE),
    (indexPos.y * BLOCK_SIZE)};

    index_pos = indexPos;
    this->SetPosition(translation);
}
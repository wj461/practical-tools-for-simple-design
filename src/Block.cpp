#include "Block.hpp"
#include "Util/Image.hpp"
#include <glm/fwd.hpp>

void Block::SetIndexMaterial(glm::int64 index, std::string fileName){
    index_material = index;

    std::string path = "../assets/sprites/" + fileName;
    this->SetDrawable(
        std::make_shared<Util::Image>(path));
}
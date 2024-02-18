#include "Block.hpp"
#include "Util/Image.hpp"
#include <glm/fwd.hpp>
#include <memory>

void Block::SetIndexMaterial(glm::int64 index, std::shared_ptr<Util::Image> material){
    index_material = index;

    this->SetDrawable(material);
}
#include "Block.hpp"
#include <glm/fwd.hpp>


Block::Block(glm::vec2 position){
    auto &pos = m_Transform.translation;
    pos = position;
}

void Block::SetPostion(glm::vec2 position){
    auto &pos = m_Transform.translation;
    pos = position;
}
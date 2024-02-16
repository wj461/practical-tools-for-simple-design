#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Util/GameObject.hpp"

class Block : public Util::GameObject {

public:
    Block(glm::vec2 position);

    void Update();

    void Start();

    void SetPostion(glm::vec2 position);
};

#endif
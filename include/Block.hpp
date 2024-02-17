#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Util/GameObject.hpp"
#include <glm/fwd.hpp>

class Block : public Util::GameObject {

public:
    void Update();

    void Start();

    glm::vec2 GetIndexPostion() { return index_pos;}
    int GetIndexMaterial() { return index_material;}

    void SetIndexPostion(glm::vec2 index) { index_pos = index; }

    void SetIndexMaterial(glm::int64 index, std::string fileName);

private:
    glm::vec2 index_pos = {0,0};
    glm::int64 index_material = 0;
};


#endif
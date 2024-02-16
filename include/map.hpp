#ifndef MAP_HPP
#define MAP_HPP

#include "Util/GameObject.hpp"
#include <vector>

class Map : public Util::GameObject {

public:
    void Update();

    void Start();

    void NewBlock(glm::vec2 mousePosition);

private:
    std::vector<std::vector<int>> map;

    glm::int64 block_size = 16;

};
#endif
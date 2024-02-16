#ifndef MAP_HPP
#define MAP_HPP

#include "Util/GameObject.hpp"

class Map : public Util::GameObject {

public:
    void Update();

    void Start();

private:
    std::shared_ptr<glm::vec2> map;

    // const glm::int64 map_size = 16;

};
#endif
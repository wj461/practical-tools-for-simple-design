#ifndef MAP_HPP
#define MAP_HPP

#include "Util/GameObject.hpp"
#include "config.hpp"
#include <glm/fwd.hpp>
#include <vector>

class Map : public Util::GameObject {

public:
    void Update();

    void Start();
private:

    void LoadMaterial();

    void LoadEmptyMap();

    void NewBlock(glm::vec2 indexPos, int indexMap);

    bool IsDrawRange(glm::vec2 indexPos);

    glm::vec2 ChooseMaterial(glm::vec2 indexPos);

    std::vector<std::vector<glm::int64>> map, material_map;
    std::vector<std::string> material_path = 
    {
    "empty48.png","block48.png","block48R.png",
    };

    glm::int64 BLOCK_SIZE = 48;
    glm::int64 MATERIAL_COL_NUM = 4;
    glm::vec2 MAP_SIZE = {10, 10};

    glm::vec2 LEFT_TOP_POS = {
        glm::int64(WINDOW_WIDTH/2) * (-1),
        (WINDOW_HEIGHT/2) };


    glm::vec2 MAP_START_POS ={
        (LEFT_TOP_POS.x)+240,
        (WINDOW_HEIGHT/2) };

    glm::vec2 MAP_START_INDEX = {
    floor(MAP_START_POS.x/BLOCK_SIZE) +1,
    floor(MAP_START_POS.y/BLOCK_SIZE) -1
    };

    glm::vec2 MAP_END_INDEX = {
    MAP_START_INDEX.x+MAP_SIZE.x,
    MAP_START_INDEX.y-MAP_SIZE.y
    };

};

#endif
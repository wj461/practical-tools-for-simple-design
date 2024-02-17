#ifndef MAP_HPP
#define MAP_HPP

#include "Block.hpp"
#include "Util/GameObject.hpp"
#include "config.hpp"
#include <glm/fwd.hpp>
#include <memory>
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

    glm::int64 ChooseMaterial(glm::vec2 indexPos);

    std::shared_ptr<Util::GameObject> material_focus = 
    std::make_shared<Util::GameObject>();

    glm::int64 index_map = 1;

    std::vector<std::vector<glm::int64>> map, material_map;

    std::vector<std::string> material_path = 
    {
    "empty48.png","block48.png","block48R.png",
    "block48.png","block48R.png",
    "block48.png","block48R.png"
    };

    glm::int64 BLOCK_SIZE = 48;
    glm::int64 MATERIAL_COL_NUM = 4;
    glm::vec2 MAP_SIZE = {20, 10};

    glm::vec2 LEFT_TOP_POS = {
        glm::int64(WINDOW_WIDTH/2) * (-1),
        glm::int64(WINDOW_HEIGHT/2) };

    glm::vec2 MATERIAL_START_INDEX = {
        glm::int64(LEFT_TOP_POS.x/BLOCK_SIZE),
        glm::int64(LEFT_TOP_POS.y/BLOCK_SIZE) -1
    };

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
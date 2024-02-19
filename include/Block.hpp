#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Event.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

enum BlockType {
    Map_Block,
    Material,
    ToolIcon,
    Focus
};

class Block : public Util::GameObject {

public:
    void Update();

    void Start();

    void CreatNewZBlock();


    glm::vec2 GetIndexPostion() { return index_pos;}

    // int GetIndexMaterial() { return index_material;}

    bool GetStand() { return stand; }


    void SetIndexPostion(glm::vec2 index);

    void SetIndexMaterial(glm::vec2 index, std::shared_ptr<Util::Image> material, bool canStand = true);

    void SetStand(bool canStand) { stand = canStand; }

    void SetBlockType(BlockType type) { block_type = type; }

private:
    std::vector<std::shared_ptr<BlockEvent>> event;

    std::vector<std::shared_ptr<Util::GameObject>> zBlock;
    std::vector<glm::int64> index_material;

    glm::vec2 index_pos = {0,0};

    bool stand = true;

    BlockType block_type;
};


#endif
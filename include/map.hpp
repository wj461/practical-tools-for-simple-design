#ifndef MAP_HPP
#define MAP_HPP

#include "Block.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "WithTextButton.hpp"
#include "config.hpp"
#include <cstddef>
#include <glm/fwd.hpp>
#include <memory>
#include <vector>

enum Tool {
    Edit,
    Event
};

class Map : public Util::GameObject {

public:
    void Update();

    void Start();
private:

    // init map
    void LoadMaterial();

    void LoadEmptyMap();

    void LoadChooseMaterialFocus();

    void LoadChooseEventFocus();
    
    void LoadToolImage();

    void LoadChooseToolFocus();

    void LoadPageIcon();

    void LoadPageFocus();

    std::shared_ptr<Block> NewBlock(glm::vec2 indexPos, glm::vec2 indexMap = {0, 0}, BlockType type = BlockType::Map_Block, glm::int64 indexZ = MAP_Z, std::shared_ptr<Util::Image> img = nullptr);

    std::shared_ptr<WithTextButton> NewTextButton(glm::vec2 indexPos, std::string text);
    //tool
    Tool ChooseTool(glm::vec2 indexPos);

    glm::int64 ChoosePage(glm::vec2 indexPos);

    void VisibleCurrentPageMaterial(glm::int64 currentPage);

    //edit map material
    glm::vec2 ChooseMaterial(glm::vec2 indexPos, glm::int64 currentPage);

    void ChangeBlockMaterial(glm::vec2 indexPos, int indexMap);

    //event
    std::shared_ptr<Block> ChooseEventBlock(glm::vec2 indexPos);

    //
    bool IsEditRange(glm::vec2 indexPos);

    std::shared_ptr<Block> FindMapBlockByIndex(glm::vec2 indexPos);

    std::shared_ptr<Util::GameObject> test = std::make_shared<Util::GameObject>();
    // focus
    std::shared_ptr<Block> material_focus, event_focus, tool_focus, page_focus;

    std::vector<std::shared_ptr<Block>> tools;
    std::vector<std::shared_ptr<WithTextButton>> pages;

    // focus
    Tool current_tool = Tool::Edit;
    glm::vec2 current_material_index = {0, 0};
    glm::int64 current_page_index = 0;
    std::shared_ptr<Block> current_event;


    std::vector<std::vector<std::shared_ptr<Block>>> map, material_map;

    std::vector<std::vector<std::shared_ptr<Util::Image>>> material_image;


    // can set
    std::vector<std::vector<std::string>> material_path = {
    { "Blank.png","empty48.png","block48.png","block48R.png", "blockHG.png" },
    { "Blank.png","empty48.png","block48R.png", "blockHG.png", "block24P.png" },
    { "Blank.png","empty48.png","block24P.png", "blockHG.png" }};

    // can set
    glm::vec2 LEFT_TOP_POS = {
        glm::int64(WINDOW_WIDTH/2) * (-1),
        glm::int64(WINDOW_HEIGHT/2) };

    glm::vec2 MATERIAL_START_INDEX = {
        glm::int64(LEFT_TOP_POS.x/BLOCK_SIZE),
        glm::int64(LEFT_TOP_POS.y/BLOCK_SIZE) -1
    };

    // can set
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

    glm::vec2 TOOL_START_INDEX = {-13, -7};

    glm::vec2 MATERIAL_PAGE_START_INDEX = {-13, -6};

};

#endif
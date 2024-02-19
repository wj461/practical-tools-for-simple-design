#ifndef CONFIG_H
#define CONFIG_H

#include "pch.hpp" // IWYU pragma: export

#include "Util/Logger.hpp"
#include <glm/fwd.hpp>

constexpr const char *TITLE = "Practical Tools for Simple Design";

constexpr int WINDOW_POS_X = SDL_WINDOWPOS_UNDEFINED;
constexpr int WINDOW_POS_Y = SDL_WINDOWPOS_UNDEFINED;

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;

constexpr unsigned int UI_Z = 6;
constexpr unsigned int FOCUS_Z = 100;
constexpr unsigned int MAP_Z = 5;
constexpr unsigned int BG_Z = 4;

constexpr int BLOCK_SIZE = 48;
constexpr glm::vec2 MAP_SIZE = {20, 10};
constexpr int MATERIAL_COL_NUM = 4;
constexpr glm::vec2 BLOCK_PIVOT ={
        (BLOCK_SIZE/2) * (-1),
        (BLOCK_SIZE/2) * (-1)};

constexpr Util::Logger::Level DEFAULT_LOG_LEVEL = Util::Logger::Level::DEBUG;

#endif

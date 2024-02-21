#ifndef TALKTEXT_HPP
#define TALKTEXT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Text.hpp"
#include <memory>
#include <string>

class TalkText : public Util::GameObject{
public:
    TalkText() = default;

    TalkText(std::string font, const int size)
        : m_Font(std::move(font)),
          m_Size(size) {}

    void Update();

    void Start();

    void SetText(std::string inputText);

    void SetTextNow(std::string inputText);
private:
    std::string SPRITES_PATH = "../assets/sprites/";


    std::string text = "";
    std::string currentText = " ";

    std::shared_ptr<Util::Text> m_Text;
    std::shared_ptr<Util::GameObject> bg = std::make_shared<Util::GameObject>();
    std::shared_ptr<Util::GameObject> character = std::make_shared<Util::GameObject>();

    std::string m_Font;
    int m_Size;

    glm::vec2 TALK_START_POINT = {-8, -3};
};
#endif
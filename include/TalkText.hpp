#ifndef TALKTEXT_HPP
#define TALKTEXT_HPP

#include "Util/GameObject.hpp"
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
private:
    std::string text = "";
    std::string currentText = " ";

    std::shared_ptr<Util::Text> m_Text;

    std::string m_Font;
    int m_Size;

};
#endif
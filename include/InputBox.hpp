#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include "Util/GameObject.hpp"
#include "Util/Keycode.hpp"
#include "Util/Text.hpp"
#include <string>
class InputBox : public Util::GameObject {
public:
    InputBox() = default;

    InputBox(std::string font, const int size)
        : m_Font(std::move(font)),
          m_Size(size) {}

    void Start();

    void Update();

    std::string ConvertKeycodeToString(Util::Keycode key);

private:
    std::shared_ptr<Util::Text> m_Text;
    std::string current_text = " ";

    std::string m_Font;
    int m_Size;

    bool enable = true;
};

#endif

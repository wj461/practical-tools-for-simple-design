
#include "InputBox.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <asm-generic/errno.h>
#include <glm/fwd.hpp>
#include <locale>
#include <spdlog/fmt/bundled/format.h>
#include <string>
void InputBox::Start() {
    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, " aaa\na",
                                          Util::Color::FromRGB(255, 255, 255));
    current_text = m_Text->GetText();
    SetDrawable(m_Text);
}

void InputBox::Update() {
    if (Util::Input::IsKeyDown(Util::Keycode::CAPSLOCK)) {
        capsLock = !capsLock;
    }

    if (enable) {
        auto current_key = Util::Input::GetCurrentKeycode();
        if (current_key != Util::Keycode::UNKNOWN) {
            auto nowKey = ConvertKeycodeToString(current_key);
            current_text += nowKey;
            m_Text->SetText(current_text + "|");
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::BACKSPACE)) {
            if (m_Text->GetText() != " ") {
                current_text = current_text.substr(0, current_text.size() - 1);
                m_Text->SetText(current_text + "|");
            }
        }
        if (Util::Input::IsKeyDown(Util::Keycode::RETURN)) {
            current_text += "\n";
            m_Text->SetText(current_text + "|");
        }
    } else {
        m_Text->SetText(current_text);
    }
}

std::string InputBox::ConvertKeycodeToString(Util::Keycode key) {
    std::string result = "";
    // A-Z
    if (capsLock) {
        for (auto str = 'A'; str <= 'Z'; str++) {
            if (str - 61 == static_cast<glm::int64>(key)) {
                result = fmt::to_string(str);
            }
        }
    } else {
        // a-z
        for (auto str = 'a'; str <= 'z'; str++) {
            if (str - 'a' + 4 == static_cast<glm::int64>(key)) {
                result = fmt::to_string(str);
            }
        }
    }

    // 1-9
    for (auto str = '1'; str <= '9'; str++) {
        if (str - 19 == static_cast<glm::int64>(key)) {
            result = fmt::to_string(str);
        }
    }

    // SPACE
    if (key == Util::Keycode::SPACE) {
        return " ";
    }
    if (key == Util::Keycode::NUM_0) {
        return "0";
    }
    if (key == Util::Keycode::BACKSLASH) {
        return "\\";
    }

    return result;
}

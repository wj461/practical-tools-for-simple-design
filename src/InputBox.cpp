
#include "InputBox.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>
#include <locale>
#include <spdlog/fmt/bundled/format.h>
#include <string>
void InputBox::Start() {
    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, " |",
                                          Util::Color::FromRGB(255, 255, 255));
    SetDrawable(m_Text);
}

void InputBox::Update() {
    auto currentKey = Util::Input::GetCurrentKeycode();
    if (currentKey != Util::Keycode::UNKNOWN) {
        auto nowKey = ConvertKeyCodeToString(currentKey);
        m_Text->SetText(m_Text->GetText() + nowKey);
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::BACKSPACE)) {
        if (m_Text->GetText() != " ") {
            m_Text->SetText(
                m_Text->GetText().substr(0, m_Text->GetText().size() - 1));
        }
    }
}

std::string InputBox::ConvertKeyCodeToString(Util::Keycode key) {
    std::string result;
    int k = static_cast<int>(key);
    LOG_DEBUG("{}", k);

    // A-Z
    for (auto str = 'A'; str <= 'Z'; str++) {
        if (str - 61 == static_cast<glm::int64>(key)) {
            result = fmt::to_string(str);
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

    return result;
}

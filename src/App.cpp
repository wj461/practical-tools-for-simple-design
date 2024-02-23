#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "GiraffeText.hpp"
#include <memory>

void App::Start() {
    LOG_TRACE("Start");

    m_Map->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/giraffe.png"));
    m_Map->SetZIndex(5);
    m_Map->Start();

    m_TalkText->Start();

    m_Root.AddChildren({m_Map, m_TalkText});

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    if (Util::Input::IsLButtonDoubleClick()) {
        LOG_DEBUG("Double Click");
    }

    if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_RB)) {
        LOG_DEBUG("Right button down");
    }
    if (Util::Input::IsKeyUp(Util::Keycode::MOUSE_RB)) {
        LOG_DEBUG("Right button up");
    }

    if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    }
    if (Util::Input::IsMouseMoving()) {
        // LOG_DEBUG("Mouse moving! x:{}, y{}", cursorPos.x, cursorPos.y);
    }

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::A)) {
        LOG_DEBUG("A Down");
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
        LOG_DEBUG("B Pressed. Setting the cursor to (0, 0).");
        Util::Input::SetCursorPosition({0.0F, 0.0F});
        LOG_DEBUG("Cursor set to {}.",
                  glm::to_string(Util::Input::GetCursorPosition()));
    }

    m_Map->Update();
    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}

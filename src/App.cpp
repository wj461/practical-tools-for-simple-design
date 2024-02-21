#include "App.hpp"

#include "TalkText.hpp"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "GiraffeText.hpp"
#include "config.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_TalkText =
        std::make_shared<TalkText>("../assets/fonts/Inter.ttf", 100);
    m_TalkText->SetZIndex(UI_Z);
    m_TalkText->Start();

    m_Giraffe->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/block.png"));
    m_Giraffe->SetZIndex(10);
    m_Giraffe->Start();
    // m_Giraffe->AddChild(m_TalkText);

    m_Map->SetDrawable(
        std::make_shared<Util::Image>("../assets/sprites/block.png"));
    m_Map->SetZIndex(MAP_Z);
    m_Map->Start();

    m_Root.AddChild(m_Giraffe);
    m_Root.AddChild(m_Map);
    m_Root.AddChild(m_TalkText);

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    if (Util::Input::IsLButtonDown()) {
        // LOG_DEBUG("Left button down");
    }
    if (Util::Input::IsLButtonEdge()) {
        // LOG_DEBUG("Left button edge");
    }

    if (Util::Input::IsLButtonDoubleClick()){
        LOG_DEBUG("double click");
    }

    if (Util::Input::IsRButtonDown()) {
        LOG_DEBUG("Right button down");
    }
    if (Util::Input::IsMButtonDown()) {
        LOG_DEBUG("Middle button down");
    }
    if (Util::Input::IfScroll()) {
        auto delta = Util::Input::GetScrollDistance();
        LOG_DEBUG("Scrolling: x: {}, y: {}", delta.x, delta.y);
    }
    if (Util::Input::IsMouseMoving()) {
        // LOG_DEBUG("Mouse moving! x:{}, y{}", cursorPos.x, cursorPos.y);
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::A)) {
        LOG_DEBUG("A");
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
        LOG_DEBUG("B");
        Util::Input::SetCursorPosition({0.0F, 0.0F});
    }

    m_Giraffe->Update();
    m_Map->Update();
    m_TalkText->Update();

    m_Root.Update();

}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}

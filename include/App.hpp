#ifndef APP_HPP
#define APP_HPP

#include "InputBox.hpp"
#include "TalkText.hpp"
#include "map.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/Root.hpp"

#include "Cat.hpp"
#include "Giraffe.hpp"
#include "GiraffeText.hpp"
#include <memory>

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();
    void Update();
    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    State m_CurrentState = State::START;

    std::shared_ptr<Map> m_Map = std::make_shared<Map>();
    std::shared_ptr<TalkText> m_TalkText = std::make_shared<TalkText>();
    std::shared_ptr<InputBox> m_InputBox = std::make_shared<InputBox>();

    Util::Root m_Root;
};

#endif

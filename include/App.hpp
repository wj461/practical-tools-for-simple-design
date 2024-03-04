#ifndef APP_HPP
#define APP_HPP

#include "Character.hpp"
#include "InputBox.hpp"
#include "TalkText.hpp"
#include "map.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Util/Renderer.hpp"

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
    std::shared_ptr<Character> m_char = std::make_shared<Character>();

    std::shared_ptr<Giraffe> m_Giraffe = std::make_shared<Giraffe>();
    //    std::shared_ptr<GiraffeText> m_GiraffeText =
    //    std::make_shared<GiraffeText>();

    std::shared_ptr<Cat> m_Cat = std::make_shared<Cat>();
    Util::Renderer m_Root;
};

#endif

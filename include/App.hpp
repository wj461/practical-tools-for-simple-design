#ifndef APP_HPP
#define APP_HPP

#include "TalkText.hpp"
#include "map.hpp"
#include "pch.hpp" // IWYU pragma: export

#include "Giraffe.hpp"
#include "GiraffeText.hpp"
#include "Util/Root.hpp"

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

    std::shared_ptr<Giraffe> m_Giraffe = std::make_shared<Giraffe>();
    std::shared_ptr<Map> m_Map = std::make_shared<Map>();
    std::shared_ptr<TalkText> m_TalkText = std::make_shared<TalkText>();
    //    std::shared_ptr<GiraffeText> m_GiraffeText =
    //    std::make_shared<GiraffeText>();
    Util::Root m_Root;
};

#endif

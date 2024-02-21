#include "GiraffeText.hpp"

#include "Util/Color.hpp"
#include "Util/Time.hpp"

void GiraffeText::Start() {
<<<<<<< HEAD
    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, "0adfasf0",
                                          Util::Color(1, 1, 1, 1));
=======
    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, "0",
                                          Util::Color::FromRGB(255, 255, 255));
>>>>>>> upstream/main
    SetDrawable(m_Text);
}

void GiraffeText::Update() {
    // m_Text->SetText(fmt::format("{:.02f}", 1.0F / Util::Time::GetDeltaTime()));

<<<<<<< HEAD
    // m_Text->SetColor({1, 0, 0, 1});
=======
    m_Text->SetColor(Util::Color::FromName(Util::Colors::RED));
>>>>>>> upstream/main
}

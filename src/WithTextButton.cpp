
#include "WithTextButton.hpp"
#include "Util/Logger.hpp"
#include <glm/fwd.hpp>

void WithTextButton::Init(std::string font, const int size) {
    m_Font = std::move(font);
    m_Size = size;

    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, "0",
                                          Util::Color(1, 1, 1, 1) );
    m_TextObject->SetDrawable(m_Text);
    m_TextObject->SetZIndex(this->GetZIndex() +1 );

    this->AddChild(m_TextObject);
}

void WithTextButton::SetTextPostionToCenter(){
    auto position = this->GetTransform().translation;

    LOG_DEBUG("size {} {}", 
    m_Text->GetSize().x, m_Text->GetSize().y);

    m_TextObject->SetPosition({
    position.x + this->GetSize().x/2 + 9,
    position.y + this->GetSize().y/2
    });
}
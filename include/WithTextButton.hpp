#ifndef WITH_TEXT_BUTTON_HPP
#define WITH_TEXT_BUTTON_HPP

#include "Block.hpp"
#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include <glm/fwd.hpp>
#include <memory>
#include <string>

class WithTextButton : public Block{
public:
    void Start();

    void Update();

    void Init(std::string font, const int size);

    void SetTextPostionToCenter();


    void SetText(const std::string text) { m_Text->SetText(text); };

private:
    std::shared_ptr<Util::Text> m_Text;
    std::shared_ptr<Util::GameObject> m_TextObject = std::make_shared<Util::GameObject>();

    std::string m_Font;
    int m_Size;
};

#endif
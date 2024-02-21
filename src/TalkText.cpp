#include "TalkText.hpp"
#include "Util/Input.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include "config.hpp"
#include <chrono>
#include <glm/detail/qualifier.hpp>
#include <string>
#include <thread>
#include <unistd.h>

void TalkText::Start(){
    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, "0",
                                          Util::Color(1, 1, 1, 1) );
    SetDrawable(m_Text);
    this->SetPosition({
    (TALK_START_POINT.x + 4) * BLOCK_SIZE,
    (TALK_START_POINT.y +2) * BLOCK_SIZE
    });



    std::shared_ptr<Util::Image> bg_img = std::make_shared<Util::Image>("../assets/sprites/talk.png");
    std::shared_ptr<Util::Image> character_img = std::make_shared<Util::Image>("../assets/sprites/character.png");

    bg->SetDrawable(bg_img);
    bg->SetZIndex(this->GetZIndex() -2);
    bg->SetPivotToLeftTop();
    bg->SetPosition({TALK_START_POINT.x*BLOCK_SIZE, TALK_START_POINT.y *BLOCK_SIZE});
    character->SetDrawable(character_img);
    character->SetZIndex(this->GetZIndex() -1);
    character->SetPivotToLeftTop();
    character->SetPosition({TALK_START_POINT.x*BLOCK_SIZE, TALK_START_POINT.y *BLOCK_SIZE});
    
    this->AddChild(bg);
    this->AddChild(character);

    SetText("ABCDEFG");
}


void TalkText::Update(){
    if (text != ""){
        // std::this_thread::sleep_for(std::chrono::milliseconds(200));
        currentText.push_back(text[0]);
        text.erase(0,1);
    }

    if (Util::Input::IsLButtonEdge()){
        SetText("123456\nasdasdsadas");
    }

    m_Text->SetText(currentText);
}

void TalkText::SetText(std::string inputText){
    text = inputText;
    currentText = " ";
}

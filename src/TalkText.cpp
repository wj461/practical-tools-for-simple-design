#include "TalkText.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"
#include "Util/Transform.hpp"
#include <chrono>
#include <string>
#include <thread>
#include <unistd.h>

void TalkText::Start(){
    m_Text = std::make_unique<Util::Text>(m_Font, m_Size, "0",
                                          Util::Color(1, 1, 1, 1) );
    SetDrawable(m_Text);

    // SetText("ABCDEFG");
}


void TalkText::Update(){
    auto &pos = m_Transform.translation;
    pos = glm::vec2{-100.0F, -100.0F};

    // if (text != ""){
        // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    //     currentText.push_back(text[0]);
    //     text.erase(0,1);
    // }

    // if (Util::Input::IsLButtonEdge()){
    //     SetText("123456");
    // }

    // m_Text->SetText(currentText);
}

void TalkText::SetText(std::string inputText){
    text = inputText;
    currentText = " ";
}

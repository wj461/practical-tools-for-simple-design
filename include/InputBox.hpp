#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"
#include <string>
class InputBox : public Util::GameObject {
public:
    void Start();

    void Update();

private:
    Util::Text text;

    bool enable = true;
};

#endif

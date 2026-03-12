#ifndef INTERFACES_INPUT
#define INTERFACES_INPUT

#include "interfaces/types.h"

class IInput {
    public:
        virtual Buttons block_until_button_press();
        virtual Buttons get_button();
};

#endif

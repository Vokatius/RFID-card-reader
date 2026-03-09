#ifndef INPUT_H
#define INPUT_H

#include <vector>

class Input {
    private:
        std::vector<int> buttons;

    public:
        Input(std::vector<int> buttons);
        int get_button();
};

#endif

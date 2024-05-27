#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <texts/TextKeysAndLanguages.hpp>

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <touchgfx/Unicode.hpp>
#include "usbd_cdc.h"

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();
private:
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    touchgfx::Callback<Screen1View, const touchgfx::AbstractButton&> buttonCallback;
    void shuffleButtons();
    ButtonWithLabel *buttons[9];
    int RANDOM_NUMBER;
};

void shuffle(const std::vector<TEXTS>& input, std::vector<TEXTS>& output, int R);

#endif // SCREEN1VIEW_HPP

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

#include "usbd_cdc_if.h"
#include "stm32h7xx_hal.h"
#include "main.h"

extern "C" {
#include "chacha.h"
}

#define BUTTON_SPACING 10
#define START_X 0
#define START_Y 0
#define BUTTON_A 100

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
    uint RANDOM_NUMBER;

    uint32_t key[KEY_SIZE] = {
        0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c,
        0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c};
    uint32_t nonce[NONCE_SIZE] = {0x00000000, 0x4a000000, 0x00000000};

};

void shuffle(const std::vector<TEXTS>& input, std::vector<TEXTS>& output, uint R);

#endif // SCREEN1VIEW_HPP

#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <stdlib.h>
#include <vector>
#include <algorithm>
//#include <time.h>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

//    void buttonCallback(const touchgfx::AbstractButton& src);
    virtual void handleTickEvent();
private:
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    touchgfx::Callback<Screen1View, const touchgfx::AbstractButton&> buttonCallback;
    void shuffleButtons();
//    std::vector<ButtonWithLabel*> buttons;
    ButtonWithLabel *buttons[9];
};

template<typename T>
void shuffle(const std::vector<T>& input, std::vector<T>& output);
void swap(TEXTS& a, TEXTS& b);

#endif // SCREEN1VIEW_HPP

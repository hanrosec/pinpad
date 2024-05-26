#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen1View::Screen1View():
	buttonCallback(this, &Screen1View::buttonCallbackHandler)
{
	// TODO nie zmienia przycisków
	const int buttonSpacing = 10;
	const int startX = 0;
	const int startY = 0;
	const int buttonA = 100;

	std::vector<ButtonWithLabel*> buttons;
    std::vector<TEXTS> number_list = {T_NINE, T_EIGHT, T_SEVEN, T_SIX, T_FIVE, T_FOUR, T_THREE, T_TWO, T_ONE};
    std::vector<TEXTS> shuffled_numbers;
    shuffle(number_list, shuffled_numbers);

    int counter = 0;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			int buttonX = startX + col * (buttonA + buttonSpacing);
			int buttonY = startY + row * (buttonA + buttonSpacing);

			ButtonWithLabel* button = new ButtonWithLabel();
			button->setXY(buttonX, buttonY);
			button->setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_SMALL_FILL_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_SMALL_FILL_PRESSED_ID));
			button->setLabelText(touchgfx::TypedText(shuffled_numbers[counter++]));
			button->setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			button->setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
			button->setAction(buttonCallback);
			add(*button);

			buttons.push_back(button);
		}
	}
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::shuffleButtons() {
    std::vector<TEXTS> number_list = {T_NINE, T_EIGHT, T_SEVEN, T_SIX, T_FIVE, T_FOUR, T_THREE, T_TWO, T_ONE};
    std::vector<TEXTS> shuffled_numbers;
    shuffle(number_list, shuffled_numbers);
    for(int i = 0; i<9; i++) {
    	buttons[i]->setLabelText(touchgfx::TypedText(shuffled_numbers[i]));
    }
}

void Screen1View::buttonCallbackHandler(const touchgfx::AbstractButton& src) {
    shuffleButtons();
}

void Screen1View::handleTickEvent()
{
    for(int i = 0; i<9; i++) {
    	buttons[i]->invalidate();
    }
}

void swap(TEXTS& a, TEXTS& b) {
    TEXTS temp = a;
    a = b;
    b = temp;
}

template<typename T>
void shuffle(const std::vector<T>& input, std::vector<T>& output) {
    output = input;

    int n = output.size();
    for (int i = n - 1; i > 0; --i) {
        int rand_index = rand() % (i + 1);
        T temp = output[i];
        output[i] = output[rand_index];
        output[rand_index] = temp;
    }
}

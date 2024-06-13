#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>


Screen1View::Screen1View():
	buttonCallback(this, &Screen1View::buttonCallbackHandler)
{
	srand(time(NULL));
	RANDOM_NUMBER = rand() * HAL_GetTick();

    std::vector<TEXTS> number_list = {T_NINE, T_EIGHT, T_SEVEN, T_SIX, T_FIVE, T_FOUR, T_THREE, T_TWO, T_ONE};
    std::vector<TEXTS> shuffled_numbers;
    shuffle(number_list, shuffled_numbers, RANDOM_NUMBER);

//    uint8_t plaintext[114] = {
//        0x4c,0x61,0x64,0x69,
//        0x65,0x73,0x20,0x61,
//        0x6e,0x64,0x20,0x47,
//        0x65,0x6e,0x74,0x6c,
//        0x65,0x6d,0x65,0x6e,
//        0x20,0x6f,0x66,0x20,
//        0x74,0x68,0x65,0x20,
//        0x63,0x6c,0x61,0x73,
//        0x73,0x20,0x6f,0x66,
//        0x20,0x27,0x39,0x39,
//        0x3a,0x20,0x49,0x66,
//        0x20,0x49,0x20,0x63,
//        0x6f,0x75,0x6c,0x64,
//        0x20,0x6f,0x66,0x66,
//        0x65,0x72,0x20,0x79,
//        0x6f,0x75,0x20,0x6f,
//        0x6e,0x6c,0x79,0x20,
//        0x6f,0x6e,0x65,0x20,
//        0x74,0x69,0x70,0x20,
//        0x66,0x6f,0x72,0x20,
//        0x74,0x68,0x65,0x20,
//        0x66,0x75,0x74,0x75,
//        0x72,0x65,0x2c,0x20,
//        0x73,0x75,0x6e,0x73,
//        0x63,0x72,0x65,0x65,
//        0x6e,0x20,0x77,0x6f,
//        0x75,0x6c,0x64,0x20,
//        0x62,0x65,0x20,0x69,
//        0x74,0x2e};
//
//    uint8_t *pplaintext = plaintext;
//    uint8_t ciphertext[sizeof(plaintext)];
//    uint8_t *pciphertext = ciphertext;
//
//    encrypt(pplaintext, sizeof(plaintext), pkey, pnonce, ciphertext);
//    test();

    int counter = 0;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			int button_x = START_X + col * (BUTTON_A + BUTTON_SPACING);
			int button_y = START_Y + row * (BUTTON_A + BUTTON_SPACING);

			ButtonWithLabel* button = new ButtonWithLabel();
			button->setXY(button_x, button_y);
			button->setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_SMALL_FILL_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_ICON_ROUNDED_SMALL_FILL_PRESSED_ID));
			button->setLabelText(touchgfx::TypedText(shuffled_numbers[counter]));
			button->setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
			button->setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
			button->setAction(buttonCallback);
			add(*button);

			buttons[counter] = button;
			counter++;
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
    shuffle(number_list, shuffled_numbers, RANDOM_NUMBER);
    for(int i = 0; i<9; i++) {
    	buttons[i]->setLabelText(touchgfx::TypedText(shuffled_numbers[i]));
    }
}

void Screen1View::buttonCallbackHandler(const touchgfx::AbstractButton& src) {
	extern UART_HandleTypeDef huart1;
//	uint8_t test[2];
//	uint8_t *ptest = test;
//	HAL_UART_Receive(&huart1, ptest, 2, 0xffffff);

    const ButtonWithLabel& button = static_cast<const ButtonWithLabel&>(src);
    touchgfx::TypedText label_text = button.getLabelText();

    const touchgfx::Unicode::UnicodeChar* unicode_text = label_text.getText();
    uint8_t button_pressed = (uint8_t)touchgfx::Unicode::atoi(unicode_text) + 48; // Wyrównanie do cyfr

    HAL_UART_Transmit(&huart1, &button_pressed, 1, 0xffff);

    shuffleButtons();
}

void Screen1View::handleTickEvent() {
	RANDOM_NUMBER += HAL_GetTick();
    for(int i = 0; i<9; i++) {
    	buttons[i]->invalidate();
    }
}

void shuffle(const std::vector<TEXTS>& input, std::vector<TEXTS>& output, uint R) {
    output = input;
    int n = output.size();

    for (int i = n - 1; i > 0; --i) {
        int rand_index = R % (i + 1);
        TEXTS temp = output[i];
        output[i] = output[rand_index];
        output[rand_index] = temp;
    }
}

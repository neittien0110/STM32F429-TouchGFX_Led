#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}


/**
 * Hàm sự kiện, được gọi ra khi nút bấm trên màn hình được bấm
 * @description
 * 	 - Hàm không được tự đông tạo ra khung sẵn, mà phải tự viết hoàn hoàn
 * 	 - Tên của hàm được định nghĩa trong phần mềm TouchGFX --> sinh ra file TouchGFX/TouchGFX_Led.touchgfx --> gen ra code ở file TouchGFX\generated\gui_generated\src\screen1_screen\Screen1ViewBase.cpp
 * @seealso Screen1ViewBase::buttonCallbackHandler()
 *
 */
void Screen1View::buttonClicked()
{
	/// Đảo giá trị tắt/bật đèn led mặc định trên board.
	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
}


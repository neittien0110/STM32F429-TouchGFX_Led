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

void Screen1View::ball_timertick()
{
	/// tickCount tăng xoay vòng: 0, 2, 4, 8, 236, 238.
	tickCount +=2;
	tickCount = tickCount % 240;

	/// Công thức tính tọa độ đốm tròn mới
	float x = tickCount / 55.0f;
	float y = sin(x) + sin(2*x) + sin(3*x) + 1;

	/** Message lấy ra từ hàng đợi*/
	uint8_t msg;

	/// Nếu như có 1 message nào đó vẫn còn trong hàng đợi chỉ định...
	if (osMessageQueueGetCount(myQueue01Handle) > 0) {
		/// thì đọc message
		osMessageQueueGet(myQueue01Handle, &msg, NULL, osWaitForever);
		/// Nếu message đúng nội dung quan tâm
		if (msg == 'X') {
			/// Di chuyển đốm đỏ đến tọa độ mới
			circle1.moveTo((int16_t)floor(x*55),200 -(int16_t)floor(y*50));
			/// Các thao tác đồ họa nói trên chỉ nhằm vẽ vào bộ đệm màn hình, trang đồ họa hậu trường.
			/// Cần phải gọi hàm invalidate để dữ liệu trong bộ đệm đó được đẩy ra màn hình chính.
			circle1.invalidate();
		}
	} else {
        /// Nếu không bấm nút thì giao diện không thay đổi
    }
}

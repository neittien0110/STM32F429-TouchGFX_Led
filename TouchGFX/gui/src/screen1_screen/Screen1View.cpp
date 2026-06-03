#include <gui/screen1_screen/Screen1View.hpp>
#include <stm32f4xx_hal.h>       /// Cần có để triệu gọi các hàm HAL
#include <cmsis_os2.h>           /// Cần có đề thao tác với MessageQueue
#include <math.h>                /// Cần có để Sử dụng các hàm toán học như sin, cos

extern "C" osMessageQueueId_t myQueue01Handle;   /// Được đặc tả trong main.c

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

# TOUCHGFX VÀ ĐIỀU KHIỂN LED

## Giới thiệu

Bộ kit STM32F429-DISC1 có tich hợp săn màn hình LCD cảm ứng chạm 2.2inch, __ILI9341__ . Màn hình này có thể [mua rời ỏ đây](https://banlinhkien.com/man-hinh-lcd-tft-2.2-spi-ili9341-p13020870.html)

## Quan trọng

  Xem lỗi [Không hiển thị được trên màn hình TouchScreen (màn hình trắng)](https://github.com/neittien0110/TouchGFX_Led/issues/1)

## Các bước lập trình

1. Tạo dự án mới bằng TouchGFX và gen code.\
   ![newproject](assets/newproject.png)
2. Ở phần mềm __TouchGFX__, mục __Canvas__,  trong màn hình __Screen1__, thêm một widget __buttonWithLabel1__.
   ![alt text](./assets/buttonWithLabel.png)\
3. Ở phần mềm __TouchGFX__, mục __Canvas__,  trong màn hình __Screen1__, tiếp tục thêm một widget __cicrle1__ với màu đỏ, đường kinh 20, nằm trong canvas 20x20.\

   Tên | Giá trị | ý nghĩa
   -- | -- | --
   Location W & H | 20 & 20 | Kích thước đường bao hình chữ 20 x 20 pixel
   Color | #FF0000 | Màu đỏ
   Center Position | 10 & 10 | Tâm quay, áp dụng cho các hiệu ứng chuyển động tròn
   Start & End Angle | 0 & 360 | Vẽ cung tròn với góc bắt đầu và kết thúc
   Radius | 10 | Bán kính cong, bằng 1/2 đường bao hình chữ nhật để tạo nên hình tròn
  
   ![alt text](./assets/CreateNewCircle.png)
   Bấm __F4__ để gen code.
4. Thêm __hàm sự kiện cho nút bấm.__\
   ![Object CallBack Functions](./assets/ObjectCallBackFunctions.png)

   Tên | Giá trị | ý nghĩa
   -- | -- | --
   Trigger | Button is clicked | Tương tác khi nút được bấm
   Choose clicked source | buttonWithLabel1 | Đối tượng áp dụng
   Action | Call new virtual function | chông hàm, gọi hàm callback
   Function Name | buttonClicked | Tên hàm call back sẽ được gọi ra khi nút được bấm
   Interaction Name | LED_Control_Clicked | Tên gợi nhớ về tương tác này

   Ví dụ:\
   ![Object CallBack Functions](./assets/ObjectCallBack_Onclick.png)\
   Bấm __F4__ để gen code.
5. Đăng kí __hàm sự kiện theo thời gian__, để tạo hiệu ứng chuyenr động của quả bóng đỏ.

   Tên | Giá trị | ý nghĩa
   -- | -- | --
   Trigger | Trigger on every N tick | Tương tác khi sau mỗi N tick thời gian
   Ticks between triggers | 1 | Chính là số N ở trên.
   Action | Call new virtual function | chông hàm, gọi hàm callback
   Function Name | ball_timertick | Tên hàm call back sẽ được gọi ra sau mỗi N tick thời gian
   Interaction Name | RedBall_Moving | Tên gợi nhớ về tương tác này

   ![Object CallBack Timer Counttick](./assets/ObjectCallBack_OnTimer.png)\
   Bấm __F4__ để gen code.
6. Mở thư mục mà mã nguồn được sinh ra với các thư mục con như hình vẽ.\
   ![alt text](./assets/ProjectDirectory.png)\
   Mở thư mục con __STM32CubeIDE__, click vào file __.project__ để mở dự án bằng STM32CubeIDE.  
   ![alt text](./assets/STM32CubeInsideTouchGFX.png)\
   > Từ bây giờ, cứ mở cả 2 cửa sổ IDE __TouchGFX__ và __STM32Cube__ cùng lúc
7. Vẫn ở công cụ __STM32CubeIDE__, và ở file __.ioc__, cấu hình 3 chân pin:
   - PA0 là GPIO_Input
   - PG13 là GPIO_Output
   - PG14 là GPIO_Output
   > Xem lỗi [Không hiển thị được trên màn hình TouchScreen (màn hình trắng)](https://github.com/neittien0110/TouchGFX_Led/issues/1)

8. Ở file __.ioc__, khai báo thêm 1 __Message Queue__, có tên __myQueue01__ để tryên thông điệp từ nút bấm __PA0__ tới giao diện.\
   ![Thêm Queue Message](./assets/FreeRTOS_AddQueue.png)
   > Lưu ý rằng: __FreeRTOS__ mặc định đã được kich hoạt để sử dụng __TouchGFX__ rồi.

9. Viết hàm sự kiện để khi __bấm nút trên màn hình Touch thì bật đèn LD3 (PG13pin), LD4 (PG14 pin)__ \
    Xem lại ảnh này để thấy cần viết hàm callback như thế nào:\
    ![Object CallBack Functions](./assets/ObjectCallBack_Onclick.png)

      1. TouchGFX đã sinh ra hàm ảo __void buttonClicked()__ của nút bấm trên giao diện, khai báo trong file hoạt cảnh [Application/User/Generated/__Screen1ViewBase.cpp__](./TouchGFX/generated/gui_generated/src/screen1_screen/Screen1ViewBase.cpp). Không cần thao tác gì thêm. Đoạn mã sau chỉ đơn giản là biết.

         ```C
         void Screen1ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
         {
            if (&src == &buttonWithLabel1)   /// Nếu đối tượng gây ra sự kiện là nút bấm có id = buttonWithLabel1
            {
               //LED_Control_Clicked         /// Tên gọi nhớ của sự kiện, trên phần mêm TouchGFX desinger
               buttonClicked();              /// Gọi hàm ảo sự kiện
            }
         }
         ```

      2. Chồng hàm ảo với đầy đủ của thao tác, trong file [__Screen1View.cpp__](./TouchGFX/gui/src/screen1_screen/Screen1View.cpp) của file hoạt cảnh screen tương ứng

         ```C
         void Screen1View::buttonClicked()
         {
            /// Đảo giá trị tắt/bật đèn led mặc định trên board.
            HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
         }
         ```

      3. Khai báo hàm chồng.\
         Trên giao diện, click vào dấu mũi tên __>__ bên cạnh file __Screen1View.cpp__ để mở ra file [__Screen1View.hpp__](./TouchGFX/gui/include/gui/screen1_screen/Screen1View.hpp) tương ứng.

         ![Mở file hpp tương ứng](./assets/HowToOpenHPP.png)

         ```C
         #include "stm32f4xx_hal.h"                   /// Cần có để triệu gọi các hàm HAL         
         class Screen1View : public Screen1ViewBase
         {
            /**
             * * Hàm sự kiện, được gọi ra khi nút bấm Led Control trên màn hình được bấm
            */
            public: void buttonClicked();
         }
         ```

    Đã xong tương tác theo hướng __Giao diện --> HAL__.\
    Tiếp theo sẽ là tương tác theo hướng __HAL --> Giao diện__.
10. Viết hàm sự kiện để khi __bấm nút trên USER trên board và hiển thị trên màn hình__: \
      1. TouchGFX đã sinh ra hàm ảo __void ball_timertick()__ của nút bấm trên giao diện, khai báo trong file hoạt cảnh [Application/User/Generated/__Screen1ViewBase.cpp__](./TouchGFX/generated/gui_generated/src/screen1_screen/Screen1ViewBase.cpp). Không cần thao tác gì thêm.

         ```C
         void Screen1ViewBase::handleTickEvent()
         {
            //RedBall_Moving                 /// Tên gọi nhớ của sự kiện, trên phần mêm TouchGFX desinger
            ball_timertick();                /// Gọi hàm ảo sự kiện
         }
         ```

      2. Xây dựng hàm ảo đầy đủ của sự kiện, trong file __.cpp__ của file hoạt cảnh screen tương ứng

         ```C
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
         ```

      3. Khai báo hàm chồng.\
         Trên giao diện, click vào dấu mũi tên __>__ bên cạnh file __Screen1View.cpp__ để mở ra file [__Screen1View.hpp__](./TouchGFX/gui/include/gui/screen1_screen/Screen1View.hpp) tương ứng.

         ```C
         #include <stm32f4xx_hal.h>       /// Cần có để triệu gọi các hàm HAL
         #include <cmsis_os2.h>           /// Cần có đề thao tác với MessageQueue
         #include <math.h>                /// Cần có để Sử dụng các hàm toán học như sin, cos

         extern "C" osMessageQueueId_t myQueue01Handle;   /// Được đặc tả trong main.c

         class Screen1View : public Screen1ViewBase
         {
            /**
            * * Hàm sự kiện, được gọi ra sau mỗi tic-tok thời gian xảy ra ở đốm đỏ trên màn hình
            */
            public: void ball_timertick();
            /**
            * Biến đếm thời gian, để gui đổi thành tọa độ đốm đỏ.
            */            
            protected: uint32_t tickCount = 0;            
         }
         ```

11. Bắt sự kiện nút bấm B1, vaf đưa thông điệp vào hàng đợi (sẽ dược ball_timertick() định kỳ đọc )

   ```C
   void StartDefaultTask(void *argument)
   {
     /* USER CODE BEGIN 5 */
     /* Infinite loop */
     for(;;)
     {
   	  /// Nếu nút bấm xanh PA0 được bấm thì ....
   	  if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
   		  /// Gửi thông điệp vào hàng đợi Queue.
   		  uint8_t data='X';
   		  osMessageQueuePut(myQueue01Handle, &data, 0, 10);
   	  }
   	  osDelay(100);
     }
     /* USER CODE END 5 */
   }
   ```

Hết.

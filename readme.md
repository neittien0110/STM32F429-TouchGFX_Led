# TOUCHGFX VÀ ĐIỀU KHIỂN LED

## Các bước lập trình

1. Tạo dự án mới bằng TouchGFX và gen code
2. Ở phần mềm __TouchGFX__, mục __Canvas__,  trong màn hình __Screen1__, thêm một widget __buttonWithLabel1__.
   ![alt text](./assets/buttonWithLabel.png)
   Bấm __F4__ để gen code.
3. Mở thư mục mà mã nguồn được sinh ra với các thư mục con như hình vẽ.\
   ![alt text](./assets/ProjectDirectory.png)
   Mở thư mục con __STM32CubeIDE__, click vào file __.project__ để mở dự án bằng STM32CubeIDE.  
   ![alt text](./assets/STM32CubeInsideTouchGFX.png)
   > Từ bây giờ, cứ mở cả 2 cửa sổ IDE __TouchGFX__ và __STM32Cube__ cùng lúc
4. Ở phần mềm __TouchGFX__, mục __Canvas__,  trong màn hình __Screen1__, tiếp tục thêm một widget __cicrle1__ với màu đỏ, đường kinh 20, nằm trong canvas 20x20.
    Bấm __F4__ để gen code.
5. Thêm hàm sự kiện cho nút bấm.\
   ![Object CallBack Functions](./assets/ObjectCallBackFunctions.png)\
   Ví dụ:\
   ![Object CallBack Functions](./assets/ObjectCallBack_Onclick.png)\
   Bấm __F4__ để gen code.
6. Đăng kí hàm sự kiện theo thời gian, để tạo hiệu ứng chuyenr động của quả bóng đỏ.\
   ![Object CallBack Timer Counttick](./assets/ObjectCallBack_OnTimer.png)
   Bấm __F4__ để gen code.

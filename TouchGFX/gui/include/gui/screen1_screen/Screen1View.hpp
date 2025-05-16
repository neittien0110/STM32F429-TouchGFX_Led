#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <stm32f4xx_hal.h>			/// Cần có để triệu gọi các hàm HAL
#include <cmsis_os2.h>				/// Cần có đề thao tác với MessageQueue
#include <math.h>					/// Cần có để Sử dụng các hàm toán học như sin, cos

extern "C" osMessageQueueId_t myQueue01Handle;	/// Được đặc tả trong main.c

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	/**
	 * * Hàm sự kiện, được gọi ra khi nút bấm Led Control trên màn hình được bấm
	 */
    void buttonClicked();
	/**
	 * * Hàm sự kiện, được gọi ra sau mỗi tic-tok thời gian xảy ra ở đốm đỏ trên màn hình
	 */
	void ball_timertick();
protected:
    /**
     * Biến đếm thời gian, để gui đổi thành tọa độ đốm đỏ.
     */
    uint32_t tickCount = 0;
};

#endif // SCREEN1VIEW_HPP

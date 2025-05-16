#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include "stm32f4xx_hal.h"			/// Cần có để triệu gọi các hàm HAL

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
protected:
};

#endif // SCREEN1VIEW_HPP

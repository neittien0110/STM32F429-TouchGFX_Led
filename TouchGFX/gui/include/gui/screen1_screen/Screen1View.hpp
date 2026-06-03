#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
/**
 * * Hàm sự kiện, được gọi ra khi nút bấm Led Control trên màn hình được bấm
*/
public: void buttonClicked();
              /**
               * * Hàm sự kiện, được gọi ra sau mỗi tic-tok thời gian xảy ra ở đốm đỏ trên màn hình
               */
public: void ball_timertick();
            protected:
               /**
               * Biến đếm thời gian, để gui đổi thành tọa độ đốm đỏ.
               */
               uint32_t tickCount = 0;
};

#endif // SCREEN1VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <windows.h>
#include "Menu.h"
#include "Pendulum.cpp"

using namespace sf;

int main()
{
    Pendulum p = (40, 40, 40);

    ContextSettings window_settings;
    window_settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(1000, 1000), "Double Pendulum", Style::Default, window_settings);

    std::vector<Pendulum> pendulum;
    int pendulum_count = 0;

    if (Menu::start(window))
    {
        Sleep(100);
        pendulum_count = Menu::double_pendulum_count(window);
        Sleep(100);

        int animation_speed;
        switch(pendulum_count)
        {
        case 1:
            animation_speed = 35;
            break;
        case 2:
            animation_speed = 40;
            break;
        case 3:
            animation_speed = 48;
            break;
        case 5:
            animation_speed = 60;
            break;
        case 10:
            animation_speed = 110;
            break;
        }

        for (int i = 0; i < pendulum_count;)
        {
            Menu::pend_settings setting = Menu::double_pendulum_settings(window, i + 1);
            pendulum.push_back(Pendulum(setting.m1, setting.m2, setting.l1, setting.l2, setting.a1, setting.a2, setting.stop, animation_speed));
            i += setting.next;
            Sleep(100);
        }
    }
    else
    {
        /**< гдеяэ рбни йнд */
    }

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

        window.clear(Color::White);
        for (int i = 0; i < pendulum_count; ++i)
            pendulum[i].draw(window);
		window.display();
	}

	return 0;
}

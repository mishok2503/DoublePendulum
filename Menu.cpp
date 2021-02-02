#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include "IsButtonClicked.h"

using namespace sf;

namespace Menu
{
    struct pend_settings
    {
        long double m1, m2;
        long double a1, a2;
        int stop, next, l1, l2;;
    };

    pend_settings double_pendulum_settings(sf::RenderWindow &window, int num)
    {
        pend_settings setting;
        setting.m1 = 40;

        bool moving[3][2];

        RectangleShape stick[3][2];
        CircleShape circle[3][2];
        Font font;
        font.loadFromFile("fonts/font.otf");
        Text txt[3][2], setting_txt[3][2];
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                moving[i][j] = false;
                stick[i][j].setSize(Vector2f(250, 10));
                stick[i][j].setPosition(i * 320 + 50, j * 400 + 250);
                stick[i][j].setFillColor(Color::White);
                circle[i][j].setPosition(i * 320 + 50, j * 400 + 240);
                circle[i][j].setRadius(15);
                circle[i][j].setFillColor(Color::Black);
                txt[i][j].setFont(font);
                txt[i][j].setCharacterSize(25);
                txt[i][j].setFillColor(Color::Black);
                setting_txt[i][j].setFont(font);
                setting_txt[i][j].setCharacterSize(25);
                setting_txt[i][j].setFillColor(Color::Black);
            }
        }
        txt[0][0].setString("mass1 to mass2");
        txt[0][1].setString("length of the first rod");
        txt[1][0].setString("length of the second rod");
        txt[1][1].setString("First angle");
        txt[2][0].setString("Second angle");
        txt[2][1].setString("Stopping coefficient");
        txt[0][0].setPosition(100, 170);
        txt[0][1].setPosition(390, 170);
        txt[1][0].setPosition(700, 170);
        txt[1][1].setPosition(130, 570);
        txt[2][0].setPosition(420, 570);
        txt[2][1].setPosition(710, 570);
        setting_txt[0][0].setPosition(140, 270);
        setting_txt[0][1].setPosition(460, 270);
        setting_txt[1][0].setPosition(770, 270);
        setting_txt[1][1].setPosition(140, 670);
        setting_txt[2][0].setPosition(460, 670);
        setting_txt[2][1].setPosition(770, 670);

        RectangleShape next(Vector2f(250, 80)), before(Vector2f(250, 80));
        next.setFillColor(Color::White);
        before.setFillColor(Color::White);
        next.setPosition(window.getSize().x - 250, window.getSize().y - 150);
        before.setPosition(0, window.getSize().y - 150);

        Text next_txt, before_txt, num_txt;
        next_txt.setFont(font);
        next_txt.setPosition(next.getPosition().x + 100, next.getPosition().y + 10);
        next_txt.setCharacterSize(45);
        next_txt.setFillColor(Color::Black);
        next_txt.setString("OK");
        before_txt.setFont(font);
        before_txt.setPosition(before.getPosition().x + 80, before.getPosition().y + 10);
        before_txt.setCharacterSize(45);
        before_txt.setFillColor(Color::Black);
        before_txt.setString("Back");
        num_txt.setFont(font);
        num_txt.setPosition(390, 30);
        num_txt.setCharacterSize(45);
        num_txt.setFillColor(Color::Black);
        num_txt.setString(std::to_string(num) + " pendulum");

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (IsButtonClicked(next, Mouse::getPosition(window)))
                    {
                        setting.next = 1;
                        return setting;
                    }
                    if (IsButtonClicked(before, Mouse::getPosition(window)) && num != 1)
                    {
                        setting.next = -1;
                        return setting;
                    }
                }
            }

            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    if (Mouse::getPosition(window).x > circle[i][j].getPosition().x && Mouse::getPosition(window).x < circle[i][j].getPosition().x + 25)
                    {
                        if (Mouse::getPosition(window).y > circle[i][j].getPosition().y && Mouse::getPosition(window).y < circle[i][j].getPosition().y + 25)
                        {
                            moving[i][j] = true;
                        }
                        else
                        {
                            moving[i][j] = false;
                        }
                    }
                    else
                    {
                        moving[i][j] = false;
                    }
                }
            }

            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    if (moving[i][j] && Mouse::isButtonPressed(Mouse::Left))
                    {
                        if (Mouse::getPosition(window).x - 9 > stick[i][j].getPosition().x && Mouse::getPosition(window).x + 18 < stick[i][j].getPosition().x + 250)
                        {
                                circle[i][j].setPosition(Mouse::getPosition(window).x - 10, circle[i][j].getPosition().y);
                        }
                    }
                }
            }

            setting.m2 = pow(2, log2((circle[0][0].getPosition().x - stick[0][0].getPosition().x) / 120 + 0.25)) * setting.m1;
            if (setting.m2 > 80) setting.m2 = 80;
            setting.l1 = (circle[1][0].getPosition().x - stick[1][0].getPosition().x) / 1.1 + 50;
            setting.l2 = (circle[2][0].getPosition().x - stick[2][0].getPosition().x) / 1.1 + 50;
            setting.a1 = (circle[0][1].getPosition().x - stick[0][1].getPosition().x) / 35.015;
            setting.a2 = (circle[1][1].getPosition().x - stick[1][1].getPosition().x) / 35.015;
            setting.stop = (circle[2][1].getPosition().x - stick[2][1].getPosition().x) / 2.2;

            setting_txt[0][0].setString(std::to_string(setting.m2 / setting.m1));
            setting_txt[0][1].setString(std::to_string(setting.l1));
            setting_txt[1][0].setString(std::to_string(setting.l2));
            setting_txt[1][1].setString(std::to_string(setting.a1));
            setting_txt[2][0].setString(std::to_string(setting.a2));
            setting_txt[2][1].setString(std::to_string(setting.stop));

            window.clear(Color(255, 127, 39));
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 2; ++j)
                {
                    window.draw(stick[i][j]);
                    window.draw(circle[i][j]);
                    window.draw(txt[i][j]);
                    window.draw(setting_txt[i][j]);
                }
            }
            if (num != 1)
            {
                window.draw(before);
                window.draw(before_txt);
            }
            window.draw(next);
            window.draw(next_txt);
            window.draw(num_txt);
            window.display();
        }
    }

    int double_pendulum_count(RenderWindow &window)
    {
        RectangleShape button[5];
        Text button_txt[5], head;
        Font font;
        font.loadFromFile("fonts/font.otf");
        for (int i = 0; i < 5; ++i)
        {
            button[i].setSize(Vector2f(400, 130));
            button[i].setFillColor(Color::White);
            button[i].setPosition(300, i * 150 + 180);
            button_txt[i].setFont(font);
            button_txt[i].setPosition(490, i * 150 + 220);
            button_txt[i].setCharacterSize(55);
            button_txt[i].setFillColor(Color::Black);
            if (i > 2) continue;
            button_txt[i].setString(std::to_string(i + 1));
        }
        button_txt[4].setPosition(475, 820);
        button_txt[3].setString("5");
        button_txt[4].setString("10");
        head.setFont(font);
        head.setPosition(330, 90);
        head.setCharacterSize(35);
        head.setFillColor(Color::Black);
        head.setString("Choose pendulum count");

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    for (int i = 0; i < 5; ++i)
                    {
                        if (IsButtonClicked(button[i], Mouse::getPosition(window)))
                        {
                            if (i < 3)
                                return i + 1;
                            else
                            {
                                if (i == 3)
                                    return 5;
                                else
                                    return 10;
                            }
                        }
                    }
                }
            }

            window.clear(Color(255, 127, 39));
            for (int i = 0; i < 5; ++i)
            {
                window.draw(button[i]);
                window.draw(button_txt[i]);
            }
            window.draw(head);
            window.display();
        }
    }

    bool start(RenderWindow &window)
    {
        RectangleShape double_pend(Vector2f(400, 150));
        RectangleShape single_pend(Vector2f(400, 150));
        double_pend.setPosition(520, 425);
        single_pend.setPosition(80, 425);
        double_pend.setFillColor(Color::White);
        single_pend.setFillColor(Color::White);

        Font font;
        font.loadFromFile("fonts/font.otf");
        Text double_pend_txt, single_pend_txt;
        double_pend_txt.setFont(font);
        single_pend_txt.setFont(font);
        double_pend_txt.setPosition(560, 470);
        single_pend_txt.setPosition(130, 470);
        double_pend_txt.setCharacterSize(45);
        single_pend_txt.setCharacterSize(45);
        double_pend_txt.setString("Double pendulum");
        single_pend_txt.setString("Single pendulum");
        double_pend_txt.setFillColor(Color::Black);
        single_pend_txt.setFillColor(Color::Black);

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();

                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if (IsButtonClicked(double_pend, Mouse::getPosition(window)))
                    {
                        return true;
                    }
                    if (IsButtonClicked(single_pend, Mouse::getPosition(window)))
                    {
                        return false;
                    }
                }
            }

            window.clear(Color(255, 127, 39));
            window.draw(double_pend);
            window.draw(single_pend);
            window.draw(double_pend_txt);
            window.draw(single_pend_txt);
            window.display();
        }
    }
}



#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

namespace Menu
{
    bool start(sf::RenderWindow &window);
    int double_pendulum_count(sf::RenderWindow &window);
    struct pend_settings
    {
        long double m1, m2;
        long double a1, a2;
        int stop, next, l1, l2;
    };
    pend_settings double_pendulum_settings(sf::RenderWindow &window, int num);
}

#endif

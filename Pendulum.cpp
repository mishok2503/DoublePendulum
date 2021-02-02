#include <SFML/Graphics.hpp>
#include <vector>
#define PI 3.14159265

using namespace sf;

class Pendulum
{
private:

    long double m1, m2, l1, l2;
    long double a1, a2, as1, as2;

    long double x1, y1, x2, y2;

    long double stopCef;

    CircleShape s1, s2, s0;
    RectangleShape stick1, stick2;

    Color clr;

    std::vector<CircleShape> points;
    int frames, points_inx;

    int calculation_per_frame;
    const int cx = 500, cy = 400;
    const long double g = 0.0001;
    const int accuracy = 8;
    const int points_count = 1000, points_rate = 4;

public:

    Pendulum(long double m1 = 40, long double m2 = 40, long double l1 = 200, long double l2 = 200, long double a1 = PI / 2, long double a2 = PI / 2, int stop = 0, int speed = 30)
    {
        this->m1 = m1;
        this->m2 = m2;
        this->l1 = l1 * accuracy;
        this->l2 = l2 * accuracy;
        this->a1 = a1;
        this->a2 = a2;

        calculation_per_frame = speed;

        clr = Color(rand() % 256, rand() % 256, rand() % 256);

        as1 = 0;
        as2 = 0;
        frames = 0;
        points_inx = 0;

        stick1.setSize(Vector2f(3, l1 + 2));
        stick2.setSize(Vector2f(3, l2 + 2));
        stick1.setFillColor(Color::Black);
        stick2.setFillColor(Color::Black);
        stick1.setPosition(cx + 10.5, cy + 10.5);

        s1.setFillColor(clr);
        s1.setRadius(12);
        s2.setFillColor(clr);
        s2.setRadius(12);
        s0.setPosition(cx, cy);
        s0.setRadius(10);
        s0.setFillColor(Color::Black);

        points.resize(1000);

        stopCef = 1 - (long double)stop / 10000;
    }

    void draw(RenderWindow &w)
    {
        ++frames;
        frames %= points_rate;

        for (int i=0; i < calculation_per_frame; ++i)
        {
            long double temp1 = -g * (2 * m1 + m2) * sin(a1);
            long double temp2 = -m2 * g * sin(a1 - 2 * a2);
            long double temp3 = -2 * sin(a1 - a2) * m2 * (as2 * as2 * l2 + as1 * as1 * l1 * cos(a1-a2));
            long double temp4 = l1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
            long double aa1 = (temp1 + temp2 + temp3) / temp4;

            temp1 = 2 * sin(a1 - a2);
            temp2 = as1 * as1 * l1 * (m1 + m2) + g * (m1 + m2) * cos(a1) + as2 * as2 * l2 * m2 * cos(a1 - a2);
            temp3 = l2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
            long double aa2 = (temp1 * temp2) / temp3;

            as1 += aa1;
            as2 += aa2;
            a1 += as1;
            a2 += as2;
        }

        as1 *= stopCef;
        as2 *= stopCef;

        x1 = l1 * sin(a1) / accuracy + cx;
        y1 = l1 * cos(a1) / accuracy + cy;
        x2 = l2 * sin(a2) / accuracy + x1;
        y2 = l2 * cos(a2) / accuracy + y1;

        if (frames == 0)
        {
            points[points_inx] = CircleShape(2);
            points[points_inx].setFillColor(clr);
            points[points_inx].setPosition(Vector2f(x2 + 6, y2 + 6));
            ++points_inx;
            points_inx %= points_count;
        }

        s1.setPosition(x1, y1);
        s2.setPosition(x2, y2);

        stick1.setRotation(-a1 * 180 / PI);
        stick2.setRotation(-a2 * 180 / PI);
        stick2.setPosition(x1 + 10.5, y1 + 10.5);

        for (int i = 0; i < points_count; ++i)
            w.draw(points[i]);
        w.draw(stick1);
        w.draw(stick2);
        w.draw(s1);
        w.draw(s2);
        w.draw(s0);
    }
};

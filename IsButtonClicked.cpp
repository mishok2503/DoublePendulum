#include <SFML/Graphics.hpp>

using namespace sf;

bool IsButtonClicked(const RectangleShape &rect, Vector2i mouse_pos)
{
    bool res = false;

    if (mouse_pos.x > rect.getPosition().x && mouse_pos.x < rect.getPosition().x + rect.getSize().x)
    {
        if (mouse_pos.y > rect.getPosition().y && mouse_pos.y < rect.getPosition().y + rect.getSize().y)
            res = true;
    }

    return res;
}

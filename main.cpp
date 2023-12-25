#include <SFML/Graphics.hpp>
#include <time.h>
#include <array>
#include <iostream>

bool hasCollided(sf::Sprite, sf::Sprite);

int main(void)
{
    srand((uint)time(NULL));

    sf::RenderWindow app(sf::VideoMode(520, 450), "Arkanoid");
    app.setFramerateLimit(60);

    sf::Texture t1, t2, t3, t4;
    t1.loadFromFile("images/block01.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");

    sf::Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(300, 440);
    sBall.setPosition(300, 300);

    std::array<sf::Sprite, 1000> sBlocks;
    // sf::Sprite sBlocks[1000];

    int n = 0;
    for (int i = 1; i < 10; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            sBlocks[n].setTexture(t1);
            sBlocks[n].setPosition(43 * i, 20 * j);
            n++;
        }
    }

    float dx = 6, dy = 5;

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        sBall.move(dx, 0);
        for (int i = 0; i < n; i++)
        {
            if (hasCollided(sBall, sBlocks[i]))
            {
                sBlocks[i].setPosition(-100, -100);
                dx = -dx;
            }
        }

        sBall.move(0, dy);
        ;
        for (int i = 0; i < n; i++)
        {
            if (hasCollided(sBall, sBlocks[i]))
            {
                sBlocks[i].setPosition(-100, -100);
                dy = -dy;
            }
        }

        sf::Vector2f posBall = sBall.getPosition();

        if (posBall.x < 0 || posBall.x > 520)
        {
            dx = -dx;
        }
        if (posBall.y < 0 || posBall.y > 440)
        {
            dy = -dy;
        }

        app.clear();
        app.draw(sBackground);
        app.draw(sBall);
        app.draw(sPaddle);

        for (int i = 0; i < n; i++)
        {
            app.draw(sBlocks[i]);
        }

        app.display();
    }
    return 0;
}

bool hasCollided(sf::Sprite s1, sf::Sprite s2)
{
    return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}
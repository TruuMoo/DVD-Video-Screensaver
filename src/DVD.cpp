#include <SFML/Graphics.hpp>
#include <iostream>


#define STARTING_X_POSITION 400
#define STARTING_Y_POSITION 400

// Pixels to move per frame (multiplied by the speed)
#define STARTING_X_VELOCITY 5 
#define STARTING_Y_VELOCITY 5

#define LOGO_SIZE sf::Vector2f(300.f, 131.f)

static constexpr int_fast16_t WINDOW_WIDTH = 900;
static constexpr int_fast16_t WINDOW_HEIGHT = 800;
static constexpr int FRAMERATE = 60;
static constexpr float SPEED = 0.4f;


sf::Color getRandomColor() {
    int r, g, b;
    r = rand() % 255 + 1;
    g = rand() % 255 + 1;
    b = rand() % 255 + 1;
    return sf::Color(r, g, b, 255);
}


int main()
{

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DVD Video");
    sf::RectangleShape shape(LOGO_SIZE);

    sf::Texture texture;
    sf::Sprite sprite;

    /* Check 2 different locations for the image*/
    if (!texture.loadFromFile("dvdLogo.png")) { 
        std::cout << "Trying a different file location.." << std::endl;
        if (!texture.loadFromFile(".\\Release\\dvdLogo.png")) {
            std::cerr << "ERROR: COULD NOT LOAD LOGO FILE!!!!" << std::endl;
        }
        else { std::cout << "Found it!" << std::endl; }
    }

            

    sprite.setTexture(texture);
    window.setFramerateLimit(FRAMERATE);
    sprite.setColor(getRandomColor());


    sprite.setPosition(STARTING_X_POSITION, STARTING_Y_POSITION);

    int x = 0; int y = 0;
    float vx = STARTING_X_VELOCITY; float vy = STARTING_Y_VELOCITY;

    /* Input Loop ----- */

    while (window.isOpen())
    {
        /* Set our new x and y variables to the center of the shape */
        x = (int)(sprite.getPosition().x + (0.5 * (sprite.getGlobalBounds().width) + 1));
        y = (int)(sprite.getPosition().y + (0.5 * (sprite.getGlobalBounds().height)));

        //std::cout << x << ", " << y << std::endl;

        if (sprite.getPosition().y <= 0 || (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) >= WINDOW_HEIGHT) {
            vy = -(vy); sprite.setColor(getRandomColor());
        }
        if (sprite.getPosition().x <= 0 || (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) >= WINDOW_WIDTH) {
            vx = -(vx); sprite.setColor(getRandomColor());
        }



        sprite.move(vx * SPEED, -vy * SPEED);


        sf::Event event;

        /* handles different types of inputs */

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) /* If window is closed */
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();

    }

    return 0;
}
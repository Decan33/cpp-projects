#include <SFML\Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <sstream>
#include "Board.h"





int main()
{
	Board* b = new Board(100, 100);


    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Game of Life");

    std::vector<sf::RectangleShape> grid = b->setup_grid(window.getSize());
    window.setKeyRepeatEnabled(false);
    while (window.isOpen())
    {
        // Event loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // If close is requested by user, close the window
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Enter)
                {
                    b->next_generation(grid);
                }
            }
            

        }

        // Display sequence : clear screen, draw circle and update display
        window.clear();
        for (const auto& k : grid)
        {
            window.draw(k);
        }
        window.display();
    }

	return 0;

}
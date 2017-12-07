// main.cpp
#include "classes.h"
#include <iostream> 
#include <sstream>

int main()
{
	Hero hero;

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(weigth, height, desktop.bitsPerPixel), "Star Wars");

	Font font;
	font.loadFromFile("zealot.ttf");
	Text text("", font, 20);
	text.setColor(Color::Red);

	float CurrentFrame = 0;
	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		hero.update(time);
		window.clear(); 
		window.draw(hero.getimage());
		
		std::ostringstream playerHPString;
		playerHPString << hero.getHP();
		text.setString("Health: " + playerHPString.str());
		text.setPosition(0, 0);
		window.draw(text);

		window.display();
	}



	return 0;
}


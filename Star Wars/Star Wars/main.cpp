// main.cpp
#include "classes.h"
#include <iostream> 
#include <sstream>
#include <list>

int main()
{
	Hero hero;
	int enemy_count = 3;
	

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(weigth, height, desktop.bitsPerPixel), "Star Wars");

	Font font;
	font.loadFromFile("zealot.ttf");
	Text text_hp("", font, 20);
	text_hp.setColor(Color::Red);
	Text text_score("", font, 20);
	text_score.setColor(Color::Red);

	std::list<Enemy*>  enemies; 
	std::list<Enemy*>::iterator it_enemy; 

	std::list<Bullet_H*>  bul_h; 
	std::list<Bullet_H*>::iterator it_h; 

	std::list<Bullet_E*>  bul_e; 
	std::list<Bullet_E*>::iterator it_e; 

	float CurrentFrame = 0;
	Clock clock;
	Clock clock2;

	int shoot_time = 0;

	for (int i = 0; i < enemy_count; i++)
	{
		enemies.push_back(new Enemy());
	}

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

			// Выстрел по нажатию пробела
			shoot_time = clock2.getElapsedTime().asMilliseconds();
			if (event.type == sf::Event::KeyPressed)
			{
				if ((event.key.code == sf::Keyboard::Space) && (hero.getLife()) && (shoot_time >= delay / 3))
				{
					clock2.restart();
					bul_h.push_back(new Bullet_H(hero.getposX(), hero.getposY()));
				}
			}

		}

		// Оживляем врагов
		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
		{
			(*it_enemy)->update(time);
		}

		// Оживляем пули героя
		for (it_h = bul_h.begin(); it_h != bul_h.end(); it_h++)
		{
			(*it_h)->update(time);
		}

		// удаляем пули героя, если они улетели за карту или попали во врага
		for (it_h = bul_h.begin(); it_h != bul_h.end();)
		{
			if ((*it_h)->getLife() == false)	
			{
				it_h = bul_h.erase(it_h); 
			}
			else  
			{
				it_h++;
			}
		}

		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
		{
			if ((*it_enemy)->getLife())
			{
				// Выстрелы врага
				//time2 += time;
				if ((*it_enemy)->shoot_delay()  /*time2 >= time * delay*/)
				{
					bul_e.push_back(new Bullet_E((*it_enemy)->getposX(), (*it_enemy)->getposY()));
					//time2 = 0;
				}
				// Оживляем пули врага
				/*for (it_e = bul_e.begin(); it_e != bul_e.end(); it_e++)
				{
					(*it_e)->update(time);
				}*/
				// Обработка попадания во врага
				for (it_h = bul_h.begin(); it_h != bul_h.end(); it_h++)
				{
					if ((*it_enemy)->getRect().intersects((*it_h)->getRect()))
					{
						// После смерти врага его пули удаляются
						for (it_e = bul_e.begin(); it_e != bul_e.end(); it_e++)
						{
							(*it_e)->setLife(false);
						}
						(*it_enemy)->setHP(-(*it_h)->getDamage());
						(*it_h)->setLife(false);
						hero.setScore(100);
					}
				}
			}
		}

		// Оживляем пули врага
		for (it_e = bul_e.begin(); it_e != bul_e.end(); it_e++)
		{
			(*it_e)->update(time);
		}

		// Обработка попадания в героя
		if (hero.getLife())
		{
			for (it_e = bul_e.begin(); it_e != bul_e.end(); it_e++)
			{
				if (hero.getRect().intersects((*it_e)->getRect()))
				{
					hero.setHP(-(*it_e)->getDamage());
					(*it_e)->setLife(false);
				}
			}
		}
		// Удаляем пули врага, если они улетели за карту или попали в героя
		for (it_e = bul_e.begin(); it_e != bul_e.end();)
		{
			if ((*it_e)->getLife() == false)	
			{
				it_e = bul_e.erase(it_e); 
			}
			else  
			{
				it_e++;
			}
		}
		
		hero.update(time);
		
		window.clear(); 

		if (hero.getLife())
		{
			window.draw(hero.getimage());
		}

		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
		{
			if ((*it_enemy)->getLife())
			{
				window.draw((*it_enemy)->getimage());
			}
		}

		for (it_h = bul_h.begin(); it_h != bul_h.end(); it_h++)
		{
			if ((*it_h)->getLife())
				window.draw((*it_h)->getimage());
		}

		for (it_e = bul_e.begin(); it_e != bul_e.end(); it_e++)
		{
			if ((*it_e)->getLife())
				window.draw((*it_e)->getimage());
		}
		
		// Вывод жизней и очков на экран
		std::ostringstream playerHPString;
		std::ostringstream playerScoreString;
		playerHPString << hero.getHP();
		playerScoreString << hero.getScore();
		text_hp.setString("Health: " + playerHPString.str());
		text_hp.setPosition(600, 0);
		text_score.setString("Score: " + playerScoreString.str());
		text_score.setPosition(10, 0);
		window.draw(text_hp);
		window.draw(text_score);

		window.display();
	}


	return 0;
}


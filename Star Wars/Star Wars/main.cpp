// main.cpp
#include "hero.h"
#include "enemy.h"
#include "bullet.h"
#include "bonus.h"
#include <iostream> 
#include <sstream>
#include <list>

int main()
{
	Hero hero;
	Bonus HP(0);
	Bonus Armor(1);
	int enemy_count = 4;
	int enemy_in_game = 0;	

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(weigth, height, desktop.bitsPerPixel), "Star Wars");

	Font font;
	font.loadFromFile("zealot.ttf");
	Text text_hp("", font, 20);
	text_hp.setColor(Color::Red);
	Text text_score("", font, 20);
	text_score.setColor(Color::Red);
	Text text_lose("", font, 50);
	text_lose.setColor(Color::Red);
	Text text_armor("", font, 20);
	text_armor.setColor(Color::Green);

	std::list<Enemy*>  enemies; 
	std::list<Enemy*>::iterator it_enemy; 

	std::list<Bullet*>  bul_h; 
	std::list<Bullet*>  bul_e; 
	std::list<Bullet*>::iterator it_h; 
	std::list<Bullet*>::iterator it_e; 

	float CurrentFrame = 0;
	Clock clock;
	Clock clock2;
	Clock clock3;

	int shoot_time = 0;
	int time2 = 0;

	for (int i = 0; i < enemy_count; i++)
	{
		enemies.push_back(new Enemy());
		enemy_in_game++;
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
				if ((event.key.code == sf::Keyboard::Space) && (hero.getLife()) && (shoot_time >= delay / 12))
				{
					clock2.restart();
					bul_h.push_back(new Bullet("hero", hero.getposX(), hero.getposY()));
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

		// Удаляем пули героя, если они улетели за карту или попали во врага
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

		// Выстрелы врага
		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
		{
			if ((*it_enemy)->getLife())
			{
				if ((*it_enemy)->shoot_delay())
				{
					bul_e.push_back(new Bullet("enemy", (*it_enemy)->getposX(), (*it_enemy)->getposY()));
				}
				// Проверяем попадание во врага
				for (it_h = bul_h.begin(); it_h != bul_h.end(); it_h++)
				{
					if ((*it_enemy)->getRect().intersects((*it_h)->getRect()))
					{
						clock3.restart();
						(*it_enemy)->setHP(-(*it_h)->getDamage());
						(*it_h)->setLife(false);
						hero.setScore(100);
					}
				}
			}
			else
			{
				time2 = clock3.getElapsedTime().asMilliseconds();
			}
		}

		// После убийства одного врага, добавляем "нового"  
		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
		{
			if (!((*it_enemy)->getLife()) && (time2 >= 800))
			{
				clock3.restart();
				(*it_enemy)->setLife(true);
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
					if (hero.getArmor())
					{
						hero.setArmor(-(*it_e)->getDamage());
					}
					else
					{
						hero.setHP(-(*it_e)->getDamage());
					}
					(*it_e)->setLife(false);
				}
			}
		}

		// Обработка сбора бонусов
		if (hero.getLife())
		{
			if (hero.getRect().intersects(HP.getRect()))
			{
				hero.setHP(HP.getHP());
				HP.setLife(false);
			}
			if (hero.getRect().intersects(Armor.getRect()))
			{
				Armor.setLife(false);
				hero.setArmor(true);
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
		
		HP.update(time);
		Armor.update(time);
		hero.update(time);
		
		window.clear(); 

		if (hero.getLife())
		{
			window.draw(hero.getimage());
		}

		if (HP.getLife())
		{
			window.draw(HP.getimage());
		}

		if (Armor.getLife())
		{
			window.draw(Armor.getimage());
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

		// Если герой умер или враги смогли пролететь, то вы проиграли
		for (it_enemy = enemies.begin(); it_enemy != enemies.end(); it_enemy++)
		{
			if (((*it_enemy)->getposY() >= (height - size_enemy - 5)) || !(hero.getLife()))
			{
				hero.setLife(false);
				text_lose.setString("You are lose!");
				text_lose.setPosition(150, height / 2 - 50);
				window.draw(text_lose);
			}
		}

		// Вывод количества брони, если она есть
		if (hero.getArmor())
		{
			std::ostringstream playerArmorString;
			playerArmorString << hero.getArmor_HP();
			text_armor.setString("Armor: " + playerArmorString.str());
			text_armor.setPosition(350, 0);
			window.draw(text_armor);
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


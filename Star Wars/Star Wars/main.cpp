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
	int enemyCount = 4;
	int enemyInGame = 0;	

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(weigth, height, desktop.bitsPerPixel), "Star Wars");

	Font font;
	font.loadFromFile("zealot.ttf");
	Text textHp("", font, 20);
	textHp.setColor(Color::Red);
	Text textScore("", font, 20);
	textScore.setColor(Color::Red);
	Text textLose("", font, 50);
	textLose.setColor(Color::Red);
	Text textArmor("", font, 20);
	textArmor.setColor(Color::Green);

	std::list<Enemy*>  enemies; 
	std::list<Enemy*>::iterator itEnemy; 

	std::list<Bullet*>  bullHero; 
	std::list<Bullet*>  bullEnemy; 
	std::list<Bullet*>::iterator itBull; 

	Clock clock;
	Clock clock2;
	Clock clock3;

	int shootTime = 0;
	int time2 = 0;

	for (int i = 0; i < enemyCount; i++)
	{
		enemies.push_back(new Enemy());
		enemyInGame++;
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
			shootTime = clock2.getElapsedTime().asMilliseconds();
			if (event.type == sf::Event::KeyPressed)
			{
				if ((event.key.code == sf::Keyboard::Space) && (hero.getLife()) && (shootTime >= delay / 12))
				{
					clock2.restart();
					bullHero.push_back(new Bullet("hero", hero.getPosX(), hero.getPosY()));
				}
			}
		}

		// Оживляем врагов
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			(*itEnemy)->update(time);
		}

		// Оживляем пули героя
		for (itBull = bullHero.begin(); itBull != bullHero.end(); itBull++)
		{
			(*itBull)->update(time);
		}

		// Удаляем пули героя, если они улетели за карту или попали во врага
		for (itBull = bullHero.begin(); itBull != bullHero.end();)
		{
			if ((*itBull)->getLife() == false)	
			{
				itBull = bullHero.erase(itBull); 
			}
			else  
			{
				itBull++;
			}
		}

		// Выстрелы врага
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			if ((*itEnemy)->getLife())
			{
				if ((*itEnemy)->shootDelay())
				{
					bullEnemy.push_back(new Bullet("enemy", (*itEnemy)->getPosX(), (*itEnemy)->getPosY()));
				}
				// Проверяем попадание во врага
				for (itBull = bullHero.begin(); itBull != bullHero.end(); itBull++)
				{
					if ((*itEnemy)->getRect().intersects((*itBull)->getRect()))
					{
						clock3.restart();
						(*itEnemy)->setHP(-(*itBull)->getDamage());
						(*itBull)->setLife(false);
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
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			if (!((*itEnemy)->getLife()) && (time2 >= 1000))
			{
				clock3.restart();
				(*itEnemy)->setLife(true);
			}
		}

		// Оживляем пули врага
		for (itBull = bullEnemy.begin(); itBull != bullEnemy.end(); itBull++)
		{
			(*itBull)->update(time);
		}

		// Обработка попадания в героя
		if (hero.getLife())
		{
			for (itBull = bullEnemy.begin(); itBull != bullEnemy.end(); itBull++)
			{
				if (hero.getRect().intersects((*itBull)->getRect()))
				{
					if (hero.getArmor())
					{
						hero.setArmor(-(*itBull)->getDamage());
					}
					else
					{
						hero.setHP(-(*itBull)->getDamage());
					}
					(*itBull)->setLife(false);
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
		for (itBull = bullEnemy.begin(); itBull != bullEnemy.end();)
		{
			if ((*itBull)->getLife() == false)	
			{
				itBull = bullEnemy.erase(itBull); 
			}
			else  
			{
				itBull++;
			}
		}
		
		// Оживляем бонус доп. жизней
		HP.update(time);

		// Оживляем бонус брони
		Armor.update(time);

		// Оживляем героя
		hero.update(time);
		
		window.clear(); 

		// Рисуем героя
		if (hero.getLife())
		{
			window.draw(hero.getImage());
		}

		// Рисуем бонус доп. жизни
		if (HP.getLife())
		{
			window.draw(HP.getImage());
		}

		// Рисуем бонус броню
		if (Armor.getLife())
		{
			window.draw(Armor.getImage());
		}

		// Рисуем врагов
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			if ((*itEnemy)->getLife())
			{
				window.draw((*itEnemy)->getImage());
			}			
		}

		// Рисуем пули героя
		for (itBull = bullHero.begin(); itBull != bullHero.end(); itBull++)
		{
			if ((*itBull)->getLife())
				window.draw((*itBull)->getImage());
		}

		// Рисуем пули врагов
		for (itBull = bullEnemy.begin(); itBull != bullEnemy.end(); itBull++)
		{
			if ((*itBull)->getLife())
				window.draw((*itBull)->getImage());
		}

		// Если герой умер или враги смогли пролететь, то вы проиграли
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			if (((*itEnemy)->getPosY() >= (height - sizeEnemy - 5)) || !(hero.getLife()))
			{
				hero.setLife(false);
				textLose.setString("You are lose!");
				textLose.setPosition(150, height / 2 - 50);
				window.draw(textLose);
			}
		}

		// Вывод количества брони, если она есть
		if (hero.getArmor())
		{
			std::ostringstream playerArmorString;
			playerArmorString << hero.getArmorHp();
			textArmor.setString("Armor: " + playerArmorString.str());
			textArmor.setPosition(350, 0);
			window.draw(textArmor);
		}
		
		// Вывод жизней и очков на экран
		std::ostringstream playerHPString;
		std::ostringstream playerScoreString;
		playerHPString << hero.getHP();
		playerScoreString << hero.getScore();
		textHp.setString("Health: " + playerHPString.str());
		textHp.setPosition(600, 0);
		textScore.setString("Score: " + playerScoreString.str());
		textScore.setPosition(10, 0);
		window.draw(textHp);
		window.draw(textScore);

		window.display();

	}

	// Очистка памяти
	for (itBull = bullHero.begin(); itBull != bullHero.end();)
	{
		itBull = bullHero.erase(itBull); 
	}

	for (itBull = bullEnemy.begin(); itBull != bullEnemy.end();)
	{
		itBull = bullEnemy.erase(itBull); 
	}

	for (itEnemy = enemies.begin(); itEnemy != enemies.end();)
	{
		itEnemy = enemies.erase(itEnemy); 
	}

	return 0;
}


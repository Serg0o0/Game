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

			// ������� �� ������� �������
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

		// �������� ������
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			(*itEnemy)->update(time);
		}

		// �������� ���� �����
		for (itBull = bullHero.begin(); itBull != bullHero.end(); itBull++)
		{
			(*itBull)->update(time);
		}

		// ������� ���� �����, ���� ��� ������� �� ����� ��� ������ �� �����
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

		// �������� �����
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			if ((*itEnemy)->getLife())
			{
				if ((*itEnemy)->shootDelay())
				{
					bullEnemy.push_back(new Bullet("enemy", (*itEnemy)->getPosX(), (*itEnemy)->getPosY()));
				}
				// ��������� ��������� �� �����
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

		// ����� �������� ������ �����, ��������� "������"  
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			if (!((*itEnemy)->getLife()) && (time2 >= 1000))
			{
				clock3.restart();
				(*itEnemy)->setLife(true);
			}
		}

		// �������� ���� �����
		for (itBull = bullEnemy.begin(); itBull != bullEnemy.end(); itBull++)
		{
			(*itBull)->update(time);
		}

		// ��������� ��������� � �����
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

		// ��������� ����� �������
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

		// ������� ���� �����, ���� ��� ������� �� ����� ��� ������ � �����
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
		
		// �������� ����� ���. ������
		HP.update(time);

		// �������� ����� �����
		Armor.update(time);

		// �������� �����
		hero.update(time);
		
		window.clear(); 

		// ������ �����
		if (hero.getLife())
		{
			window.draw(hero.getImage());
		}

		// ������ ����� ���. �����
		if (HP.getLife())
		{
			window.draw(HP.getImage());
		}

		// ������ ����� �����
		if (Armor.getLife())
		{
			window.draw(Armor.getImage());
		}

		// ������ ������
		for (itEnemy = enemies.begin(); itEnemy != enemies.end(); itEnemy++)
		{
			if ((*itEnemy)->getLife())
			{
				window.draw((*itEnemy)->getImage());
			}			
		}

		// ������ ���� �����
		for (itBull = bullHero.begin(); itBull != bullHero.end(); itBull++)
		{
			if ((*itBull)->getLife())
				window.draw((*itBull)->getImage());
		}

		// ������ ���� ������
		for (itBull = bullEnemy.begin(); itBull != bullEnemy.end(); itBull++)
		{
			if ((*itBull)->getLife())
				window.draw((*itBull)->getImage());
		}

		// ���� ����� ���� ��� ����� ������ ���������, �� �� ���������
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

		// ����� ���������� �����, ���� ��� ����
		if (hero.getArmor())
		{
			std::ostringstream playerArmorString;
			playerArmorString << hero.getArmorHp();
			textArmor.setString("Armor: " + playerArmorString.str());
			textArmor.setPosition(350, 0);
			window.draw(textArmor);
		}
		
		// ����� ������ � ����� �� �����
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

	// ������� ������
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


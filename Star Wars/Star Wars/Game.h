// Game.h заголовочный файл с персонажами и оружием.

namespace game
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	const int weigth = 800;
	const int height = 600;

	ref class Hero
	{
	private:
		int hp;
		int posX, posY;
		
	public:
		Hero() 
		{
			hp = 100;
			posX = (weigth - 50) / 2;
			posY = height - 50;
		}
		Image^ getimage();
		int getHP();
		int getposX();
		int getposY();
		void setposX(int);
		void setposY(int);
	};

	ref class Alian : public Hero
	{
	private:
		int hp;
		int posX, posY;

	public:
		Alian()
		{
			hp = 100;
		}
		Image^ getimage();
		int getHP();
		int getposX();
		int getposY();
		void setposX(int);
		void setposY(int);
	};

	ref class Bullet
	{
	private:
		int damage;
		int posX, posY;

	public:
		Bullet()
		{
			damage = 50;
		}
		Image^ getimage();
		int getposX();
		int getposY();
		void setposX(int);
		void setposY(int);
		int hit();
	};

	Image^ Hero::getimage()
	{
		return Image::FromFile("hero.png");
	}

	Image^ Alian::getimage()
	{
		return Image::FromFile("alian.png");
	}

	Image^ Bullet::getimage()
	{
		return Image::FromFile("bullet.png");
	}

	int Hero::getHP()
	{
		return hp;
	}

	int Hero::getposX()
	{
		return posX;
	}

	int Hero::getposY()
	{
		return posY;
	}

	void Hero::setposX(int x)
	{
		posX = x;
	}

	void Hero::setposY(int y)
	{
		posY = y;
	}

	int Alian::getHP()
	{
		return hp;
	}

	int Alian::getposX()
	{
		return posX;
	}

	int Alian::getposY()
	{
		return posY;
	}

	void Alian::setposX(int x)
	{
		posX = x;
	}

	void Alian::setposY(int y)
	{
		posY = y;
	}

	int Bullet::getposX()
	{
		return posX;
	}

	int Bullet::getposY()
	{
		return posY;
	}

	void Bullet::setposX(int x)
	{
		posX = x;
	}

	void Bullet::setposY(int y)
	{
		posY = y;
	}

	int Bullet::hit()
	{
		return damage;
	}
}
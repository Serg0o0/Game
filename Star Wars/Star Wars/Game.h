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
		int posX;
		int posY;
		
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

	Image^ Hero::getimage()
		{
			return Image::FromFile("hero.png");
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

}
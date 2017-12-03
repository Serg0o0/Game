#include "Game.h"
#pragma once

namespace StarWars {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace game;

	/// <summary>
	/// —водка дл€ Form1
	/// </summary>

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			this->pictureBox1->Size = System::Drawing::Size(weigth, height);
			this->ClientSize = System::Drawing::Size(weigth, height);
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;



	protected: 

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Black;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(800, 600);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 600);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form1";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}

#pragma endregion

		Hero hero;

private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 //Brush^ fill = gcnew SolidBrush(Color::Orange);
			 Graphics^ b = pictureBox1->CreateGraphics();

			 pictureBox1->Refresh();
			 
			 switch (Convert::ToInt32(e->KeyCode))
			 {
			 case 27:
				 Close();
				 break;
			 case 37:
				 if (hero.getposX() > 0) 
					 hero.setposX(hero.getposX() - 15);
				 b->DrawImage(hero.getimage(), PointF(hero.getposX(), hero.getposY()));
				 break;
			 case 39:
				 if (hero.getposX() < (weigth - 50)) 
					 hero.setposX(hero.getposX() + 15);
				 b->DrawImage(hero.getimage(), PointF(hero.getposX(), hero.getposY()));
				 break;
			 case 38:
				 if (hero.getposY() > (2 * height / 3)) 
					 hero.setposY(hero.getposY() - 15);
				 b->DrawImage(hero.getimage(), PointF(hero.getposX(), hero.getposY()));
				 break;
			 case 40:
				 if (hero.getposY() < (height - 50)) 
					 hero.setposY(hero.getposY() + 15);
				 b->DrawImage(hero.getimage(), PointF(hero.getposX(), hero.getposY()));
				 break;
			 default:
				 b->DrawImage(hero.getimage(), PointF(hero.getposX(), hero.getposY()));
				 break;
			 }

			 //delete fill;
			 delete b;
		 }
};
}
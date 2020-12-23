#pragma once
#include <iostream>
#include <msclr\marshal_cppstd.h>
#include <windows.h>
//Для работы со строками
#include <string>
#include <sstream>

extern std::string Login;
extern int Scor, Life;

namespace airplan {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media; //для воспроизведения звуков
	using namespace System::IO; //для записи
	using namespace std;


	/// <summary>
	/// Сводка для gamewin
	/// </summary>
	public ref class gamewin : public System::Windows::Forms::Form
	{
	public:	
		gamewin(int n)
		{
			InitializeComponent();
			rnd = gcnew System::Random();
			enemy1->Left = -200;
			enemy2->Left = -500;
			enemy3->Left = -800;
			bullet->Top = -100;
			bullet->Left = -100;
			if (n == 2) {
			score = Scor;
			i = Life;
			}
			else {
				score = 0;
				i = 0;
			}
			lvl = 1;
		}
		
		void string_to_char(string str, char *b)
		{
			int i;
			for (i = 0; i < str.length(); i++)
				b[i] = str[i];
			b[i] = '\0';
		}

		bool save(char* n, string log, int score, int i)
		{
			HANDLE hEventTermination,
				hEvent,
				hServer1,
				hMemory;
			LPCTSTR lpEventName = L"$EventName$",
				lpEventTerminationName = L"$TerminationName$",
				lpServer1 = L"$Server$",
				lpFileShareName = L"$ShareName$";
			LPVOID memory;

			hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpEventName);
			hServer1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpServer1);
			hEventTermination = OpenEvent(EVENT_ALL_ACCESS, FALSE, lpEventTerminationName);
			hMemory = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, lpFileShareName);
			memory = MapViewOfFile(hMemory, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);


			char message[255];
			bool ch;
			//Проверка наличия отображения файла в памяти
			if (hMemory != NULL)
			{
				string message1 = (string)n + " " + log + " " + to_string(score) + " " + to_string(i);
				char message3[255] = "";
				string_to_char(message1, message3);
				memcpy(memory, message3, sizeof(message3));
				SetEvent(hEvent);
				SetEvent(hEventTermination);
				WaitForSingleObject(hServer1, INFINITE);
				Sleep(100);
				memcpy(message, memory, sizeof(message));
			}
			if (message[0] == '1')
			{
				ch = true;
			}
			else {
				ch = false;
			}
			ResetEvent(hServer1);
			return ch;
		}





		//проверка попадания пули во врага
	public: void enemyHit()
	{
		SoundPlayer^ sound2 = gcnew SoundPlayer(Application::StartupPath + "\\popal.wav");

		if ((bullet->Location.X < enemy1->Location.X + 72) && (bullet->Location.X + 13 > enemy1->Location.X)
			&& (bullet->Location.Y < enemy1->Location.Y + 56) && (bullet->Location.Y > enemy1->Location.Y))
		{
			sound2->Play();
			score += 100;
			if (score % 1000 == 0)
			{
				lvl++;
				enemyMove += 2;
			}
			enemy1->Left = -200;
			enemy1->Top = rnd->Next(90, 176);
			shooting = false;
			bulletSpeed = 0;
			bullet->Left = -100;
			bullet->Top = -100;
		}
		if ((bullet->Location.X < enemy2->Location.X + 72) && (bullet->Location.X + 13 > enemy2->Location.X)
			&& (bullet->Location.Y < enemy2->Location.Y + 56) && (bullet->Location.Y > enemy2->Location.Y))
		{
			sound2->Play();
			score += 100;
			if (score % 1000 == 0)
			{
				lvl++;
				enemyMove += 2;
			}
			enemy2->Left = -500;
			enemy2->Top = rnd->Next(176, 262);
			shooting = false;
			bulletSpeed = 0;
			bullet->Left = -100;
			bullet->Top = -100;
		}
		if ((bullet->Location.X < enemy3->Location.X + 72) && (bullet->Location.X + 13> enemy3->Location.X)
			&& (bullet->Location.Y < enemy3->Location.Y + 56) && (bullet->Location.Y > enemy3->Location.Y))
		{
			sound2->Play();
			score += 100;
			if (score % 1000 == 0)
			{
				lvl++;
				enemyMove += 2;
			}
			enemy3->Left = -800;
			enemy3->Top = rnd->Next(262, 350);
			shooting = false;
			bulletSpeed = 0;
			bullet->Left = -100;
			bullet->Top = -100;
		}

	}
		//Конец игры
	public: void GameOver()
	{
		playTimer->Enabled = false;
		MessageBox::Show("Вы проиграли!\nВаш счет: "+score+ "\nУровень: "+lvl, "Конец игры", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
		this->Close();
	}
	
	public: void enemyPosition()
	{
		if (enemy1->Left >= 832 || enemy2->Left >= 832 || enemy3->Left >= 832) //если враг достиг предела экрана
		{
			i++; //счетчик потеряных жизней
			if (i >= 1)
				life1->Visible = false; //отображение жизни на экране
			if (i >= 2)
				life2->Visible = false;
			if (i >= 3)
				life3->Visible = false;
			if (i >= 4)
				life4->Visible = false;
			if (i >= 5)
			{
				life5->Visible = false;
				GameOver();  
			}

			if (enemy1->Left >= 832 ) //если враг достиг предела экрана
			{
				enemy1->Left = -200; //перемещение на стартовую позицию
				enemy1->Top = rnd->Next(90, 176);
			}
			if (enemy2->Left >= 832)
			{
				enemy2->Left = -500;
				enemy2->Top = rnd->Next(176, 262);
			}
			if (enemy3->Left >= 832)
			{
				enemy3->Left = -800;
				enemy3->Top = rnd->Next(262, 350);
			}
		}
	}


	private:
		System::Random^ rnd;
		int moveLeft = 0;
		int enemyMove = 2;
		int bulletSpeed = 20;
		bool shooting = false;
		int  k = 0, i, score, lvl;
	private: System::Windows::Forms::Label^  pause;
	private: System::Windows::Forms::Button^  Exitbutton;
	private: System::Windows::Forms::Button^  Savebutton;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  Level;


	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~gamewin()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  playTimer;
	protected:

	private: System::Windows::Forms::PictureBox^  enemy1;
	private: System::Windows::Forms::PictureBox^  enemy2;
	private: System::Windows::Forms::PictureBox^  enemy3;
	private: System::Windows::Forms::PictureBox^  life1;
	private: System::Windows::Forms::PictureBox^  life2;
	private: System::Windows::Forms::PictureBox^  life3;
	private: System::Windows::Forms::PictureBox^  life4;
	private: System::Windows::Forms::PictureBox^  life5;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  Score;
	private: System::Windows::Forms::PictureBox^  player;
	private: System::Windows::Forms::PictureBox^  bullet;

	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(gamewin::typeid));
			this->playTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->enemy1 = (gcnew System::Windows::Forms::PictureBox());
			this->enemy2 = (gcnew System::Windows::Forms::PictureBox());
			this->enemy3 = (gcnew System::Windows::Forms::PictureBox());
			this->life1 = (gcnew System::Windows::Forms::PictureBox());
			this->life2 = (gcnew System::Windows::Forms::PictureBox());
			this->life3 = (gcnew System::Windows::Forms::PictureBox());
			this->life4 = (gcnew System::Windows::Forms::PictureBox());
			this->life5 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Score = (gcnew System::Windows::Forms::Label());
			this->player = (gcnew System::Windows::Forms::PictureBox());
			this->bullet = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pause = (gcnew System::Windows::Forms::Label());
			this->Exitbutton = (gcnew System::Windows::Forms::Button());
			this->Savebutton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Level = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->player))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// playTimer
			// 
			this->playTimer->Enabled = true;
			this->playTimer->Interval = 10;
			this->playTimer->Tick += gcnew System::EventHandler(this, &gamewin::playTimer_Tick);
			// 
			// enemy1
			// 
			this->enemy1->BackColor = System::Drawing::Color::Transparent;
			this->enemy1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"enemy1.Image")));
			this->enemy1->Location = System::Drawing::Point(12, 86);
			this->enemy1->Name = L"enemy1";
			this->enemy1->Size = System::Drawing::Size(56, 82);
			this->enemy1->TabIndex = 0;
			this->enemy1->TabStop = false;
			// 
			// enemy2
			// 
			this->enemy2->BackColor = System::Drawing::Color::Transparent;
			this->enemy2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"enemy2.Image")));
			this->enemy2->Location = System::Drawing::Point(12, 215);
			this->enemy2->Name = L"enemy2";
			this->enemy2->Size = System::Drawing::Size(56, 82);
			this->enemy2->TabIndex = 1;
			this->enemy2->TabStop = false;
			// 
			// enemy3
			// 
			this->enemy3->BackColor = System::Drawing::Color::Transparent;
			this->enemy3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"enemy3.Image")));
			this->enemy3->Location = System::Drawing::Point(12, 343);
			this->enemy3->Name = L"enemy3";
			this->enemy3->Size = System::Drawing::Size(56, 82);
			this->enemy3->TabIndex = 2;
			this->enemy3->TabStop = false;
			// 
			// life1
			// 
			this->life1->BackColor = System::Drawing::Color::Transparent;
			this->life1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"life1.Image")));
			this->life1->Location = System::Drawing::Point(628, 19);
			this->life1->Name = L"life1";
			this->life1->Size = System::Drawing::Size(31, 32);
			this->life1->TabIndex = 3;
			this->life1->TabStop = false;
			// 
			// life2
			// 
			this->life2->BackColor = System::Drawing::Color::Transparent;
			this->life2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"life2.Image")));
			this->life2->Location = System::Drawing::Point(665, 19);
			this->life2->Name = L"life2";
			this->life2->Size = System::Drawing::Size(31, 32);
			this->life2->TabIndex = 4;
			this->life2->TabStop = false;
			// 
			// life3
			// 
			this->life3->BackColor = System::Drawing::Color::Transparent;
			this->life3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"life3.Image")));
			this->life3->Location = System::Drawing::Point(702, 19);
			this->life3->Name = L"life3";
			this->life3->Size = System::Drawing::Size(31, 32);
			this->life3->TabIndex = 5;
			this->life3->TabStop = false;
			// 
			// life4
			// 
			this->life4->BackColor = System::Drawing::Color::Transparent;
			this->life4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"life4.Image")));
			this->life4->Location = System::Drawing::Point(739, 19);
			this->life4->Name = L"life4";
			this->life4->Size = System::Drawing::Size(31, 32);
			this->life4->TabIndex = 6;
			this->life4->TabStop = false;
			// 
			// life5
			// 
			this->life5->BackColor = System::Drawing::Color::Transparent;
			this->life5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"life5.Image")));
			this->life5->Location = System::Drawing::Point(776, 19);
			this->life5->Name = L"life5";
			this->life5->Size = System::Drawing::Size(31, 32);
			this->life5->TabIndex = 7;
			this->life5->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(84, 19);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(80, 25);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Score:";
			// 
			// Score
			// 
			this->Score->AutoSize = true;
			this->Score->BackColor = System::Drawing::Color::Transparent;
			this->Score->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Score->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Score->Location = System::Drawing::Point(170, 19);
			this->Score->Name = L"Score";
			this->Score->Size = System::Drawing::Size(25, 25);
			this->Score->TabIndex = 9;
			this->Score->Text = L"0";
			// 
			// player
			// 
			this->player->BackColor = System::Drawing::Color::Transparent;
			this->player->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"player.Image")));
			this->player->Location = System::Drawing::Point(386, 520);
			this->player->Name = L"player";
			this->player->Size = System::Drawing::Size(53, 73);
			this->player->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->player->TabIndex = 10;
			this->player->TabStop = false;
			// 
			// bullet
			// 
			this->bullet->BackColor = System::Drawing::Color::Transparent;
			this->bullet->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"bullet.Image")));
			this->bullet->Location = System::Drawing::Point(403, 488);
			this->bullet->Name = L"bullet";
			this->bullet->Size = System::Drawing::Size(13, 37);
			this->bullet->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->bullet->TabIndex = 11;
			this->bullet->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox1->Location = System::Drawing::Point(23, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(45, 40);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 12;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &gamewin::pictureBox1_Click);
			// 
			// pause
			// 
			this->pause->AutoSize = true;
			this->pause->BackColor = System::Drawing::Color::Transparent;
			this->pause->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->pause->Location = System::Drawing::Point(330, 294);
			this->pause->Name = L"pause";
			this->pause->Size = System::Drawing::Size(166, 55);
			this->pause->TabIndex = 13;
			this->pause->Text = L"Пауза";
			this->pause->Visible = false;
			// 
			// Exitbutton
			// 
			this->Exitbutton->BackColor = System::Drawing::Color::Transparent;
			this->Exitbutton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Exitbutton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Exitbutton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Exitbutton->Location = System::Drawing::Point(374, 397);
			this->Exitbutton->Name = L"Exitbutton";
			this->Exitbutton->Size = System::Drawing::Size(75, 28);
			this->Exitbutton->TabIndex = 14;
			this->Exitbutton->TabStop = false;
			this->Exitbutton->Text = L"Выйти";
			this->Exitbutton->UseVisualStyleBackColor = false;
			this->Exitbutton->Visible = false;
			this->Exitbutton->Click += gcnew System::EventHandler(this, &gamewin::Exit_Click);
			// 
			// Savebutton
			// 
			this->Savebutton->BackColor = System::Drawing::Color::Transparent;
			this->Savebutton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->Savebutton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->Savebutton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Savebutton->Location = System::Drawing::Point(354, 363);
			this->Savebutton->Name = L"Savebutton";
			this->Savebutton->Size = System::Drawing::Size(110, 28);
			this->Savebutton->TabIndex = 15;
			this->Savebutton->TabStop = false;
			this->Savebutton->Text = L"Сохранить";
			this->Savebutton->UseVisualStyleBackColor = false;
			this->Savebutton->Visible = false;
			this->Savebutton->Click += gcnew System::EventHandler(this, &gamewin::Savebutton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(356, 19);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 25);
			this->label2->TabIndex = 16;
			this->label2->Text = L"Level:";
			// 
			// Level
			// 
			this->Level->AutoSize = true;
			this->Level->BackColor = System::Drawing::Color::Transparent;
			this->Level->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Level->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Level->Location = System::Drawing::Point(438, 19);
			this->Level->Name = L"Level";
			this->Level->Size = System::Drawing::Size(25, 25);
			this->Level->TabIndex = 17;
			this->Level->Text = L"0";
			// 
			// gamewin
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(819, 642);
			this->Controls->Add(this->Level);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->Savebutton);
			this->Controls->Add(this->Exitbutton);
			this->Controls->Add(this->pause);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->bullet);
			this->Controls->Add(this->player);
			this->Controls->Add(this->Score);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->life5);
			this->Controls->Add(this->life4);
			this->Controls->Add(this->life3);
			this->Controls->Add(this->life2);
			this->Controls->Add(this->life1);
			this->Controls->Add(this->enemy3);
			this->Controls->Add(this->enemy2);
			this->Controls->Add(this->enemy1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"gamewin";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Сбей самолет!";
			this->Load += gcnew System::EventHandler(this, &gamewin::gamewin_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &gamewin::gamewin_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &gamewin::gamewin_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->enemy3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->life5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->player))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bullet))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//загрузка формы
private: System::Void gamewin_Load(System::Object^  sender, System::EventArgs^  e) 
	{
	if (score>-1) //если выбрана загрузка игры
	{
		lvl = (score / 1000)+1;
		if (lvl != 1)
		{
			enemyMove = 2 + (lvl * 2);
		}
		//отображение жизней на экран
		if (i >= 1)
			life1->Visible = false;
		if (i >= 2)
			life2->Visible = false;
		if (i >= 3)
			life3->Visible = false;
		if (i >= 4)
			life4->Visible = false;
	}
	}
private: System::Void gamewin_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
	{
	SoundPlayer^ sound1 = gcnew SoundPlayer(Application::StartupPath + "\\gun_fire.wav"); //воспроизведение звука
	if (e->KeyCode == Keys::Left) //если нажата клавиша влево
	{
		if (player->Location.X < 0)
		{
			moveLeft = 0;
		}
		else
		{
			moveLeft = -12-(score / 3000)*3;
		}
	}
	
		if (e->KeyCode == Keys::Right) //если нажата клавиша вправо
		{
			if (player->Location.X > 769)
			{
				moveLeft = 0;
			}
			else
			{
				moveLeft = 12+(score/3000)*3;
			}
		}
	
		if (e->KeyCode == Keys::Space) //если нажат пробел
	{
		if (shooting == false)
		{
			sound1->Play();
			bulletSpeed = 20+(score/4000)*5;
			bullet->Left = player->Left + 20;
			bullet->Top = player->Top;
			shooting = true;
		}
	}
	}

private: System::Void gamewin_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) 
{
	if (e->KeyCode == Keys::Left)
		moveLeft = 0;
	else if (e->KeyCode == Keys::Right)
		moveLeft = 0;
}

		 //обработчик событий
private: System::Void playTimer_Tick(System::Object^  sender, System::EventArgs^  e)
{
	//перемещение игрока, снаряда и противников
	player->Left += moveLeft;
	bullet->Top -= bulletSpeed; 
	enemy1->Left += enemyMove; 
	enemy2->Left += enemyMove;
	enemy3->Left += enemyMove;
	Level->Text = Convert::ToString(lvl);
	Score->Text = Convert::ToString(score);//ведение счета

	enemyPosition();

	if (shooting && bullet->Top < 0) //проверка положения снаряда
	{
		shooting = false;
		bulletSpeed = 0;
		bullet->Top = -100;
		bullet->Left = -100;
	}
	enemyHit();
}


		 //вызов паузы
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		k++; //счетчик активации паузы
		if (k == 1) //отображение пайзы
		{
			playTimer->Enabled = false; //остановка времени
			pause->Visible = true;
			Exitbutton->Visible = true;
			Savebutton->Visible = true;
			Savebutton->Enabled = true;
			pictureBox1->BackgroundImage=Image::FromFile(Application::StartupPath + "\\play.png"); //смена картинки
		}
		else //отключенние паузы
		{
			playTimer->Enabled = true;
			pause->Visible = false;
			Exitbutton->Visible = false;
			Savebutton->Visible = false;
			Focus();
			k = 0;
			pictureBox1->BackgroundImage = Image::FromFile(Application::StartupPath + "\\pause.png");
		}
	}


			 //нажатие кнопки сохранить
private: System::Void Savebutton_Click(System::Object^  sender, System::EventArgs^  e) {
	Savebutton->Enabled = false; //кнопка становится неактивна
	if (save("4", Login, score, i))
	{
		MessageBox::Show("Игра сохранена!", "Уведомление", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
}
		 // выход
		 private: System::Void Exit_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 this->Close();
		 }

};
}

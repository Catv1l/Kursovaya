#pragma once
#include "MyForm.h"
#include "registration.h"
#include "records.h"
#include <msclr\marshal_cppstd.h>
#include <windows.h>
//Для работы со строками
#include <string>
#include <sstream>
extern std::string Login;
namespace airplan {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	/// <summary>
	/// Сводка для authorization
	/// </summary>
	public ref class authorization : public System::Windows::Forms::Form
	{
	public:

		authorization(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		//Метод производящий перевод числовых значений в текстовые
		void Int_To_Char(int a, char *b)
		{
			//Переводим число в строку
			string str = "";
			ostringstream s;
			s << a;
			str += s.str();
			str += ' ';

			//Переводим строку в массив символов
			string_to_char(str, b);
		}
		void string_to_char(string str, char *b)
		{
			int i;
			for (i = 0; i < str.length(); i++)
				b[i] = str[i];
			b[i] = '\0';
		}

		bool a(char* n, string log, string pass)
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
			

			char message[255] = "";
			bool ch;
			//Проверка наличия отображения файла в памяти
			if (hMemory != NULL)
			{
				string message1 = (string)n + " " + log + " " + pass;
				char message3[255] = "";
				string_to_char(message1, message3);
				memcpy(memory, message3, sizeof(message3));
				SetEvent(hEvent);
				SetEvent(hEventTermination);
				WaitForSingleObject(hServer1, INFINITE);
				Sleep(100);
				memcpy(message, memory, sizeof(memory)); 
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


	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~authorization()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button4;
	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(authorization::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(127, 208);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(186, 35);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Войти";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &authorization::button1_Click);
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(127, 249);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(186, 35);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Зарегистрироваться";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &authorization::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(127, 72);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(186, 26);
			this->textBox1->TabIndex = 5;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(127, 130);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(186, 26);
			this->textBox2->TabIndex = 6;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::Control;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(183, 45);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 24);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Логин:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::SystemColors::Control;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(176, 103);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 24);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Пароль:";
			// 
			// button4
			// 
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(321, 281);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(107, 35);
			this->button4->TabIndex = 9;
			this->button4->Text = L"Выйти";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &authorization::button4_Click);
			// 
			// authorization
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(440, 328);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"authorization";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Сбей самолет!";
			this->Load += gcnew System::EventHandler(this, &authorization::authorization_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		//выход
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		//отображение сообщения, если выбрано "Да" закрытие формы и проекта
		if (MessageBox::Show("Выйти из игры?", "Внимание!", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
			System::Windows::Forms::DialogResult::Yes)
			Application::Exit();
	}

		//вход
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	Login = msclr::interop::marshal_as<string>(textBox1->Text);
	string upass = msclr::interop::marshal_as<string>(textBox2->Text);
	MyForm^ Menu = gcnew MyForm();
	if (textBox1->Text == "" && textBox2->Text == "" || textBox1->Text == "" || textBox2->Text == "")
	{
		MessageBox::Show("Вы ничего не ввели", "Внимание!", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	else
	{
		bool s;
		s = a("1", Login, upass);
		if (s) {
			MessageBox::Show("Приятной игры, " + textBox1->Text + "!", "Добро пожаловать!", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			this->Hide();
			Menu->Show();
		}
		else 
		{
			MessageBox::Show("Неверный логин или пароль!", "Внимание!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	registration^ Reg = gcnew registration();
	Reg->ShowDialog();
}

private: System::Void authorization_Load(System::Object^  sender, System::EventArgs^  e) {
	SoundPlayer^ soundF = gcnew SoundPlayer(Application::StartupPath + "\\fon.wav"); //воспроизведение звука
	soundF->PlayLooping();
}
};
}

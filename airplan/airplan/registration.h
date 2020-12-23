#pragma once
#include <msclr\marshal_cppstd.h>
#include <windows.h>
//Для работы со строками
#include <string>
#include <sstream>
namespace airplan {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::OleDb;
	using namespace std;

	/// <summary>
	/// Сводка для registration
	/// </summary>
	public ref class registration : public System::Windows::Forms::Form
	{
	public:

		/*bool add_acc(TextBox^ Login, TextBox^ Password)
		{
			auto connection = gcnew OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application::StartupPath + "\\users.accdb");
			connection->Open();
			auto strConnect = gcnew OleDbCommand("SELECT * FROM LOG_PASS WHERE login ='" + Login->Text + "'AND password ='" + Password->Text + "'", connection);
			if (strConnect->ExecuteScalar() != nullptr)
			{
				MessageBox::Show("Пользователь с именем " + Login->Text + " уже существует", "Внимание!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				connection->Close();
				return false;
			}
			else 
			{
				strConnect = gcnew OleDbCommand("INSERT INTO [LOG_PASS] (" + "[login],[password]) VALUES ('" + Login->Text + "','" + Password->Text + "')");
				strConnect->Connection = connection;
				strConnect->ExecuteNonQuery();
				connection->Close();
				MessageBox::Show("Вы успешно зарегистрировались в системе", "Регистрация", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				return true;
			}
		}*/

		registration(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		void string_to_char(string str, char *b)
		{
			int i;
			for (i = 0; i < str.length(); i++)
				b[i] = str[i];
			b[i] = '\0';
		}

		bool reg(char* n, string log, string pass)
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
		~registration()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button4;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;

	protected:

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(registration::typeid));
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button4
			// 
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(321, 281);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(107, 35);
			this->button4->TabIndex = 16;
			this->button4->Text = L"Выйти";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &registration::button4_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(176, 103);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(88, 24);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Пароль:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(183, 45);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 24);
			this->label1->TabIndex = 14;
			this->label1->Text = L"Логин:";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(127, 130);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(186, 26);
			this->textBox2->TabIndex = 13;
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(127, 72);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(186, 26);
			this->textBox1->TabIndex = 12;
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(127, 217);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(186, 35);
			this->button2->TabIndex = 11;
			this->button2->Text = L"Зарегистрироваться";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &registration::button2_Click);
			// 
			// registration
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->ClientSize = System::Drawing::Size(440, 328);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"registration";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Регистрация";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		string ulog = msclr::interop::marshal_as<string>(textBox1->Text);
		string upass = msclr::interop::marshal_as<string>(textBox2->Text);
		if (textBox1->Text == "" && textBox2->Text == "" || textBox1->Text == "" || textBox2->Text == "")
		{
			MessageBox::Show("Вы ничего не ввели", "Внимание!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else
		{
			bool s;
			s = reg("2", ulog, upass);
			if (s) {
				MessageBox::Show("Вы успешно зарегистрировались в системе", "Регистрация", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				this->Close();
			}
			else
			{
				MessageBox::Show("Пользователь с логином: " + textBox1->Text + " уже существует", "Внимание!", MessageBoxButtons::OK, MessageBoxIcon::Error);

			}
			//if (add_acc(textBox1, textBox2))
		}
	}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}
};
}

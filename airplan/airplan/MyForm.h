#pragma once
#include "gamewin.h"
#include "pravila.h"
#include "records.h"
#include <msclr\marshal_cppstd.h>
#include <windows.h>
//��� ������ �� ��������
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
	using namespace std;
	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm()
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}
		void string_to_char(string str, char *b)
		{
			int i;
			for (i = 0; i < str.length(); i++)
				b[i] = str[i];
			b[i] = '\0';
		}
		//�������� � ���������� ������ �� ����� � �����������
		bool opensave(char* n, string log)
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
			//�������� ������� ����������� ����� � ������
			if (hMemory != NULL)
			{
				string message1 = (string)n + " " + log;
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
				char str_score[255];
				char str_life[1];
				for (int i = 2; i < 255; i++)
				{
					str_score[i-2] = message[i];
					if (message[i] == ' ')
					{
						str_life[0] = message[i+1];
						break;
					}
				}
				Scor = atoi(str_score);
				Life = atoi(str_life);
			}
			else {
				ch = false;
			}
	
			ResetEvent(hServer1);
			return ch;
		}



		bool delsave(char* n, string log)
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
			//�������� ������� ����������� ����� � ������
			if (hMemory != NULL)
			{
				string message1 = (string)n + " " + log;
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


	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: int score, i;

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::Button^  button6;
	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(167, 79);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(107, 35);
			this->button1->TabIndex = 1;
			this->button1->Text = L"����� ����\r\n";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(167, 211);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(107, 35);
			this->button2->TabIndex = 4;
			this->button2->Text = L"�����";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->Enabled = false;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(167, 120);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(107, 35);
			this->button3->TabIndex = 2;
			this->button3->Text = L"���������";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button4->Enabled = false;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(167, 161);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(107, 44);
			this->button4->TabIndex = 3;
			this->button4->Text = L"�������\r\n����������";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(167, 25);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(107, 48);
			this->button5->TabIndex = 0;
			this->button5->Text = L"�������\r\n����";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button6->Location = System::Drawing::Point(167, 293);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(107, 23);
			this->button6->TabIndex = 5;
			this->button6->Text = L"�� ������";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(440, 328);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"���� �������!";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
		SoundPlayer^ soundF = gcnew SoundPlayer(Application::StartupPath + "\\fon.wav"); //��������������� �����
		// �������� ��������� ����
		private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
			soundF->PlayLooping();
			Sleep(100);
			bool s;
			s = opensave("3",Login); //�������� ������� ����������
			if (s) //���� ���� ����������
			{
				//������ "���������" � "������� ����������" ���������� ������
				button3->Enabled = true; 
				button4->Enabled = true;
			}
		}

				 // ������� "����� ����"
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		soundF->Stop();
		int c = 1;
		MyForm::Visible = false; //������� ���� �� ������������

		// �������� ������� ����� ����
		gamewin^ Game = gcnew gamewin(1);
		Game->ShowDialog();
		soundF->PlayLooping();
		// ����� �������� ���� � ����� ������� 
		MyForm::Visible = true; // ����������� �������� ����
		bool s;
		s = opensave("3", Login); //�������� ������� ����������
		if (s) 
		{
			button3->Enabled = true;
			button4->Enabled = true;
		}
	}

			 // �����
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		//����������� ���������, ���� ������� "��" �������� ����� � �������
		if (MessageBox::Show("����� �� ����?", "��������!", MessageBoxButtons::YesNo, MessageBoxIcon::Question) ==
			System::Windows::Forms::DialogResult::Yes)
			Application::Exit();

	}

			 // ������� "���������"
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		MyForm::Visible = false;
		gamewin^ Game = gcnew gamewin(2);
		soundF->Stop();
		Game->ShowDialog();
		MyForm::Visible = true;
		soundF->PlayLooping();
		bool s;
		s = opensave("3", Login); //�������� ������� ����������
		if (s)
		{
			button3->Enabled = true;
			button4->Enabled = true;
		}
	}

			 // ������� "������� ����������"
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		if (delsave("5", Login))
		{
			MessageBox::Show("���������� �������.", "�����������", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
			button3->Enabled = false;
			button4->Enabled = false;
		}
}

		 // ������� "������� ����"
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) 
{
	MyForm::Visible = false;
	pravila^ prav = gcnew pravila();
	prav->ShowDialog();
	MyForm::Visible = true;
}

		 // ������� "�� ������"
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("������:\n��������� ���������\n������� �����\n�������� ������\n����� ���������\n������ ����������\n������ ���1702\n", "���1702", MessageBoxButtons::OK);
}

};
}

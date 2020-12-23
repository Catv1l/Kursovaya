#include "pch.h"
#include <fstream>
#include <iostream>
//Для работы с Windows API
#include <Windows.h>
//Для работы со строками
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

bool remove_line(const char *filename, size_t index)
{
	std::vector<std::string> vec;
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string str;
		while (std::getline(file, str))
			vec.push_back(str);
		file.close();
		if (vec.size() < index)
			return false;
		vec.erase(vec.begin() + index);
		std::ofstream outfile(filename);
		if (outfile.is_open())
		{
			std::copy(vec.begin(), vec.end(),
				std::ostream_iterator<std::string>(outfile, "\n"));
			outfile.close();
			return true;
		}
		return false;
	}
	return false;
}


string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

string get_score(int line_num) {
	string line = "";
	int num=1;
	char char_array[255];

	std::ifstream in("C:\\temp\\Курсач Т_Т\\Server\\Debug\\save.txt"); // окрываем файл для чтения
	while (getline(in, line)&& num!=line_num)
	{	
		num++;
		if (num==line_num) strcpy_s(char_array, line.substr(line.find(" ")).c_str());
	}
	in.close();

	line = convertToString(char_array, sizeof(char_array));
	return line;
}

int Char_To_Int(char *);
bool check_acc(string, string);
bool add_acc(string, string);
bool open_save(string, string&);
bool save(string, string, string);
bool del_save(string);

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//Блокировка запуска нескольких экземпляров сервера
	HANDLE Mute;
	Mute = CreateMutex(NULL, true, L"DontOpenAnotherServ");
	DWORD wait_obj = WaitForSingleObject(Mute, 0);
	if (wait_obj != WAIT_OBJECT_0)
		exit(0);

	cout << "Сервер запущен и готовится к работе..." << endl;
	HANDLE hEventChar,
		hEventTermination,
		hEvents[2],
		hServer,
		hMemory;
	LPCTSTR lpEventName = L"$EventName$",
		lpEventTerminationName = L"$TerminationName$",
		lpServer1 = L"$Server$",
		lpFileShareName = L"$ShareName$";
	LPVOID memory;
	DWORD dwRetCode;
	hEventChar = CreateEvent(NULL, FALSE, FALSE, lpEventName);
	hEventTermination = CreateEvent(NULL, FALSE, FALSE, lpEventTerminationName);
	hServer = CreateEvent(NULL, FALSE, FALSE, lpServer1);
	hMemory = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, 100, lpFileShareName);
	memory = MapViewOfFile(hMemory, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);

	hEvents[0] = hEventTermination;
	hEvents[1] = hEventChar;
	int n;
	string message;
	char message1[255]="";
	char* message3 = new char[510];
	string ulog="";
	string upas="";
	cout << "Сервер готов к работе" << endl;
	cout << "Ожидание запроса..." << endl;

	while (true)
	{
		//Ожидание получения запроса
		while (true)
		{
			dwRetCode = WaitForMultipleObjects(2, hEvents, FALSE, NULL);
			if (dwRetCode == WAIT_ABANDONED_0 || dwRetCode == WAIT_ABANDONED_0 + 1 || dwRetCode == WAIT_OBJECT_0 || dwRetCode == WAIT_FAILED)
			{
				memcpy(message1, memory, sizeof(message1));
				UnmapViewOfFile(memory);
				message = convertToString(message1, sizeof(message1));
				SetEvent(hServer);
				break;
			}
		}
		cout << "Полученное сообщение: " << message << endl;
		string del = " ";
		size_t del_size = del.size();
		string str[5];
		int i = 0;
		int line_num = 0;
		while (true)
		{	
			str[i] = message.substr(0, message.find(" "));	
			if (str[i].size() == message.size())
				{
					break;
				}
			else
				{
					message = message.substr(str[i].size() + del_size);
				}
			i++;
		}
		//
		//
		//
		if (str[0] == "1")
		{
			if (check_acc(str[1], str[2]))
			{
				message3[0] = '1';
			}
			else
			{
				message3[0] = '0';
			}
			memory = MapViewOfFile(hMemory, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
			memcpy(memory, message3, 1);
			cout << "Результат: " << message3[0] << endl;
			cout << "Ответ отправлен " << endl;
			SetEvent(hServer);
		}

		if (str[0] == "2")
		{
			if (add_acc(str[1], str[2]))
			{
				message3[0] = '1';
			}
			else
			{
				message3[0] = '0';
			}
			memory = MapViewOfFile(hMemory, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
			memcpy(memory, message3, 1);
			cout << "Результат: " << message3[0] << endl;
			cout << "Ответ отправлен " << endl;
			SetEvent(hServer);
		}

		if (str[0] == "3")
		{
			string score;
			if (open_save(str[1], score))
			{
				message3[0] = '1';
				for (int k = 1; k < score.length(); k++)
				{
					message3[k] = score[k-1];
				}
				cout << "Результат: " << message3 << endl;
			}
			else
			{
				message3[0] = '0';
				cout << "Результат: " << message3[0] << endl;
			}
			memory = MapViewOfFile(hMemory, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
			memcpy(memory, message3, 255);
			cout << "Ответ отправлен " << endl;
			SetEvent(hServer);
		}

		if (str[0] == "4")
		{
			if (save(str[1], str[2], str[3]))
			{
				message3[0] = '1';
			}
			else
			{
				message3[0] = '0';
			}
			memory = MapViewOfFile(hMemory, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
			memcpy(memory, message3, 1);
			cout << "Результат: " << message3[0] << endl;
			cout << "Ответ отправлен " << endl;
			SetEvent(hServer);
		}

		if (str[0] == "5")
		{
			if (del_save(str[1]))
			{
				message3[0] = '1';
			}
			else
			{
				message3[0] = '0';
			}
			memory = MapViewOfFile(hMemory, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
			memcpy(memory, message3, 1);
			cout << "Результат: " << message3[0] << endl;
			cout << "Ответ отправлен " << endl;
			SetEvent(hServer);
		}
		cout << "Ожидание запроса..." << endl << endl;
	}

	CloseHandle(hEventChar);
	CloseHandle(hEventTermination);
	CloseHandle(hServer);
	UnmapViewOfFile(memory);
	CloseHandle(hMemory);
}

int Char_To_Int(char *a)
{
	return atoi(a);
}

bool check_acc(string Login, string Password)
{
	int line_num = 1;
	string line;
	string search = Login + " " + Password;
	int find_result = 0;
	std::ifstream in("C:\\temp\\Курсач Т_Т\\Server\\Debug\\users.txt"); // окрываем файл для чтения

	if (in.is_open())
	{
		while (getline(in, line))
		{
			if ((line.substr(0, line.find(" ")) == Login) &&(line.substr(line.find(" ")+1) == Password))
			{
					cout << "Совпадение обнаружено на строке: " << line_num << endl;
					find_result++;
			}
			line_num++;
		}
	}
	in.close();

	if (find_result != 0) return true;
	if (find_result == 0) {
		cout << "Совпадение не обнаружено!" << endl;
		return false;
	}
}

bool add_acc(string Login, string Password)
{
	string line;
	string search = Login + " " + Password;
	int find_result = 0;

	std::ifstream in("C:\\temp\\Курсач Т_Т\\Server\\Debug\\users.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (line.substr(0, line.find(" ")) == Login)
			{
				find_result++;
			}
		}
	}
	in.close();

	ofstream out("C:\\temp\\Курсач Т_Т\\Server\\Debug\\users.txt", std::ios::app);
	if (out.is_open())
	{
		if (find_result == 0) 
		{
			out << search << endl;
			out.close();
			return true;
		}
		else
		{
			out.close();
			return false;
		}
	}
}


bool open_save(string Login, string& score)
{
	int line_num = 1;
	string line="";
	string search;
	int find_result = 0;
	char char_array[50];
	char score_array[255];
	strcpy_s(char_array, Login.c_str());
	std::ifstream in("C:\\temp\\Курсач Т_Т\\Server\\Debug\\save.txt"); // окрываем файл для чтения

	if (in.is_open())
	{
		while (getline(in, line))
		{
			//search = line.substr(0, line.find(" "));
			if (line.substr(0, line.find(" "))==char_array)
			{
				cout << "Совпадение обнаружено на строке: " << line_num << endl;
				strcpy_s(score_array, line.substr(line.find(" ")).c_str());
				find_result++;
			}
			score=convertToString(score_array, sizeof(score_array));
			line_num++;
		}
	}
	in.close();

	if (find_result != 0) return true;
	if (find_result == 0) {
		cout << "Совпадение не обнаружено!" << endl;
		return false;
	}

}


bool save(string Login, string Score, string Life)
{
	string line;
	string search = Login + " " + Score + " " + Life;
	int line_num = 1;
	int find_result = 0;
	int index = 0;

	std::ifstream in("C:\\temp\\Курсач Т_Т\\Server\\Debug\\save.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (line.substr(0, line.find(" ")) == Login)
			{
				find_result++;
				index = line_num-1;
			}
			line_num++;
		}
	}
	in.close();

	ofstream out("C:\\temp\\Курсач Т_Т\\Server\\Debug\\save.txt", std::ios::app);
	if (out.is_open())
	{
		if (find_result != 0)
		{
			remove_line("C:\\temp\\Курсач Т_Т\\Server\\Debug\\save.txt", index);
			out << search << endl;
			out.close();
			return true;
		}
		else
		{
			out << search << endl;
			out.close();
			return true;
		}
	}
}


bool del_save(string Login)
{
	int index = 0;
	int line_num = 1;
	string line = "";
	string search;
	int find_result = 0;
	char char_array[50];
	char score_array[255];
	strcpy_s(char_array, Login.c_str());
	std::ifstream in("C:\\temp\\Курсач Т_Т\\Server\\Debug\\save.txt"); // окрываем файл для чтения

	if (in.is_open())
	{
		while (getline(in, line))
		{
			if (line.substr(0, line.find(" ")) == char_array)
			{
				cout << "Совпадение обнаружено на строке: " << line_num << endl;
				find_result++;
				index = line_num-1;
			}
			line_num++;
		}
	}
	in.close();
	
	if (find_result != 0)
	{
		remove_line("C:\\temp\\Курсач Т_Т\\Server\\Debug\\save.txt", index);
		return true;
	}
	return false;
}
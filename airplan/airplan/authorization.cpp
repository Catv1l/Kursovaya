#include "authorization.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute] //STA - Single Thread Apartment, �.�. ��� 
					 // �������, �������� ��� ����� ����� ������������ ������ ����������
int Main(array<String^>^args)//�������� � ������� �������
									 //CLR-������� ��������� ����������(������������ ������������ � CLR)
{
	Application::EnableVisualStyles();//�������� ���������� �����
									  //�����, �������� ����������� ������������ ������������ ����������, �����
									  //�������� ���������� ���������� ����� GDI, ���������� �� TextRenderer:
	Application::SetCompatibleTextRenderingDefault(false);
	//������ ���������� � �������� ������ � �������� �������� ����:
	airplan::authorization form; Application::Run(%form);

	return 0;
}
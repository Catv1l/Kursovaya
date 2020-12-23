#include "authorization.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute] //STA - Single Thread Apartment, т.е. это 
					 // атрибут, задающий для точки входа однопоточную модель выполнения
int Main(array<String^>^args)//передача в главную функцию
									 //CLR-массива строковых аргументов(отслежование дескрипторов в CLR)
{
	Application::EnableVisualStyles();//включаем визуальные стили
									  //метод, задающий теххнологию визуализации графического интерфейса, когда
									  //элементы управления используют класс GDI, основанный на TextRenderer:
	Application::SetCompatibleTextRenderingDefault(false);
	//запуск приложения с заданной формой в качестве главного окна:
	airplan::authorization form; Application::Run(%form);

	return 0;
}
#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, " ");
#ifdef WRITE_TO_FILE
	std::ofstream fout;                   //1) создаем поток
	//fout.open("File.txt");			  //2) открываем поток
	fout.open("File.txt", std::ios::app); //std::ios::app - append не переписывать 
										  //файл,а дописывать в конец файла     
	fout << "Hello Files" << endl;        //3) пишем в поток
	fout.close();					      //4) закрываем поток

	system("notepad File.txt");
#endif

	ifstream fin("File.txt");
	if (fin.is_open())
	{
		//будем читать файл
		const int SIZE = 256;
		char buffer[SIZE] = {};
		while (!fin.eof())
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
}
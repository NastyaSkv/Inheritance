// 1) сохранить группу в файл;
// 2) загрузить группу из файла.

#include<iostream>
#include<fstream>
using namespace std;

#define T " "

void main()
{
	setlocale(LC_ALL, "");

	std::ofstream fout;
	fout.open("Group.txt");

	fout << "Student" << T << "Pinkman" << T << "Jessie" << T << 25 << T << "Chemistry" << T << "WW_220" << T << 90 << T << 95 << endl;
	fout << "Teacher" << T << "White" << T << "Walter" << T << 50 << T << "Chemistry" << T << 20 << endl;
	fout << "Undergrad" << T << "Schreader" << T << "Hank" << T << 40 << T << "Criminalistic" << T << "WW_220" << T << 95 << T << 80 << T << "How to catch Heisenberg" << endl;
	fout << "Student" << T << "Vercetti" << T << "Tomas" << T << 30 << T << "Criminalistic" << T << "Vice" << T << 98 << T << 99 << endl;
	fout << "Teacher" << T << "Diaz" << T <<  "Ricardo" << T << 50 << T << "Weapons distribution" << T << 15 << endl;
	fout << "Teacher" << T << "Einstein" << T << " Albert" << T << 143 << T << "Astronomy" << T << 120 << endl;
	fout.close();
	
	system("notepad Group.txt");

	ifstream fin("Group.txt");
	if (fin.is_open())
	{
		const int SIZE = 256;
		char buffer[SIZE] = {};
		while (!fin.eof())
		{
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


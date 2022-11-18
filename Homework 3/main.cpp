//1) Из файла 201 RAW.txt сделать новый файл 201 ready.txt, в котором столбики с IP и MAC адресами поменяны местами
//2) Из файла 201 RAW.txt сделать новый файл 201.dhcpd, следующего формата
#include<iostream>
#include<fstream>
using std::cout;
using namespace std;

//#define TASK_1 
//#define TASK_2 

void main()
{
	setlocale(LC_ALL, "");

#ifdef TASK_1 
	ifstream fin("201 RAW.txt");      //открыли файл
	if (fin.is_open())
	{
		std::ofstream fout;
		fout.open("201 ready.txt");   //создали файл

		const int SIZE = 50;
		char buffer[SIZE] = {};
		char reserve[SIZE] = {};

		for (int i = 0; !fin.eof(); i++)
		{
			fin.getline(buffer, SIZE);
			cout << buffer << endl;

			int j = 0;
			for (; buffer[j] != ' '; j++)reserve[j] = buffer[j];       //IP загружаем в резерв

			for (; buffer[j] == ' '; j++) {}                           //пробелы

			for (int z = 0; buffer[j] != '\0'; j++, z++)
			{
				buffer[z] = buffer[j];                 //MAC записываем вместо IP
				buffer[j] = reserve[z];                //IP записываем вместо MAC
			}

			for (int z = 0; buffer[z] != '\0'; z++)fout << buffer[z];  //запись в поток

			fout << endl;
		}
		fout.close();
		fin.close();
		system("notepad 201 ready.txt");
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif // TASK_1 
#ifdef TASK_2
	ifstream fin("201 RAW.txt");      //открыли файл
	if (fin.is_open())
	{
		std::ofstream fout;
		fout.open("201.dhcpd.txt");   //создали файл

		const int SIZE = 50;
		char buffer[SIZE] = {};
		char reserve[SIZE] = {};

		for (int i = 0; !fin.eof(); i++)
		{
			fin.getline(buffer, SIZE);
			cout << buffer << endl;

			int j = 0;
			for (; buffer[j] != ' '; j++)reserve[j] = buffer[j];       //IP загружаем в резерв
			for (; buffer[j] == ' '; j++) {}                           //пробелы
			for (int z = 0; buffer[j] != '\0'; j++, z++)
			{
				buffer[z] = buffer[j];                 
				buffer[j] = reserve[z];                
			}
			fout << "host" << " 201-" << i + 1 << endl << "{" << endl << "\t" << "hardware ethernet"<<"\t";
			
			int t = 0;
			for (; buffer[t] != ' '; t++)
			{
				if (buffer[t] == '-')fout << ':';
				else fout << buffer[t];
			}fout << ';' << endl;
			 
			for (; buffer[t] == ' '; t++) {}                  //пробелы

			fout << "\t"<<"fixed-address"<< "\t\t";
			for (int z = 0; reserve[z] != '\0'; t++, z++)fout << reserve[z];

			fout << ';' << endl << "}" << endl << endl << endl;
		}
		fout.close();
		fin.close();
		system("notepad 201.dhcpd.txt");
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
#endif // TASK_2 
}
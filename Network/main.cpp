#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");

	char number[10] = {};
	char src_filename[_MAX_FNAME] = {};	//_MAX_FNAME - это втроенная константа, которая содержит максимально возможную длину имени файла
	char wal_filename[_MAX_FNAME] = {};
	char dhcpd_filename[_MAX_FNAME] = {};
	//src (source) - файл источник, из которого изначально берутся MAC и IP адреса
	//dst (destination) - это конечный файл, в котором столбики будут поменяны местами

	cout << "Введите номер аудитории: "; cin >> number;
	//По введенному номеру аудитории формируем имена файлов, как исходного, так и конечного:
	strcat(src_filename, number);
	strcat(src_filename, " RAW.txt");
	//strcat(dst, src);	//содержимое строки src добавляет в конец строки dst
	//strcat - выполняет конкатенацию строк, а именно,
	//к первой строке (filename) добавляет вторую строку (" RAW.txt");
	strcat(wal_filename, number);
	strcat(wal_filename, " ready.txt");

	strcat(dhcpd_filename, number);
	strcat(dhcpd_filename, ".dhcpd");

	const int IP_SIZE = 16;
	const int MAC_SIZE = 18;

	char sz_ip_buffer[IP_SIZE] = {};
	char sz_mac_buffer[MAC_SIZE] = {};

	ofstream fout(wal_filename);
	ifstream fin(src_filename);

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> sz_ip_buffer;
			fin >> sz_mac_buffer;
			cout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
			fout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
		}
		//fin.close();	//Будем еще раз читать файл, только позже.
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	fout.close();
	char sz_command[_MAX_FNAME] = "start notepad ";
	strcat(sz_command, wal_filename);
	system(sz_command);

	/////////////////////////////////////////////////////////////////////////////

	//Возвращаемся в начало файла
	fin.clear();
	fin.seekg(0);
	cout << fin.tellg() << endl;
	fout.open(dhcpd_filename);

	if (fin.is_open())
	{
		for (int i = 1; !fin.eof(); i++)
		{
			fin >> sz_ip_buffer >> sz_mac_buffer;
			for (int i = 0; sz_mac_buffer[i]; i++)
				if (sz_mac_buffer[i] == '-')sz_mac_buffer[i] = ':';
			cout << number << "-" << i << endl;
			cout << "{\n";
			cout << "\thardware ethernet\t" << sz_mac_buffer << ";\n";
			cout << "\tfixed-address\t\t" << sz_ip_buffer << ";\n";
			cout << "}\n";

			fout << number << "-" << i << endl;
			fout << "{\n";
			fout << "\thardware ethernet\t" << sz_mac_buffer << ";\n";
			fout << "\tfixed-address\t\t" << sz_ip_buffer << ";\n";
			fout << "}\n";
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}

	strcpy(sz_command + strlen("start notepad "), dhcpd_filename);
	system(sz_command);
	//strcpy(dst, src);	//String Copy
	//strcpy() копирует строку src в строку dst
}
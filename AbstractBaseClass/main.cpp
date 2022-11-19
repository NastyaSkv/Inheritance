#include<iostream>
using namespace std;

class Animal
{
	std::string name;
public:
	virtual void sound()const = 0;
};
class Cat :public Animal
{

};
class Tiger :public Cat
{
public:
	void sound()const override
	{
		cout << "Ppppppppppp" << endl;
	}
};
class Lion :public Cat
{
public:
	void sound()const override
	{
		cout << "Ща я тебя схаваю" << endl;
	}
};
class Dog :public Animal{};
class Wolf :public Dog
{
public:
	void sound()const override
	{
		cout << "Ayyyyyy" << endl;
	}
};
void main()
{
	setlocale(LC_ALL, "");
	//Animal slonohobotan;
	//Cat tom;
	/*Tiger tiger;
	tiger.sound();

	Lion killer;
	killer.sound();

	Wolf wolf;
	wolf.sound();*/

	Animal* zoo[] =
	{
		new Lion,
		new Tiger,
		new Wolf
	};
	for (int i = 0; i < sizeof(zoo) / sizeof(Animal*); i++)
	{
		zoo[i]->sound();
	}
}
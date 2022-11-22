#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
	};

	class Shape
	{
	protected:
		Color color;
	public:
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual double area()const = 0;
		virtual double perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << area() << endl;
			cout << "Периметр фигуры: " << perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < 5)side = 5;
			if (side > 20)side = 20;
			this->side = side;
		}
		//				Constructors:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}
		double area()const override
		{
			return side * side;
		}
		double perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << side << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width < 8)width = 8;
			if (width > 30)width = 30;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < 3)length = 3;
			if (length > 20)length = 20;
			this->length = length;
		}
		Rectangle(double width, double length, Color color) :Shape(color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double area()const override
		{
			return width * length;
		}
		double perimeter()const override
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < length; i++)
			{
				for (int j = 0; j < width; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);*/
			//1) Получаем окно консоли
			HWND hwnd = GetConsoleWindow();
			//2) Получаем контекст устройства для окна консоли:
			HDC hdc = GetDC(hwnd);  //это то, на чем мы будем рисовать
			//3) Создаем карандаш - это то, чем мы будем рисовать
			//карандаш рисует линии
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			//4) Создаем кисть. Кисть рисует заливку в замкнутой фигуре

			HBRUSH hBrush = CreateSolidBrush(color);

			//5) Выбираем чем и на чем мы будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольнки:
			::Rectangle(hdc, 100, 100, 500, 300);

			//Удаляем карандаш:
			DeleteObject(hPen);

			//Освобождаем констекст устройства:
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина:" << width << endl;
			cout << "Длина:" << length << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape
	{
		double a_x;
		double a_y;
		double b_x;
		double b_y;
		double c_x;
		double c_y;
		int size;

	public:
		double get_a_x()const
		{
			return a_x;
		}	
		double get_a_y()const
		{
			return a_y;
		}	
		double get_b_x()const
		{
			return b_x;
		}	
		double get_b_y()const
		{
			return b_y;
		}
		double get_c_x()const
		{
			return c_x;
		}
		double get_c_y()const
		{
			return c_y;
		}	
		int get_size()const
		{
			return size;
		}	
		void set_a_x(double a_x)
		{
			if (a_x < 3)a_x = 100;
			if (a_x > 300)a_x = 20;
			this->a_x = a_x;
		}
		void set_a_y(double a_y)
		{
			if (a_y < 3)a_y = 100;
			if (a_y > 300)a_y = 30;
			this->a_y = a_y;
		}
		void set_b_x(double b_x)
		{
			if (b_x < 3)b_x = 50;
			if (b_x > 300)b_x = 10;
			this->b_x = b_x;
		}
		void set_b_y(double b_y)
		{
			if (b_y < 3)b_y = 50;
			if (b_y > 300)b_y = 15;
			this->b_y = b_y;
		}
		void set_c_x(double c_x)
		{
			if (c_x < 3)c_x = 60;
			if (c_x > 300)c_x = 18;
			this->c_x = c_x;
		}
		void set_c_y(double c_y)
		{
			if (c_y < 3)c_y = 10;
			if (c_y > 300)c_y = 35;
			this->c_y = c_y;
		}

		void set_size(int size)
		{
			if (size < 7)size = 3;
			if (size > 300)size = 10;
			this->size = size;
		}
		Triangle(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, int size, Color color) :Shape(color)
		{
			set_a_x(a_x);
			set_a_y(a_y);
			set_b_x(b_x);
			set_b_y(b_y);
			set_c_x(c_x);
			set_c_y(c_y);
			set_size(size);
		}
		~Triangle() {}
		double area()const override //формула Герона
		{
			//double p = (side_1 + side_2 + side_3) / 2;
			double p = 5 / 2;
			//return sqrt(p*(p- side_1)* (p - side_2)* (p - side_3));
			return sqrt(4);
		}
		double perimeter()const override
		{
			//return side_1 + side_2 + side_3;
			return 3;
		}
		void draw()const
		{
			//+
			/*HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			
			HPEN hPen = CreatePen(PS_SOLID, 5, color);

			HBRUSH hBrush = CreateSolidBrush(color);*/

			//SelectObject(hdc, hPen);
			//SelectObject(hdc, hBrush);
			/*
			//::Rectangle(hdc, 100, 100, 500, 300);
			MoveToEx(hdc, x, y-size, NULL);
			LineTo(hdc, x+size, y+size);
			LineTo(hdc, x-size, y+size);
			LineTo(hdc, x, y-size);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);*/
		
		
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);  
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			//5) Выбираем чем и на чем мы будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			Polygon(hdc,Triangle, int size);

			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "ax: " << a_x << endl;
			cout << "ay: " << a_y<< endl;
			cout << "bx: " << b_x << endl;
			cout << "by: " << b_y << endl;
			cout << "cx: " << c_x << endl;
			cout << "cy: " << c_y << endl;
			cout << "Введите количество углов" << size << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape;
	Geometry::Square square(8, Geometry::Color::console_red);
	square.info();

	Geometry::Rectangle rect(15, 7, Geometry::Color::console_yellow);
	rect.info();

	Geometry::Triangle tri(1,2, 2,1, 2, 3, 3, Geometry::Color::console_green);
	tri.info();
}
//copy AbstractGeometry
//В иерархии геометрических фигур расширить иерархию треугольников равнобедренным и прямоугольным треугольниками.
#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,              //alpha канал
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000AAFF,
		white = 0x00FFFFFF,
		grey = 0x00AAAAAA,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE,
	};

	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 800)start_x = 800;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 500)start_y = 500;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width > 30)line_width = 30;
			this->line_width = line_width;
		}
		Shape(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
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
		Square(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Shape(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~Square() {}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
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
			if (width < 30)width = 30;
			if (width > 300)width = 300;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < 20)length = 20;
			if (length > 200)length = 200;
			this->length = length;
		}
		Rectangle(double width, double length, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color) :
			Shape(start_x, start_y, line_width, color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double get_area()const override
		{
			return width * length;
		}
		double get_perimeter()const override
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
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			//4) Создаем кисть. Кисть рисует заливку в замкнутой фигуре

			HBRUSH hBrush = CreateSolidBrush(color);

			//5) Выбираем чем и на чем мы будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//6) Рисуем прямоугольнки:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + width);

			//Удаляем карандаш:
			DeleteObject(hPen);
			DeleteObject(hBrush);

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

	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		void set_radius(double radius)
		{
			if (radius < 20)radius = 20;
			if (radius > 220)radius = 220;
			this->radius = radius;
		}
		Circle(double radius, unsigned int start_x, unsigned start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color)
		{
			set_radius(radius);
		}
		~Circle() {}
		double get_area()const override
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return 2 * M_PI * radius;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + radius * 2, start_y + radius * 2);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Radius:\t" << radius << endl;
			Shape::info();
		}
	};

	class Triangle :public Shape    //виртуальный класс Треугольники
	{
	public:
		Triangle(unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Shape(start_x, start_y, line_width, color) {}
		virtual double get_height()const = 0;
		void info()const
		{
			cout << "Height:\t" << get_height() << endl;
			Shape::info();
		}
	};   
	class EquilateralTriangle :public Triangle   //равносторонний треугольник
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			if (side < 20)side = 20;
			if (side > 200)side = 200;
			this->side = side;
		}
		EquilateralTriangle(double side, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}
		double get_height()const override
		{
			return 2 * get_area() / side;
		}
		double get_area()const override
		{
			return side * side * sqrt(3) / 4;
		}
		double get_perimeter()const override
		{
			return side * 3;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vert[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()},
			};
			::Polygon(hdc, vert, 3);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Side:\t" << side << endl;
			Triangle::info();
		}
	};
	class IsoscelesTriangle :public Triangle    //равнобедренный треугольник
	{
		double side;
		double footing;
	public:
		double get_side()const
		{
			return side;
		}
		double get_footing()const
		{
			return footing;
		}
		void set_side(double side)
		{
			if (side < 20)side = 100;
			if (side > 200)side = 600;
			this->side = side;
		}
		void set_footing(double footing)
		{
			if (footing < 20)footing = 20;
			if (footing > 200)footing = 200;
			this->footing = footing;
		}
		IsoscelesTriangle(double side, double footing, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Triangle(start_x, start_y, line_width, color)
		{
			set_side(side);
			set_footing(footing);
		}
		~IsoscelesTriangle() {}
		double get_height()const override
		{
			return sqrt(side * side - footing * footing / 4);
		}
		double get_area()const override
		{
			return footing * sqrt(side * side - footing * footing / 4) / 2;
		}
		double get_perimeter()const override
		{
			return side * 2 + footing;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vert[] =
			{
				{start_x, start_y + side},
				{start_x + footing, start_y + side},
				{start_x + footing / 2, start_y + side - get_height()},
			};
			::Polygon(hdc, vert, 3);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Side:\t" << side << endl;
			cout << "Footing:\t" << footing << endl;
			Triangle::info();
		}
	};
	class RectangularTriangle :public Triangle    //прямоугольный треугольник
	{
		double catheter_1;
		double catheter_2;
	public:
		double get_catheter_1()const
		{
			return catheter_1;
		}
		double get_catheter_2()const
		{
			return catheter_2;
		}
		void set_catheter_1(double catheter_1)
		{
			if (catheter_1 < 20)catheter_1 = 100;
			if (catheter_1 > 200)catheter_1 = 600;
			this->catheter_1 = catheter_1;
		}
		void set_catheter_2(double catheter_2)
		{
			if (catheter_2 < 20)catheter_2 = 200;
			if (catheter_2 > 200)catheter_2 = 800;
			this->catheter_2 = catheter_2;
		}
		RectangularTriangle(double catheter_1, double catheter_2, unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color)
			:Triangle(start_x, start_y, line_width, color)
		{
			set_catheter_1(catheter_1);
			set_catheter_2(catheter_2);
		}
		~RectangularTriangle() {}
		double get_height()const override
		{
			return catheter_1 * catheter_2 / sqrt(catheter_1 * catheter_1 + catheter_2 * catheter_2);
		}
		double get_area()const override
		{
			return catheter_1 * catheter_2 / 2;
		}
		double get_perimeter()const override
		{
			return catheter_1 + catheter_2 + sqrt(catheter_1 * catheter_1 + catheter_2 * catheter_2);
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vert[] =
			{
				{start_x, start_y + catheter_2},
				{start_x + catheter_1, start_y + catheter_2},
				{start_x, start_y},
			};
			::Polygon(hdc, vert, 3);
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "catheter_1:\t" << catheter_1 << endl;
			cout << "catheter_2:\t" << catheter_2 << endl;
			cout << "hypotenuse:\t" << sqrt(catheter_1 * catheter_1 + catheter_2 * catheter_2) << endl;
			Triangle::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape;
	Geometry::Square square(6, 900, 200, 11, Geometry::Color::console_red);
	square.info();

	Geometry::Rectangle rect(150, 70, 300, 100, 11, Geometry::Color::grey);
	rect.info();

	Geometry::Circle circle(100, 500, 100, 11, Geometry::Color::yellow);
	circle.info();

	Geometry::EquilateralTriangle e_try(170, 350, 300, 15, Geometry::Color::green);
	e_try.info();

	Geometry::IsoscelesTriangle i_try(200, 50, 600, 400, 10, Geometry::Color::blue);
	i_try.info();

	Geometry::RectangularTriangle rec_try(16, 15, 700, 350, 10, Geometry::Color::white);
	rec_try.info();

}
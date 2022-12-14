//Academy
#include<iostream>
#include<string>
using namespace std;

#define delimiter "\n-----------------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}

	//						Constractors:
	Human(HUMAN_TAKE_PARAMETERS) :last_name(last_name), first_name(first_name), age(age)
	{
		cout << "HConstructor:\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//						Methods:
	void print()const
	{
		cout << last_name << " " << first_name << " " << age << " лет.\n";
	}
};

#define STUDENT_TAKE_PARAMETERS const std::string& specialty, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS specialty, group, rating, attendance

class Student :public Human
{
	std::string specialty;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_specialty()const
	{
		return specialty;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_specialty(const std::string& specialty)
	{
		this->specialty = specialty;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//						Constractors:
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		this->specialty = specialty;
		this->group = group;
		this->rating = rating;
		this->attendance = attendance;
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//						Methods:
	void print()const
	{
		Human::print();
		cout << specialty << " " << group << " " << rating << " " << attendance << endl;
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& specialty, unsigned int experience
#define TEACHER_GIVE_PARAMETERS specialty, experience

class Teacher :public Human
{
	std::string specialty;
	unsigned int experience;
public:
	const std::string& get_specialty()const
	{
		return specialty;
	}
	unsigned int get_experience()const
	{
		return experience;
	}
	void set_specialty(const std::string& specialty)
	{
		this->specialty = specialty;
	}
	void set_experience(unsigned int experience)
	{
		this->experience = experience;
	}

	//						Constractors:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_specialty(specialty);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//						Methods:
	void print()const
	{
		Human::print();
		cout << specialty << " " << experience << endl;
	}
};

#define GRADUATE_TAKE_PARAMETERS const std::string& subject_exam, unsigned int estimation, bool graduation_work
#define GRADUATE_GIVE_PARAMETERS subject_exam, estimation, graduation_work

class Graduate :public Student
{
	std::string subject_exam;
	unsigned int estimation;
	bool graduation_work;
public:
	const std::string& get_subject_exam()const
	{
		return subject_exam;
	}
	unsigned int get_estimation()const 
	{
		return estimation;
	}
	bool get_graduation_work()const
	{
		return graduation_work;
	}
	void set_subject_exam(const std::string& subject_exam)
	{
		this->subject_exam = subject_exam;
	}
	void set_estimation(unsigned int estimation)
	{
		this->estimation = estimation;
	}
	void set_graduation_work(bool graduation_work)
	{
		this->graduation_work = graduation_work;
	}

	//						Constractors:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS) :Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		set_subject_exam(subject_exam);
		set_estimation(estimation);
		set_graduation_work(graduation_work);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//						Methods:
	void print()const
	{
		Student::print();
		cout << subject_exam << " " << estimation << " " << graduation_work << " " << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	Human human("Montana", "Antoio", 25);
	human.print();
	cout << delimiter << endl;

	Student stud("Pinkman", "Jessie", 25, "Chemistry", "WW_220", 90, 95);
	stud.print();
	cout << delimiter << endl;

	Teacher professor("White", "Walter", 50, "Chemistry", 20);
	professor.print();
	cout << delimiter << endl;

	Graduate grad("Key", "Jon", 20, "Chemistry", "OO_105", 61, 93, "Math", 4, 1);
	grad.print();
}
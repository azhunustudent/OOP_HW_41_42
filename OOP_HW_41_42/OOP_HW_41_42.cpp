#include <iostream>
#include <fstream>  // файловые потоки
#include <iomanip>  // манипуляторы
#include <string>
#include <algorithm> // алгоритмические ф-ции STL
#include <time.h>
using namespace std;
#define RAND(Min,Max)  (rand()%((Max)-(Min)+1)+(Min))
struct LC { LC() { system("chcp 1251 > nul"); srand(time(0)); }~LC() { cin.get(); cin.get(); } } _;


// Создать базовый класс Employer(служащий) с методами Print(), Input().
// Создайте три производных класса : President, Manager, Worker.
// Переопределите функции Input() и Print() для ввода и вывода информации, соответствующие каждому типу служащего.

class Employer
{
private:
	double Salary;
	int Year;			// год приема на работу
protected:
	string FIO;
public:
	Employer() = delete;
	Employer(string fio) : FIO(fio), Salary(), Year() {}

	double GetSalary()   const { return Salary; }
	int GetYear()	     const { return Year; }
	string GetFIO()      const { return FIO; }
	
	void SetSalary(double val)   { Salary = val; }
	void SetYear(int val)		 { Year = val; }
	void SetFIO(string val)      { FIO = val; }

	virtual void Print()
	{
		//cout << typeid(*this).name() << endl;
		cout << "FIO: "    << GetFIO() << endl
			 << "Year of hire: "   << GetYear() << endl
			 << "Salary: " << GetSalary() << endl;
	}

	virtual void Input()
	{
		string temp;
		int temp2;

		cout << "Enter FIO: ";
		getline(cin, temp);
		SetFIO(temp);
		
		while (true)
		{
			cout << "Enter Year of hire: ";
			(cin >> temp2).ignore();
			if (temp2 >= 1970 && temp2 <= 2023)
			{
				SetYear(temp2);
				break;
			}
			else { cout << "Error: Year of hire cannot be lower than 1970 and higher than 2023. Repeat the entry!" << endl; }
		}

		while (true)
		{
			cout << "Enter Salary: ";
			(cin >> temp2).ignore();
			if (temp2 >= 50000)
			{
				SetSalary(temp2);
				break;
			}
			else { cout << "Error: Salary cannot be lower than 50,000 KZT. Repeat the entry!" << endl; }
		}
	}
	virtual ~Employer() {}
};


class President : virtual public Employer
{
private:
	string Company;
protected:
public:
	President() : Employer("Ivananov Ivan Ivanovich") {}
	President(string company) : Company(company), Employer("Ivananov Ivan Ivanovich") {}

	virtual void Print() override
	{
		Employer::Print();
		cout << "Company: " << Company << endl;
	}
	virtual void Input() override
	{	
		cout << "Enter info for " << typeid(*this).name() << endl;
		Employer::Input();
		cout << "Enter Title of Company: ";
		getline(cin, Company);
	}
	virtual ~President() {}
};


class Manager : virtual public Employer
{
private:
	string Department;
protected:
public:
	Manager() : Employer("Petrov Petr Petrovich") {}
	Manager(string dep) : Department(dep), Employer("Petrov Petr Petrovich") {}

	virtual void Print() override
	{
		Employer::Print();
		cout << typeid(*this).name() << endl;
		cout << "Department: " << Department << endl;
	}
	virtual void Input() override
	{
		cout << "Enter info for " << typeid(*this).name() << endl;
		Employer::Input();
		cout << "Enter Department: ";
		getline(cin, Department);
	}
	virtual ~Manager() {}
};


class Worker : virtual public Employer
{
private:
	string Position;
protected:
public:
	Worker() : Employer("Sidorov Sidor Sidorovich") {}
	Worker(string pos) : Position(pos), Employer("Sidorov Sidor Sidorovich") {}

	virtual void Print() override
	{
		Employer::Print();
		cout << typeid(*this).name() << endl;
		cout << "Position: " << Position << endl;
	}
	virtual void Input() override
	{
		cout << "Enter info for " << typeid(*this).name() << endl;
		Employer::Input();
		cout << "Enter Position: ";
		getline(cin, Position);
	}
	virtual ~Worker() {}
};


enum EmpType
{
	EmPresident = 1,
	EmManager,
	EmWorker
};

Employer* CreateClass(EmpType Type)
{
	switch (Type)
	{
		case EmPresident: return new President;
		case EmManager:   return new Manager;
		case EmWorker:    return new Worker;
	}
	return nullptr;
}

int main()
{
	for (;;)
	{
		cout << "1. President.\n"
			 << "2. Manager.\n"
			 << "3. Worker.\n"
			 << "0. Exit.\n";
		cout << "Enter choice: ";
		int choice;
		(cin >> choice).ignore();

		Employer* emp = CreateClass((EmpType)choice);
		if (emp == nullptr) { break; }
		cout << "--------------------------------------------------\n";
		emp->Input();
		cout << "--------------------------------------------------\n";
		emp->Print();
		cout << "--------------------------------------------------\n";
		delete emp;
	}
	cout << "Good bye...\n";
}
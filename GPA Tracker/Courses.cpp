#include "Courses.h"

Courses::Courses()
{
}

Courses::~Courses()
{
}

int Courses::_size()
{
	return _classes.size();
}

Course Courses::operator[](int n)
{
	return _classes[n];
}

void Courses::_add_class()
{
	Course new_class = _read_new_class();
	_classes.push_back(new_class);
}

void Courses::_add_class(Course new_class)
{
	_classes.push_back(new_class);
}

void Courses::_update_class()
{
	if (_classes.empty())
	{
		std::cout << "\n No classes\n";
		return;
	}

	int index = _find_class();
	if (index == -1)
		std::cout << "\n Class not found";
	else
		_classes[index] = _read_new_class();
}

void Courses::_erase_class()
{
	if (_classes.empty())
	{
		std::cout << "\n No classes\n";
		return;
	}

	int index = _find_class();
	if (index == -1)
		std::cout << "\n Class not found";
	else
		_classes.erase(_classes.begin() + index);
}

void Courses::_print_classes()
{
	if (_classes.empty())
	{
		std::cout << "\n No classes\n";
		return;
	}

	std::cout << "\n   Name             Units      Grade      Creditor"
		<< "\n-------------------------------------------------------";

	for (int i = 0; i < _classes.size(); i++)
	{
		std::cout << "\n ";
		_classes[i]._print_class();
	}

	std::cout << std::endl;
}

void Courses::_print_GPAs()
{
	if (_classes.empty())
	{
		std::cout << "\n No classes\n";
		return;
	}

	std::cout << "\n Cumulative GPA: " << std::fixed << _get_GPA()
		<< "\n UC transferable GPA: " << _get_accreditor_GPA("UC")
		<< "\n CSU transferable GPA: " << _get_accreditor_GPA("CSU")
		<< std::endl;
}

Course Courses::_read_new_class()
{
	std::string name;
	int units;
	char grade;
	std::string accreditors;

	std::cout << "\n Enter name: ";
	std::getline(std::cin, name);
	std::cout << "\n Enter units: ";
	std::cin >> units;
	std::cout << "\n Enter grade: ";
	std::cin >> grade;
	std::cout << "\n Enter creditor(s): ";
	std::cin >> accreditors;

	return Course(name, units, grade, accreditors);
}

int Courses::_find_class()
{
	std::cout << "\n\n Enter class name: ";
	std::string name;
	std::cin.ignore();
	std::getline(std::cin, name);

	for (int i = 0; i < _classes.size(); i++)
	{
		if (name == _classes[i]._get_name())
			return i;
	}

	return -1;
}

double Courses::_get_GPA()
{
	int total_grade_points = 0,
		total_units_attempted = 0;

	for (int i = 0; i < _classes.size(); i++)
	{
		total_grade_points += _classes[i]._get_grade_points();
		total_units_attempted += _classes[i]._get_units();
	}

	return (double)total_grade_points / total_units_attempted;
}

double Courses::_get_accreditor_GPA(std::string accreditor)
{
	int total_grade_points = 0,
		total_units_attempted = 0;

	for (int i = 0; i < _classes.size(); i++)
	{
		if (_classes[i]._get_accreditors().find(accreditor) != std::string::npos)
		{
			total_grade_points += _classes[i]._get_grade_points();
			total_units_attempted += _classes[i]._get_units();
		}
	}

	return (double)total_grade_points / total_units_attempted;
}

#include "Courses.h"

Courses::Courses()
{
}

Courses::~Courses()
{
}

int Courses::_size()
{
	return _courses.size();
}

bool Courses::_empty()
{
	return !_size();
}

Course Courses::operator[](int n)
{
	return _courses[n];
}

void Courses::_add_course()
{
	Course new_course = _read_new_course();
	_courses.push_back(new_course);
}

void Courses::_add_course(Course new_course)
{
	_courses.push_back(new_course);
}

void Courses::_insert_course()
{
	if (_courses.empty())
	{
		std::cout << "\n No courses\n";
		return;
	}

	Course new_course = _read_new_course();
	std::cout << "\n Which course should be below this new one?";
	int index = _find_course();
	if (index == -1)
		std::cout << "\n Course not found\n";
	else
		_courses.insert(_courses.begin() + index, new_course);
}

void Courses::_edit_course()
{
	if (_courses.empty())
	{
		std::cout << "\n No courses\n";
		return;
	}

	int index = _find_course();
	if (index == -1)
		std::cout << "\n Course not found\n";
	else
		_courses[index] = _read_new_course();
}

void Courses::_erase_course()
{
	if (_courses.empty())
	{
		std::cout << "\n No courses\n";
		return;
	}

	int index = _find_course();
	if (index == -1)
		std::cout << "\n Course not found\n";
	else
		_courses.erase(_courses.begin() + index);
}

void Courses::_print_courses()
{
	if (_courses.empty())
	{
		std::cout << "\n No courses\n";
		return;
	}

	std::cout << "\n   Name             Units      Grade      Accreditor"
		<< "\n-------------------------------------------------------";

	for (int i = 0; i < _courses.size(); i++)
	{
		std::cout << "\n ";
		_courses[i]._print_course();
	}

	std::cout << std::endl;
}

void Courses::_print_GPAs()
{
	if (_courses.empty())
	{
		std::cout << "\n No courses\n";
		return;
	}

	std::cout << "\n Cumulative GPA: " << std::fixed << _get_GPA("")
		<< "\n UC transferable GPA: " << _get_GPA("UC")
		<< "\n CSU transferable GPA: " << _get_GPA("CSU")
		<< std::endl;
}

Course Courses::_read_new_course()
{
	std::cout << "\n Enter name: ";
	std::string name;
	std::getline(std::cin, name);

	int units = _read_units();

	std::cout << "\n Enter grade: ";
	char grade;
	std::cin >> grade;
	grade = toupper(grade);

	std::cout << "\n Enter accreditor(s), e.g. CSU/UC: ";
	std::string accreditors;
	std::cin >> accreditors;

	if (grade == 'W')
		std::cout << "\n Do not enter courses that do not count towards your GPA\n";

	return Course(name, units, grade, accreditors);
}

int Courses::_read_units()
{
	bool invalid_input = true;
	char units;

	do
	{
		std::cout << "\n Enter units: ";
		std::cin >> units;

		if (units < '0' || units > '9')
			std::cout << "\n Invalid units entered";
		else
			invalid_input = false;
	} while (invalid_input);

	return units - '0';
}

int Courses::_find_course()
{
	std::cout << "\n\n Enter course name: ";
	std::string name;
	std::cin.ignore();
	std::getline(std::cin, name);

	for (int i = 0; i < _courses.size(); i++)
	{
		if (name == _courses[i]._get_name())
			return i;
	}

	return -1;
}

double Courses::_get_GPA(std::string accreditor)
{
	int total_grade_points = 0,
		total_units_attempted = 0;

	for (int i = 0; i < _courses.size(); i++)
	{
		if (_courses[i]._get_accreditors().find(accreditor) != std::string::npos)
		{
			total_grade_points += _courses[i]._get_grade_points();
			total_units_attempted += _courses[i]._get_units();
		}
	}

	return (double)total_grade_points / total_units_attempted;
}

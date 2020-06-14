#include "Course.h"
#include <cassert>

Course::Course()
{
	_grade = 'Z';
	_semester_units = -1;
}

Course::Course(std::string new_name, int new_units, char new_grade, std::string new_accreditors)
{
	_name = new_name;
	_semester_units = new_units;
	_grade = new_grade;
	_accreditors = new_accreditors;
}

Course::~Course()
{
}

void Course::_print_course()
{
	std::cout << std::setw(21) << std::left << _name
		<< std::setw(11) << _semester_units << std::setw(9)
		<< _grade << _accreditors;
}

std::string Course::_get_name()
{
	return _name;
}

int Course::_get_units()
{
	return _semester_units;
}

char Course::_get_grade()
{
	return _grade;
}

// returns a negative number if the course's grade is 'W'
int Course::_get_grade_points()
{
	int grade_value = 0;

	switch (_grade)
	{
	case 'A':
		grade_value = 4;
		break;
	case 'B':
		grade_value = 3;
		break;
	case 'C':
		grade_value = 2;
		break;
	case 'D':
		grade_value = 1;
		break;
	case 'F':
		grade_value = 0;
		break;
	case 'W':
		grade_value = -1;
	}

	return _semester_units * grade_value;
}

std::string Course::_get_accreditors()
{
	return _accreditors;
}

void Course::_set_name(std::string new_name)
{
	_name = new_name;
}

void Course::_set_units(int new_units)
{
	_semester_units = new_units;
}

void Course::_set_grade(char new_grade)
{
	_grade = new_grade;
}

void Course::_set_accreditors(std::string new_accreditors)
{
	_accreditors = new_accreditors;
}

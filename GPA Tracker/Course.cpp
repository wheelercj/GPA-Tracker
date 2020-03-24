#include "Course.h"
#include <cassert>

Course::Course()
{
	_grade = 'Z';
	_semester_units = -1;
}

Course::Course(std::string new_name, int new_units, char new_grade, std::string new_accreditor)
{
	_name = new_name;
	_semester_units = new_units;
	_grade = new_grade;
	_accreditor = new_accreditor;
}

Course::~Course()
{
}

void Course::_print_course()
{
	std::cout << std::setw(21) << std::left << _name
		<< std::setw(11) << _semester_units << std::setw(9)
		<< _grade << _accreditor;
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
	}

	return _semester_units * grade_value;
}

std::string Course::_get_accreditors()
{
	return _accreditor;
}

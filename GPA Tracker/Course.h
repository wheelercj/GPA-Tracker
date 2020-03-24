#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class Course
{
public:
	Course();
	Course(std::string new_name, int new_units, char new_grade, std::string new_accreditor);
	~Course();
	void _print_class();

	std::string _get_name();
	int _get_units();
	char _get_grade();
	int _get_grade_points();
	std::string _get_accreditors();
private:
	std::string _name;
	int _semester_units;
	char _grade;
	std::string _accreditor;
};

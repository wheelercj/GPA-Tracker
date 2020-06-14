#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class Course
{
public:
	Course();
	Course(std::string new_name, int new_units, char new_grade, std::string new_accreditors);
	~Course();
	void _print_course();

	std::string _get_name();
	int _get_units();
	char _get_grade();
	int _get_grade_points();
	std::string _get_accreditors();

	void _set_name(std::string new_name);
	void _set_units(int new_units);
	void _set_grade(char new_grade);
	void _set_accreditors(std::string new_accreditors);
private:
	std::string _name;
	int _semester_units;
	char _grade;
	std::string _accreditors;
};

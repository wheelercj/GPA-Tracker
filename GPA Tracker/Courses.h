#pragma once
#include "Course.h"
#include <vector>

class Courses
{
public:
	Courses();
	~Courses();
	int _size();
	Course operator[](int n);
	void _add_class();
	void _add_class(Course new_class);
	void _update_class();
	void _erase_class();
	void _print_classes();
	void _print_GPAs();
private:
	std::vector<Course> _classes;
	Course _read_new_class();
	int _find_class();
	double _get_GPA();
	double _get_accreditor_GPA(std::string accreditor);
};

#pragma once
#include "Course.h"
#include <vector>

class Courses
{
public:
	Courses();
	~Courses();
	int _size();
	bool _empty();
	Course operator[](int n);
	void _add_course();
	void _add_course(Course new_course);
	void _insert_course();
	void _edit_course();
	void _erase_course();
	void _print_courses();
	void _print_GPAs();
private:
	std::vector<Course> _courses;
	Course _read_new_course();
	int _read_units();
	int _find_course();
	std::vector<std::string> _list_accreditors();
	double _get_GPA(std::string accreditor);
};

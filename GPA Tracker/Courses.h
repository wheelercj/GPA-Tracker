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
	void _print_edit_menu();
	void _run_edit_menu(std::string menu_choice, Course& course);
	void _erase_course();
	void _print_courses();
	void _print_GPAs();
	void _print_transferable_units(std::vector<std::string> accreditors);
private:
	std::vector<Course> _courses;
	enum { NAME = 1, UNITS, GRADE, ACCREDITORS, RETURN };

	Course _read_new_course();
	std::string _read_name();
	int _read_units();
	char _read_grade();
	std::string _read_accreditors();

	int _find_course();
	std::vector<std::string> _list_accreditors();
	double _get_GPA(std::string accreditor);
};

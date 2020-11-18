#include "Courses.h"
#include <fstream>

Courses load_courses_from_file();
Course parse_course(std::string line);
void save_courses_to_file(Courses courses);
void print_menu();
void run_menu(std::string menu_choice, Courses& courses);
enum { ADD = 1, INSERT, EDIT, DELETE, VIEW_COURSES, VIEW_GPA_AND_UNITS, EXIT };

int main()
{
	Courses courses = load_courses_from_file();

	std::string menu_choice;
	do
	{
		print_menu();
		std::cin >> menu_choice;
		run_menu(menu_choice, courses);
	} while (menu_choice != std::to_string(EXIT));

	save_courses_to_file(courses);
}

void print_menu()
{
	std::cout << "\n GPA Tracker:"
		<< "\n " << ADD << ". add course"
		<< "\n " << INSERT << ". insert course"
		<< "\n " << EDIT << ". edit course"
		<< "\n " << DELETE << ". delete course"
		<< "\n " << VIEW_COURSES << ". view courses"
		<< "\n " << VIEW_GPA_AND_UNITS << ". view GPAs and transferable units"
		<< "\n " << EXIT << ". save and exit"
		<< "\n> ";
}

void run_menu(std::string menu_choice, Courses& courses)
{
	if (menu_choice < "1" || menu_choice > "9")
		return;
	
	switch (stoi(menu_choice))
	{
	case ADD: // add a course
		std::cin.ignore();
		courses._add_course();
		break;
	case INSERT: // insert a course
		courses._insert_course();
		break;
	case EDIT: // edit a course
		courses._edit_course();
		break;
	case DELETE: // delete a course
		courses._delete_course();
		break;
	case VIEW_COURSES: // view all courses
		courses._print_courses();
		break;
	case VIEW_GPA_AND_UNITS: // view all GPAs and transferable units
		courses._print_GPAs_and_units();
		break;
	case EXIT: // save and quit the program
		break;
	}
}

Courses load_courses_from_file()
{
	Courses courses;

	std::ifstream file("saved_courses.txt");
	if (file)
	{
		// each course is on one line
		for (std::string line; std::getline(file, line);)
			courses._add_course(parse_course(line));
		file.close();

		if (courses._empty())
			return courses;

		std::cout << "\n Loaded saved courses from saved_courses.txt\n";
	}

	return courses;
}

Course parse_course(std::string line)
{
	// each part of the course is delimited by ASCII character 219.
	int i = 0;

	// parse course name
	for (; line[i] != (char)219; i++);
	std::string name = line.substr(0, i);
	line.erase(0, i + 1);
	i = 0;

	// parse course units
	for (; line[i] != (char)219; i++);
	int units = stoi(line.substr(0, i));
	line.erase(0, i + 1);
	i = 0;

	// parse course grade
	for (; line[i] != (char)219; i++);
	char grade = line[0];
	line.erase(0, i + 1);
	i = 0;

	// parse course accreditors
	for (; line[i] != (char)219; i++);
	std::string accreditors = line.substr(0, i);
	line.erase(0, i + 1);
	i = 0;

	return Course(name, units, grade, accreditors);
}

void save_courses_to_file(Courses courses)
{
	if (courses._empty())
		return;

	std::ofstream file("saved_courses.txt");

	for (int i = 0; i < courses._size(); i++)
	{
		file << courses[i]._get_name() << (char)219
			<< courses[i]._get_units() << (char)219
			<< courses[i]._get_grade() << (char)219
			<< courses[i]._get_accreditors() << (char)219
			<< std::endl;
	}

	file.close();
}

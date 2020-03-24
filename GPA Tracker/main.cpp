#include "Courses.h"
#include <fstream>

Courses load_courses();
Course load_course(std::string line);
void save_courses(Courses courses);
void print_menu();
void run_menu(std::string menu_choice, Courses& courses);
enum { ADD = 1, INSERT, EDIT, DELETE, VIEW_COURSES, VIEW_GPA, EXIT };

int main()
{
	Courses courses = load_courses();

	std::string menu_choice;
	do
	{
		print_menu();
		std::cin >> menu_choice;
		run_menu(menu_choice, courses);
	} while (menu_choice != std::to_string(EXIT));

	save_courses(courses);
}

void print_menu()
{
	std::cout << "\n GPA Tracker:"
		<< "\n " << ADD << ". Add course"
		<< "\n " << INSERT << ". Insert course"
		<< "\n " << EDIT << ". Edit course"
		<< "\n " << DELETE << ". Delete course"
		<< "\n " << VIEW_COURSES << ". View courses"
		<< "\n " << VIEW_GPA << ". View GPA"
		<< "\n " << EXIT << ". Save and Exit"
		<< "\n> ";
}

void run_menu(std::string menu_choice, Courses& courses)
{
	if (menu_choice < "1" || menu_choice > "9")
		return;
	
	switch (stoi(menu_choice))
	{
	case ADD:
		std::cin.ignore();
		courses._add_course();
		break;
	case INSERT:
		std::cin.ignore();
		courses._insert_course();
		break;
	case EDIT:
		courses._edit_course();
		break;
	case DELETE:
		courses._erase_course();
		break;
	case VIEW_COURSES:
		courses._print_courses();
		break;
	case VIEW_GPA:
		courses._print_GPAs();
		break;
	case EXIT:
		break;
	}
}

Courses load_courses()
{
	Courses courses;

	std::ifstream file("saved_courses.txt");
	if (file)
	{
		for (std::string line; std::getline(file, line);)
			courses._add_course(load_course(line));
		file.close();

		if (courses._empty())
			return courses;

		std::cout << "\n Loaded saved courses from saved_courses.txt\n";
	}

	return courses;
}

Course load_course(std::string line)
{
	std::string name = "";
	int units = -1;
	char grade = 'Z';
	std::string accreditor = "";

	for (int i = 0, j = 0; i < line.size(); i++)
	{
		if (line[i] == (char)219)
		{
			if (name.empty())
			{
				name = line.substr(j, i);
				j = i + 1;
			}
			else if (units == -1)
			{
				units = stoi(line.substr(j, i - j));
				j = i + 1;
			}
			else if (grade == 'Z')
			{
				grade = line[i - 1];
				j = i + 1;
			}
			else if (accreditor.empty())
			{
				accreditor = line.substr(j, i - j);
			}
		}
	}

	return Course(name, units, grade, accreditor);
}

void save_courses(Courses courses)
{
	if (courses._empty())
		return;

	std::ofstream file("saved_courses.txt");

	for (int i = 0; i < courses._size(); i++)
	{
		file << courses[i]._get_name() << (char)219
			<< courses[i]._get_units() << (char)219
			<< courses[i]._get_grade() << (char)219
			<< courses[i]._get_accreditors() << (char)219 << std::endl;
	}

	file.close();
}

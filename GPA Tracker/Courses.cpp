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

// add a course to the end of the list
void Courses::_add_course()
{
	_courses.push_back(_read_new_course());
}

// add a course to the end of the list
void Courses::_add_course(Course new_course)
{
	_courses.push_back(new_course);
}

// insert a new course above an existing course in the list
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

	std::cout << "\n Which course would you like to edit?";
	int index = _find_course();
	if (index == -1)
		std::cout << "\n Course not found\n";
	else
	{
		std::string menu_choice = "";
		do
		{
			std::cout << "\n ";
			_courses[index]._print_course();
			_print_edit_menu();
			std::cin >> menu_choice;
			_run_edit_menu(menu_choice, _courses[index]);
		} while (menu_choice != std::to_string(RETURN));
	}
}

void Courses::_print_edit_menu()
{
	std::cout << "\n\n Edit course:"
		"\n " << NAME << ". Name"
		"\n " << UNITS << ". Units"
		"\n " << GRADE << ". Grade"
		"\n " << ACCREDITORS << ". Accreditors"
		"\n " << RETURN << ". Exit"
		"\n> ";
}

void Courses::_run_edit_menu(std::string menu_choice, Course& course)
{
	if (menu_choice < "1" || menu_choice > "9")
		return;

	switch (stoi(menu_choice))
	{
	case NAME: // edit course name
		course._set_name(_read_name());
		break;
	case UNITS: // edit course units
		course._set_units(_read_units());
		break;
	case GRADE: // edit course grade
		course._set_grade(_read_grade());
		break;
	case ACCREDITORS: // edit course accreditors
		course._set_accreditors(_read_accreditors());
		break;
	case RETURN: // exit
		break;
	}
}

// delete a course
void Courses::_erase_course()
{
	if (_courses.empty())
	{
		std::cout << "\n No courses\n";
		return;
	}

	std::cin.ignore();
	int index = _find_course();
	if (index == -1)
		std::cout << "\n Course not found\n";
	else
		_courses.erase(_courses.begin() + index);
}

// print all courses
void Courses::_print_courses()
{
	if (_courses.empty())
	{
		std::cout << "\n No courses\n";
		return;
	}

	std::cout << "\n   Name             Units      Grade      Accreditor(s)"
		<< "\n-------------------------------------------------------";

	for (int i = 0; i < _courses.size(); i++)
	{
		std::cout << "\n ";
		_courses[i]._print_course();
	}

	std::cout << std::endl;
}

// print each accreditor's GPA
void Courses::_print_GPAs()
{
	if (_courses.empty())
	{
		std::cout << "\n No courses\n";
		return;
	}

	std::vector<std::string> accreditors = _list_accreditors();
	for (int i = 0; i < accreditors.size(); i++)
	{
		double GPA = _get_GPA(accreditors[i]);
		if (GPA >= 0)
			std::cout << "\n " << accreditors[i] << " GPA: " << std::fixed << GPA;
	}

	std::cout << std::endl;
}

// get a new course from the user
Course Courses::_read_new_course()
{
	std::string name = _read_name();
	int units = _read_units();
	char grade = _read_grade();
	std::string accreditors = _read_accreditors();

	return Course(name, units, grade, accreditors);
}

std::string Courses::_read_name()
{
	std::cout << "\n Enter name: ";
	std::string name;
	std::cin.ignore();
	std::getline(std::cin, name);
	return name;
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

char Courses::_read_grade()
{
	std::cout << "\n Enter grade: ";
	char grade;
	std::cin >> grade;
	grade = toupper(grade);
	return grade;
}

std::string Courses::_read_accreditors()
{
	std::cout << "\n Enter accreditor(s) as a slash-separated list, e.g. LAVC/CSU/UC:\n ";
	std::string accreditors;
	std::cin.ignore();
	std::getline(std::cin, accreditors);
	return accreditors;
}

int Courses::_find_course()
{
	std::cout << "\n\n Enter course name: ";
	std::string name;
	std::getline(std::cin, name);

	for (int i = 0; i < _courses.size(); i++)
	{
		if (name == _courses[i]._get_name())
			return i;
	}

	return -1;
}

std::vector<std::string> Courses::_list_accreditors()
{
	std::vector<std::string> list;

	// for each course
	for (int i = 0; i < _courses.size(); i++)
	{
		// for each course's accreditors
		std::string accreditors = _courses[i]._get_accreditors();
		for (int j = 0; j < accreditors.size(); j++)
		{
			// the accreditors must be seperated by slashes
			if (accreditors[j] == '/' || j == accreditors.size() - 1)
			{
				if (accreditors[j] == '/')
				{
					accreditors.erase(j, 1);
					j--;
				}

				std::string next = accreditors.substr(0, j + 1);

				// add the accreditor to the list if it's not already there
				bool found = false;
				for (int k = 0; !found && k < list.size(); k++)
				{
					if (next == list[k])
						found = true;
				}
				if (!found)
					list.push_back(next);

				accreditors.erase(0, j + 1);
				j = 0;
			}
		}
	}

	return list;
}

// Returns the GPA for one accreditor.
// Returns -1 if the accreditor is not giving credit for any units
// e.g. if the user entered "none" as the accreditor for all courses 
// with a grade of 'W'.
double Courses::_get_GPA(std::string accreditor)
{
	int total_grade_points = 0,
		GPA_units = 0; // the total units attempted that count towards the GPA

	// for each course
	for (int i = 0; i < _courses.size(); i++)
	{
		// if the course is accredited
		if (_courses[i]._get_accreditors().find(accreditor) != std::string::npos)
		{
			// if the course's grade is not a 'W'
			int grade_points = _courses[i]._get_grade_points();
			if (grade_points >= 0)
			{
				// add its grade points and GPA units to the totals
				total_grade_points += grade_points;
				GPA_units += _courses[i]._get_units();
			}
		}
	}

	if (!GPA_units)
		return -1;
	return (double)total_grade_points / GPA_units;
}

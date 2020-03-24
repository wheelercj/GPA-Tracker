#include "Courses.h"
#include <fstream>

Courses load_classes();
Course load_class(std::string line);
void save_classes(Courses classes);
void print_menu();
void run_menu(int menu_choice, Courses& classes);
enum { ADD = 1, UPDATE, DELETE, VIEW_CLASSES, VIEW_GPA, EXIT };

int main()
{
	Courses classes = load_classes();

	int menu_choice;
	do
	{
		print_menu();
		std::cin >> menu_choice;
		run_menu(menu_choice, classes);
	} while (menu_choice != EXIT);

	save_classes(classes);
}

void print_menu()
{
	std::cout << "\n Transfer GPA Calculator:"
		<< "\n " << ADD << ". Add a class" // TODO: add an insert option?
		<< "\n " << UPDATE << ". Update a class"
		<< "\n " << DELETE << ". Delete a class"
		<< "\n " << VIEW_CLASSES << ". View classes"
		<< "\n " << VIEW_GPA << ". View GPA" // TODO: add a help option that shows an example table of classes? Andn says not to add classes that don't count towards GPA?
		<< "\n " << EXIT << ". Exit"
		<< "\n> ";
}

void run_menu(int menu_choice, Courses& classes)
{
	switch (menu_choice)
	{
	case ADD:
		std::cin.ignore();
		classes._add_class();
		break;
	case UPDATE:
		classes._update_class();
		break;
	case DELETE:
		classes._erase_class();
		break;
	case VIEW_CLASSES:
		classes._print_classes();
		break;
	case VIEW_GPA:
		classes._print_GPAs();
		break;
	case EXIT:
		break;
	}
}

Courses load_classes()
{
	Courses classes;

	std::ifstream file("saved_classes.txt");
	if (file)
	{
		for (std::string line; std::getline(file, line);)
			classes._add_class(load_class(line));
		file.close();
		std::cout << "\n Loaded saved classes from saved_classes.txt\n";
	}

	return classes;
}

Course load_class(std::string line)
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

void save_classes(Courses classes)
{
	std::ofstream file("saved_classes.txt");

	for (int i = 0; i < classes._size(); i++)
	{
		file << classes[i]._get_name() << (char)219
			<< classes[i]._get_units() << (char)219
			<< classes[i]._get_grade() << (char)219
			<< classes[i]._get_accreditors() << (char)219 << std::endl;
	}

	file.close();
}

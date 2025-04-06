#include <iostream>
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "BinarySearchTree.h"
using namespace std;

void printItem(int item)
{
	cout << item << " ";
}

class Date {
public:
	int day;
	int month;
	int year;

	// Constructor to initialize a date
	Date(int d, int m, int y) : day(d), month(m), year(y) {}

	// Function to display the date
	void displayDate() const {
		cout << month << "/" << day << "/" << year << endl;
	}
};

// Person struct with a Date member for the birthday
struct Person {
	string name; 
	Date birthday;  

	Person() : name(""), birthday(0, 0, 0) {}

	//Operator overloaders
	bool operator==(const Person& other) const 
	{
		return (name == other.name);
	}
	bool operator>(const Person& rhs) const
	{
		return (name > rhs.name);
	}
	bool operator<(const Person& rhs) const
	{
		return (name < rhs.name);
	}
};

void displayPerson(Person person)
{
	cout << "Name: " << person.name << endl;
	cout << "Birthday: ";
	person.birthday.displayDate();
}

int main()
{
	BinaryNodeTree<Person> tree;
	char choice;
	string newName;
	int newDay, newMonth, newYear;
	Person person;
	char repeat = 'a';

	do
	{
		//Output menu
		cout << "\n\n(E)nter--add a new person to your list\n"
			<< "(M)odify--change the name or birthday of a person\n"
			<< "(R)emove--remove a person from your list\n"
			<< "(S)earch--display the information about a given person\n"
			<< "(Q)uery--run a query by entering a month\n"
			<< "(P)rint--print list of people\n"
			<< "(Q)uit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice)
		{
		case 'e':
		case 'E':
			cin.ignore();
			cout << "Enter person's name: ";
			getline(cin, newName);
			cout << "\nEnter person's birth year: ";
			cin >> newYear;
			cout << "\nEnter person's birth month(1-12): ";
			cin >> newMonth;
			cout << "\nEnter person's birth day: ";
			cin >> newDay;
			person.name = newName;
			person.birthday.year = newYear;
			person.birthday.month = newMonth;
			person.birthday.day = newDay;

			tree.add(person);
			break;
		case 'm':
		case 'M':
			cout << "Enter name of person you want to modify: ";
			getline(cin, newName);

			if (tree.contains())
			break;
		case 'p':
		case 'P':
			tree.inorderTraverse(displayPerson);
			break;
		}
	} while (repeat != 'q' || repeat != 'Q');


	
	return 0;
}
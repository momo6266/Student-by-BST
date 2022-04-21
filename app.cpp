#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	<string>
#include	<iomanip>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(char*, BST*);

int menu();
char filename1[] = "student.txt";
int studcount, order, source, options;
char quit = 'N';


BST tree = BST();
BST tree2 = BST();
BTNode* cur;
Student student = Student();
Queue q = Queue();
Student stu = Student();

int main() {

	do
	{
		menu();

		if (options == 1)
		{
			readFile(filename1, &tree);
		}

		if (options == 2)
		{
			tree.deepestNodes();
		}

		if (options == 3)
		{
			cout << "Which order according to id do you want to display the output (1 - Ascending / 2 - Descending): ";
			cin >> order;
			cout << "Where do you want to display the output (1 - Screen / 2 - File): ";
			cin >> source;
			tree.display(order, source);
		}

		if (options == 4)
		{
			cout << "Please enter node of subtree you want to clone:";
			cin >> stu.id;
			tree.CloneSubtree(tree2, stu);
			
		}

		if (options == 5)
		{
			cout << "Please enter node you wish to find it's ancestors:";
			cin >> stu.id;
			tree.printAncestor(stu);
			cout << endl;
			
		}

		if (options == 6)
		{
			tree.printSpiral();
		}

		if (options == 7)
		{
			quit = 'Y';
		}


	} while (quit != 'Y');

	cout << "\n\n";
	system("pause");
	return 0;
}

bool readFile(char* filename, BST* t1)
{
	string temp, tmp;


	ifstream read(filename, ios::in);

	if (read.fail())
	{
		return false;
	}

	while (!read.eof())
	{

		read >> temp >> tmp;
		read >> student.id; // read from file to struct
		read >> temp >> temp;
		read.getline(student.name, 30);
		read >> temp >> temp;
		read.getline(student.address, 100);
		read >> temp >> temp;
		read.getline(student.DOB, 20);
		read >> temp >> temp;
		read.getline(student.phone_no, 10);
		read >> temp >> temp;
		read >> student.course;
		read >> temp >> temp;
		read >> student.cgpa;

		if (tmp == "=")
		{
			t1->insert(student); // insert into Binary Search Tree
		}
		
		tmp = "0";

		
	}

	studcount = t1->countNode(); // record student count
	cout << studcount << " new records have been successfully read." << endl << endl;
	return true;
}

int menu()
{
	cout << endl <<
		R"(
		Menu
		(1)	Read data to BST
		(2)	Print deepest nodes
		(3)	Display student
		(4)	Clone Subtree
		(5)	Print Ancestor
		(6)	Print Spiral
		(7)	Exit

		Enter your choice :)";

	cin >> options;
	cout << endl;

	return options;
}


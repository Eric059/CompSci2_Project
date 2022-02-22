#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

void menu();
void NewCust();
void DelCust();

int main()
{
	int choice;
	menu();
	cout << "Enter your chioce(1-8): ";
	cin >> choice;
	switch (choice)
	{
	case 1:NewCust();
	}
	
	return 0;
}

void menu()
{
	cout << "Lawrence Tech Employee Credit Union" << endl << endl;
	cout << "*****Welcome to the Main Menu*****" << endl << endl;
	cout << "1.Creat a new checking account." << endl;
	cout << "2.Remove an existing account." << endl;
	cout << "3.Update name,address information for an existing customer." << endl;
	cout << "4.Deposit transaction." << endl;
	cout << "5.Withdrawal transaction." << endl;
	cout << "6.List information of an existing customer." << endl;
	cout << "7.List customer names and ids" << endl;
	cout << "8.Exit the program." << endl << endl;
}
void NewCust()
{
	string name,
		type,
		address;
	int ssn,
		birth,
		phone;
	float deposit = 0;
	ofstream output;
	output.open("CustomerData.txt");
	if (output.fail())
	{
		cout << "The file out put fail" << endl;
		system("pause");
		exit(0);
	}
	cout << "Please enter your name: ";
	getchar();
	getline(cin, name);
	cout << "Please enter your date of birth £¨MMDDYYYY): ";
	cin >> birth;
	cout << "Please enter your SSN: ";
	cin >> ssn;
	cout << "Please enter your address: ";
	getchar();
	getline(cin, address);
	cout << "please enter your phone number:";
	cin >> phone;
	cout << "Please type the type of your account.(C or S)";
	cin >> type;
	output << setw(15) << name << setw(10) << birth << setw(10) << ssn << setw(50) << address << setw(15) << phone << setw(20) << type << setw(10) << deposit << endl;
}
void Delcust()
{

}

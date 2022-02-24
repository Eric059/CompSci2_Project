#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct CustInfo
{
	string name,
		type,
		address;
	int ssn,
		birth,
		phone;
	float deposit;
};

void menu();
void printdata(CustInfo *);
void NewCust(CustInfo *);
void DelCust(CustInfo *);
void editCust(CustInfo *);

int main()
{
	int choice;
	CustInfo info[10];
	menu();
	cout << "Enter your chioce(1-8): ";
	cin >> choice;
	switch (choice)
	{
	case 1:NewCust(info);
		break;
	case 2:DelCust(info);
		break;
	case 3:editCust(info);
		break;
}
	system("pause");
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
void NewCust(CustInfo *p)
{
	int n,
		i;
	cout << "Please enter how many account you want create?" << endl;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		cout << "Please enter your name: ";
		cin.ignore();
		getline(cin,p[i].name);
		cout << "Please enter your date of birth （MMDDYYYY): ";
		cin >> p[i].birth;
		cout << "Please enter your SSN: ";
		cin >> p[i].ssn;
		cout << "Please enter your address: ";
		cin.ignore();
		getline(cin, p[i].address);
		cout << "please enter your phone number:";
		cin >> p[i].phone;
		cout << "Please type the type of your account.(C or S)";
		cin.ignore();
		getline(cin, p[i].type);
		cout << "How much you want put to open your account?";
		cin >> p[i].deposit;
	}
	
}
void printdata(CustInfo* p)
{
	int i = 0,
		n = 10;
	for (i = 0; i < n; i++)
	{
		cout << "The customer information you have are: " << endl;
		cout << "Customer ID: " << i << endl;
		cout << "   Customer Name: " << p[i].name;
		cout << "   Date of Birth: " << p[i].birth;
		cout << "   SSN: " << p[i].ssn;
		cout << "   Address: " << p[i].address;
		cout << "   Phone: " << p[i].phone;
		cout << "   Account Type: " << p[i].type;
		cout << "   Deposit: " << p[i].deposit << endl;
	}
}
void DelCust(CustInfo *p)
{
	int i = 0;
	string deletename;
	string nullstr = { "\0" };
	cout << ("\nEnter Name to delete: ");
	cin >> deletename;
	for (i = 0; i < 10; i++)
	{
		if (strcmp(deletename, p[i].name) == 0)
		{
			strcpy(p[i].name, nullstr);
			strcpy(p[i].type, nullstr);
			strcpy(p[i].birth, nullstr);
			strcpy(p[i].ssn, nullstr);
			strcpy(p[i].phone, nullstr);
			strcpy(p[i].deposit, nullstr);
			i--;
		}
	}
}
void editCust(CustInfo *p)
{
	int i;
	cout << "Please enter the ID number you want edit." << endl;
	cin >> i;
	cout << endl;
	cout << "SSN number: ";
	cin >> p[i].ssn;
	cout << "Phone Number: ";
	cin >> p[i].phone;
	cout << "Birthday: ";
	cin >> p[i].birth;
}

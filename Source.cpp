//Team Project Part 2 
//Xinrui Li and Elijah Nemr

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int s = 100; // Size of array

fstream customerinfo;
fstream tempinfo;


struct Customer
{
	char name[s];
	char address[s];
	char dob[s];
	char ssn[s];
	char phone[s];
	double balance;
	char type[s];
};

void NewCust(long);
long SearchInfo();
void Deposit(long);
void Withdrawl(long);
void DelCust(long);
void ViewCustInfo(long);
void ListCust();

bool newCustomer = false;
bool modified = false;

int main()
{
	long fileposition;
	int choice = 8;
	char YesOrNo;

	do
	{
		cout << "\n Lawrence Tech Employee Credit Union \n\n";
		cout << "*****Welcome to the Main Menu*****\n";
		cout << "1. Create a new checking account . \n";
		cout << "2. Remove an existing account.   \n";
		cout << "3. Update name,address information for an existing customer. \n";
		cout << "4. Deposit transaction .\n";
		cout << "5. Withdrawal transaction.\n";
		cout << "6. List information of an existing customer.\n";
		cout << "7. List customer names and ids.\n";
		cout << "8. Exit the program.\n\n";
		cout << "Enter your choice (1-8):";
		cin >> choice;
		while (choice < 1 || choice > 8) // Add letter support later
		{
			cout << "Enter number 1 to 8 please:";
			cin >> choice;
		}

		switch (choice)
		{
		case 1:
			cin.get();
			cout << "You selected Create a new Checking Account.\n";
			newCustomer = true;
			NewCust(0);
			newCustomer = false;
			break;

		case 2:
			cout << "\nYou selected Remove a existing account.\n\n";
			fileposition = SearchInfo();
			if (fileposition != -1)
			{
				ViewCustInfo(fileposition);
				cout << "\nARE YOU SURE YOU WANT TO REMOVE THIS RECORD? (Y/N) ";
				cin >> YesOrNo;
				YesOrNo = toupper(YesOrNo);
				if (YesOrNo == 'Y')
				{
					DelCust(fileposition);
					break;
				}
				else
				{
					cout << "\nRecord was not deleted.\n";
					break;
				}
			}
			else
				cout << "\nRecord not found.\n";
			break;

		case 3:
			cout << "\nYou select update name,address information for an existing customer.\n\n";
			fileposition = SearchInfo();
			modified = true;
			if (fileposition != -1)
			{
				cout << "\nRECORD INFORMATION: \n";
				ViewCustInfo(fileposition);
				cout << "\nENTER NEW INFORMATION: \n";
				NewCust(fileposition);
				modified = false;
			}
			else
				cout << "\nRecord not found.\n";
			break;


		case 4:


		case 5:


		case 6:
			cout << "\nYou selected list information of an existing customer.\n\n";
			fileposition = SearchInfo();
			if (fileposition != -1)
			{
				ViewCustInfo(fileposition);
			}
			else
				cout << "\nRecord not found.";
			break;

		case 7:
			cout << "\nYou selected list customer names and ids.\n\n";
			ListCust();
			break;

		case 8:
			exit(EXIT_SUCCESS);
			break;

		default:
			break;

		}
	} while (choice != 8);

	return 0;
}

void NewCust(long position)
{
	Customer c;

	cout << "\nPlease enter the following information for customer:\n";
	cout << "\nCustomer name: ";
	cin.getline(c.name, s);
	while (strlen(c.name) == 0)
	{
		cout << "You must enter a name: ";
		cin.getline(c.name, s);
	}

	cout << "Date of birth: ";
	cin.getline(c.dob, s);
	while (strlen(c.dob) == 0)
	{
		cout << "You must enter an address: ";
		cin.getline(c.dob, s);
	}

	cout << "SSN: ";
	cin.getline(c.ssn, s);
	while (strlen(c.ssn) == 0)
	{
		cout << "You must enter an address: ";
		cin.getline(c.ssn, s);
	}

	cout << "Customer address: ";
	cin.getline(c.address, s);
	while (strlen(c.address) == 0)
	{
		cout << "You must enter an address: ";
		cin.getline(c.address, s);
	}

	cout << "Telephone: ";
	cin.getline(c.phone, s);
	while (strlen(c.phone) == 0)
	{
		cout << "You must enter a telephone number: ";
		cin.getline(c.phone, s);
	}

	cout << "Account balance: ";
	cin >> c.balance;
	while (c.balance < 0)
	{
		cout << "Please enter 0 or geater for account balance: ";
		cin >> c.balance;
	}

	cout << "Account Type (1 for Saving,0 for Checking: ";
	cin >> c.type;

	if (newCustomer)
	{
		customerinfo.open("cust.txt", ios::out | ios::app | ios::binary);
	}
	else if (modified)
	{
		customerinfo.open("cust.txt", ios::in | ios::out | ios::binary);
		customerinfo.seekp(position, ios::beg);
	}

	if (customerinfo.fail())
	{
		cout << "\nError opening file.\n";
		exit(0);
	}

	customerinfo.write(reinterpret_cast<char*>(&c), sizeof(c));
	if (customerinfo.fail())
	{
		cout << "\nError writing record to file.\n";
		exit(0);
	}
	else
	{
		cout << "\nRecord written to file.\n\n";
		cout << "\nPress Enter to continue...";
		cin.get();
	}

	customerinfo.close();
}

long SearchInfo()
{
	char name[s];
	Customer c;
	long position;
	cout << "\nEnter all or part of the customer name: ";
	cin.ignore();
	cin.getline(name, s);

	if (name[0] == '\0')
	{
		return -1;
	}

	customerinfo.open("cust.txt", ios::in | ios::binary);
	if (customerinfo.fail())
	{
		cout << "\nError opening file.\n";
		customerinfo.close();
		exit(0);
	}

	while (!customerinfo.eof())
	{
		customerinfo.read(reinterpret_cast<char*>(&c), sizeof(Customer));

		if (strstr(c.name, name) != nullptr)
		{
			position = static_cast<long>(customerinfo.tellg());
			customerinfo.close();
			return (position - sizeof(c));
		}
	}

	cout << "Record not found\n";
	customerinfo.close();

	return -1;
}

void DelCust(long position)
{
	Customer c;
	int Rec = 0;
	customerinfo.open("cust.txt", ios::in | ios::out | ios::binary);
	if (customerinfo.fail())
	{
		cout << "\nError opening file.\n";
		customerinfo.close();
		exit(0);
	}

	strcpy_s(c.name, "\0");
	customerinfo.seekp(position, ios::beg);
	customerinfo.write(reinterpret_cast<char*>(&c), sizeof(c));
	customerinfo.close();
	customerinfo.open("cust.txt", ios::in | ios::binary);
	tempinfo.open("temp.txt", ios::out | ios::binary);

	customerinfo.read(reinterpret_cast<char*>(&c), sizeof(c));
	while (customerinfo)
	{
		tempinfo.write(reinterpret_cast<char*>(&c), sizeof(c));
		customerinfo.read(reinterpret_cast<char*>(&c), sizeof(c));
	}

	customerinfo.close();
	tempinfo.close();

	tempinfo.open("temp.txt", ios::in | ios::binary);
	customerinfo.open("cust.txt", ios::out | ios::binary);

	tempinfo.read(reinterpret_cast<char*>(&c), sizeof(c));
	while (!tempinfo.eof())
	{
		if (c.name[0] != '\0')
		{
			customerinfo.write(reinterpret_cast<char*>(&c), sizeof(c));
		}
		tempinfo.read(reinterpret_cast<char*>(&c), sizeof(c));
	}

	tempinfo.close();
	customerinfo.close();
	cout << "\nDeletion successful.\n";
}

void ViewCustInfo(long position)
{
	Customer c;

	customerinfo.open("cust.txt", ios::in | ios::binary);
	if (customerinfo.fail())
	{
		cout << "\nError opening file.\n";
		exit(0);
	}
	if (!customerinfo)
	{
		cout << "\nFile is empty.\n";
		customerinfo.close();
		exit(0);
	}

	customerinfo.seekg(position, ios::beg);
	customerinfo.read(reinterpret_cast<char*>(&c), sizeof(Customer));

	cout << fixed << showpoint << setprecision(2);
	cout << "Customer name: " << c.name << endl;
	cout << "Customer address: " << c.address << endl;
	cout << "Date of Birth: " << c.dob << endl;
	cout << "SSN: " << c.ssn << endl;
	cout << "Telephone: " << c.phone << endl;
	cout << "Account balance: $" << c.balance << endl;
	cout << "Account Type (1 for Saving,0 for Checking: " << c.type << endl;

	customerinfo.close();
	cout << "\nPress Enter to continue.";
	cin.get();
}

void ListCust()
{
	cin.ignore();
	Customer c;
	int count = 0;
	customerinfo.open("cust.txt", ios::in | ios::binary);
	if (customerinfo.fail())
	{
		cout << "\nError opening file.\n";
		customerinfo.close();
		exit(0);
	}
	cout << "\n***Customer list***\n\n";

	customerinfo.read(reinterpret_cast<char*>(&c), sizeof(Customer));
	while (customerinfo)
	{
		cout << fixed << showpoint << setprecision(2);
		cout << "\nRECORD NUMBER " << ++count << ":" << endl;
		cout << "\nCustomer name: " << c.name << endl;
		cout << endl;
		cout << "\nPress Enter to Continue...";
		cin.get();
		customerinfo.read(reinterpret_cast<char*>(&c), sizeof(Customer));
	}
	if (count == 0)
	{
		cout << "\nFile is empty." << endl;
	}
	cout << "\n***End of Customer Record Listing***\n\n";
	customerinfo.close();
}

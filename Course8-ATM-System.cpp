#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

string clientsFilePath = "C:\\Users\\Gsty\\source\\repos\\Course8-Bank-Extension-Project\\Clients.txt";
string delim = "#//#";

struct stClient
{
	string accountNumber, pinCode, name, phone;
	double accountBalance;
};

enum enATMscreen
{
	quickWithdraw = 1,
	normalWithdraw = 2,
	deposit = 3,
	checkBalance = 4,
	logout = 5
};

void printMainMenu(stClient& client);

enATMscreen readATMChoice()
{
	short num;
	cout << "Choose What Do You Want to Do? [1 to 5]? ";
	do
	{
		cin >> ws >> num;
		if (num < 1 || num > 5)
		{
			cout << "\nSorry wrong input please enter a number between 1 to 5: ";
		}

	} while (num < 1 || num > 5);

	return enATMscreen(num);
}

vector <string> splitString(string line)
{
	short pos = 0;
	string word = "";
	vector <string> vS1;

	while ((pos = line.find(delim)) != std::string::npos)
	{
		word = line.substr(0, pos);

		if (word != "")
			vS1.push_back(word);

		line.erase(0, pos + delim.length());
	}

	if (line != "")
		vS1.push_back(line);

	return vS1;
}

stClient assignClientData(const vector <string>& vS1)
{
	stClient client;

	client.accountNumber = vS1[0];
	client.pinCode = vS1[1];
	client.name = vS1[2];
	client.phone = vS1[3];
	client.accountBalance = stod(vS1[4]);

	return client;
}

vector <stClient> readClientsFromFile()
{
	fstream myFile;
	stClient client;
	vector <string> vS1;
	vector <stClient> vClient;

	myFile.open(clientsFilePath, ios::in);

	if (myFile.is_open())
	{
		string line;
		while (getline(myFile, line))
		{
			vS1 = splitString(line);
			client = assignClientData(vS1);
			vClient.push_back(client);
		}

		myFile.close();
	}

	return vClient;
}

stClient getClientData(vector <stClient>& vClient, string accountNum)
{
	stClient client;

	for (stClient& c : vClient)
	{
		if (c.accountNumber == accountNum)
		{
			client = c;
			return client;
		}
	}
}

void loginScreen()
{
	vector <stClient> vClient = readClientsFromFile();
	string accountNumber, pinCode;
	stClient client;

	bool validClient = false;

	cout << "\n-----------------------------------";
	cout << "\n\tLogin Screen";
	cout << "\n-----------------------------------\n";

	cout << "\nEnter Account Number: ";
	getline(cin >> ws, accountNumber);

	cout << "\nEnter Pin Code: ";
	cin >> pinCode;

	for (short i = 0; i < vClient.size(); i++)
	{
		if (vClient[i].accountNumber == accountNumber && vClient[i].pinCode == pinCode)
		{
			validClient = true;
			client = getClientData(vClient, vClient[i].accountNumber);
			break;
		}
	}

	if (!validClient)
	{
		do
		{
			system("cls");
			cout << "\n-----------------------------------";
			cout << "\n\tLogin Screen";
			cout << "\n-----------------------------------\n";
			cout << "\nInvalid Account Number\\Pin Code!";
			cout << "\n\nEnter Account Number: ";
			getline(cin >> ws, accountNumber);

			cout << "\nEnter Pin Code: ";
			cin >> pinCode;

			for (short i = 0; i < vClient.size(); i++)
			{
				if (vClient[i].accountNumber == accountNumber && vClient[i].pinCode == pinCode)
				{
					validClient = true;
					client = getClientData(vClient, vClient[i].accountNumber);
					break;
				}
			}

		} while (!validClient);
	}

	if (validClient)
	{
		system("cls");
		printMainMenu(client);
	}
}

void checkBalanceScreen(stClient& client)
{
	cout << "\n===========================================\n";
	cout << "\tCheck Balance Screen";
	cout << "\n===========================================\n";
	cout << "\nYour Balance is " << to_string(client.accountBalance);

	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	printMainMenu(client);

}

void selectATMChoice(enATMscreen choice, stClient client)
{
	switch (choice)
	{
	case quickWithdraw:
		break;

	case normalWithdraw:
		break;

	case deposit:
		break;

	case checkBalance:
		checkBalanceScreen(client);
		break;

	default:
		loginScreen();
		break;
	}
}

void printMainMenu(stClient& client)
{
	enATMscreen choice;

	cout << "\n===========================================\n";
	cout << "\tATM Main Menu Screen";
	cout << "\n===========================================\n";
	cout << "\t[1] Quick Withdraw";
	cout << "\n\t[2] Normal Withdraw";
	cout << "\n\t[3] Deposit";
	cout << "\n\t[4] Check Balance";
	cout << "\n\t[5] Logout";
	cout << "\n===========================================\n";
	choice = readATMChoice();
	system("cls");
	selectATMChoice(choice, client);
}

//void printClientList(const vector <stClient>& vClient)
//{
//	short clientNumber = vClient.size();
//
//	
//		cout << "\n\t\t\t\t Client List (" << clientNumber << ") Client(s).\n";
//		cout << "\n___________________________________________________________________________________________\n";
//		cout << "\n| Account Number | Pin Code\t| Client Name\t\t\t| Phone\t\t| Balance\n";
//		cout << "\n___________________________________________________________________________________________\n";
//		for (short i = 0; i < clientNumber; i++)
//		{
//			cout << "\n| " << vClient[i].accountNumber << "\t\t | " << vClient[i].pinCode << "\t\t| " << left << setw(20) << vClient[i].name << "\t\t| " << vClient[i].phone << "\t| " << fixed << vClient[i].accountBalance;
//		}
//		cout << "\n___________________________________________________________________________________________\n";
//		cout << "\n\nPress any key to go back to main menu...";
//		system("pause>0");
//		system("cls");
//
//}


int main()
{
	loginScreen();

	system("pause>0");
	return 0;
}
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

enum enQuickChoice
{
	first_20 = 1,
	second_50 = 2,
	third_100 = 3,
	fourth_200 = 4,
	fifth_400 = 5,
	sixth_600 = 6,
	seventh_800 = 7,
	eighth_1000 = 8,
	exitQuick = 9
};

void printMainMenu(stClient& client, vector <stClient>& vClient);

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

enQuickChoice readQuickChoice()
{
	short num;
	cout << "Choose What to Withdraw from [1] to [8]? ";
	do
	{
		cin >> ws >> num;
		if (num < 1 || num > 9)
		{
			cout << "\nSorry wrong input please enter a number between [1] to [8]: ";
		}

	} while (num < 1 || num > 9);

	return enQuickChoice(num);
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

string convertClientToLine(stClient& client)
{
	string line = "";

	line += client.accountNumber + delim
		+ client.pinCode + delim
		+ client.name + delim
		+ client.phone + delim
		+ to_string(client.accountBalance);

	return line;
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

void writeClientsBackToFile(vector <stClient>& vClient, stClient& client)
{
	fstream myFile;

	myFile.open(clientsFilePath, ios::out);
	{
		if (myFile.is_open())
		{
			string line;
			for (stClient& c : vClient)
			{
				if (c.accountNumber == client.accountNumber)
					c.accountBalance = client.accountBalance;

				line = convertClientToLine(c);
				myFile << line << endl;
			}

			myFile.close();
		}
	}
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
		printMainMenu(client, vClient);
	}
}

void checkBalanceScreen(stClient& client, vector <stClient>& vClient)
{
	cout << "\n===========================================\n";
	cout << "\tCheck Balance Screen";
	cout << "\n===========================================\n";
	cout << "\nYour Balance is " << to_string(client.accountBalance);

	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	printMainMenu(client, vClient);

}

void withdrawMoney(stClient& client, int amount, vector <stClient>& vClient)
{
	int currentBalance = client.accountBalance;

	if (amount > currentBalance)
		cout << "\n\nThe amount exceeds your balance, make another choice.";

	else
	{
		char answer = 'n';
		cout << "\n\nAre you sure you want to perform this transaction? y/n: ";
		cin >> ws >> answer;

		if (tolower(answer) == 'y')
		{
			client.accountBalance -= amount;
			cout << "\n\nDone successfully. New balance is: " << client.accountBalance;
			writeClientsBackToFile(vClient, client);
		}
	}

	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	printMainMenu(client, vClient);
}

void selectQuickChoice(enQuickChoice choice, stClient& client, vector <stClient>& vClient)
{
	switch (choice)
	{
	case first_20:
		withdrawMoney(client, 20, vClient);
		break;

	case second_50:
		withdrawMoney(client, 50, vClient);
		break;

	case third_100:
		withdrawMoney(client, 100, vClient);
		break;

	case fourth_200:
		withdrawMoney(client, 200, vClient);
		break;

	case fifth_400:
		withdrawMoney(client, 400, vClient);
		break;

	case sixth_600:
		withdrawMoney(client, 600, vClient);
		break;

	case seventh_800:
		withdrawMoney(client, 800, vClient);
		break;

	case eighth_1000:
		withdrawMoney(client, 1000, vClient);
		break;

	default:
		printMainMenu(client, vClient);
		break;
	}
}

void quickWithdrawScreen(stClient& client, vector <stClient>& vClient)
{
	enQuickChoice choice;

	cout << "\n===========================================\n";
	cout << "\tQuick Withdraw";
	cout << "\n===========================================\n";
	cout << "\t[1] 20  \t[2] 50";
	cout << "\n\t[3] 100 \t[4] 200";
	cout << "\n\t[5] 400 \t[6] 600";
	cout << "\n\t[7] 800 \t[8] 1000";
	cout << "\n\t[9] Exit";
	cout << "\n===========================================\n";
	cout << "\nYour Balance is " << to_string(client.accountBalance);
	choice = readQuickChoice();
	selectQuickChoice(choice, client, vClient);

}

void normalWithdrawScreen(stClient& client, vector <stClient>& vClient)
{
	int amount = 0;

	cout << "\n===========================================\n";
	cout << "\tNormal Withdraw Screen";
	cout << "\n===========================================\n";
	cout << "Your Balance is: " << client.accountBalance;
	cout << "\n\nEnter an amount multiple of 5's: ";

	do
	{
		cin >> amount;

		if (amount % 5 != 0)
			cout << "\n\nWrong input, please enter an amount multiple of 5's: ";

		if (amount > client.accountBalance)
			cout << "\n\nYou dont have this much, your current balance is: " << client.accountBalance << " please enter an amount: ";

	} while ( (amount % 5 != 0)  || (amount > client.accountBalance) );

	char answer = 'n';
	cout << "Are you sure you want to perform this transaction? y/n: ";
	cin >> answer;

	if (tolower(answer) == 'y')
	{
		client.accountBalance -= amount;
		cout << "\n\nDone successfully. New balance is: " << client.accountBalance;
		writeClientsBackToFile(vClient, client);
	}

	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	printMainMenu(client, vClient);
}

void depositScreen(stClient& client, vector <stClient>& vClient)
{
	cout << "\n===========================================\n";
	cout << "\tDeposit Screen";
	cout << "\n===========================================\n";
	cout << "Your balance is: " << client.accountBalance;
	cout << "\n\nEnter a positive deposit amount: ";

	int amount;
	do
	{
		cin >> amount;

		if (amount < 0)
			cout << "\n\nNegative amount not accepted, please enter positive amount: ";

	} while (amount < 0);

	char answer = 'n';
	cout << "\n\nAre you sure you want to perform this transaction? y/n: ";
	cin >> ws >> answer;

	if (tolower(answer) == 'y')
	{
		client.accountBalance += amount;
		writeClientsBackToFile(vClient, client);
		cout << "\n\nDone successfully. New balance is: " << client.accountBalance;
	}

	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	printMainMenu(client, vClient);
}

void selectATMChoice(enATMscreen choice, stClient& client, vector <stClient>& vClient)
{
	switch (choice)
	{
	case quickWithdraw:
		quickWithdrawScreen(client, vClient);
		break;

	case normalWithdraw:
		normalWithdrawScreen(client, vClient);
		break;

	case deposit:
		depositScreen(client, vClient);
		break;

	case checkBalance:
		checkBalanceScreen(client, vClient);
		break;

	default:
		loginScreen();
		break;
	}
}

void printMainMenu(stClient& client, vector <stClient>& vClient)
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
	selectATMChoice(choice, client, vClient);
}


int main()
{
	loginScreen();

	system("pause>0");
	return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string clientsFilePath = "C:\\Users\\Gsty\\source\\repos\\Course8-Bank-Extension-Project\\Clients.txt";
string delim = "#//#";

struct stClient
{
	string accountNumber, pinCode, name, phone;
	double accountBalance;
};

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


int main()
{
	system("pause>0");
	return 0;
}
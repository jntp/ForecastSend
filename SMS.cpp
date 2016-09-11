#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

#include "Utils.h"
#include "Rest.h"
#include "TwiML.h"

using namespace twilio;

int main() {
	// Twilio REST API version
	const string API_VERSION = "2010-04-01";

	// Twilio AccountSid and AuthToken
	const string ACCOUNT_SID = "XXXX";
	const string ACCOUNT_TOKEN = "XXXX";

	// Outgoing Caller ID previously validated with Twilio
	const string CALLER_ID = "XXXX";

	string response;
	
 	vector<Var> vars; 

	// Prompt input from user 
	string sInput = ""; 
	string sChar = ""; // For later confirmation
	int iLength; // Measures the length of the message in characters

	cout << "Enter your message here: " << endl;
	getline(cin, sInput);
	iLength = sInput.size(); // Get length of string

	// Display output and ask for confirmation
	cout << endl;
	cout << "The message you are about to send is: " << endl;
	cout << sInput << endl;
	cout << endl;
	cout << "Message length: " << iLength << " characters or " << iLength/160 + 1 << " message(s) [MAX: 1600 characters]" << endl;
	cout << "This message will be sent to Justin Tang (+7143996939)" << endl;
	cout << "Are you sure you want to send this message? (y/n)" << endl;
	cout << "WARNING! ENTERING 'n' or any other character besides 'y'  will exit the program." << endl;
	getline(cin, sChar);
	char cConfirm = sChar[0]; // Obtain the first character of string and convert to char
	
	// Check confirmation 
	if (cConfirm != 'y') { 
		exit(EXIT_FAILURE); // Exit the program 
	} 

	try {
		// Twilio REST
		Rest t (ACCOUNT_SID, ACCOUNT_TOKEN);

		// Send SMS
		vars.push_back(Var("To", "XXXX"));
		vars.push_back(Var("From", "XXXXTWILIOPHONENUMBERXXXX"));
		vars.push_back(Var("Body", sInput));
		response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/SMS/Messages", "POST", vars);
		cout << response << endl;  
	} catch (char const* str) {
		cout << "Exception raised: " << str << endl; 
	}

	return 0;
}



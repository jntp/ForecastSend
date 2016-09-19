#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream> 
#include <sstream> 

using namespace std;

#include "Utils.h"
#include "Rest.h"
#include "TwiML.h"

using namespace twilio;

/* 
 * Prompts user to enter a city or region. Checks for proper input and assigns an integer. Coverts integer to a string used as an identifier in the 
 * database.
 * Output: string code for identification  
 */
string City();


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
	
	// Prompt user to indicate who will receive the message, based on the city/region
	string sIdentifier = City(); // Get the string to search later	

	// Open data.txt and search for recipients 
	string line;
	ifstream database("data.txt");

	if (database.is_open()) { // Check for open file
		// Create a vector to dynamically allocate space for array string
		vector<string> saRecipients; 
		int iTest; // Testing
	
		// Search through the text.file and look for recipients in the specified region 
		while (getline(database, line)) { // Go through each line
			iTest++; // Testing

			// Check if every user specified to send the message to every recipient in the database 
			if (sIdentifier == "ALL") {
				saRecipients.push_back(line); // Add each recipient information to the array of strings
			} else { 
				if (line.find(sIdentifier, 0) != string::npos) { // Search for item not an the end of the string (!= string::npos)
					// Store in array of strings
					saRecipients.push_back(line); 
				}
			}

			cout << saRecipients[iTest] << endl; // Testing
		}

		database.close();
	} else {
		cout << "Error! Unable to open file. Program will exit." << endl;
		exit(EXIT_FAILURE); // Exit the program 
	}

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
		vars.push_back(Var("From", "XXTWILIONUMBERXX"));
		vars.push_back(Var("Body", sInput));
		response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/SMS/Messages", "POST", vars);
		cout << response << endl;  
	} catch (char const* str) {
		cout << "Exception raised: " << str << endl; 
	}

	return 0;
}

/* 
 * Prompts user to enter a city or region. Checks for proper input and assigns an integer. Coverts integer to a string used as an identifier in the 
 * database.
 * Output: string code for identification  
 */
string City() {
	string sInput = ""; // For inputing integers 
	int iInput;

	while (true) {
		cout << endl;
		cout << "Of which city/region will recipients receive your message?" << endl;
		cout << "0: ALL RECIPIENTS" << endl;
		cout << "1: San Francisco/Oakland, CA" << endl;
		cout << "2: Davis/Sacramento, CA" << endl;
		cout << "3: Los Angeles Area, CA" << endl;
		cout << "4: Tucson, AZ" << endl; 
		getline(cin, sInput); 

		if (stringstream(sInput) >> iInput) { // Check for integer
			if (iInput >= 0 && iInput <= 4) { // Correct input
				break; // End the while loop
			}
		}	
	}

	// Convert integer to a string code, which can be identifed in the database
	switch (iInput) {
		case 0: // All Recipients
			sInput = "ALL";
			break;
		case 1: // San Francisco/Oakland, CA
			sInput = "SF";
			break;
		case 2: // Davis/Sacramento, CA
			sInput = "SAC";
			break;
		case 3: // Los Angeles, CA
			sInput = "LA";
			break;
		case 4: // Tucson, AZ
			sInput = "TCSN";
			break;
	}

	return sInput; 
}



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
	string sLine;
	ifstream database("data.txt");

	// Create a vector to dynamically allocate space for array strings
	vector<string> saNames; // For the names of recipients
	vector<string> saNumbers; // For the recipients' phone numbers
	unsigned int uiTally = 0; // Keeps track of number of recipients

	if (database.is_open()) { // Check for open file 
		// Variables for parsing strings 
		string sDelimiter = ", "; 
		string sToken; // Temporarily stores parsed substring
		size_t pos = 0; // Starting position of string
	
		// Search through the text file and look for recipients in the specified region 
		while (getline(database, sLine)) { // Go through each line
			// Check if every user specified to send the message to every recipient in the database 
			if (sIdentifier == "ALL" || sLine.find(sIdentifier, 0) != string::npos) {
				// Parse the string
				pos = sLine.find(sDelimiter); // Find position of delimiter in string and assign to pos
				sToken = sLine.substr(0, pos); // Get the substring and assign to the temporary sToken string
				saNames.push_back(sToken); // Add to the array of strings
				sLine.erase(0, pos + sDelimiter.length()); // Erase the name part of the string

				pos = 0 + sLine.find(sDelimiter); // Reset the position and assign new position based on the next delimiter
				sLine.erase(0, pos + sDelimiter.length()); // Erase the city part, leaving out only the phone number
				saNumbers.push_back(sLine); // Amend to string array 

				uiTally++; 				 
			} 
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

	// Display recipients' name and phone number
	cout << "This message will be sent to ";
	for (unsigned int i = 0; i < uiTally; i++) {
		cout << saNames[i] << " (" << saNumbers[i] << ")";
		
		// Determine if the current recipient is not the last one... for formatting purposes 
		if (i != (uiTally - 1)) {
			cout << ", ";
		}
	}
	cout << "." << endl; // Amend a period to end the sentence

	cout << endl; 
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
		vars.push_back(Var("From", "XXTWILIONUMBERXX"));
		vars.push_back(Var("Body", sInput));
		vars.push_back(Var("To", ""));

		// Send to each recipient individually 
		for (unsigned int j = 0; j < uiTally; j++) {  
			vars[2].value = saNumbers[j]; // vars[2] refers to the "To" parameter
			response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/Messages", "POST", vars);
			cout << response << endl;  
			cout << endl; 
		}
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
		cout << "5: San Jose, CA" << endl; 
		cout << "6: San Diego Area, CA" << endl; 
		getline(cin, sInput); 

		if (stringstream(sInput) >> iInput) { // Check for integer
			if (iInput >= 0 && iInput <= 6) { // Correct input
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
		case 5: // San Jose, CA
			sInput = "SJ";
			break; 
		case 6: // San Diego Area, CA
			sInput = "SD";
			break; 
	}

	return sInput; 
}



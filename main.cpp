#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "parameters.h"

using namespace std;

#include "Utils.h"
#include "Rest.h"
#include "TwiML.h"

using namespace twilio;

int main() {
	string sForecast = Parameters(); // Run the "Fill in Parameters" part of the code and obtain weather forecast

	// Display the string
	cout << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "The following text will be printed onto 'forecast.txt'" << endl;
	cout << "Modifications may be done via a text editor." << endl;
	cout << endl;
	cout << "*****START*****" << endl;
	cout << sForecast << endl;
	cout << "******END******" << endl;
	cout << endl;
	cout << "Now saving text onto 'forecast.txt'..." << endl;

	// Open a file
	ofstream endFile("forecast.txt");

	// Check if the file opened successfully
	if (endFile.is_open()) { // If file opened successfully
		endFile << sForecast; // Save forecast onto the file
		endFile.close(); // Close the file
		cout << "Complete! You may now view 'forecast.txt' using a text editor." << endl; // Display message indicating success
	} else { // If file failed to open succesfully
		cout << "Error! Unable to open file." << endl; // Display error message 
	}

	// Give user time to edit forecast.txt
	string sInput = ""; // Allow for user input using getline
	
	cout << endl;
	cout << "Please take the time to make any last minute changes to the file." << endl;
	cout << "When you're done, press any key to continue." << endl; 
	getline(cin, sInput);


	/****** HERE MARKS THE BEGINNING OF TWILIO REST API CODE ******/

	// Twilio REST API version
	const string API_version = "2010-04-01"; 
	
	// Twilio AccountSid and AuthToken
	const string ACCOUNT_SID = "XXXX";
	const string ACCOUNT_TOKEN = "XXXX";
	
	// Outgoing Caller ID previous validated with Twilio
	const string CALLER_ID = "XXXX";

	string response;
	
	vector<Var> vars;

	

		

	
	
	return 0;
}


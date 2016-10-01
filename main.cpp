#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

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
	const string API_VERSION = "2010-04-01"; 
	
	// Twilio AccountSid and AuthToken
	const string ACCOUNT_SID = "XXXX";
	const string ACCOUNT_TOKEN = "XXXX";
	
	// Outgoing Caller ID previous validated with Twilio
	const string CALLER_ID = "XXXX";

	string response;
	
	vector<Var> vars;

	// Get the city code string
	string sCity = CityCode();

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
			if (sLine.find(sCity, 0) != string::npos) { 
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
		cout << "Error! Unable to open data.txt. Program will exit." << endl;
		exit(EXIT_FAILURE); // Exit the program 
	}

	// Open forecast.txt to display for user confirmation 
	string sProduct = ""; // Forecast to send via Twilio 
	int iLength; // Measures the length of the message in characters 

	while (true) { // Loops to allow for user confirmation 
		ifstream forecast("forecast.txt"); 

		if (forecast.is_open()) {
			// Go through each line and save in a string
			while (getline(forecast, sLine)) {
 				// Check if sLine is the greeting message
				if (sProduct == "") {
					sLine = sLine + "\n"; // Amend a newline character to format the message
				}

				// Check for empty line
				if (sLine == "") {
					sLine = "\n\n"; // Assign two newline characters to sLine for double spacing 
				} 

				sProduct = sProduct + sLine; // Concatenate to sProduct each time the program retrieves sLine from file
			}

			iLength = sProduct.size(); // Get length of string 

			forecast.close(); 
		} else {
			cout << "Error! Unable to open forecast.txt. Program will exit." << endl;
			exit(EXIT_FAILURE); 
		}

		// Prepare to display the forecast
		cout << endl; 
		cout << "-------------------------------------------------------" << endl;
		
		// Display the recipients' name and phone number
		cout << "The following text will be sent to ";
		for (unsigned int i = 0; i < uiTally; i++) {
			cout << saNames[i] << " (" << saNumbers[i] << ")";

			// Determine if the current recipient is not the last one... for formatting purposes
			if (i != (uiTally - 1)) {
				cout << ", ";
			}
		}
		cout << "." << endl; // Amend a period to end the sentence
		
		cout << endl;
		cout << "*****START*****" << endl;
		cout << sProduct << endl; // Display the forecast 
		cout << "******END******" << endl;
		cout << endl; 
		cout << "MESSAGE LENGTH: " << iLength << " characters." << endl;
		cout << "NUMBER OF MESSAGES: " << iLength/160 + 1 << endl; 

		// Prompt user for confirmation
		cout << endl;
		cout << "Are you sure you want to send the forecast? (y/n)" << endl;
		getline(cin, sInput);

		if (sInput == "y") {
			break; // End the while loop
		} else if (sInput == "n") {
			sProduct = ""; // Empty the forecast string
			cout << endl;
			cout << "Please edit forecast.txt and try again." << endl;
			cout << "Press any key to continue." << endl;
			getline(cin, sInput); 
		} else {	
			sProduct = ""; 
			cout << endl;
			cout << "Error! Please enter 'y' or 'n' only. Try again!" << endl;
		}
	}

	// Send the SMS message
	try {
		// Twilio Rest
		Rest t (ACCOUNT_SID, ACCOUNT_TOKEN);
		vars.push_back(Var("From", "XXTWILIONUMBERXX"));
		vars.push_back(Var("Body", sProduct));
		vars.push_back(Var("To", ""));

		// Send each message individually
		for (unsigned int j = 0; j < uiTally; j++) {
			vars[2].value = saNumbers[j]; // vars[2] refers to the "To" parameter
			response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/Messages", "POST", vars);
			cout << endl;
			cout << response << endl; 
		}	
	} catch (char const* str) {
		cout << "Exception raised: " << str << endl;
	}

	return 0;
}


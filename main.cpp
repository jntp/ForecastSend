#include <iostream>
#include <string>
#include <fstream>

#include "parameters.h"


int main() {
	using namespace std;

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
	
	return 0;
}


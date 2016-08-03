#include <iostream>
#include <string>
#include <sstream> 

struct parameters {
	int iCity, // Stores the indicated city/region
	    iStorm, // Type of storm
	    iWeather, // Type of weather
	    iPop,  // Probability of Precipitation 
	    iAmtType, // Used to indicate whether precipitation amount will be presented as a number or a range
	    iWindLower, // Lower range of wind speed
	    iWindUpper, // Upper range of wind speed
	    iGust; // Wind Gust (not applicable for every forecast)
	bool bWind;  // True for windy weather events
	std::string sStart, // Start time for precipitation event
		    sEnd, // End time for preciptation event
		    sTemp, // Temperature
		    sTempTwo; // Temperature
	double dAmtLower, // Lower range of precipitation amount
	       dAmtUpper; // Upper range of precipitation amount 
} forecast;

/*
 * Checks input variable to see if it falls within the correct parameters. Returns a bool based on the response to the condition.  
 * Input: int variable to be checked, lower range, upper range, bool variable 
 * Output: bool variable in response to the condition 
 */
bool CheckInput(int iKey, int iLower, int iUpper, bool bBounds);

/*
 * Converts input string to int, and checks for integer. Returns the converted int and a bool based on the given conditions.
 * Input: string containing an integer, pointer to an int in struct parameters, bool for do-while loops, lower range, upper range 
 * Output: pointer to int, bool variable in response to the condition 
 */ 
bool CheckInt(std::string sString, int* ipTarget, bool bResult, int iLower, int iUpper);

/*
 * Based on the indicator, displays the user's response for confirmation. Asks if user wants to confirm response, and checks for proper input.
 * Input: bool variable, integer that indicates what responses to show
 * Output: bool variable in response to the condition 
 */
bool Confirm(bool bResult, int iIndicator);

/* 
 * Converts input string to double, and checks if the input is a double. Returns a double and a bool based on the given conditions.
 * Input: stringing containing a decimal, pointer to a double in struct parameters, bool for do-while loops
 * Output: pointer to double, bool variable in response to the condition 
 */
bool ConvertDecimal(std::string sString, double* dpTarget, bool bResult);

/*
 * Prompts user to input high and low temperature. For some cities/regions, a string concatenation will take place.
 * Input: integer that indicates whether the program will store the concatenated string in forecast.sTemp or forecast.sTempTwo. 
 */
int HighLow(int i);


int main() {
	using namespace std;
	
	// Fill in parameters
	bool bLoop = true; // Indicates whether do-while loop should repeat
	string sInput = ""; // Used for std::getline, getting input from user	

	// City/Region
	forecast.iCity = 0; // Assign 0 to allow for conversion  
 
	do {
		// List options for user to choose
		cout << "Choose your city/region: " << endl;
		cout << "0: San Francisco/Oakland, CA" << endl;
		cout << "1: Davis/Sacramento, CA" << endl;
		cout << "2: Los Angeles Area, CA" << endl;
		cout << "3: Tucson, AZ" << endl;
		getline(cin, sInput); // Prompt user input
		bLoop = CheckInt(sInput, &forecast.iCity, bLoop, 0, 3); // Call CheckInt to verify if input is correct
	} while (!bLoop);

	// Storm Type
	forecast.iStorm = 0; // Assign 0 to allow for conversion 

	do {
		cout << "Choose the storm type: " << endl; 
		cout << "0: Weak Storm" << endl;
		cout << "1: Moderate Storm" << endl;
		cout << "2: Strong Storm" << endl;
		cout << "3: Tropical Remnants" << endl;
		cout << "4: Tropical Storm" << endl; 
		getline(cin, sInput); 
		bLoop = CheckInt(sInput, &forecast.iStorm, bLoop, 0, 4); // Check for correct input 
	} while (!bLoop);

	// Weather Type
	int iWind; // Temporary store as int variable before converting to bool
	bool bLoopTwo; // Checks if nested while loop should repeat
	forecast.iWeather = 0; // Assign 0 to allow for conversion 	

	do {
		bLoopTwo = true; // By default while loop below should not run
		
		cout << "Choose the weather type: " << endl;
		cout << "0: Light Rain" << endl;
		cout << "1: Moderate Rain" << endl;
		cout << "2: Heavy Rain" << endl;
		cout << "3: Thunderstorms" << endl;
		cout << "4: Fog/Drizzle" << endl;
		cout << "5: Snow Showers" << endl;
		cout << "6: Rain mixed with Snow" << endl; 
		getline(cin, sInput); 
		bLoop = CheckInt(sInput, &forecast.iWeather, bLoop, 0, 6); // Check for correct input
	
		if (bLoop) { // If the above input is correct then run the while loop 
			bLoopTwo = false; // Set to false so that while loop below can run 
		}

		// Confirm to user if strong winds exist in this event	
		while (!bLoopTwo) { // Repeat if user fails to give proper answer
			cout << "Are there strong winds with this event?" << endl;
			cout << "0: no" << endl;
			cout << "1: yes" << endl; 	
			getline(cin, sInput);
			bLoopTwo = CheckInt(sInput, &iWind, bLoopTwo, 0, 1); // Check for correct input 
			if (bLoopTwo) { // Check for correct input before assigning value for bWind
				forecast.bWind = iWind; // Assign the iWind input to the bool bWind	
			}
		}
	} while (!bLoop);	

	// Onset of Precipitation
	forecast.iPop = 0; // Assign 0 to allow for conversion 

	do {
		cout << "Choose the start and end time for the precipitation event (Format: # am/pm). " << endl;
		cout << "Start: ";
		getline(cin, forecast.sStart); // Input the start time
		cout << "End: ";
		getline(cin, forecast.sEnd); // Input the end time
		cout << endl;
		
		bLoop = Confirm(bLoop, 0); // Check for confirmation 
	} while (!bLoop); 

	// Probability of Precipitation
	do {
		cout << "Please enter the probability of precipitation (PoP) for this event, rounded to the nearest tenth." << endl;
		cout << "PoP: "; 
		getline(cin, sInput);
		bLoop = CheckInt(sInput, &forecast.iPop, bLoop, 0, 100);

		// Check if input is rounded to the nearest tenth
		if (bLoop == true && forecast.iPop % 10 > 0) {
			// Output error message
			cout << "Error! Please enter an integer rounded to the nearest tenth (e.g. 10, 20, etc.). " << endl;
			cout << endl;
			bLoop = false; // Run the do-loop again 
		} 
	} while (!bLoop); 

	// Precipitation Amount
	forecast.dAmtLower = 0; // Assign 0 to allow for conversion
	forecast.dAmtUpper = 0;

	do { 
		cout << "Please enter the forecasted precipitation amount, up to the hundredth decimal place." << endl;
		cout << "First, please indicate whether the amount is a single number or a range (two numbers)." << endl;
		cout << "0: Single Number" << endl;
		cout << "1: Range" << endl;
	  	getline(cin, sInput);
 		bLoop = CheckInt(sInput, &forecast.iAmtType, bLoop, 0, 1); // Check for correct input 
		
		// Based on user response, prompt user to input a single number or a range
		if (forecast.iAmtType == 0) {
			cout << "Enter an amount, up to the hundredth decimal place." << endl;
			cout << "Precip Amount: ";
			getline(cin, sInput);
			bLoop = ConvertDecimal(sInput, &forecast.dAmtLower, bLoop); // Check input, and convert string to double
			
			// Set forecast.dAmtLower equal to forecast.dAmtUpper if input verifies as correct
			if (bLoop) { // For correct input only
				forecast.dAmtUpper = forecast.dAmtLower; 
			}
		} else if (forecast.iAmtType == 1) {
			cout << "Enter a lower and an upper amount of the range." << endl;
			cout << "Lower Amount: ";
			getline(cin, sInput);
			bLoop = ConvertDecimal(sInput, &forecast.dAmtLower, bLoop); // Check input, and convert string to double
			
			// Only allow user to enter the upper amount if the lower amount is correct
			if (bLoop) {
				cout << "Upper Amount: ";
				getline(cin, sInput);
				bLoop = ConvertDecimal(sInput, &forecast.dAmtUpper, bLoop);
			} 
		}
		
		cout << endl; 		
	} while (!bLoop); // Run if either of the conditions are false  

	// Temperature	
	do { 
		// Check the stored value in iCity to determine the respones user needs to provide
		// The temperature section will vary based on the indicated city/region
		switch (forecast.iCity) {
			case 0: // San Francisco/Oakland, CA
				cout << "For your chosen region, you must enter the high and low temperatures twice." << endl;
				cout << "The first time for San Francisco and the second time for Oakland." << endl;
				cout << endl; 
				cout << "San Francisco" << endl;
				HighLow(1); // Call function to input high/low temperature for SF
				cout << "Oakland" << endl;
				HighLow(2); // Call function to input high/low temperature for Oakland 		
				break;
			case 2: // Los Angeles Area, CA
				cout << "For this region, you must enter a range for both the high and low temperatures." << endl;
				cout << "Please represent the range in this format: ##-## (e.g. 67-75)." << endl;
				cout << "You must enter the high and low temperatures twice for the coast and the inland valleys." << endl;
				cout << endl;
				cout << "Coast" << endl;
				HighLow(1);
				cout << "Inland Valleys" << endl;
				HighLow(2); 
				break; 
			case 1: // Davis/Sacramento, CA
			case 3: // Tucson, AZ
				// Call function to input high/low temperature
				cout << "Please input the high and low temperature." << endl;
				HighLow(0);
				break;
		}

		bLoop = Confirm(bLoop, 1); // Check for confirmation 
	} while (!bLoop); 

	// Wind Speed (not applicable for every forecast)
	// Set wind speed variables equal to zero as default value
	forecast.iWindLower = 0;
	forecast.iWindUpper = 0;
	forecast.iGust = 0;

	if (forecast.bWind) { // Only applies if bWind equals true
		// Lower range of wind speed 
		do { 
			cout << "Enter the lower and upper range of the wind speed." << endl;
			cout << "Lower Range: ";
			getline(cin, sInput);
			bLoop = CheckInt(sInput, &forecast.iWindLower, bLoop, 0, 250); // Convert to int, and check for correct input		
		} while (!bLoop); // Runs again if user fails to provide correct input
	
		// Upper range of wind speed
		do { 
			cout << "Upper Range: ";
			getline(cin, sInput);
			bLoop = CheckInt(sInput, &forecast.iWindUpper, bLoop, 0, 250);
		} while (!bLoop);

		// Ask user if he/she wants to provide wind gust speed
		do { 
			bLoop = Confirm(bLoop, 2); // Check for correct input
		} while (!bLoop);

		// Max speed of wind gusts (not applicable for every forecast)	
		do { 	
			cout << "Enter a maximum speed for wind gusts." << endl;
			cout << "Gust Speed: ";
			getline(cin, sInput);		
			bLoop = CheckInt(sInput, &forecast.iGust, bLoop, 0, 250);
		} while (!bLoop); 			
	} 
	
	return 0;	
}

/*
 * Checks input variable to see if it falls within the correct parameters. Returns a bool based on the response to the condition.  
 * Input: int variable to be checked, lower range, upper range, bool variable 
 * Output: bool variable in response to the condition 
 */
bool CheckInput(int iKey, int iLower, int iUpper, bool bBounds) {
	// Check if iKey is within iLower and iUpper
	if (iKey >= iLower && iKey <= iUpper)  { // Within in the range
		std::cout << std::endl; 
		bBounds = true; 
		return bBounds; // Return the bool variable
	} else { // Out of bounds
		std::cout << "Error! Please input a number between " <<  iLower << " and " << iUpper << "." << std::endl; 
		std::cout << std::endl; 
		bBounds = false;  
		return bBounds; 
	}
}

/*
 * Converts input string to int, and checks for integer. Returns the converted int and a bool based on the given conditions.
 * Input: string containing an integer, pointer to an int in struct parameters, bool for do-while loops, lower range, upper range 
 * Output: pointer to int, bool variable in response to the condition 
 */ 
bool CheckInt(std::string sString, int* ipTarget, bool bResult, int iLower, int iUpper) {
	if (std::stringstream(sString) >> *ipTarget) { // Convert string to int, and check if it is an integer 
		bResult = CheckInput(*ipTarget, iLower, iUpper, bResult); // Check for correct input
	} else { // If not an integer
		std::cout << "Error! Please input a number only." << std::endl; // Display error message
		std::cout << std::endl; 
		bResult = false; // Run the loop again
	}
	
	return bResult; // Return the bool variable 
}

/*
 * Based on the indicator, displays the user's response for confirmation. Asks if user wants to confirm response, and checks for proper input.
 * Input: bool variable, integer that indicates what responses to show
 * Output: bool variable in response to the condition 
 */
bool Confirm(bool bResult, int iIndicator) {
	using namespace std; 

	string sInput = ""; // Initialize string for getline
	char cAffirm; // Response to the confirmation message; carries only 'y' or 'n' 
	
	// Check for confirmation
	while (true) {
		// Display different messages based on the value of iIndicator
		switch (iIndicator) {
			case 0: // Indicates Forecast Start and End Time
				cout << "Please confirm. The start time is '" << forecast.sStart << "' and the end time is '"; 
				cout << forecast.sEnd << ".' " << endl;
				cout << "Is this correct? (y/n)" << endl;
				break;
			case 1: // Indicates Temperature
				cout << "Temperature Field 1 is " << forecast.sTemp << " degrees." << endl;
				cout << "Temperature Field 2 is " << forecast.sTempTwo << " degrees." << endl;
				cout << "Is this correct? (y/n)" << endl; 
				break;
			case 2: // Special case for wind gusts
				cout << "Would you like to include a maximum speed for wind gusts? (y/n)" << endl;
				break;
		}
			
		getline(cin, sInput);
		 
		// Check for correct input 
		if (sInput.length() == 1) { // Check if length of the input string is equal to one
			cAffirm = sInput[0]; // Assign the first character of the string to variable cAffirm				

			if (cAffirm == 'y') { // If user confirms response
				bResult = true; // Don't have the do-whie loop repeat
				break; // Stop the while loop 
			} else if (cAffirm == 'n') { // If user wants to resubmit the entry
				bResult = false; // Have the do-while loop repeat 
				break; // Stop the while loop
			}
		}

			cout << "Error! Please input 'y' or 'n' only. " << endl; // Output error message if user gets to this stage
			cout << endl;
	}
	
	cout << endl; // Double space 
	return bResult; 
}

/* 
 * Converts input string to double, and checks if the input is a double. Returns a double and a bool based on the given conditions.
 * Input: stringing containing a decimal, pointer to a double in struct parameters, bool for do-while loops
 * Output: pointer to double, bool variable in response to the condition 
 */
bool ConvertDecimal(std::string sString, double* dpTarget, bool bResult) {
	std::string sNew; // Carries sString truncated to the hundredth decimal place

	// Convert input string to double, and check for correct input
	if (std::stringstream(sString) >> *dpTarget) { // If input is a double
		// Obtain only the first three digits 
		for (int i = 0; i < 4; i++) { // Index goes up to 3 because decimal point is included
			sNew[i] = sString[i]; // Takes the first 4 indices of sString and copies them to sNew 
		}

		std::stringstream(sNew) >> *dpTarget; // Converts new string to double
		bResult = true; // End the loop
	} else { // If the input is not a double; improper input
		std::cout << "Error! Please enter a decimal." << std::endl; // Output error message
		std::cout << std::endl; 
		bResult = false; // Run the loop again
	}

	return bResult; // Return the bool variable
}

/*
 * Prompts user to input high and low temperature. For some cities/regions, a string concatenation will take place.
 * Input: integer that indicates whether the program will store the concatenated string in forecast.sTemp or forecast.sTempTwo. 
 */
int HighLow(int i) {
	using namespace std;

	string sHigh = "", // Temporarily stores high temperature
	       sLow = ""; // Temporarily stores low temperature

	// Prompt user to input high temperature
	cout << "High: ";
	getline(cin, sHigh); 
	
	// Prompt user to input low temperature
	cout << "Low: "; 
	getline(cin, sLow); 
	cout << endl; 	

	// Check the city/region to see if string concatenation is necessary
	switch (forecast.iCity) {
		case 0: // San Francisco/Oakland, CA
		case 2: // Los Angeles Area, CA
			// Based on the value i, concatenate sHigh and sLow with either sTemp or sTempTwo
			if (i == 1) {
				forecast.sTemp = sHigh + '/' + sLow;
  			} else if (i == 2) 
				forecast.sTempTwo = sHigh + '/' + sLow; 
			break;
		default:
			// Simply assign the sHigh and sLow strings to forecast.sTemp and forecast.sTempTwo
			forecast.sTemp = sHigh;
			forecast.sTempTwo = sLow; 
			break;
	} 
	
	return 0;
}


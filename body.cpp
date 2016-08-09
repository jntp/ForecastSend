#include <iostream>
#include <string>
#include <sstream> 

#include "body.h" 


/*
 * Takes the value found in iCity, iStorm, iWeather, and bWind and creates an opening message for the forecast. 
 * Input: three int variables from earlier operations, bool indicating whether wind exists in this event
 * Output: a char pointer to a concatenated string
 */
const char* Greetings(int iCity, int iStorm, int iWeather, bool bWind) {
	using namespace std;

	// Initialize the strings for concatenation
	string sStrOne, sStrTwo, sStrThree, sResult; 
	
	// Get sStrOne based on storm type
	switch (iStorm) {
		case 0: // Weak storm
			sStrOne = "A weak storm";
			break;
		case 1: // Moderate storm
			sStrOne = "A storm";
			break;
		case 2: // Strong storm
			sStrOne = "A strong storm";
			break;
		case 3: // Monsoonal moisture
			sStrOne = "Monsoonal moisture";
			break;
		case 4: // Tropical remnants
			sStrOne = "Tropical remnant moisture";
			break;
		case 5: // Tropical storm
			sStrOne = "A tropical storm";
			break; 
	}

	// Get sStrTwo based on weather type
	switch(iWeather) {
		case 0: // Light rain
			sStrTwo = "light rain";
			break;
		case 1: // Moderate rain
			sStrTwo = "rain";
			break;
		case 2: // Heavy rain
			sStrTwo = "heavy rain";
			break;
		case 3: // Thunderstorms
			if (bWind == true) {
				sStrTwo = "rain, thunderstorms,";
			} else {
				sStrTwo = "rain and thunderstorms";
			} 
			break;
		case 4: // Fog/drizzle
			sStrTwo = "fog and drizzle";
			break;
		case 5: // Snow showers
			sStrTwo = "snow showers";
			break;
		case 6: // Rain mixed with snow
			sStrTwo = "rain mixed with snow";
			break;
	}

	// Get sStrThree based on city/region 
	switch (iCity) {
		case 0: // San Francisco/Oakland, CA
		case 1: // Davis/Sacramento, CA
			sStrThree = "NorCal";
			break;
		case 2: // Los Angeles Area, CA
			sStrThree = "SoCal";
			break;
		case 3: // Tucson, AZ
			sStrThree = "Southern AZ";
			break;
	} 
	 
	// Concatenate the three strings to produce sResult
	// Based on bWind, include or exclude wind in string
	if (bWind == true) { // Include wind
		sResult = sStrOne + " will bring " + sStrTwo + " and wind to " + sStrThree + " tomorrow.";
	} else if (bWind == false) { // Exclude wind
		sResult = sStrOne + " will bring " + sStrTwo + " to " + sStrThree + " tomorrow."; 
	}
	
	// Convert string to char* to return the value
	const char* ckpReturn = sResult.c_str(); 

	return ckpReturn; 
}

/*
 * Takes the lower precip amount and the upper amount, which are both doubles, and converts them strings. Based on the iAmtType and dAmtLower,
 * creates a message to store as sResult. Returns a char pointer.
 * Input: int specifying amount type, two doubles specifying the lower range and the upper rangeo the precip ammount.
 * Output: a char pointer to a concatenated string 
 */
const char* PrecipAmt(int iAmtType, double dAmtLower, double dAmtUpper) {
	std::string sResult; // String to return as char*

	// Convert doubles to strings using sstream
	std::ostringstream strOne;
	strOne << dAmtLower;
	std::string sAmtLower = strOne.str(); // Assign converted dAmtLower to sAmtLower

	std::ostringstream strTwo; // For dAmtupper
	strTwo << dAmtUpper;
	std::string sAmtUpper = strTwo.str(); // Assign converted dAmtUpper to dAmtLower

	// Check if user specified single number or range for precip amount and print
	if (iAmtType == 0) { // For single numbers
		// For certain values, print a custom message
		// Otherwise, print the default message (else branch of if statement)
		if (dAmtLower <= 0.10) {
			sResult = "Rainfall less than a tenth of an inch.";
		} else if (dAmtLower == 0.25) {
			sResult = "Rainfall near a quarter of an inch.";
		} else if (dAmtLower == 0.50) {
			sResult = "Rainfall near a half an inch.";
		} else if (dAmtLower == 0.75) {
			sResult = "Rainfall near three quarters of an inch.";
		} else if (dAmtLower == 1.00) {
			sResult = "Rainfall near one inch.";
		} else { 
			sResult = "Rainfall near " + sAmtLower + " inches."; 
		}
	} else if (iAmtType == 1) { // For ranges
		// Messages will vary based on whether the lower amount is less than or greater than/equal to one inch.
		if (dAmtLower < 1.00) {
			sResult = "Rainfall between " + sAmtLower + " and " + sAmtUpper + " inches.";
		} else if (dAmtLower >= 1.00) {
			sResult = sAmtLower + " to " + sAmtUpper + " inches of rain expected.";
		}
	}

	// Convert string to char* to return value
	const char* ckpReturn = sResult.c_str();

	return ckpReturn; 
}

const char* Temperature(int iCity, std::string sTemp, std::string sTempTwo) {
	switch (iCity) {
		switch 0: // San Francisco/Oakland, CAi
			
		switch 2: // Los Angeles Area, CA	

	}

}

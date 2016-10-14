#include <iostream>
#include <string>
#include <sstream> 

#include "body.h" 


/* 
 * Takes in a variable of a class numtype (either int or double). Converts numType to string.
 * Input: variable of class numtype (either int or double)
 * Output: Converted string  
 */
template <class numtype>
std::string ToString(numtype toConvert) {
	std::ostringstream buffer;
	buffer << toConvert;
	
	return buffer.str();
}

/*
 * Takes the value found in iCity, iStorm, iWeather, and bWind and creates an opening message for the forecast. 
 * Input: three int variables from earlier operations, bool indicating whether wind exists in this event
 * Output: a concatenated string
 */
std::string Greetings(int iCity, int iStorm, int iWeather, bool bWind) {
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
		case 4: // SF Bay Area, CA (The Peninsula & South Bay) 
			sStrThree = "NorCal";
			break;
		case 2: // Los Angeles Area, CA
		case 5: // San Diego Area, CA 
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
	
	return sResult; 
}

/*
 * Takes the lower precip amount and the upper amount, which are both doubles, and converts them strings. Based on the iAmtType and dAmtLower,
 * creates a message to store as sResult. Returns a string.
 * Input: int specifying amount type, two doubles specifying the lower range and the upper range of the precip amount.
 * Output: a concatenated string 
 */
std::string PrecipAmt(int iAmtType, double dAmtLower, double dAmtUpper) {
	std::string sResult; // String to return 

	// Convert doubles to strings using sstream
	std::string sAmtLower = ToString<double>(dAmtLower); 
	std::string sAmtUpper = ToString<double>(dAmtUpper);

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

	return sResult; 
}

/*
 * Takes the forecast.sTemp and forecast.sTempTwo strings and produces a string based on the chosen city/region. 
 * Input: integer containing the city/region, string of temperature parameter 1, string of temperature parameter 2
 * Output: a concatenated string 
 */
std::string Temperature(int iCity, std::string sTemp, std::string sTempTwo) {
	std::string sResult; // String to return as char* 

	// Based on the city/region, displaying the temperature will differ
	switch (iCity) {
		case 0: // San Francisco/Oakland, CA
			sResult = "The high/low will be " + sTemp + "F in SF and " + sTempTwo + "F in Oakland.";
			break; 	
		case 2: // Los Angeles Area, CA
		case 5: // San Diego Area, CA	
			sResult = "The high/low will be " + sTemp + "F near the coast and " + sTempTwo + "F in the inland valleys.";
			break;
		case 4: // SF Bay Area, CA (The Peninsula & South Bay) 
			sResult = "The high/low will be " + sTemp + "F in the Peninsula and " + sTempTwo + "F in South Bay.";
			break; 
		default:
			sResult = "The high will be " + sTemp + "F and the low " + sTempTwo + "F."; 
			break; 

	}

	return sResult; 
}

/*
 * Takes the lower and upper wind speeds as well as the wind gusts and produces a concatenated string.
 * Input: three ints featuring lower wind speed, upper wind speed, and wind gust
 * Output: a concatenated string 
 */
std::string Wind(int iWindLower, int iWindUpper, int iGust) {
	std::string sResult; // String to return as char*

	// Convert ints to strings
	std::string sWindLower = ToString<int>(iWindLower);  
	std::string sWindUpper = ToString<int>(iWindUpper);
	std::string sGust = ToString<int>(iGust); 

	// Check for wind gusts, then create the message based on the lower wind speed
	if (iGust > 0) {
		if (iWindLower < 15) { // For lower wind speeds less than 15 mph
			sResult = "Breezy--winds " + sWindLower + "-" + sWindUpper + " mph with gusts up to " + sGust + " mph.";
		} else {
			sResult = "Windy--winds " + sWindLower + "-" + sWindUpper + " mph with gusts up to " + sGust + " mph.";
		}
	} else {
		if (iWindLower < 15) {
			sResult = "Breezy--winds " + sWindLower + "-" + sWindUpper + " mph.";
		} else {
			sResult = "Windy--winds " + sWindLower + "-" + sWindUpper + " mph.";
		}
	}

	return sResult; 
}

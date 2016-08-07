#include <iostream>
#include <string>


/*
 * Takes the value found iCity, iStorm, iWeather, and bWind and creates an opening message for the forecast. 
 * Input: three int variables from earlier operations, bool indicating whether wind exists in this event
 * Output: a char pointer to a concatenated string
 */
char* Greetings(int iCity, int iStorm, int iWeather, bool bWind) {
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
			sStrTwo = "rain and thunderstorms";
			break;
		case 4: // Fog/drizzle
			sStrTwo = "fog and drizzle";
			break;
		case 5: // Snow showers
			sStrTwo = "snow showers";
			break;
		case 6: // Rain mixed with snow
			sStrTwo = "wintry mix of rain and snow";
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
	if (bWind) { // Include wind
		sResult = sStrOne + " will bring " + sStrTwo + " to " + sStrThree + " tomorrow.";
	} else if (!bWind) { // Exclude wind
		sResult = sStrOne + " will bring " + sStrTwo + " and wind to " + sStrThree + " tomorrow."; 
	}
	
	// Convert string to char* to return the value
	const char* ckpReturn = sResult.c_str(); 

	return ckpReturn; 

	return 0;
}


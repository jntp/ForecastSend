#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include <string> 

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
		    sTempTwo, // Temperature
		    sClosing; // Closing message for forecast
	double dAmtLower, // Lower range of precipitation amount
	       dAmtUpper; // Upper range of precipitation amount 
};

/*
 * The "main" function of parameters.cpp. Returns a string of a full weather forecast.
 * Output: string featuring the forecast 
 */
std::string Parameters();

/*
 * Based on the user responses, produce and concatenate strings to create a weather forecast.
 * Output: string featuring the weather forecast
 */
std::string Concatenate();

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

/*
 * Converts forecast.iCity to a string used as an identifier in the data.txt database.
 * Output: string code for identification 
 */
std::string CityCode();


#endif /* PARAMETERS_H_ */  

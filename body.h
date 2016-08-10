#ifndef BODY_H_
#define BODY_H_

#include <string> 

/* 
 * Takes in a variable of a class numtype (either int or double). Converts numType to string.
 * Input: variable of class numtype (either int or double)
 * Output: Converted string  
 */
template <class numtype> std::string ToString(numtype toConvert);


/*
 * Takes the value found iCity, iStorm, iWeather, and bWind and creates an opening message for the forecast. 
 * Input: three int variables from earlier operations, bool indicating whether wind exists in this event
 * Output: a const char pointer to a concatenated string
 */
const char* Greetings(int iCity, int iStorm, int iWeather, bool bWind);


/*
 * Takes the lower precip amount and the upper amount, which are both doubles, and converts them strings. Based on the iAmtType and dAmtLower,
 * creates a message to store as sResult. Returns a string.
 * Input: int specifying amount type, two doubles specifying the lower range and the upper range of the precip amount.
 * Output: a concatenated string 
 */
std::string PrecipAmt(int iAmtType, double dAmtLower, double dAmtUpper);


/*
 * Takes the forecast.sTemp and forecast.sTempTwo strings and produces a concatenated string based on the chosen city/region. 
 * Input: integer containing the city/region, string of temperature parameter 1, string of temperature parameter 2
 * Output: a concatenated string 
 */
std::string Temperature(int iCity, std::string sTemp, std::string sTempTwo);


/*
 * Takes the lower and upper wind speeds as well as the wind gusts and produces a concatenated string.
 * Input: three ints featuring lower wind speed, upper wind speed, and wind gust
 * Output: a concatenated string 
 */
std::string Wind(int iWindLower, int iWindUpper, int iGust);


#endif /* BODY_H_ */

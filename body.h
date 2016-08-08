#ifndef BODY_H_
#define BODY_H_

/*
 * Takes the value found iCity, iStorm, iWeather, and bWind and creates an opening message for the forecast. 
 * Input: three int variables from earlier operations, bool indicating whether wind exists in this event
 * Output: a char pointer to a concatenated string
 */
char* Greetings(int iCity, int iStorm, int iWeather, bool bWind);


/*
 * Takes the lower precip amount and the upper amount, which are both doubles, and converts them strings. Based on the iAmtType and dAmtLower,
 * creates a message to store as sResult. Returns a char pointer.
 * Input: int specifying amount type, two doubles specifying the lower range and the upper rangeo the precip ammount.
 * Output: a char pointer to a concatenated string 
 */
char* PrecipAmt(int iAmtType, double dAmtLower, double dAmtUpper);







#endif /* BODY_H_ */

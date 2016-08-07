#ifndef BODY_H_
#define BODY_H_

/*
 * Takes the value found iCity, iStorm, iWeather, and bWind and creates an opening message for the forecast. 
 * Input: three int variables from earlier operations, bool indicating whether wind exists in this event
 * Output: a char pointer to a concatenated string
 */
char* Greetings(int iCity, int iStorm, int iWeather, bool bWind);









#endif /* BODY_H_ */

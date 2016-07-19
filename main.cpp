#include <iostream>
#include <string> 

struct parameters {
	int iCity; // Stores the indicated city/region 

} forecast;

/*
 * Checks input vaiable to see if it falls within the correct parameters. If not, "switches" the bool variable and returns it. 
 * Input: int variable to be checked, lower range, upper range, bool variable 
 * Output: bool variable "switched"
 */
bool checkInput(int iKey, int iLower, int iUpper, bool bSwitch);

int main() {
	using namespace std;
	
	// Fill in parameters
	bool bLoop = false; 
	
	// City/Region 
	do {
		cout << "Choose your city/region: " << endl;
		cout << "0: San Francisco/Oakland, CA" << endl;
		cout << "1: Davis/Sacramento, CA" << endl;
		cout << "2: Los Angeles Area, CA" << endl;
		cout << "3: Tucson, AZ" << endl;
		cin >> forecast.iCity; // Prompt user input
		bLoop = CheckInput(forecast.iCity, 0, 3, bLoop); // Check for correct input
	} while (!bLoop);

	return 0;
}

/*
 * Checks input vaiable to see if it falls within the correct parameters. If not, "switches" the bool variable and returns it. 
 * Input: int variable to be checked, lower range, upper range, bool variable 
 * Output: bool variable "switched"
 */
bool CheckInput(int iKey, int iLower, int iUpper, bool bSwitch) {
	// Check if iKey is within iLower and iUpper
	if (iKey >= iLower && iKey <= iUpper)  { // Within in the range
		return bSwitch; // Simply return the bool variable
	} else { // Out of bounds
		std::cout << "Error! Please input a number between " iLower " and " iUpper "." << std::endl; 
		bSwitch = !bSwitch // "Switch" the bool variable
		return bSwitch; // Return switched bool variable
	}
}



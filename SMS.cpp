#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Utils.h"
#include "Rest.h"
#include "TwiML.h"

using namespace twilio;

int main() {
	// Twilio REST API version
	const string API_VERSION = "2010-04-01";

	// Twilio AccountSid and AuthToken
	const string ACCOUNT_SID = "AC331b62196886f4458f3f134d5043abfc";
	const string ACCOUNT_TOKEN = "48758d26dc705807695acb4de23436cb";

	// Outgoing Caller ID previously validated with Twilio
	const string CALLER_ID = "+17148315677";

	string response;
	
 	vector<Var> vars; 

	try {
		// Twilio REST
		Rest t (ACCOUNT_SID, ACCOUNT_TOKEN);

		// Send SMS
		vars.push_back(Var("To", "+17143996939"));
		vars.push_back(Var("From", "+17148315677"));
		vars.push_back(Var("Body", "Yo whatsup"));
		response = t.request("/" + API_VERSION + "/Accounts/" + ACCOUNT_SID + "/SMS/Messages", "POST", vars);
		cout << response << endl; 


	} catch (char const* str) {
		cout << "Exception raised: " << str << endl; 
	}


	return 0;
}



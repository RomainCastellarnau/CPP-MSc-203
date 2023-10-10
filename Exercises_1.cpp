/* ------------------------ Exercise 1 --------------------------
* Parse the following text to retrieve options characteristic and 
* output a statement for every option as in the example below: 
* • Input text:
* In the index book options, there are
* 25M C/SX5E/20221223/100 
* -25M C/SX5E/20220321/100 
* 40M C/SX5E/20220921/90
* -20M P/SPX/20220921/90
* • Output (sample):
* A long position for 25M of a call option on SX5E of maturity Dec 2022 and strike 100.
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
using namespace std;

/*The function parse_string parses the string message and returns a vector of strings containing the different characteristics of the option of the order.
*
* Takes as input: 
* - message: (string) with the order format Direction(-) NotionalAmount(in M) OptionType(C/P)/UnderlyingName(Ticker)/MaturityDate(YYYYMMDD)/StrikePrice (%)
*
* Returns:
* - output_variables: (vector of strings) with the different characteristics of the option of the order
*/ 
vector<string> parse_string(const string& message) {
    vector<string> output_variables;

    // Find the position (long or short) and notional amount
    size_t space_pos = message.find(' ');
    if (space_pos == string::npos) {
        // Invalid message format
        cout << "Invalid message format. Please try again.\n";
        return output_variables;
    }

    // Determine position (long or short) and notional amount based on '-'
    // Then deduce the notional amount in M. 
    string position;
    string notional_amount;
    if (message[0] == '-') {
        position = "-";
        notional_amount = message.substr(1, space_pos - 1);
    } else {
        position = "";
        notional_amount = message.substr(0, space_pos);
    }

    output_variables.push_back(position);
    output_variables.push_back(notional_amount);

    // Split the remaining message based on '/'
    string remaining_message = message.substr(space_pos + 1);
    istringstream tokenizer(remaining_message);
    string token;
    while (getline(tokenizer, token, '/')) {
        output_variables.push_back(token);
    }

    return output_variables;
}

/* The function output takes as input a vector of strings with the different characteristics of the option and returns a string with the output statement correctly formatted.
*
* Takes as input:
*   - output_variables: (vector of strings) with the different characteristics of the option of the order
*
* Returns:
*   - output_string: (string) with the output statement correctly formatted 
*/
string output(vector<string>& output_variables){
    string output_string;

    //Prepare the formatting of the first part of the output statement
    if (output_variables[0] == "-"){
        output_string = "A short position for " + output_variables[1] + " of a ";
    }
    else{
        output_string = "A long position for " + output_variables[1] + " of a ";
    }
    if (output_variables[2] == "C"){
        output_string = output_string + "call option on ";
    }
    else{
        output_string = output_string + "put option on ";
    }

    // Map to convert month number to month abbreviation
    map<string, string> month_map = {
        {"01", "Jan."}, {"02", "Feb."}, {"03", "Mar."}, {"04", "Apr."},
        {"05", "May."}, {"06", "Jun."}, {"07", "Jul."}, {"08", "Aug."},
        {"09", "Sep."}, {"10", "Oct."}, {"11", "Nov."}, {"12", "Dec."}
    };

    // Convert maturity date to correct format
    string maturity_date = output_variables[4];
    string maturity_date_year = maturity_date.substr(2, 2);
    string maturity_date_month = maturity_date.substr(4, 2);
    string maturity_date_month_abbrev = month_map[maturity_date_month];
    string maturity_date_formatted =  maturity_date_month_abbrev + " " + maturity_date_year;

    //Return final statement
    output_string = output_string + output_variables[3] + " of maturity " + maturity_date_formatted + " and strike " + output_variables[5] + "%.";
    return output_string;
}

int main() {
    cout << "Welcome to the option order parser!\n";
    cout << "This program allows parsing option orders and generating statements for each option.\n";
    cout << "Example: for the option order such as 25M C/SX5E/20221223/100 for a 25M ATM Call on SX5E Mat. Dec 22\n";
    cout << "The code will output the following statement: A long position for 25M of a call option on SX5E of maturity Dec 2022 and strike 100.\n";

    // Example of option orders from the course
    vector<string> example_orders = {
        "25M C/SX5E/20221223/100",
        "-25M C/SX5E/20220321/100",
        "40M C/SX5E/20220921/90",
        "-20M P/SPX/20220921/90"
    };

    //Loop over the example orders and output the statement for each
    for (const string& example : example_orders) {
        vector<string> parsed_example = parse_string(example);
        string output_example = output(parsed_example);
        cout << "Example of order: " << example << "\n";
        cout << output_example << '\n';
    }

    // Ask user to input their own option order
    cout << "Please enter your own option order with the correct format:\n";
    string message;
    getline(cin, message);
    vector<string> output_variables = parse_string(message);
    string output_string = output(output_variables);
    cout << "Your option order is:\n";
    cout << output_string << '\n';

    return 0;
}

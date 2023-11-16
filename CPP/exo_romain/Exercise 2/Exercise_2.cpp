/* Exercise 2
----------------------------------------------------------------------------
Write a program that prompts the user to ask for:

    1. A trade name;
    2. An underlying reference (ticker);
    3. A notional amount;
    4. A currency;
    5. An option type (Call/Put);
    6. A Maturity;
    7. A strike;

The parameters are inputted by the user one by one and are stored in an output .txt file.  The output file should be formatted as follows:
The output file should be formatted as follows:

*****************************************
-------------- TRADE RECAP --------------
*****************************************
Trade name: ---------------- <trade_name>
Underlying reference: ---------- <ticker>
Notional amount: ------ <notional_amount>
Currency: -------------------- <currency>
Option type: -------------- <option_type>
Maturity: -------------------- <maturity>
Strike: ------------------------ <strike>

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <locale>
#include <sstream>

#if __cplusplus >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

using namespace std;

void format_output(vector<string> parameters_input, vector<string> parameters_name, int header_length); // Function to format the text file output
float dash_number(string parameter_name, string input, int header_length);                              // Function to calculate the number of dashes needed to align the text
string format_number(double number);                                                                    // Function to format the numbers

int main()
{
    string input; // User input
    float header_length = 101;
    vector<string> parameters_input = {};
    vector<string> parameters_name = {"Trade name: ", "Underlying reference: ", "Notional amount: ", "Currency: ", "Option type: ", "Maturity (Years): ", "Strike: "};

    cout << "\n";
    cout << "Welcome to the trade recap program!"
         << "\n";
    cout << "\n";
    cout << "This program will ask you for the several parameters of your trade a complete recap will be formatted and saved in a txt file in the same directory."
         << "\n";
    cout << "\n";
    cout << "Here are the parameters required:"
         << "\n";
    cout << "\n";
    cout << "   1. A trade name;"
         << "\n";
    cout << "   2. An underlying reference (ticker);"
         << "\n";
    cout << "   3. A notional amount;"
         << "\n";
    cout << "   4. A currency;"
         << "\n";
    cout << "   5. An option type (Call/Put);"
         << "\n";
    cout << "   6. A Maturity;"
         << "\n";
    cout << "   7. A strike;"
         << "\n";
    cout << "\n";
    // Ask the user for the trade parameters
    for (int i = 0; i < parameters_name.size(); i++)
    {
        if (parameters_name[i] == "Option type: ")
        {
            cout << "Please enter the option type 'C' for Call / 'P' for Put: ";
            cin >> input;
            cin.ignore(); // Add this line to clear the newline character

            while (input != "C" && input != "P")
            {
                cout << "Please enter a valid option type 'C' for Call / 'P' for Put: ";
                cin >> input;
                cin.ignore(); // Add this line to clear the newline character
            }

            if (input == "C")
            {
                parameters_input.push_back("Call");
            }
            else if (input == "P")
            {
                parameters_input.push_back("Put");
            }
        }

        // If the input is not a string convert to a string
        else if (parameters_name[i] == "Notional amount: " || parameters_name[i] == "Strike: ")
        {
            double double_input;
            cout << "Please enter the " << parameters_name[i];
            cin >> double_input;
            cin.ignore(); // Add this line to clear the newline character
            parameters_input.push_back(to_string(double_input));
        }
        else
        {
            cout << "Please enter the " << parameters_name[i];
            getline(cin, input);
            parameters_input.push_back(input);
        }
    }

    // Format the output
    format_output(parameters_input, parameters_name, header_length);
    cout << "\n";
    cout << "Your trade recap has been saved in the file 'trade_recap.txt' in the same directory."
         << "\n";
    return 0;
}

// Function that formates the text file output
void format_output(vector<string> parameters_input, vector<string> parameters_name, int header_length)
{
    double precision;
    // Open the file
    fs::path file_path = fs::path(__FILE__).parent_path() / "trade_recap.txt";
    ofstream output_file(file_path); // Output file stream

    // Check if the file already exists, if not create it
    if (!output_file)
    {
        output_file.open(file_path);
    }

    // Calculate the number of dashes needed to align the text on the header
    string header = string(header_length, '*');
    int dash_header = (header_length - 13) / 2;

    // Clear the output file
    output_file.clear();

    // Create the header
    output_file << header << "\n";
    output_file << string(dash_header, '-') << " TRADE RECAP " << string(dash_header, '-') << "\n";
    output_file << header << "\n";
    output_file << string(header_length, ' ') << "\n";
    // Use a flag to check if "Strike" has been already written
    bool strikeWritten = false;
    bool notionalWritten = false;

    // Write the parameters in the output file
    for (int i = 0; i < parameters_name.size(); i++)
    {
        int dash_number_value = dash_number(parameters_name[i], parameters_input[i], header_length);

        // If "Strike" hasn't been written, print it and set the flag
        if (parameters_name[i] == "Strike: " && !strikeWritten)
        {

            string formatted_strike = format_number(stod(parameters_input[i]));
            int dash_number_value = dash_number(parameters_name[i], formatted_strike, header_length);
            output_file << parameters_name[i] << string(dash_number_value, '-') << " " << formatted_strike << "\n";
            strikeWritten = true;
        }

        // If "Notional Amount" hasn't been written, print it and set the flag
        else if (parameters_name[i] == "Notional amount: " && !notionalWritten)
        {
            string formatted_notional = format_number(stod(parameters_input[i]));
            int dash_number_value = dash_number(parameters_name[i], formatted_notional, header_length);
            output_file << parameters_name[i] << string(dash_number_value, '-') << " " << formatted_notional << "\n";
            notionalWritten = true;
        }

        else if (parameters_name[i] == "Maturity (Years): ")
        {
            int dash_number_value = dash_number(parameters_name[i], parameters_input[i], header_length);
            output_file << parameters_name[i] << string(dash_number_value - 1, '-') << " " << parameters_input[i] << "Y"
                        << "\n";
        }

        // Else print the parameters as usual
        else
        {
            int dash_number_value = dash_number(parameters_name[i], parameters_input[i], header_length);
            output_file << parameters_name[i] << string(dash_number_value, '-') << " " << parameters_input[i] << "\n";
        }
    }
    output_file.close();
}

// Function that computes the number of dashes needed to align the text for the trade parameters;
float dash_number(string parameter_name, string input, int header_length)
{
    float dash_number;
    int parameter_name_length = parameter_name.length();
    int input_length = input.length();
    dash_number = (header_length - parameter_name_length - input_length) - 1;
    return dash_number;
}

// Takes a double and returns a string with the proper format (decimal point and commas for each thousand)
string format_number(double number)
{
    // Create a string stream to build the formatted number
    ostringstream formatted_stream;

    // Add a decimal point
    formatted_stream << fixed << setprecision(1) << number;

    // Add commas for each thousand
    char separator = use_facet<numpunct<char>>(cout.getloc()).thousands_sep();
    string formatted_number = formatted_stream.str();
    size_t pos = formatted_number.find('.');

    // Insert commas for thousands before the decimal point
    for (int i = static_cast<int>(pos) - 3; i > 0; i -= 3)
    {
        formatted_number.insert(i, 1, separator);
    }

    return formatted_number;
}

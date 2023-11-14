/* Exercise 5
------------------------------------------------------------------------------------------------------------------------

Write a program that:

    1. Prompts the user to enter one by one the digits of his/her phone number.
    2. Ends the input by inputting ‘#’.
    3. If a character other than a digit is inputted, prompt the user with a warning.
    4. Sets up a control to avoid infinite loops.
    5. Prints out the phone number to the screen in case of success.

*/

#include <vector>
#include <iostream>
#include <string>

using namespace std;

const int numCountries = 10;

int main()
{

    int digit_limit = 14;
    string phone_number;
    string extension;

    // Create a multidimensional table called calling codes with calling code and the corresponding G10 country
    string countryTable[numCountries][2] = {
        {"+1", "United States"},
        {"+44", "United Kingdom"},
        {"+81", "Japan"},
        {"+49", "Germany"},
        {"+33", "France"},
        {"+39", "Italy"},
        {"+86", "China"},
        {"+91", "India"},
        {"+7", "Russia"},
        {"+55", "Brazil"}};

    cout << "Welcome to the phone number generator!" << endl;
    cout << "This program allow you to input an international phone number (G10) in your terminal and output the final phone number." << endl;
    cout << "Here are the list of countries and their corresponding calling codes covered by the program:" << endl;
    cout << "Country Calling Code\tCountry" << endl;
    for (int i = 0; i < numCountries; ++i)
    {
        cout << countryTable[i][0] << "\t\t\t" << countryTable[i][1] << endl;
    }

    cout << "Please enter the calling code of the country you are in: ";
    cin >> extension;
    // Check if the extension is valid and returns a statement
    for (int i = 0; i < numCountries; ++i)
    {
        if (extension == countryTable[i][0])
        {
            cout << "Your calling code is valid and correspond to the country: " << countryTable[i][1] << endl;
            break;
        }
        else if (i == numCountries - 1)
        {
            cout << "The calling code you entered is not valid." << endl;
            return 0;
        }
    }

    cout << "Please enter your phone number digit by digit. Enter '#' to stop inputting digits." << endl;
    cout << "Your phone number: ";
    // Loop to input the phone number digit by digit
    for (int i = 0; i < digit_limit; ++i)
    {
        char digit;
        cin >> digit;
        if (digit == '#')
        {
            break;
        }
        else if (isdigit(digit))
        {
            phone_number += digit;
            cout << "Phone number: " << extension << " " << phone_number << endl;
        }
        else
        {
            cout << "You entered an invalid character. Please enter a digit or '#' to stop inputting digits." << endl;
            --i;
        }
    }
    cout << "Your phone number is: " << extension << " " << phone_number << endl;
}

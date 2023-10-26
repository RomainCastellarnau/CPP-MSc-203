// --- Exercise 5 ---

// Write a program that:

// 1. Prompts the user to enter one by one the digits of his/her phone number.
// 2. Ends the input by inputting ‘#’.
// 3. If a character other than a digit is input, prompt the user with a warning.
// 4. Sets up a control to avoid infinite loops.
// 5. Prints out the phone number to the screen in case of success.

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

int main() {
    char digit;
    int bypass = 0;
    std::vector <char> phone_number;
    std::cout << "Please input your phone number one digit after the other (end with a '#' sign):" << std::endl;

    do {
        std::cin >> digit;
        phone_number.push_back(digit);

        // to prevent infinite loops
        bypass++;
        
        // to prevent non-digit input by the user
        if (!isdigit(digit) && digit != '#') {
            std::cout << "You must only input digits (from 0 to 9) and '#'" << std::endl;
            return 0;
        }

    } while (digit != '#' && bypass < 15);

    phone_number.pop_back();
    std::cout << "The phone number you did input is the following: ";
    
    for (char number : phone_number) {
        std::cout << number;
    }

    return 0;
}
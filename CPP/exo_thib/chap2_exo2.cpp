// --- Exercise 2 ---

// Write a program that:

// 1. Prompts the user to ask for: a trade name,
// 2. An underlying reference, a notional, an option type, a maturity,
// 3. And a strike. The data has to be input into an output file.

#include <iostream>
#include <string>
#include <fstream>

std::string dash_liner(int length);

int main() {
    std::string trade_name, udl_ref, matu, notional, strike;
    char opt_type;
    std::ofstream outFile("output.txt");

    std::cout << "Enter trade name" << std::endl;
    std::getline(std::cin, trade_name);
    std::cout << "Enter underlying reference" << std::endl;
    std::getline(std::cin, udl_ref);
    std::cout << "Enter the trade notional in MEur" << std::endl;
    std::getline(std::cin, notional);
    std::cout << "Enter 'C' for call / 'P' for put" << std::endl;
    std::cin >> opt_type;
    std::cin.ignore();
    std::cout << "Enter the maturity" << std::endl;
    std::getline(std::cin, matu);
    std::cout << "Enter strike value" << std::endl;
    std::getline(std::cin, strike);

    // Writing data to the output file
    if (outFile.is_open()) {
        outFile << std::string(50, '*') << std::endl;
        outFile << "Trade name:" << dash_liner(39 - trade_name.length()) << trade_name << std::endl;
        outFile << "Underlying reference:" << dash_liner(29 - udl_ref.length()) << udl_ref << std::endl;
        outFile << "Notional:" << dash_liner(41 - notional.length()) << notional << std::endl;
        outFile << "Option type:" << dash_liner(37) << opt_type << std::endl;
        outFile << "Maturity:" << dash_liner(41 - matu.length()) << matu << std::endl;
        outFile << "Strike:" << dash_liner(43 - strike.length()) << strike << std::endl;
        outFile.close();
    } else {
        std::cout << "Unable to open the output file." << std::endl;
    }

    return 0;
}

std::string dash_liner(int length) {
    if (length < 0) {
        length = 0;
    }
    return std::string(length, '-');
}

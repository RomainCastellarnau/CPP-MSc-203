// --- Exercise 3 ---

// Let us consider the function 𝑓(𝑥) = ln(𝑥) - sqrt(𝑥).
// Write a program that:

// 1. Asks the user to enter as many real numbers as he wants.
// 2. Computes and displays the value of 𝑓 on the input abscissa.
// 3. Finds the zero (or zeros) of the function 𝑓.
// 4. Outputs results to a file stream.

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

double func(double number);
double func_deriv(double number);
double newton_raphson(std::vector <double> numbers);

int main() {
    std::vector<double> numbers;
    std::vector<double> results;
    std::ofstream outFile("output.txt");

    double number;
    double solution;

    // structure that fills the vector of numbers based on what was provided by user
    std::cout << "Enter as many real numbers as you would like (it will stop if you input 0):" << std::endl;

    // the vector stops filling when 0 is input (function not defined for 0 bc of log)
    do {
        std::cin >> number;
        if (number != 0) {
            numbers.push_back(number);
        }
    } while (number != 0);

    // computes and displays the value of f on the input abcissa
    for (double number : numbers) {
        std::cout << func(number) << std::endl;
        results.push_back(func(number));
    }

    // finds the zero or zeroes of that function (various methods can be used, we will use Newton Raphson algorithm)
    solution = newton_raphson(numbers);

    // outputs the results in a file stream
    if (outFile.is_open()) {
        outFile << "Here are the results for the written function f(x) = ln(x) + x:" << std::endl;
        outFile << "The provided values were: ";
        
        for (double number : numbers) {
            outFile << number;
            outFile << ", ";
        }
        outFile << 0. << std::endl;
        outFile << "Inputting those values in the function gave the following results:" << std::endl;

        for (size_t i = 0; i < numbers.size(); i++) {
            outFile << "f(";
            outFile << numbers[i];
            outFile << ") = ";
            outFile << results[i] << std::endl;
        }
        outFile << "f(0) = -inf" << std::endl;
        outFile << "We used the Newton-Raphson algorithm to find the x values such that f(x) = 0" << std::endl;
        outFile << "We found that f(";
        outFile << solution;
        outFile << ") = 0";
    }
}

double func(double number) {
    return log(number) + sqrt(number);
}

double func_deriv(double number) {
    return 1/number - 1/(2*sqrt(number));
}

double newton_raphson(std::vector <double> numbers) {
    double init_guess = numbers[0];
    double potential_solution = init_guess;
    double threshold = 1e-4;

    do {
        double delta_x = func(potential_solution) / func_deriv(potential_solution);
        potential_solution -= delta_x;
    } while (std::abs(func(potential_solution)) > threshold);

    return potential_solution;
}
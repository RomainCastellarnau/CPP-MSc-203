/* Exercise 3
------------------------------------------------------------------------------------------------------------------------
Let us consider the real-valued function:
𝑓(𝑥) =ln(𝑥) − sqrt(𝑥) + 4 defined and differential on R+.

Write a program that:

    1. asks the  user to enter  as many  real numbers  as he wants.
    2. computes  and displays the value  of 𝑓on the  input  abscissa.
    3. finds the  zero (or zeros)  of the  function  𝑓().
    4. outputs  results  to a file  stream.
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

// function studied in this exercise: f(x) = ln(x) - sqrt(x) + 4 with x > 0
double f(double x)
{
    return log(x) - sqrt(x) + 4;
}

// derivative of the function studied in this exercise: f'(x) = 1/x - 1/(2*sqrt(x)) with x > 0
double f_prime(double x)
{
    return 1 / x - 1 / (2 * sqrt(x));
}

// Implementation of the Newton-Raphson method to find the zero of given real-valued function
// If too many iterations are performed and no values is close to the threshold epsilon, the function returns an error message
double newton_raphson_method(double x_0)
{
    double x_n = x_0; // initial guess for the root
    double x_n_plus_1 = x_0;
    double epsilon = 1e-6; // Iteration precision
    double delta = 1e-6;   // Function precision
    int max_iterations = 10000;

    do
    {
        x_n = x_n_plus_1;
        x_n_plus_1 = x_n - f(x_n) / f_prime(x_n);
        max_iterations--;
    } while (abs(x_n_plus_1 - x_n) > epsilon && abs(f(x_n_plus_1)) > delta && max_iterations > 0);

    // Return the root if it is found, otherwise return an error message
    if (max_iterations == 0)
    {
        return -1;
    }
    else
    {
        return x_n_plus_1;
    }
}

int main()
{
    vector<double> input = {};               // Real numbers inputed by the user
    vector<double> results = {};             // Results of the function f(x) = ln(x) - sqrt(x) + 4 for each input
    double root;                             // Solution of the equation f(x) = 0
    double x;                                // Discrete input given by the user
    ofstream outFile("function_output.txt"); //.txt file containing the output of our program

    cout << "Welcome to the Functional Analysis Program" << endl;
    cout << "This program will compute the value of the function f(x) = ln(x) - sqrt(x) for any real number x in R+" << endl;
    cout << "It will also find the zero of the function f(x) = ln(x) - sqrt(x) using the Newton-Raphson method" << endl;
    cout << "Results of the program will be outputed to a .txt file called 'function_ouput.txt' located in the same directory" << endl;
    cout << "Please enter some values x for which you want to evaluate the function f()" << endl;
    cout << "Enter -1 to stop inputing values" << endl;

    // Filling the vector input with the values inputed by the user
    do
    {
        cin >> x;
        if (x != -1)
        {
            input.push_back(x);
        }
    } while (x != -1);

    /* Computing the value of the function f(x) = ln(x) - sqrt(x) + 4 for each input
    and storing the results in the vector results.
    */
    for (double x : input)
    {
        results.push_back(f(x));
    }

    // Finding the zero of the function f(x) = ln(x) - sqrt(x) + 4 using the Newton-Raphson method
    root = newton_raphson_method(input[0]);

    // Outputing the results of the program to a .txt file
    if (outFile.is_open())
    {
        outFile << "Results of the program for the function f(x) = ln(x) - sqrt(x) are as follows:" << endl;

        for (double x : input)
        {
            outFile << "f(" << x << ") = " << f(x) << endl;
        }

        outFile << "We used the Newton-Raphson method to find the zero of the function f(x) = ln(x) - sqrt(x) + 4" << endl;
        if (root == -1)
        {
            outFile << "The Newton-Raphson method failed to find a zero of the function f(x) = ln(x) - sqrt(x) + 4" << endl;
        }
        else
        {
            outFile << "We found that f(" << root << ") = 0" << endl;
        }
    }

    return 0;
}
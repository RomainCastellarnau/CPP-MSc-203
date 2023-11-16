/* Exercise 9
----------------------------------------------------------------------------

Write a small program that finds the position of the minimum of an array of decimal / double inputs.
Enhance your program to perform a selection sort.

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

double find_min(vector<double> &v);
double selection_sort(vector<double> &v);

int main()
{
    vector<double> v;
    double input;
    cout << "\n";
    cout << "Welcome to the minimum finder program!"
         << "\n";
    cout << "This program will find the minimum of a list of numbers using a basic method and a selection sort."
         << "\n";
    cout << "\n";
    cout << "Enter a list of numbers (enter a letter to stop): "
         << "\n";

    while (cin >> input)
    {
        v.push_back(input);
    }
    cout << "\n";
    cout << "The list of numbers you entered is: "
         << "\n";
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
    cout << "The minimum is: " << find_min(v) << "\n";
    cout << "The minimum is: " << selection_sort(v) << "\n";

    return 0;
}

double find_min(vector<double> &v)
{
    double min = numeric_limits<double>::max();
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] < min)
        {
            min = v[i];
        }
    }
    return min;
}

double selection_sort(vector<double> &v)
{
    int vecsize = v.size();
    for (int j = 0; j < vecsize - 1; ++j)
    {
        // Initialize the minimum element index
        int min = j;
        for (int i = j + 1; i < vecsize; ++i)
        {
            if (v.at(min) > v.at(i))
            {
                min = i;
            }
        }

        // Swap the found minimum element with the first element of the sub-list starting at j
        if (min != j)
            swap(v.at(j), v.at(min));
    }
    double min_value = v[0];
    return min_value;
}

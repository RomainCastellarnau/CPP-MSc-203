// --- Exercise 9 ---

// Write down a program that:

// 1. Finds the position of the minimum of an array of decimal / double inputs.
// 2. Enhance your program to perform a selection sort.

#include <iostream>

int minimum_finder(double array[], int n, int k);
double selection_sort(double array[], int n);

int main() {
    int n;
    std::cout << "How many doubles do you want to fill your list with :" << std::endl;
    std::cin >> n;

    double input;
    double array[n];
    std::cout << "Type one by one below the doubles you want to fill your list with :" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cin >> input;
        array[i] = input;
    }

    std::cout << std::endl;

    // function that will find the minimum of the list
    int mini_pos = minimum_finder(array, n, 0);
    std::cout << "The minimum of the array is located at the position " << mini_pos;
    std::cout << " (1st element being at position 0)" << std::endl;

    // function that will sort the list using the minimum_finder function above recursively
    selection_sort(array, n);

    return 0;
}

int minimum_finder(double array[], int n, int k) {

    double mini = array[k];
    int pos = k;
    int mini_pos = k;

    for (int j = k; j < n; j++) {
        // iteratively replaces the previous minimum if a smaller value is observed
        if (array[j] < mini) {
            mini = array[j];

            // saves the position of the new minimum
            mini_pos = pos;
        }
        pos++;
    }

    return mini_pos;
}

double selection_sort(double array[], int n) {
    int mini_pos;

    // we will create n-1 sublists, and keep moving to the left the smallest element of the list
    for (int i = 0; i < n; i++) {
        mini_pos = minimum_finder(array, n, i);
        std::swap(array[i], array[mini_pos]);
    }

    std::cout << std::endl;
    std::cout << "The sorted list is now : ";
    for (int i = 0; i < n; i++) {std::cout << array[i] << " ";}

    return 0;
}
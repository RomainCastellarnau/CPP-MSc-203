// --- Exercise 4 ---

// Write a program that:

// 1. Takes as input (from user) two integers.
// 2. Computes their least common multiple (ppcm) and greatest common divisor (pgcd).
// 3. Displays the results.

#include <iostream>
#include <cmath>
#include <algorithm>

int pgcd(int int1, int int2);
int ppcm(int int1, int int2, int pgcd_res);

int main() {
    int int1, int2;

    std::cout << "Please provide two positive integers:" << std::endl;
    std::cin >> int1;
    std::cin >> int2;

    std::cout << "The greatest common divisor of these two integers is:" << std::endl;
    std::cout << pgcd(int1, int2) << std::endl;

    std::cout << "The least common multiple of these two integers is:" << std::endl;
    std::cout << ppcm(int1, int2, pgcd(int1, int2)) << std::endl;
}

int pgcd(int int1, int int2) {

    int max_int = std::max(int1, int2);
    int min_int = std::min(int1, int2);

    // bypass for any zeroes
    if (min_int == 0) {
        return max_int;
    }

    // the pgcd of two integers also divides their difference (iterative process until we find a new min that divides the new max)
    do {
        int r = max_int % min_int;
        max_int = min_int;
        min_int = r;
    } while (min_int != 0);

    return max_int;
}

int ppcm(int int1, int int2, int pgcd_res) {
    // the product of two numbers int1 and int2 is comprised of their unique and shared prime factors
    // by dividing by the pgcd (which contains their share prime factors) -> we get the smallest numbers such that int1 and int2 are factors
    // which is the definition of the least common multiple
    return abs(int1 * int2) / pgcd_res;
}
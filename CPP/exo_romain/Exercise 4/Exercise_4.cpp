/* Exercise 4
------------------------------------------------------------------------------------------------------------------------
Write a program that:

    1. Takes as input (from user) two integers.
    2. Computes their least common multiple (LCM) and greatest common divisor (GCD).
    3. Displays the results.
*/

#include <iostream>
#include <cmath>

using namespace std;

int lcm(int a, int b);
int gcd(int a, int b);

int main()
{
    int a, b;
    cout << "Enter two integers a and b: " << endl;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "The least common multiple of " << a << " and " << b << " is " << lcm(a, b) << endl;
    cout << "The greatest common divisor of " << a << " and " << b << " is " << gcd(a, b) << endl;
    return 0;
}

// Function that computes he greatest common divisor (gcd) of two integers using Euclid's algorithm: gcd(a, b) = gcd(b, a % b)
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

/*
Function that computes the least common multiple (LCM) of two integers.
The least common multiple can be computed very fast from the greatest common divisor (gcd) using the formula:
lcm(a, b) = |b| * (|a| / gcd(a, b))
*/
int lcm(int a, int b)
{
    return abs(b) * (abs(a) / gcd(a, b));
}
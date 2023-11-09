// --- Exercise 7 ---

// Write down a program that:

// 1. Generates n uniform numbers (in 0,1) where n is input by user
// 2. Compute the minimum of the sequence, consider a recursive and a non recursive implementation
// 3. Compare the performance of the recursive and non recursive approaches
// 4. Show empirically that this minimum converges to 0 in probability
// 5. Prove it using probability theory.

#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <random>

std::vector<double> uniforms(int n);
double minimum_recursive(std::vector<double> unif);
double minumum_non_recursive(std::vector<double> unif);

int main() {
    int n;
    double start;
    double end;
    std::vector <double> unif;

    std::cout << "Please input the number of elements you want to generate: " << std::endl;
    std::cin >> n;
    unif = uniforms(n);

    std::cout << "You generated a list of ";
    std::cout << n;
    std:: cout << " random elements between [0,1]" << std::endl;

    start = clock();
    std::cout << "Following the recursive method, the minimum is " << minimum_recursive(unif);
    end = clock();
    std::cout << " and it took " << (end - start) << "ms" << std::endl;

    start = clock();
    std::cout << "Following the non-recursive method now, the minimum is " << minumum_non_recursive(unif);
    end = clock();
    std::cout << " and it took " << (end - start) << "ms" << std::endl;

    return 0;
}

std::vector<double> uniforms(int n) {
    std::vector <double> unif;

    // provides a seed to synthetize randomization within the random number generator
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

    // fetches a gaussian random value within the [0,1] set
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < n; i++) {
        unif.push_back(distribution(generator));
    }

    return unif;
}

double minimum_recursive(std::vector<double> unif) {
    if (unif.size() == 1) {
        // stops when only one element left (logically the minimum)
        return unif[0];
    }

    if (unif.front() < unif.back()) {
        // removes the last element if bigger than the first one
        std::vector<double> smallerUnif(unif.begin(), unif.end() - 1);
        return minimum_recursive(smallerUnif);

    } else {
        // removes the first element if bigger than the last one
        std::vector<double> smallerUnif(unif.begin() + 1, unif.end());
        return minimum_recursive(smallerUnif);
    }
}

double minumum_non_recursive(std::vector<double> unif) {
    double mini = unif[0];

    for (double u : unif) {
        // iteratively replaces the previous minimum if a smaller value is observed
        if (u < mini) mini = u;
    }

    return mini;
}
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

vector<double> uniform_generator(double lower_bound = 0 , double upper_bound = 1 , int n = 0){
    // Initialize a normal distribution generator with mean 0 and standard deviation sigma
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(lower_bound, upper_bound);
    vector<double> uniform;
    for (int i = 0 ; i < n ; i++){
        double sample = dis(gen);
        uniform.push_back(sample);
    }
    return uniform;
}

double find_min_vector_recursive(vector<double> uniform, int n){
    // if size = 0 means whole array has been traversed 
    if (n == 1) 
        return uniform[0];   
    return min(uniform[n-1], find_min_vector_recursive(uniform, n-1)); 
} 

double find_min_vector_recursive_2(vector<double> values , size_t starIndex , size_t endIndex){
    if (starIndex == endIndex){
        return values[starIndex];
    }
    size_t midIndex = (starIndex + endIndex) / 2;
    double leftMin = find_min_vector_recursive_2(values, starIndex, midIndex);
    double rightMin = find_min_vector_recursive_2(values, midIndex + 1, endIndex);
    return min(leftMin, rightMin);
}

double find_min_vector_iterative(vector<double> uniform, int n){
    double min = uniform[0];
    for (int i = 1 ; i < n ; i++){
        if (uniform[i] < min){
            min = uniform[i];
        }
    }
    return min;
}

int main(){

    int n = 10000;
    vector<double> time1; // time vector for the first recursive method
    vector<double> time2; // time vector for the second recursive method
    vector<double> time3; // time vector for the iterative method
    vector<double> time4; // time vector for the built-in method
    vector<double> timecomparison;

    for (int i = 0 ; i < 10 ; i++){
        vector<double> uniform = uniform_generator(0, 100, n);
        clock_t t1;
        t1 = clock();
        double min = find_min_vector_recursive(uniform, n);
        t1 = clock() - t1;
        time1.push_back(((float)t1) / CLOCKS_PER_SEC);

        clock_t t2;
        t2 = clock();
        double min2 = find_min_vector_recursive_2(uniform, 0 , n-1);
        t2 = clock() - t2;
        time2.push_back(((float)t2) / CLOCKS_PER_SEC);

        clock_t t3;
        t3 = clock();
        double min3 = find_min_vector_iterative(uniform, n);
        t3 = clock() - t3;
        time3.push_back(((float)t3) / CLOCKS_PER_SEC);

        clock_t t4;
        t4 = clock();
        double min4 = *min_element(uniform.begin(), uniform.end());
        t4 = clock() - t4;   
        time4.push_back(((float)t4) / CLOCKS_PER_SEC);
    }

    cout << "The average time taken to find the minimum value of the vector using the recursive method is: " << accumulate(time1.begin(), time1.end(), 0.0)*1000.0 / time1.size() << " ms" << endl;
    cout << "The average time taken to find the minimum value of the vector using the second recursive method is: " << accumulate(time2.begin(), time2.end(), 0.0)*1000.0  / time2.size() << " ms" << endl;
    cout << "The average time taken to find the minimum value of the vector using the iterative method is: " << accumulate(time3.begin(), time3.end(), 0.0)*1000.0  / time3.size() << " ms" << endl;
    cout << "The average time taken to find the minimum value of the vector using the built-in method is: " << accumulate(time4.begin(), time4.end(), 0.0)*1000.0  / time4.size() << " ms" << endl;
    
    timecomparison.push_back(accumulate(time1.begin(), time1.end(), 0.0)*1000.0 / time1.size());
    timecomparison.push_back(accumulate(time2.begin(), time2.end(), 0.0)*1000.0 / time2.size());
    timecomparison.push_back(accumulate(time3.begin(), time3.end(), 0.0)*1000.0 / time3.size());
    timecomparison.push_back(accumulate(time4.begin(), time4.end(), 0.0)*1000.0 / time4.size());
    double min = *min_element(timecomparison.begin(), timecomparison.end());
    cout << "The best method is the " << distance(timecomparison.begin(), find(timecomparison.begin(), timecomparison.end(), min)) + 1 << "th method with an average time of " << min << " ms to find the minimum value of the vector" << endl;
    
    return 0;
}




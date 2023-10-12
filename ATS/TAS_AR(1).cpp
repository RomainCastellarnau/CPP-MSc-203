
#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

/* The function white_noise_generator allow to generate a white noise process with a given sigma and length
* and stores the values in a vector.
* 
* Takes as input:  
* - sigma (double): standard deviation of the white noise process
* - length (int): length of the white noise process
* 
* Returns: 
* - white noise (vector <double>): vector containing the value of the white noise process
*/
vector<double> white_noise_generator(double sigma, int length){

    // Initialize a normal distribution generator with mean 0 and standard deviation sigma
    default_random_engine generator;
    normal_distribution<double> distribution(0,sigma);
    vector<double> white_noise;
    // Generate the white noise process of length equal to the length input
    for (int i = 0 ; i < length ; i++){
        double sample = distribution(generator);
        white_noise.push_back(sample);
    }
    return white_noise;
}

/* The function AR1 allow to generate an AR(1) process with a given c, phi_1 and white noise process 
* and stores the values of the process in a vector. 
*
* Takes as input:
* - c (double): constant of the AR(1) process
* - phi_1 (double): phi_1 of the AR(1) process
* - white_noise (vector <double>): vector containing the value of the white noise process
*
* Returns: 
* - AR1_process (vector <double>): vector containing the value of the AR(1) process
*/
vector <double> AR1(double c , double phi_1, vector<double> white_noise){
    vector <double> AR1_process; 
    AR1_process.push_back(c);
    //Generate the AR(1) process using the equation X_t = c + phi_1 * X_t-1 + epsilon_t
    //Where epsilon_t is a white noise process
    for (int i = 0; i < white_noise.size(); i++){
        AR1_process.push_back(c + phi_1 * AR1_process[i] + white_noise[i]);
    }
    return AR1_process;
}

int main(){
    cout << "Welcome to the Autoregressive process simulator \n";
    cout << "This program allow you to simulate an AR(1) process with the following equation: \n";
    cout << "X_t = c + phi_1 * X_t-1 + epsilon_t \n";
    cout << "Where epsilon_t is a white noise process \n";
    double c;
    double phi_1;
    double mu;
    double sigma;
    int length;
    cout << "Please enter the value of c: \n";
    cin >> c;
    cout << "Please enter the value of phi_1: \n";
    cin >> phi_1;
    cout << "Please enter the value of sigma: \n";
    cin >> sigma;
    cout << "Please enter the length of the process: \n";
    cin >> length;
    vector <double> my_white_noise = white_noise_generator(sigma, length);
    vector <double> my_AR1_process = AR1(c, phi_1, my_white_noise);
    cout << "The AR(1) process is: \n";
    for (int i = 0; i < my_AR1_process.size(); i++){
        cout << my_AR1_process[i] << '\n';
    }
}

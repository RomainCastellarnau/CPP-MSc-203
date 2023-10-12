
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

/* The function MA1 allow to generate an MA(1) process with a given c, theta_1 and white noise process 
* and stores the values of the process in a vector. X_t = c + theta_1 * epsilon_t-1 + epsilon_t
*
* Takes as input:
* - c (double): constant of the MA(1) process
* - theta_1 (double): phi_1 of the MA(1) process 
* - white_noise (vector <double>): vector containing the value of the white noise process
*
* Returns: 
* - MA1_process (vector <double>): vector containing the value of the MA(1) process
*/

vector <double> MA1(double c, double theta_1 , vector<double> white_noise){
    vector <double> MA1_process; 
    MA1_process.push_back(c); 
    //Generate the MA(1) process using the equation X_t = c + theta_1 * epsilon_t-1 + epsilon_t
    //Where epsilon_t is a white noise process
    for (int i = 0 ; i < white_noise.size(); i++){
        MA1_process.push_back(c + theta_1 * white_noise[i-1] + white_noise[i]); 
    }
    return MA1_process;
}

int main(){
    cout << "Welcome to the Moving-Average process simulator \n";
    cout << "This program allow you to simulate an MA(1) process with the following equation: \n";
    cout << "X_t = c + theta_1 * epsilon_t-1 + epsilon_t \n";
    cout << "Where epsilon_t is a white noise process \n";
    
    double c;
    double theta_1;
    double sigma; 
    double length;

    cout << "Please enter the value of c: \n";
    cin >> c;
    cout << "Please enter the value of theta_1: \n";
    cin >> theta_1;
    cout << "Please enter the value of sigma: \n";
    cin >> sigma;
    cout << "Please enter the value of length: \n";
    cin >> length;

    vector <double> my_white_noise = white_noise_generator(sigma, length);
    vector <double> my_MA1_process = MA1(c, theta_1, my_white_noise);

    for (int i = 0; i < my_MA1_process.size(); i++){
        cout << my_MA1_process[i] << '\n';
    }

    return 0;
    
}

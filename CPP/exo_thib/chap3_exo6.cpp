// --- Exercise 6 ---

// Write down a program that parses a csv numerical matrix input:

// The input to be parsed looks like what is present in exo6_data.csv
// Your code should parse this data, store it into a vector of vector (matrix-like format) and display it.

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

std::vector<std::vector<int>> matrix_creator(std::ifstream& input); // function that builds the matrix
void matrix_displayer(std::vector<std::vector<int>> vec); // function that displays the built matrix

int main() {

    // we need to fetch the data in the first place
    std::ifstream input("exo6_data.csv");

    // we create the matrix afterwards
    std::vector<std::vector<int>> mat = matrix_creator(input);

    // we display the retrieved matrix
    matrix_displayer(mat);

    return 0;
}

std::vector<std::vector<int>> matrix_creator(std::ifstream& input) {

    std::vector<std::vector<int>> mat;
    std::string line;

    while (std::getline(input, line)) {

        std::vector<int> row;
        std::stringstream ss(line); // convertion of the line to a string
        std::string value;

        while (std::getline(ss, value, ',')) {
            row.push_back(std::stoi(value)); // we append to the vector each char that is an int
        }

        mat.push_back(row); // once the row is fully filled within the vector, we append it to the global matrix
    }
    
    return mat; // once all integers are fetched, we return the matrix
}

void matrix_displayer(std::vector<std::vector<int>> mat) {

    std::cout << "Below is the matrix displayed from the .csv" << std::endl;

    // we loop through all columns, then lines to fetch each char at its specific position
    for(int j = 0; j < mat.size(); j++) {
        for(int i = 0; i < mat[j].size(); i++) {
            std::cout << mat[j][i];
            std::cout << " ";
        }

        // for readability we go back to the line
        std::cout << std::endl;
    }
}
// --- Exercise 8 ---

// Write down a program that:

// 1. Asks the user to enter a text file path
// 2. Asks the user to enter a string to look for
// 3. Returns the number of occurrences as well as the position (in line and column format) of all occurences

#include <iostream>
#include <string>
#include <fstream>

int occurences(std::ifstream& txt_file, std::string str);

int main() {

    // lets the user enter the text file path
    std::string file_path; // chap5_exo8_file.txt
    std::cout << "Enter the file path of your text file :" << std::endl;
    std::cin >> file_path;

    // fetch the file
    std::ifstream txt_file(file_path);

    // lets the user enter the string to look for in the file
    std::string str;
    std::cout << "Enter the string you want to look for in that file :" << std::endl;
    std::cin >> str;

    // we call the function that will be responsible for displaying the wanted info
    occurences(txt_file, str);

    return 0;
}

int occurences(std::ifstream& txt_file, std::string str) {

    int nb_occurences = 0; // will sum up to the nb of occurences of the string in the file
    int y_position = 1; // will be the line position of each point

    std::string line;
    int length_line;
    int length_str = str.size();

    std::cout << std::endl;

    // we have to loop through all lines of that txt file
    while (std::getline(txt_file, line)) {
        length_line = line.length(); // we first calculate the length of the line looked at
        int x_position = 1; // will represent the column coordinate

        // we look through each chain of characters that could potentially contain the entire looked for string
        for (int i = 0; i <= length_line - length_str; i++) {
            std::string test_str = line.substr(i, length_str); // we isolate each string to then evaluate it

            // if that sub string is equal to the looked for string, we display coordinates and increment the total
            if (test_str == str) {
                std::cout << "present at line " << y_position << ", column " << x_position;
                std::cout << " to " << x_position + length_str - 1 << std::endl;
                nb_occurences++;
            }
            x_position++;
        }
        y_position++;
    }

    std::cout << std::endl;
    std::cout << "The number of occurences of the string (" << str;
    std::cout << ") in the chosen file is " << nb_occurences;

    return 0;
}
/* Exercise 6
----------------------------------------------------------------------------
Write down a program that parses a CSV numerical matrix input:

    1. The input to be parsed looks like what is present in exo6_data.csv;
    2. Your code should parse this data, store it into a vector of vector (matrix-like format) and display it;
    
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#if __cplusplus >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

using namespace std;

vector<vector<int>> matrix_parser(ifstream &input);
void display_terminal(vector<vector<int>> data_matrix);

int main()
{
    // Open the file
    fs::path file_path = fs::path(__FILE__).parent_path() / "exo6_data.csv";
    ifstream inFile(file_path); // Input file stream
    // Check if the file is open
    if (!inFile.is_open())
    {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }

    // Parse and store the file data
    vector<vector<int>> mat = matrix_parser(inFile);

    // Display the parsed data
    display_terminal(mat);

    // Close the file
    inFile.close();
    return 0;
}

vector<vector<int>> matrix_parser(ifstream &input)
{
    string line;
    vector<vector<int>> result;

    // Extract each line from the .csv file
    while (getline(input, line))
    {
        vector<int> row;           // Vector containing the numbers of the line
        stringstream stream(line); // Line to string conversion
        string data;               // String containing the numbers of the line

        // Extract each number from the line
        while (getline(stream, data, ','))
        {
            row.push_back(stoi(data)); // String to int conversion
        }
        result.push_back(row);
    }
    return result;
}

void display_terminal(vector<vector<int>> data_matrix)
{
    cout << "Below is the data contained in the exo6_data.csv file" << endl;
    for (int row = 0; row < data_matrix.size(); row++)
    {
        for (int col = 0; col < data_matrix[row].size(); col++)
        {
            cout << data_matrix[row][col];
            cout << " ";
        }
        cout << endl;
    }
}

/* Exercise 8
---------------------------------------------------------------------------------------------------------
Write a program that:

    1. Asks the user to enter a text file path;
    2. Asks the user to enter a string to look for;
    3. Returns the number of occurrences as well as the position (in line and column format) of all occurrences;

---------------------------------------------------------------------------------------------------------
Example:

If the user can enter the following text file path and string to look for:
Path name: /Users/romaincastellarnau/Desktop/MSc. 203/M2/C++/Exercises/Exercise 8/my_example_text_file.txt
String to look for: Hello

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

/*
The function count_word counts the number of occurrences of the string word in the string line.

Takes as input:
   - word: (string) the string to look for
   - line: (string) the string to look in

Returns:
   - count (int) the number of occurrences of the word in the line
*/
int count_word(string &word, string &line)
{
    int count = 0;
    size_t pos = line.find(word);
    while (pos != string::npos)
    {
        count++;
        pos = line.find(word, pos + 1);
    }
    return count;
}

/*
The function count_find_pos_word parses the text file and returns the position of the occurrences of the string word on each line.

Takes as input:
   - word: (string) the string to look for

Returns:
   - pair<map<int, vector<int>>, int> (map) the position of the occurrences of the word in the text line and the total number of occurrences of the word in the text file
*/
pair<map<int, vector<int>>, int> count_find_pos_word(string &word, ifstream &inputStream)
{
    map<int, vector<int>> position;
    int total_occurrences = 0;
    string line;
    int line_number = 0;
    while (getline(inputStream, line))
    {
        line_number++;
        int count = count_word(word, line);
        total_occurrences += count;
        if (count > 0)
        {
            vector<int> pos;
            size_t pos_word = line.find(word);
            while (pos_word != string::npos)
            {
                pos.push_back(pos_word + 1);
                pos_word = line.find(word, pos_word + 1);
            }
            position[line_number] = pos;
        }
    }
    return make_pair(position, total_occurrences);
}

int main()
{
    cout << "Please enter a text file path: "
         << "\n";
    ifstream inputStream;
    string path;
    getline(cin, path);
    inputStream.open(path);

    // Check if the file exists for the path given
    while (!inputStream.is_open())
    {
        cout << "No file found. Please enter a valid text file path: "
             << "\n";
        cin >> path;
        inputStream.open(path);
    }
    cout << "Please enter a string to look for in your text file: "
         << "\n";

    string stringToLookFor;
    getline(cin, stringToLookFor);

    pair<map<int, vector<int>>, int> position = count_find_pos_word(stringToLookFor, inputStream);
    cout << "The expression" << stringToLookFor << " appears a total of " << position.second << " times in the text given file."
         << "\n";
    cout << "The expression " << stringToLookFor << " appears at the following positions: "
         << "\n";
    for (auto it = position.first.begin(); it != position.first.end(); it++)
    {
        cout << "Line " << it->first << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << *it2 << " ";
        }
        cout << "\n";
    }

    inputStream.close();
    return 0;
}

/* Exercise 10
------------------------------------------------------------------------------------------------------------

Write a program that parses the responses of the students to a test.
Checks it against the correct response (provided in the first row of the file).
If the response is correct, the student receives +1, if it is not correct then the score is decremented (-1).
If no response, the student is given the mark 0 for the specific question.

Your program should display results for each student (by increasing name) in the following format:
« Student a received b mark. His grade is c. He is ranked d. »
The grade scale is 90%-100%: A, 80%-89,99%: B, 70%-79,99%: C, 60%-69,99%: D, E otherwise.
Test your program against the given input sample.
------------------------------------------------------------------------------------------------------------

Example of input file:

Response TTFTFFTFFTFTTTFTTFFF
Claude TT  FTTFFTFTFTFTTFFF
Jean TFFTFFTFFTTTTTFTTFF
Marie  TFTFFT  FTFTTTFTTFFT
Alain TTFTFFTFFTFTTTFTTFFF
Eric   TFTFTFF   TFFFTFFTT
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <locale>
#include <sstream>
#include <algorithm>

#if __cplusplus >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

using namespace std;

vector<string> test_score(string line);                                                  // Function to parse the txt file containing the name of the student and their answers to the test.
int scoring(vector<string> correct_answer, vector<string> student_answer);               // Function to compute the score of the student.
vector<pair<string, double>> sort_alphabetical(vector<pair<string, double>> test_recap); // Function to sort the vector test recap in alphabetically ascending order the student names.
char grade(int student_score, vector<string> correct_answer);                            // Function to compute the grade of the student based on his / her score.
vector<double> selection_sort(vector<pair<string, double>> test_recap);                  // Function to sort the vector test recap in descending order of the student scores.
int student_rank(vector<double> scores_sorted, double student_score);                    // Function to compute the rank of the student based on his / her score.

int main()
{
    // Open the file
    fs::path file_path = fs::path(__FILE__).parent_path() / "score_ex10.txt";
    ifstream inFile(file_path); // Input file stream
    // Check if the file is open
    if (!inFile.is_open())
    {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }
    // Parse and store the file data
    vector<string> correct_answer = {};
    vector<vector<string>> students_answers = {};
    string line;
    // Parse the txt file containing the name of the student and their answers to the test.
    while (getline(inFile, line))
    {
        if (correct_answer.empty())
        {
            correct_answer = test_score(line);
        }
        else
        {
            students_answers.push_back(test_score(line));
        }
    }
    // Close the input txt file
    inFile.close();

    // Creation of the vector containing for each student the pair (student_name, test_score).
    vector<pair<string, double>> test_recap = {};
    for (int i = 0; i < students_answers.size(); i++)
    {
        test_recap.push_back(make_pair(students_answers[i][0], scoring(correct_answer, students_answers[i])));
    }
    // Sort the vector test recap in descending order of the student scores.
    vector<double> sorted_scores = selection_sort(test_recap);

    // Sort the vector test recap in ascending order of alphabetical name.
    test_recap = sort_alphabetical(test_recap);
    int header_length = 60;
    string header = string(header_length, '*');
    int dash_header = (header_length - 12) / 2;
    string header_message = string(dash_header, '-') + " TEST RECAP " + string(dash_header, '-');

    // Display the header
    cout << "\n";
    cout << header << "\n";
    cout << header_message << "\n";
    cout << header << "\n";
    cout << string(header_length, ' ') << "\n";

    // Display the results for each student.
    for (int i = 0; i < test_recap.size(); i++)
    {
        cout << test_recap[i].first << " received " << test_recap[i].second << "/" << correct_answer.size() - 1 << " mark. His grade is " << grade(test_recap[i].second, correct_answer) << ". He is ranked " << student_rank(sorted_scores, test_recap[i].second) << "."
             << "\n";
    }

    return 0;
}

vector<string> test_score(string line)
{
    vector<string> extracted_score;
    // Extract the first word of the line (up to the first space)
    string student_name = line.substr(0, line.find(" "));
    extracted_score.push_back(student_name); // Add the student name to the vector
    // Starting index after the first space
    int index = line.find(" ") + 1;
    for (int i = index; i < line.length(); i++)
    {
        // Add the answer to the vector
        extracted_score.push_back(line.substr(i, 1));
    }
    return extracted_score;
}

int scoring(vector<string> correct_answer, vector<string> student_answer)
{
    int student_score = 0;
    // Starting at index 1, index 0 contains the student's name.
    for (int i = 1; i < correct_answer.size(); i++)
    {
        if (correct_answer[i] == student_answer[i])
        {
            student_score++;
        }
        else if (student_answer[i] == " ")
        {
            student_score += 0;
        }
        else
        {
            student_score--;
        }
    }
    return student_score;
}

vector<pair<string, double>> sort_alphabetical(vector<pair<string, double>> test_recap)
{
    sort(test_recap.begin(), test_recap.end(), [](const pair<string, double> &a, const pair<string, double> &b)
         { return a.first < b.first; });
    return test_recap;
}

char grade(int student_score, vector<string> correct_answer)
{
    double score = student_score / static_cast<double>(correct_answer.size() - 1);
    char grade = ' ';
    if (score >= 0.9)
    {
        grade = 'A';
    }
    else if (score >= 0.8)
    {
        grade = 'B';
    }
    else if (score >= 0.7)
    {
        grade = 'C';
    }
    else if (score >= 0.6)
    {
        grade = 'D';
    }
    else
    {
        grade = 'E';
    }
    return grade;
}

vector<double> selection_sort(vector<pair<string, double>> test_recap)
{
    int vecsize = test_recap.size();
    for (int j = 0; j < vecsize - 1; ++j)
    {
        // Initialize the minimum element index
        int max = j;
        for (int i = j + 1; i < vecsize; ++i)
        {
            if (test_recap.at(max).second < test_recap.at(i).second)
            {
                max = i;
            }
        }
        // Swap the found minimum element with the first element of the sub-list starting at j
        if (max != j)
            swap(test_recap.at(max), test_recap.at(j));
    }
    vector<double> sorted_scores = {};
    for (int i = 0; i < test_recap.size(); i++)
    {
        sorted_scores.push_back(test_recap[i].second);
    }

    return sorted_scores;
}

int student_rank(vector<double> scores_sorted, double student_score)
{
    int student_rank = -1;
    for (int i = 0; i < scores_sorted.size(); i++)
    {
        if (scores_sorted[i] == student_score)
        {
            student_rank = i + 1;
            return student_rank;
        }
    }
    return student_rank;
}

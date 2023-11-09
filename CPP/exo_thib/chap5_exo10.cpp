// --- Exercise 10 ---

// Write down a program that:

// 1. Parses the responses of the students to a test
// 2. Checks it against the correct response (provided in the first row of the file)
// 3. If the response is correct, the student receives +1, if it is not correct then the score is decremented
// 4. If no response the student is given 0 mark for the specific question
// 5.1 Your program should display results for each student (by increasing name) in the following format:
// 5.2 « Student a received b mark. His grade is c . He is ranked d »
// 5.3 The grade scale is 90%-100%: A, 80%-89,99%: B, 70%-79,99%: C, 60%-69,99%: D, E otherwise.
// 5.4 Test your program against the given input sample

#include <iostream>
#include <vector>
#include <fstream>
#include <map>

double mark_calculator(std::string correction, std::string student);
char mark_convertor(double mark);
int mark_ranker(std::map <std::string, double> dicoMarks, std::string name);

int main() {
    std::string correction; // line of the corrector
    std::string student; // line provided by the student
    std::string name; // name of the student
    std::string line; // line of the text, will contain name+student
    
    std::map<std::string, double> dicoMarks; // dico combining name+mark for all students
    double mark;

    // we fetch the text file where the results are located
    std::ifstream results("chap5_exo10_file.txt");

    // we isolate here the first line (ie the correction)
    std::getline(results, line);

    // we here find a way to strip the left part, only to keep the grid of answers later used for correction
    correction = line.substr(line.find(" ") + 1, line.size() - line.find(" "));

    // now we can loop on all the other lines of the txt file (ie the results from the students)
    while (std::getline(results, line)) {

        // like above we strip the left part (student's name) to only keep the grid of answers
        student = line.substr(line.find(" ") + 1, line.size() - line.find(" "));
        mark = mark_calculator(correction, student);

        name = line.substr(0, line.find(" "));
        dicoMarks[name] = mark;
    }

    // we note that using a map (and not an unassigned map) we directly get our keys sorted alphabetically
    for (const auto&pair : dicoMarks) {
        std::cout << "Student " << pair.first << " received ";
        std::cout << mark_convertor(pair.second) << " mark.";
        std::cout << " His grade is " << pair.second;
        std::cout << ". He is ranked " << mark_ranker(dicoMarks, pair.first) << "." << std::endl;
    }

    return 0;
}

// function that counts the correct answers and applies the notation system detailed in the exercise
double mark_calculator(std::string correction, std::string student) {
    double pts = 0;

    for (int i = 0; i < student.size(); i++) {
        if (student.substr(i, 1) == correction.substr(i, 1)) {
            pts++; // incremented if the answer is correct
        } else if (student.substr(i, 1) == " ") {
            continue; // 0 if no answer
        } else {
            pts--; // decremented if the answer is incorrect
        }
    }
    
    // we then directly return the grade following the formula given in the exercise
    return pts/correction.size();
}

// small function to convert the mark into a readable letter (compact version)
char mark_convertor(double mark) {
    if (mark >= 0.9) {return 'A';} else if (mark >= 0.8) { return 'B';} else if (mark >= 0.7) {
        return 'C';} else if (mark >= 0.6) {return 'D';} else {return 'E';}
}

// function that will determine the rank of a student given the whole class marks
int mark_ranker(std::map <std::string, double> dicoMarks, std::string name) {
    // we initialize the rank at the first place, if the loop is never entered, it means no one was graded higher
    int rank = 1;

    // we loop through all marks, for each mark that is above the student, we increment the rank
    for (const auto &pair : dicoMarks) {if (pair.second > dicoMarks[name]) {rank++;}}

    return rank;
}
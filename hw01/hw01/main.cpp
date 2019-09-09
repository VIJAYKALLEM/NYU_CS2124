// Simran Soin
// CS UY 2124
// 11 September 2019
// Homework 1 -- Caesar Cypher

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void decrypt_line(string& line, int step) {
    // line takes the line and step as input
    // iterates through each character and decrypts it
    // returns the decrypted line
    for (size_t i=0; i< line.size(); ++i) {
        if (line[i] > 96 && line[i] < 123) {
            line[i] = line[i] - step;
            if (line[i] < 97){
                line[i] = line[i] + 26;
            }
        }
    }
}

string open_file_and_decrypt_file(ifstream& file) {
    string decrypted_text;
    string line;
    int step;
    // reads the first thing in the file and sets it as the int "step"
    file >> step;
    while (getline(file, line)) {
        
        // for each line in the file, calls function decrypt_line on that string
        decrypt_line(line, step);
        // adds line on TOP of the other decrypted text, to reverse the order of the lines.
        decrypted_text = line + "\n" + decrypted_text;
    }
    file.close();
    return(decrypted_text);
}

int main() {
    ifstream file("encrypted.txt");
    if (!file) {
        cout << "Could not open the file";
    }
    else {
        cout << open_file_and_decrypt_file(file) << endl;
    }
    return 0;
}

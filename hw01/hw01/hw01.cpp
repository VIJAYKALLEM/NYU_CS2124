/*
Simran Soin
CS UY 2124
11 September 2019
Homework 1 -- Caesar Cypher
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
const int alphabet_length = 26;

void decrypt_line(string& line, int step) {
    // function takes the line and step as input
    // iterates through each character and decrypts it
    // returns the decrypted line
    for (size_t i=0; i< line.size(); ++i) {
        if (line[i] >= 'a' && line[i] <= 'z') {
            // if char is out of lowercase alphabet ASCII range, it adds 26 to wrap around
            line[i] = line[i] - step;
            if (line[i] < 'a'){
                line[i] += alphabet_length;
            }
        }
    }
}

vector<string> open_file_and_decrypt_file(ifstream& file) {
    vector<string> decrypted_text;
    string line;
    int step;
    // reads the first thing in the file and sets it as the int "step"
    file >> step;
    while (getline(file, line)) {
        // for each line in the file, calls function decrypt_line on that string
        decrypt_line(line, step);
        decrypted_text.push_back(line);
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
        vector<string> decrypted_file = open_file_and_decrypt_file(file);
        for (size_t vector_size=decrypted_file.size() - 1; vector_size>0; --vector_size) {
            cout << decrypted_file[vector_size] << endl;
        }
    }
    return 0;
}

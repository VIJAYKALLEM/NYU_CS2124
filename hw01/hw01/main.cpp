// Simran Soin
// CS UY 2124
// 11 September 2019
// Homework 1 -- Caesar Cypher

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

char get_char_from_rotated_index(int index) {
    // input is a number corresponding to letter of alphabet
    // output is the corresponding letter
    // e.g. get_char(1) returns a
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    // if index is less than 1, it wraps around to 26
    if (index < 0) {
        index = index + 26;
    }
    char retval = alphabet[index];
    return(retval);
}


char decrypt_char(char original_char, int step) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i=0; i<26; ++i) {
        // loops through each letter in alphabet and checks if the given character is that letter
        if (alphabet[i] == original_char) {
            return(get_char_from_rotated_index(i-step));
        }
    }
    // if arrives here, then character was not in lowercase alphabet
    return(original_char);
}

void decrypt_line(string& line, int step) {
    // line takes the line and step as input
    // iterates through each character and decrypts it
    // returns the decrypted line
    for (size_t i=0; i< line.size(); ++i) {
        line[i] = decrypt_char(line[i], step);
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

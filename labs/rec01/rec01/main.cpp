#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void print_lines(ifstream& file) {
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}




int count_words(ifstream& file) {
    string word;
    file.clear();
    file.seekg(0);
    int word_count = 0;
    while (file >> word) {
        ++word_count;
    }
    file.close();
    return(word_count);
}




int main() {
    ifstream file("jabberwocky.txt");
    if (!file) {
        cout << "Could not open the file" << endl;
    }
    else {
        print_lines(file);
        cout << "\nWord count: " << count_words(file) << endl;
    }
}

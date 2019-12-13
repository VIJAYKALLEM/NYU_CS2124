/*
 Simran Soin
 CS2124
 Rec13
 6 December 2019
 */

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;
// Task 9 function (print list using iterator)
void printListUsingIter(const list<int>& orig_list){
    for (list<int>::const_iterator iter = orig_list.begin(); iter != orig_list.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
}

// Task 11 function (print every other item in list using auto)
void printAlternateItems(const list<int>& orig_list){
    bool print_item = true;
    for (auto iter = orig_list.begin(); iter != orig_list.end(); ++iter){
        if (print_item){
            cout << *iter << " ";
            print_item = false;
        }
        else print_item = true;
    }
    cout << endl;
}

// Task 12 function (find item in list, return iterator)
list<int>::const_iterator findItemInList(const list<int>& orig_list, int target){
    for (list<int>::const_iterator iter = orig_list.begin(); iter != orig_list.end(); ++iter){
        if (*iter == target) return iter;
    }
    return orig_list.end();
}

// Task 13 function (task 12 but with auto)
auto findItemInListWithAuto(const list<int>& orig_list, int target){
    for (auto iter = orig_list.begin(); iter != orig_list.end(); ++iter){
        if (*iter == target) return iter;
    }
    return orig_list.end();
}

// Task 15 (supplementary if even function)
bool isEven(int x){ return x%2==0;}

// Task 16 (if even functor)
class intIsEven{
public:
    bool operator() (int x){
        return x%2 == 0;
    }
};

// Task 19 (implement my own find algorithm)
list<int>::const_iterator ourFind(const list<int>::const_iterator& iterbegin, const list<int>::const_iterator& iterend, int target){
    cout << "Currently looking through list (in my own find function)" << endl;
    for (list<int>::const_iterator iter = iterbegin; iter != iterend; ++iter){
        if (*iter == target) return iter;
    }
    return iterend;
}

// Task 20 (implement my own templated find algorithm)
template<typename T, typename targetType>
T ourFind(const T& orig_list_begin, const T& orig_list_end, targetType target){
    cout << "In the function template" << endl;
    for (auto iter = orig_list_begin; iter != orig_list_end; ++iter){
        if (*iter == target) return iter;
    }
    return orig_list_end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vect({3, 2,1, 4, 5, 6, 8, 9});
    for (int i : vect){
        cout << i << " ";
    }
    cout << endl;
    
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> linked_list(vect.begin(), vect.end());
    for (int i : linked_list){
        cout << i << " ";
    }
    cout << endl;
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vect.begin(), vect.end());
    cout << "Vector: ";
    for (int i : vect){
        cout << i << " ";
    }
    cout << endl;
    cout << "Linked List: ";
    //sort(list);
    for (int i : linked_list){
        cout << i << " ";
    }
    cout << endl;

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for(int i = 0; i<vect.size(); i+=2){
        cout << vect[i] << " ";
    }
    cout << endl;
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    cout << "~code commented out because does not compile~" << endl;
    /*
    for(int i = 0; i<linked_list.size(); i+=2){
        cout << linked_list[i] << " ";
    }
    cout << endl;
     */
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator i = vect.begin(); i != vect.end(); i+=2){
        cout << *i << " ";
    }
    cout << endl;
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    bool print_this_one = true;
    for (list<int>::iterator i = linked_list.begin(); i != linked_list.end(); ++i){
        if (print_this_one){
            cout << *i << " ";
            print_this_one = false;
        }
        else print_this_one = true;
    }
    cout << endl;
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    linked_list.sort();
    for (int i : linked_list){
        cout << i << " ";
    }
    cout << endl;
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printListUsingIter(linked_list);
    cout <<endl;
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    for (int i : linked_list){
        cout << i << " ";
    }
    cout << endl;
    cout <<endl;
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printAlternateItems(linked_list);
    cout <<endl;
    
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int>::const_iterator iter = findItemInList(linked_list, 3);
    cout << "Found it:  " << *iter << endl;
    cout << endl;
    
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    auto iter_auto = findItemInListWithAuto(linked_list, 5);
    cout << "Found it:  " << *iter_auto << endl;
    cout << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    auto iter_pos = find(linked_list.begin(), linked_list.end(), 6);
    cout << "Found it:  " << *iter_pos << endl;
    cout << endl;

    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    auto find_if_even_iter = find_if(linked_list.begin(), linked_list.end(), isEven);
    cout << "Found it:  " << *find_if_even_iter << endl;
    cout << endl;

    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    find_if_even_iter = find_if(linked_list.begin(), linked_list.end(), intIsEven());
    cout << "Found it:  " << *find_if_even_iter << endl;
    cout << endl;
    
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    
    find_if_even_iter = find_if(linked_list.begin(), linked_list.end(), [](int x){return x%2 == 0;});
    cout << "Found it:  " << *find_if_even_iter << endl;
    cout << endl;

    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[8];
    cout << "Array: ";
    copy(linked_list.begin(), linked_list.end(), arr);
    for (int i : arr){
        cout << i << " ";
    }
    cout << endl;
    int* find_6 = find(arr, arr+8, 6);
    cout << "Found it:  " << *find_6 << endl;
    
    int* find_first_even = find_if(arr, arr+8, isEven);
    cout << "Found it:  " << *find_first_even << endl;
    cout << endl;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *ourFind(linked_list.begin(), linked_list.end(), 6) << endl;
    cout << endl;
    
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *ourFind(linked_list.begin(), linked_list.end(), 6) << endl;
    cout << endl;
    cout << *ourFind(vect.begin(), vect.end(), 6) << endl;
    cout << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream ifs;
    ifs.open("pooh-nopunc.txt");
    string word;
    vector<string> all_words;
    while (ifs >> word){
        // check if word is in vector already
        bool already_added = false;
        for (const string& vect_word : all_words){
            if (vect_word == word){
                already_added = true;
                break;
            }
        }
        if (!already_added) all_words.push_back(word);
    }
    ifs.close();
    cout << "Vector Size: " << all_words.size() << endl;
    /*
    for (const string& word : all_words){
        cout << word << ", ";
    }
    cout << endl;
     */
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifstream ifs2;
    ifs.open("pooh-nopunc.txt");
    set<string> all_added_words;
    while (ifs >> word){
        all_added_words.insert(word);
    }
    ifs2.close();
    cout << "Set Size: " << all_added_words.size() << endl;
    /*
     for (const string& word : all_added_words){
        cout << word << ", ";
    }
    cout << endl;
     */
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    ifstream ifs3("pooh-nopunc.txt");
    int pos = 0;
    while (ifs3 >> word){
        wordMap[word].push_back(pos);
        // keep track of word position
        ++pos;
    }
    ifs3.close();
    for (const auto& pair : wordMap){
        cout << pair.first << ":  ";
        for (int pos : pair.second){
            cout << pos << ", ";
        }
        cout << endl;
    }
    cout << "=======\n";
}

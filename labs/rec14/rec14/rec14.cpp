#include <iostream>
#include <list>
using namespace std;

struct Node{
    Node(int data, Node* link = nullptr): data(data), link(link) {};
    int data;
    Node* link;
};

// Task 1
bool numberOfOnes(int num){
    if (num <= 0) return true;
    bool curr_value = (num%2==0);
    bool retval = (numberOfOnes(num/2) == curr_value);
    return retval;
}

// Task 2
Node* sumOfBothLists(const Node* list1, const Node* list2){
    if (list1 == nullptr && list2 == nullptr){
        return nullptr;
    }
    if (list1 == nullptr){
        return new Node(list2->data, sumOfBothLists(list1->link, list2));
    }
    if (list2 == nullptr){
        return new Node(list1->data, sumOfBothLists(list1->link, list2));
    }
    return new Node(list1->data+list2->data, sumOfBothLists(list1->link, list2->link));
}


// Task 4
bool palindrome(char* char_array, int arraysize){
    if (arraysize <=1){
        return true;
    }
    //checks if first letter == last letter
    bool firstandlast = (char_array[0] == char_array[arraysize-1]);
    // if false, return false to save time checking the letters in between
    if (!firstandlast) return false;
    
    // checks if letters in between the first and last letter match up
    return palindrome(char_array+1, arraysize-2);
}


// Task 3
struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
    if (root == nullptr){
        throw invalid_argument("cannot calculate max of empty tree");
    }
    if (root->left == nullptr && root->right == nullptr){
        return root->data;
    }
    int curr_max = root->data;
    if (root->left != nullptr){
        int max_left = max(root->left);
        if (max_left > curr_max) curr_max = max_left;
    }
    if (root->right != nullptr){
        int max_right = max(root->right);
        if (max_right > curr_max) curr_max = max_right;
    }
    return curr_max;
}

// Task 5
int towers(int num_disks, char starting, char spare, char target){
    if (num_disks==1){
        return 1;
    }
    int step1 = towers(num_disks-1, starting, target, spare);
    int step2 = towers(1, starting, spare, target);
    int step3 = towers(num_disks-1, spare, starting, target);
    return step1+step2+step3;
}

void mystery(int n) {
   if (n > 1) {
      cout << 'a';
      mystery(n/2);
      cout << 'b';
      mystery(n/2);
   }
   cout << 'c';
}

int main() {
    //tester code for task 1
    cout << "EVEN OR ODD: 10 ";
    if (numberOfOnes(10)) cout << "EVEN" << endl;
    else { cout << "ODD" << endl; }
    
    // tester code for task 2
    Node* list1 = new Node(1, new Node(2, new Node(3)));
    Node* list2 = new Node(2, new Node(3, new Node(4)));
    Node* sumofboth = sumOfBothLists(list1, list2);
    while (sumofboth != nullptr){
        cout << sumofboth->data << endl;
        sumofboth = sumofboth->link;
    }
    
    // tester code for task 3
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << max(&f) << endl;
    
    
    // tester code for task 4
    char s[] = "racecar";
    if (palindrome(s, 7)) { cout << "Yes!\n"; }
    else{ cout << "No!\n";}
    
    // tester code for task 5
    cout << towers(10, 'a', 'b', 'c') << endl;
    
    // task 6
    for (int i=0; i<=10; ++i){
        mystery(i);
        cout << endl;
    }
}


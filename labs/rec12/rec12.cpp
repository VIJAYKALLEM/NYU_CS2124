// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;
struct Node{
    Node(int data = 0, Node* prior = nullptr, Node* next = nullptr): data(data), prior(prior), next(next) {};
    int data;
    Node* prior;
    Node* next;
};

class List {
    friend ostream& operator<<(ostream& os, const List& rhs){
        if (rhs.curr_size != 0){
            Node* curr_node = rhs.header->next;
            while (curr_node != rhs.trailer){
                os << curr_node->data << " ";
                curr_node = curr_node->next;
            }
        }
        return os;
    }
public:
    class GenericIterator{
        friend List;
        friend bool operator!=(const GenericIterator& lhs, const GenericIterator& rhs);
    public:
        GenericIterator(Node* first_node): position(first_node) {};
        void operator++(){
            position = position->next;
        }
        void operator--(){
            position = position->prior;
        }
    protected:
        Node* position;
    };
    
    class ConstIterator : public GenericIterator{
    public:
        ConstIterator(Node* first_node): GenericIterator(first_node) {};
        int operator*() const{
            return position->data;
        }
    };
    
    class NonConstIterator : public GenericIterator{
    public:
        NonConstIterator(Node* first_node): GenericIterator(first_node) {};
        int& operator*(){
            return position->data;
        }
    };
    //constructor
    //initializes size=0, sentinal nodes are created
    List(): curr_size(0) {
        header = new Node();
        trailer = new Node(0, header, nullptr);
        header->next = trailer;
    }
    
    //copy constructor
    List(const List& rhs): List(){
        for (int new_val: rhs){
            push_back(new_val);
        }
    }
    
    //destructor
    ~List(){
        clear();
        delete header;
        delete trailer;
    }
    void push_back(int data){
        //adds new node before trailer
        //sets new node to be the current last node's next
        //sets new node to be trailer's prior
        
        Node* curr_prior = trailer->prior;
        curr_prior->next = new Node(data, curr_prior, trailer);
        trailer->prior = curr_prior->next;
        curr_size+= 1;
    }
    
    //assignment operator
    List& operator=(const List& rhs){
        if (this != &rhs){
            clear();
            for (int new_val: rhs){
                push_back(new_val);
            }
        }
        return *this;
    }
    
    void pop_back(){
        //deletes last (non-trailer) node
        //sets trailer prior to second-to-last node
        //sets second-to-last node's next to trailer
        if (curr_size == 0){
            return;
        }
        Node* curr_prior = trailer->prior;
        Node* new_prior = curr_prior->prior;
        new_prior->next = trailer;
        trailer->prior = new_prior;
        delete curr_prior;
        curr_size-=1;
    }
    
    int front() const{
        //const version returns copy of data in first node
        Node* first_node = header->next;
        return first_node->data;
    }
    
    int& front() {
        //non-const version returns reference to data in first node
        Node* first_node = header->next;
        return first_node->data;
    }
    
    int back() const{
        //const version returns copy of data in last node
        Node* last_node = trailer->prior;
        return last_node->data;
    }
    
    int& back() {
        //non-const version returns reference to data in last node
        Node* last_node = trailer->prior;
        return last_node->data;
    }
    
    int size() const{
        return curr_size;
    }
    
    void push_front(int data){
        //adds new node to front of list
        Node* old_first = header->next;
        header->next = new Node(data, header, old_first);
        old_first->prior = header->next;
        curr_size +=1;
    }
    
    void pop_front(){
        if (curr_size == 0){
            return;
        }
        Node* node_to_delete = header->next;
        Node* new_first = node_to_delete->next;
        header->next = new_first;
        new_first->prior = header;
        delete node_to_delete;
        curr_size -=1;
    }
    
    void clear(){
        while (curr_size != 0){
            pop_back();
        }
    }
    
    int operator[](size_t index) const{
        if (curr_size == 0){
            return 0;
        }
        Node* curr_node = header->next;
        while (index>0){
            curr_node = curr_node->next;
            index -=1;
        }
        return curr_node->data;
    }
    
    int& operator[](size_t index){
        if (curr_size == 0){
            return header->data;
        }
        Node* curr_node = header->next;
        while (index>0){
            curr_node = curr_node->next;
            index -=1;
        }
        return curr_node->data;
    }
    
    NonConstIterator begin(){
        return NonConstIterator(header->next);
    }
    
    ConstIterator begin() const{
        return ConstIterator(header->next);
    }
    
    NonConstIterator end(){
        return NonConstIterator(trailer);
    }
    
    ConstIterator end() const{
        return ConstIterator(trailer);
    }
    
    NonConstIterator insert(const NonConstIterator& iter, int new_item){
        Node* prior_node = iter.position->prior;
        Node* next_node = iter.position;
        prior_node->next = new Node(new_item, prior_node, next_node);
        next_node->prior = prior_node->next;
        NonConstIterator new_iter(prior_node->next);
        curr_size+=1;
        return new_iter;
    }
    
    NonConstIterator erase(const NonConstIterator& iter){
        Node* prior_node = iter.position->prior;
        Node* to_delete = iter.position;
        Node* next_node = iter.position->next;
        prior_node->next = next_node;
        next_node->prior = prior_node;
        delete to_delete;
        curr_size-=1;
        return NonConstIterator(next_node);
        
    }
private:
    int curr_size;
    Node* header;
    Node* trailer;
};

bool operator!=(const List::GenericIterator& lhs, const List::GenericIterator& rhs){
    return lhs.position != rhs.position;
}

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
//void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
//}

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}
// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    
    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::NonConstIterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    cout << endl;
    cout << "CUSTOM TESTING FOR CONST ITERATOR"<<endl;

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";
    
    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}

/*
 Simran Soin
 CS2124 Recitation 11
 Linked List basics
 */
#include <iostream>
#include <vector>
#include<unordered_set>
using namespace std;
/*
  functions for use with CS2124 rec11
  -jbs
*/

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}

void splice(Node* list_to_add, Node*& location){
    // if the list we are adding is null, then theres nothing to modify
    if (list_to_add == nullptr){ return; }
    // if the location is null, we just set location to the list to add
    if (location == nullptr){
        location = list_to_add;
        return;
    }
    // store original next node
    // set current location.next to the list_to_add
    // set last node in list_to_add as the original next node
    Node* original_next_node = location->next;
    location->next = list_to_add;
    while (list_to_add->next != nullptr){
        list_to_add = list_to_add->next;
    }
    list_to_add->next = original_next_node;
}

Node* isSublist(Node* sublist, Node* orig_list){
    // if original list is nullptr, return nullptr
    if (orig_list == nullptr){ return nullptr;}
    Node* sublist_curr = sublist;
    while (orig_list != nullptr){
        if (sublist_curr->data == orig_list->data){
            Node* orig_list_curr = orig_list;
            bool matching = true;
            while (sublist_curr != nullptr){
                if (orig_list_curr->data != sublist_curr->data){
                    matching = false;
                    break;
                }
                else{
                    orig_list_curr = orig_list_curr->next;
                    sublist_curr = sublist_curr->next;
                }
            }
            if (matching){ return orig_list;}
            else{sublist_curr = sublist;}
        }
        orig_list = orig_list->next;
    }
    return nullptr;
}


Node* sharedListBruteForce(Node* list1, Node* list2){
    while (list1 != nullptr){
        Node* list2_curr = list2;
        while (list2_curr != nullptr){
            if (list1 == list2_curr){
                return list2_curr;
            }
            list2_curr = list2_curr->next;
        }
        list1 = list1->next;
    }
    return nullptr;
}

Node* sharedListUsingSet(Node* list1, Node* list2){
    Node* list1_curr = list1;
    unordered_set<Node*> nodes_from_list1;
    while (list1_curr != nullptr){
        nodes_from_list1.insert(list1_curr);
        list1_curr = list1_curr->next;
    }
    while (list2 != nullptr){
        if (nodes_from_list1.find(list2) != nodes_from_list1.end()){
            return list2;
        }
        list2 = list2->next;
    }
    return nullptr;
}

Node* sharedListUsingConstSpace(Node* list1, Node* list2){
    int size_list1 = 0;
    int size_list2 = 0;
    
    // count size of list1
    Node* list1_curr = list1;
    while (list1_curr != nullptr){
        size_list1 += 1;
        list1_curr = list1_curr->next;
    }
    
    //count size of list2
    Node* list2_curr = list2;
    while (list2_curr != nullptr){
        size_list2 += 1;
        list2_curr = list2_curr->next;
    }
    
    //determine which list is smaller, larger, and diff in sizes
    Node* larger;
    Node* smaller;
    int difference;
    if (size_list1 > size_list2){
        larger = list1;
        smaller = list2;
        difference = size_list1 - size_list2;
    }
    else{
        larger = list2;
        smaller = list1;
        difference = size_list2 - size_list1;
    }
    
    //walk down larger until it is the size of smaller
    for (int i = 0; i < difference; ++i){
        larger = larger->next;
    }
    
    //compare corresponding nodes
    while (smaller != nullptr){
        if (smaller == larger){
            return smaller;
        }
        smaller = smaller->next;
        larger = larger->next;
    }
    return nullptr;
}

int main(){
    //test code for list splice function
    vector<int> original_list{5,7,2,9,1};
    Node* headPtr = listBuild(original_list);
    vector<int> new_list{6,3,2};
    Node* newHeadPtr = listBuild(new_list);
    Node* location_of_7 = headPtr->next;
    cout << "ORIGINAL LIST: ";
    Node* curr_node = headPtr;
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    cout <<endl;
    cout << "LIST_TO_SPLICE: ";
    curr_node = newHeadPtr;
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    cout <<endl;
    cout << "FINAL SPLICING: ";
    splice(newHeadPtr, location_of_7);
    curr_node = headPtr;
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    listClear(headPtr);
    cout << endl;
    
    cout << endl;
    cout << endl;
    //test code for sublist function
    vector<int> original_sublist_list{1,2,3,2,3,2,4,5,6};
    Node* orig_list = listBuild(original_sublist_list);
    Node* sublist = listBuild({2,3,2,4});
    cout << "ORIGINAL LIST: ";
    curr_node = orig_list;
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    cout <<endl;
    cout << "SUBLIST: ";
    curr_node = sublist;
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    cout <<endl;
    cout << "OUTPUT: ";
    Node* sublist_loc = isSublist(sublist, orig_list);
    while(sublist_loc != nullptr){
        cout << sublist_loc->data << ", ";
        sublist_loc = sublist_loc->next;
    }
    cout<< endl;
    listClear(sublist);
    listClear(orig_list);
    
    
    cout<< endl;
    cout<< endl;
    //test code for sharedList functions
    Node* list1 = listBuild({2,3});
    Node* list2 = listBuild({2,3,3});
    Node* shared_list = listBuild({4,5});
    splice(shared_list, list1->next->next);
    splice(shared_list, list2->next->next->next);
    
    cout << "LIST 1: ";
    curr_node = list1;
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    cout<< endl;
    
    cout << "LIST 2: ";
    curr_node = list2;
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    cout<< endl;
    
    cout<< "Shared List Using Brute Force: ";
    curr_node = sharedListBruteForce(list1, list2);
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    cout<< endl;
    
    cout<< "Shared List Using Set: ";
    curr_node = sharedListUsingSet(list1, list2);
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    cout<< endl;
    cout<< "Shared List Using Const Space: ";
    curr_node = sharedListUsingConstSpace(list1, list2);
    while(curr_node != nullptr){
        cout << curr_node->data << ", ";
        curr_node = curr_node->next;
    }
    
    
}

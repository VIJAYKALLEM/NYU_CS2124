/*
Simran Soin
CS2124
Homework 8 — implementing polynomial using a singly linked list
Polynomial .cpp File
*/
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "polynomial.h"
using namespace std;

int listLength(const Node* p) {
    int length = 0;
    while (p != NULL) {
        length++;
        p = p->link;
    }
    return length;
}

void listInsertHead(int data, Node*& headPtr) {
    // Create a new node, holding data and pointing to headPtr.
    // Put the address of this new node back into headPtr.
    headPtr = new Node(data,  headPtr);
}

void listRemoveHead(Node*& headPtr) {
    if (headPtr) {
        Node* second = headPtr->link;
        delete headPtr;
        headPtr = second;
    }
}

void listInsertAfter(int entry, Node* previousPtr) {
    // Create a new node, holding data and pointing to the node
    // that comes after the node pointed to by previousPtr.
    // Store the address of the new Node back into that same link.
    previousPtr->link = new Node(entry,  previousPtr->link);
}

void listRemoveAfter(Node* previousPtr) {
    Node* removePtr = previousPtr->link;
    previousPtr->link = removePtr->link;
    delete removePtr;
}

Node* listFindLast(Node* p) {
    if (p)
        while (p->link) p = p->link;
    return p;
}

void listAppend(Node*& listOne, Node* listTwo) {
    if (listOne) {
        Node* p = listFindLast(listOne);
        p->link = listTwo;
    } else
        listOne = listTwo;
}

void listClear(Node*& p) {
    while (p) {
        Node *temp = p->link;
        delete p;
        p = temp;
    }
}

// As far as understanding pointer manipulation,
// it is better that you understand the code
// above for listClear.
// But this certainly is a tidier way to do the job.
void listClear2(Node*& p) {
    while (p) listRemoveHead(p);
}

Node* listSearch(int target, Node* p) {
    while (p && p->data != target)
        p = p->link;
    return p;
}

Node* listNodeAtIndex(int index, Node* p) {
    int count = 0;
    while (count < index && p != NULL) {
        count++;
        p = p->link;
    }
    return p;
}


const Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial larger;
    Polynomial smaller;
    if (lhs.degree <= rhs.degree){
        smaller = lhs;
        larger = rhs;
    }
    else{
        smaller = rhs;
        larger = lhs;
    }
    Polynomial retval = larger;
    Node* retval_pos = retval.headptr;
    Node* smaller_pos = smaller.headptr;
    for (int i=0; i<(smaller.degree+1); ++i){
        retval_pos->data += smaller_pos->data;
        if (i == retval.degree && retval_pos->data == 0){
            retval.degree -= 1;
        }
        retval_pos = retval_pos->link;
        smaller_pos = smaller_pos->link;
    }
    return retval;
    
}
bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if (lhs.degree != rhs.degree){
        return false;
    }
    Polynomial larger;
    Polynomial smaller;
    if (lhs.degree <= rhs.degree){
        smaller = lhs;
        larger = rhs;
    }
    else{
        smaller = rhs;
        larger = lhs;
    }
    Node* lhs_pos = lhs.headptr;
    Node* rhs_pos = rhs.headptr;
    for (int i=0; i<(smaller.degree); ++i){
        if (lhs_pos->data != rhs_pos->data){
            return false;
        }
        lhs_pos = lhs_pos->link;
        rhs_pos = rhs_pos->link;
    }
    return true;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}
ostream& operator<<(ostream& os, const Polynomial& rhs){
    string final_str = "";
    int degree = 0;
    Node* curr_node = rhs.headptr;
    if (degree == 0 && curr_node==nullptr){
        final_str = "0";
    }
    else{
        while (curr_node != nullptr) {
            if (curr_node->data != 0){
                if (final_str != ""){
                    final_str = " + " + final_str;
                }
                if (degree != 0){
                    if (degree == 1){final_str = "x" + final_str;}
                    else{final_str = "x^" + to_string(degree) + final_str;}
                }
                
                if (curr_node->data != 1 || degree == 0){
                    final_str = to_string(curr_node->data) + final_str;
                }
            }
            curr_node = curr_node->link;
            ++degree;
        }
    }
    os << final_str;
    return os;
}

Polynomial::Polynomial(): headptr(nullptr), degree(0) {};

Polynomial::Polynomial(std::initializer_list<int> nums){
    degree = 0;
    Node* old_headptr = nullptr;
    size_t list_size = 0;
    for (int i : nums){
        if (old_headptr == nullptr && i == 0){
            continue;
        }
        headptr = new Node(i, old_headptr);
        old_headptr = headptr;
        ++ list_size;
    }
    degree = list_size - 1;
}

Polynomial::Polynomial(const Polynomial& rhs) : degree(rhs.degree){
    if (rhs.headptr == nullptr){
        headptr = nullptr;
        return;
    }
    headptr = new Node(rhs.headptr->data);
    Node* currTail = headptr;

    const Node* p = rhs.headptr->link;
    while (p) {
        listInsertAfter(p->data, currTail);
        currTail = currTail->link;
        p = p->link;
    }
}

Polynomial::~Polynomial(){
    listClear(headptr);
}

Polynomial& Polynomial::operator=(const Polynomial& rhs){
    degree = rhs.degree;
    listClear(headptr);
    if (rhs.headptr == nullptr){
        headptr = nullptr;
        return *this;
    }
    headptr = new Node(rhs.headptr->data);
    Node* currTail = headptr;

    const Node* p = rhs.headptr->link;
    while (p) {
        listInsertAfter(p->data, currTail);
        currTail = currTail->link;
        p = p->link;
    }
    return *this;
}

Polynomial Polynomial::operator+=(const Polynomial& rhs){
    Polynomial retval;
    retval = *this + rhs;
    *this = retval;
    return retval;
}

int Polynomial::evaluate(int x_val){
    size_t curr_degree = 0;
    int final_val = 0;
    Node* curr_node = headptr;
    while (curr_node != nullptr){
        final_val += (curr_node->data * pow(x_val, curr_degree));
        ++curr_degree;
        curr_node = curr_node->link;
    }
    return final_val;
}

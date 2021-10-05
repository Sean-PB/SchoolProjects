/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa5
* List.cpp
* Implementation file for List ADT
***************************************************************************************************/
#include<iostream>
#include<string>
#include<climits>
#include"List.h"

using namespace std;

// ------------------------------ Private Constructor ----------------------------------------------

// Node constructor
List::Node::Node(LIST_ELEMENT x){
    data = x;
    next = nullptr;
    prev = nullptr;
}
// ------------------------ Class Constructors & Destructors ---------------------------------------

// Creates a new List in the empty state
List::List(){
    Node* frontN = new Node(LONG_MIN);
    Node* backN = new Node(LONG_MAX);
    frontN->next = backN;
    backN->prev = frontN;
    frontDummy = frontN;
    backDummy = backN;
    beforeCursor = frontN;
    afterCursor = backN;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor
List::List(const List& L){
    // make this an empty ListTest
    Node* frontN = new Node(LONG_MIN);
    Node* backN = new Node(LONG_MAX);
    frontN->next = backN;
    backN->prev = frontN;
    frontDummy = frontN;
    backDummy = backN;
    beforeCursor = frontN;
    afterCursor = backN;
    pos_cursor = 0;
    num_elements = 0;

    // load elements of L into this
    Node* N = L.frontDummy->next;
    while(N != L.backDummy){
        this->insertBefore(N->data);
        N = N->next;
    }

    while (this->position() != L.pos_cursor){
        this->movePrev();
    }
}

// Destructor
List::~List(){
    clear();
    beforeCursor = nullptr;
    afterCursor = nullptr;
    delete frontDummy;
    delete backDummy;
}


// ------------------------------------- Access functions ------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
    return(num_elements == 0);
}

// size()
// Returns the size of this List.
int List::size(){
    return(num_elements);
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position(){
    return(pos_cursor);
}

// -------------------------------- Manipulation Procedures ----------------------------------------

// moveFront()
// Moves cursor to position 0 in this list.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack(){
    pos_cursor = num_elements;
    afterCursor = backDummy;
    beforeCursor = backDummy->prev;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
LIST_ELEMENT List::peekNext(){
    if (position() >= size()){
        cerr << "List Error: calling peekNext when cursor is at the end of List" << endl;
        exit(EXIT_FAILURE);
    }

    return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
LIST_ELEMENT List::peekPrev(){
    if (position() <=  0){
        cerr << "List Error: calling peekPrev when cursor is at the begining of List" << endl;
        exit(EXIT_FAILURE);
    }

    return(beforeCursor->data);
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that was passed over.
// pre: position()<size()
LIST_ELEMENT List::moveNext(){
    if (position() >= size()){
        cerr << "List Error: calling moveNext when cursor is at the end of List" << endl;
        exit(EXIT_FAILURE);
    }

    pos_cursor++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    return(beforeCursor->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
LIST_ELEMENT List::movePrev(){
    if (position() <= 0){
        cerr << "List Error: calling movePrev when cursor is at the begining of List" << endl;
        exit(EXIT_FAILURE);
    }

    pos_cursor--;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    return(afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(LIST_ELEMENT x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    afterCursor = N;
    num_elements++;
}


// insertBefore()
// Inserts x before cursor.
void List::insertBefore(LIST_ELEMENT x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    afterCursor->prev = N;
    beforeCursor = N;
    pos_cursor++;
    num_elements++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){
     if(position() >= size()){
         cerr << "List Error: calling eraseAfter when cursor is at the end of List" << endl;
         exit(EXIT_FAILURE);
     }

     Node* N = afterCursor;
     beforeCursor->next = afterCursor->next;
     afterCursor->next->prev = beforeCursor;
     afterCursor = afterCursor->next;
     num_elements--;
     delete N;

}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(position() <= 0){
        cerr << "List Error: calling eraseBefore when cursor is at the begining of List" << endl;
        exit(EXIT_FAILURE);
    }

    Node* N = beforeCursor;
    afterCursor->prev = beforeCursor->prev;
    beforeCursor->prev->next = afterCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    num_elements--;
    delete N;
}

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(LIST_ELEMENT x){
    while(position() < size()){
        if(moveNext() == x){
            return(position());
        }
    }
    return(-1);
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(LIST_ELEMENT x){
    while(position() > 0){
        if(movePrev() == x){
            return(position());
        }
    }
    return(-1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup(){
    Node* N;
    Node* M;
    Node* temp;

    for (N = frontDummy->next; N != backDummy; N = N->next){ // for every element in the list
        M = N->next;
        while (M != backDummy){     // for every other element in the list
            temp = M->next;
            if (M->data == N->data){
                // if the element in the list (N) is found further in the list (M), delete M
                M->prev->next = M->next;
                M->next->prev = M->prev;
                if(beforeCursor == M){
                    beforeCursor = M->prev;
                }
                if (afterCursor == M){
                    afterCursor = M->next;
                }
                num_elements--;
                delete M;
            }
            M = temp;
        }
    }
    // Fix the pos_cursor number
    pos_cursor = 0;
    for (N = frontDummy->next; N != beforeCursor->next; N = N->next){
        pos_cursor++;
    }
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    for(moveBack(); position() > 0; eraseBefore());
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
    List cat = List(L);

    cat.moveFront();
    for (Node* N = this->backDummy->prev; N != this->frontDummy; N = N->prev){
        cat.insertAfter(N->data);
    }
    return(cat);
}

// ---------------------------------- Other Functions ----------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string(){
    Node* N;
    string s = "(";

    for (N = frontDummy->next; N != backDummy; N = N->next){
        s += std::to_string(N->data);
        if (N != backDummy->prev){
            s += ", ";
        }
    }
    s += ")";
    return(s);
}

// equals()
// Returns true if and only if this List is the same LIST_ELEMENT sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R){
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while(eq && N != this->backDummy){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// ------------------------------------ Overriden Operators ----------------------------------------
// operator<<()
// Inserts string representation of L into stream.
ostream& operator<< (ostream& stream, List& L){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same LIST_ELEMENT sequence as B. The
// cursors in both Lists are unchanged are unchanged.
bool operator== (List& A, const List& B){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
    if( this != &L ){ // not self assignment
        // make a copy of L
        List temp = L;

        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }

    // return this with the new data installed
    return *this;

    // the copy, if there is one, is deleted upon return
}

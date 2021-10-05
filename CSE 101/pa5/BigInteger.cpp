//--------------------------------------------------------------------------------------------------
// Sean Brandon, spbrando
// 2021 Spring CSE101 pa5
// BigInteger.cpp
// Implementation file for the BigInteger ADT
//--------------------------------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<math.h>
#include"BigInteger.h"

using namespace std;

const int power = 9;
const LIST_ELEMENT base = pow(10, power);

// --------------------------------- Class Constructors & Destructors ------------------------------
// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    // Precondition checks
    if (s.empty()){
        cerr << "BigInteger Error: constructor called on empty string" << '\n';
        exit(EXIT_FAILURE);
    }
    if((!isdigit(s[0]) && s[0] != '+' && s[0] != '-') || (!isdigit(s[0]) && s.length() == 1)) {
        cerr << "BigInteger Error: constructor called on non-numeric string\n";
        exit(EXIT_FAILURE);
    }
    for (ulong i = 1; i < s.length(); i++){
        if (!isdigit(s[i])){
            cerr << "BigInteger Error: constructor called on non-numeric string\n";
            exit(EXIT_FAILURE);
        }
    }

    std::string stringNum;

    // signum
    if (s[0] == '+'){
        signum = 1;
        stringNum = s.substr(1, s.length());
    }
    else if(s[0] == '-'){
        signum = -1;
        stringNum = s.substr(1, s.length());
    }
    else{
        signum = 1;
        stringNum = s;
    }
    // digits
    for (int i = stringNum.length(); i > 0; i -= power){
        if (i < power){
            digits.insertAfter(stol(stringNum.substr(0, i)));
        }
        else{
            digits.insertAfter(stol(stringNum.substr(i - power, power)));
        }
    }
}

// BigInteger()
// Constructor that copies the BigInteger N.
BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = N.digits;
}


// ~BigInteger()
// Destructor (optional)
//~BigInteger();


// ------------------------------------- Access functions ------------------------------------------
// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign(){
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(BigInteger N){
    LIST_ELEMENT x, y;

    // remove leading zeros for later
    for (this->digits.moveFront(); (this->digits.position() < (this->digits.size() - 1)) && this->digits.peekNext() == 0; this->digits.eraseAfter());
    for (N.digits.moveFront(); (N.digits.position() < (N.digits.size() - 1)) && N.digits.peekNext() == 0; N.digits.eraseAfter());
    // compare signs
    if(this->signum < N.signum){
        return -1;
    }
    else if (this->signum > N.signum){
        return 1;
    }
    // signs same so if one is 0 then they're equal
    else if(this->signum == 0){
        return 0;
    }
    // signs same so now compare number of elements in list
    else if (this->digits.size() > N.digits.size()){
        if (this->signum == -1){     // if they're both - and this is bigger than N, then this < N
            return -1;
        }
        else{                       // if they're both + and this is bigger than N, then this > N
            return 1;
        }
    }
    else if(this->digits.size() < N.digits.size()){
        if (this->signum == -1){     // if they're both - and this is less than N, then this > N
            return 1;
        }
        else{                       // if they're both + and this is less than N, then this < N
            return -1;
        }
    }
    // if their number of elements and signs are the same, then compare first elements
    else{
        this->digits.moveFront();
        N.digits.moveFront();

        while(this->digits.position() < this->digits.size()){
            x = this->digits.moveNext();
            y = N.digits.moveNext();
            if (x < y){
                if(this->signum == -1){  // they're both - and this.moveNext < N.moveNext, then this > N
                    return 1;
                }
                else{                    // they're both - and this.moveNext < N.moveNext, then this < N
                    return -1;
                }
            }
            else if(x > y){
                if(this->signum == -1){  // they're both - and this.moveNext > N.moveNext, then this < N
                    return -1;
                }
                else{                   // they're both - and this.moveNext > N.moveNext, then this > N
                    return 1;
                }
            }
        }
        // if their number of elements, signs, and front elements are the same, they are =
        return 0;
    }
}


// -------------------------------- Manipulation Procedures ----------------------------------------
// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    signum = 0;
    digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate(){
    if (signum == -1){
        signum = 1;
    }
    else if(signum == 1){
        signum = -1;
    }
}

// ------------------------------------ Helper functions -------------------------------------------
// negateList()
// Changes the sign of each LIST_ELEMENT in List L. Used by sub().
void negateList(List& L){
    LIST_ELEMENT num;
    L.moveFront();
    while (L.position() < L.size()){
        num = L.moveNext();
        L.eraseBefore();
        L.insertBefore(-num);
    }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
    S.clear();
    A.moveBack();
    B.moveBack();
    if(B.size() < A.size()){          // B < A
        while (B.position() > 0){
            S.insertAfter(A.movePrev() + (sgn * B.movePrev()));
        }
        while(A.position() > 0){
            S.insertAfter(A.movePrev());
        }
    }
    else{                               // B >= A
        while (A.position() > 0){
            S.insertAfter(A.movePrev() + (sgn * B.movePrev()));
        }
        while(B.position() > 0){
            S.insertAfter(sgn * B.movePrev());
        }
    }
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
    LIST_ELEMENT num;
    LIST_ELEMENT carry = 0;

    // remove leading zeros (MUST DO! OTHERWISE INFINITE BORROWS AND INFINITE EDGE CASE)
    for (L.moveFront(); (L.position() < (L.size() - 1)) && L.peekNext() == 0; L.eraseAfter());

    L.moveBack();
    while (L.position() > 0){
        num = L.movePrev() + carry;
        carry = 0;
        if (num >= base){                   // carry
            L.eraseAfter();
            L.insertAfter(num % base);
            carry = num / base;
        }
        else if(num < 0){                   // borrow
            L.eraseAfter();
            if (num < -base){
                L.insertAfter(-(num % base));
                carry = (num / base) - 1;
            }
            else if (num == -base) {
                L.insertAfter(num % base);
                carry = (num / base);
            }
            else {
                L.insertAfter(num + base);
                carry = -1;
            }
        }
        else{
            L.eraseAfter();
            L.insertAfter(num);
            carry = 0;
        }
    }
    if (carry != 0){
        L.insertAfter(carry);
    }

    // edge case
    // remove any possible leading zeros first
    for (L.moveFront(); (L.position() < (L.size() - 1)) && L.peekNext() == 0; L.eraseAfter());
    L.moveFront();
    if (L.peekNext() < 0) {
        negateList(L);
        normalizeList(L);
        return -1;
    }
    else if (L.peekNext() > 0){
        return 1;
    }
    else {
        return 0;
    }
}

// shiftList()
// Appends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
    L.moveBack();
    for (int i = 0; i < p; i++){
        L.insertBefore(0);
    }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, LIST_ELEMENT m){
    LIST_ELEMENT num;
    L.moveFront();
    while (L.position() < L.size()){
        num = L.moveNext() * m;
        L.eraseBefore();
        L.insertBefore(num);
    }
}

// ----------------------------- BigInteger Arithmetic operations ----------------------------------
// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N){
    BigInteger num;
    int sign;
    if (N.signum == 0 && this->signum == 0) {
        sign = 0;
    }
    else if (N.signum + this->signum == 0){
        sign = -1;
    }
    else {
        sign = 1;
    }

    sumList(num.digits, this->digits, N.digits, sign);
    sign = normalizeList(num.digits);
    if (this->signum == N.signum) {
        num.signum = this->signum;
    }
    else if (this->signum == 0){
       num.signum = N.signum * sign;
    }
    else{
        num.signum = this->signum * sign;
    }
    return(num);
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N){
    BigInteger num;
    int sign;
    if (N.signum == 0 && this->signum == 0) {
        sign = 0;
    }
    else if (N.signum + this->signum == 0){
        sign = 1;
    }
    else {
        sign = -1;
    }

    sumList(num.digits, this->digits, N.digits, sign);
    sign = normalizeList(num.digits);
    if (this->signum == N.signum) {
        num.signum = this->signum * sign;
    }
    else if(this->signum == 0){
       num.signum = N.signum * sign;
    }
    else{
        num.signum = this->signum;
    }
    return(num);
}

// mult()
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger& N){
    BigInteger rNum;
    BigInteger tempNum;
    BigInteger nCopy = N;
    BigInteger thisCopy = *this;
    nCopy.digits.moveBack();
    for (int i = 0; nCopy.digits.position() > 0; i++){  // loop through each digit of bottom number
        tempNum.digits = thisCopy.digits;
        tempNum.signum = thisCopy.signum;
        scalarMultList(tempNum.digits, nCopy.digits.movePrev());
        shiftList(tempNum.digits, i);
        rNum += tempNum;
    }
    if (nCopy.signum == 0 || thisCopy.signum == 0) {
        rNum.signum = 0;
    }
    else if (nCopy.signum + thisCopy.signum == 0){
        rNum.signum = -1;
    }
    else {
        rNum.signum = 1;
    }
    return rNum;
}

// ---------------------------------- Other Functions ----------------------------------------------
// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string s;
    std::string numS;
    LIST_ELEMENT num;

    if (signum == -1){
        s += '-';
    }

    // Remove leading zeros
    for(digits.moveFront(); (digits.position() < (digits.size() - 1) && digits.moveNext() == 0); digits.eraseBefore());

    digits.moveFront();
    while (digits.position() < digits.size()){
        num = digits.moveNext();
        if (digits.position() == 1){        // Don't pad first digit with 0's
            s += std::to_string(num);
        }
        else if (digits.position() > 1){    // Pad the rest of the digits with appropriate number of 0's
            numS = std::to_string(num);
            for (int i = std::to_string(num).length(); i < power; i++){
                numS = '0' + numS;
            }
            s += numS;
        }
    }
    if (s.length() == 0){    // if the number is 0
        s += '0';
    }
    return s;

}

// ------------------------------------ Overridden Operators ----------------------------------------
// operator<<()
// Inserts string representation of N into stream.
ostream& operator<<( ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==( BigInteger& A, const BigInteger& B ){
    if (A.BigInteger::compare(B) == 0){
        return true;
    }
    else{
        return false;
    }
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<( BigInteger& A, const BigInteger& B ){
    if (A.BigInteger::compare(B) == -1) return true;
    else return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=( BigInteger& A, const BigInteger& B ){
    if (A.BigInteger::compare(B) == -1 || A.BigInteger::compare(B) == 0) return true;
    else return false;
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>( BigInteger& A, const BigInteger& B ){
    if (A.BigInteger::compare(B) == 1) return true;
    else return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=( BigInteger& A, const BigInteger& B ){
    if (A.BigInteger::compare(B) == 1 || A.BigInteger::compare(B) == 0) return true;
    else return false;
}

// operator+()
// Returns the sum A+B.
BigInteger operator+( BigInteger A, const BigInteger& B ){
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-( BigInteger A, const BigInteger& B ){
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return B;
}

// operator*()
// Returns the product A*B.
BigInteger operator*( BigInteger A, const BigInteger& B ){
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}

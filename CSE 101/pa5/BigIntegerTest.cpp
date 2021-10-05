/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa5
* BigIntegerTest.cpp
* Tests BigInteger operations in isolation
***************************************************************************************************/
#include <string>
#include "BigInteger.h"

using namespace std;

int main(){

    BigInteger zero = BigInteger();                             // BigInteger()
    BigInteger C = BigInteger();

    BigInteger A = BigInteger("+111122223333");                 // BigInteger(std::string s)
    BigInteger B = BigInteger("+222211110000");
    BigInteger D = BigInteger(A);                               // BigInteger(const BigInteger& N)

    cout << "A = " << A.to_string() << endl;                    // to_string()
    cout << "B = "<< B << endl;                                 // <<

    if (!(A.sign() == 1)){                                      // sign()
        cout << "sign() failed\n";
    }

    if (A.compare(D) != 0){                                       // compare()
        cout << "compare() failed\nCompare() returns: " << A.compare(D) << endl;
    }

    D.makeZero();                                               // makeZero()
    if(!(D == zero)){
        cout << "makeZero() failed\n";
    }

    cout << "333333333333 == " << A.add(B) << endl;            // add

    cout << "-111088886667 == " << A.sub(B) << endl;           // sub()

    cout << "A * B == " << A.mult(B) << endl;                   // mult

    B.negate();                                                 // negate()
    cout << "B negated == " << B << endl;
    B.negate();

    C += A;                                                     // +=

    if (!(A == C)){                                             // ==
        cout << "== failed:" << endl << A << " should equal " << C << endl;
        cout << "(A == C) == " << (A == C) << endl;
        cout << "A.compare(C) == " << A.compare(C) << endl;
        cout << "A.signum == " << A.sign() << endl;
        cout << "C.signum == " << C.sign() << endl << endl;
    }

    if (B < A){                                                 // <
        cout << "> failed" << endl;
    }

    if (B <= A){                                                // <=
        cout << "<= failed" << endl;
    }

    if (A > B){                                                 // >
        cout << "< failed" << endl;
    }

    if (A >= B){                                                // >=
        cout << ">= failed" << endl;
    }

    cout << "A + B = " << A+B << endl;                          // +

    cout << "B - A = " << B-A << endl;                          // -

    C -= C;                                                     // -=

    cout << "B * 0 == " << B * C << endl;                       // *

    B *= C;                                                     // *=

    if (!(B == zero)){
        cout << "B *= failed" << endl;
        cout << "B.sign == " << B.sign() << endl;
        cout << "zero.sign == " << zero.sign() << endl;
    }
}

/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa5
* Arithmetic.cpp
* Client file for BigInteger arithmetic testing
***************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
    ifstream in;
    ofstream out;
    string stringA, stringB, garbage;
    BigInteger A, B, C, D;

    // check comman line for correct number of arguments
    if (argc != 3){
        cerr << "Ussage: " << argv [0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing
    in.open(argv[1]);
    if (!in.is_open()){
        cerr << "Unable to open file " << argv [1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if (!out.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // read each line of the input file
    getline(in, stringA);
    getline(in, garbage);
    getline(in, stringB);

    A = BigInteger(stringA);
    B = BigInteger(stringB);
    C = BigInteger("3");
    D = BigInteger("2");

    out << A << endl << endl;
    out << B << endl << endl;
    out << A+B << endl << endl;
    out << A-B << endl << endl;
    out << A-A << endl << endl;
    out << (C*A)-(D*B) << endl << endl;
    out << A*B << endl << endl;
    out << A*A << endl << endl;
    out << B*B << endl << endl;
    C = BigInteger("9");
    D = BigInteger("16");
    out << (C*(A*A*A*A) + (D*(B*B*B*B*B))) << endl << endl;

    // close files
    in.close();
    out.close();

    return (EXIT_SUCCESS);
}

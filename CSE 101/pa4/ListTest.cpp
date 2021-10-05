/***************************************************************************************************
* Sean Brandon, spbrando
* 2021 Spring CSE101 pa4
* ListTest.cpp
* Tests List operations in isolation
***************************************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

int main(){
    List l1, l2, l3, l4;                                        // List()

    std::cout << "Emtpy list print: " << l1 << '\n';

    if(!l1.isEmpty()){                                          // isEmpty()
        std::cout << "isEmpty() failed" << '\n';
    }

    for(int i = 1; i < 11; i++){
        l1.insertBefore(i);                                     // insertBefore()
        l3.insertAfter(i);                                      // insertAfter()
    }

    l2 = List(l1);                                              // List(L)
    l4 = l3;                                                    // =

    if(!l1.equals(l2)){                                         // equals()
        std::cout << "equals() or List(L) failed" << '\n';
    }

    if(!(l3 == l4)){                                              // ==
        std::cout << "== or = failed" << '\n';
    }

    if(l1.size() != 10){                                        // size()
        std::cout << "size() failed" << '\n';
    }

    l1.moveFront();                                             // moveFront()

    if(l1.peekNext() != 1){                                     // peekNext()
        std::cout << "peekNext() failed" << '\n';
    }

    if(l1.moveNext() != 1){                                     // moveNext()
        std::cout << "moveNext() failed" << '\n';
    }

    l1.moveBack();                                              // moveBack()

    if(l1.peekPrev() != 10){                                    // peekPrev()
        std::cout << "peekPrev() failed" << '\n';
    }

    if(l1.position() != 10){                                    // position()
        std::cout << "position() failed" << '\n';
    }

    if(l1.movePrev() != 10){                                     // movePrev()
        std::cout << "movePrev() failed" << '\n';
    }

    l1.to_string();                                             // to_string()

    l4.clear();                                                 // clear()

    for (int i = 1; i < 11; i++){
        l4.insertBefore((i%2)+1);
    }

    l4.moveFront();

    l4.eraseAfter();                                            // eraseAfter()

    l4.moveBack();

    l4.eraseBefore();                                           // eraseBefore()

    if(l4.findPrev(1) != 6){                                    // findPrev()
        std::cout << "findPrev() failed" << '\n';
    }

    if(l4.findNext(2) != 8){                                   // findNext()
        std::cout << "findNext() failed" << '\n';
    }

    std::cout << "before cleanup(): " << l4 << '\n';              // <<

    l4.cleanup();                                               // cleanup()

    std::cout << "after cleanup(): " << l4 << '\n';

    std::cout << "l1 = " << l1 << '\n';

    std::cout << "l4 = " << l4 << '\n';

    List cat = l1.concat(l4);                                              // concat()

    std::cout << "l1 concat l4: " << cat << '\n';

}

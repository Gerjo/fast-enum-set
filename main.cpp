#include <cstdlib>
#include <iostream>
#include <cassert>

#include "EnumSet.h"
#include "ExampleEnum.h"

using std::cout;
using std::endl;



int main(int, char**) {

    EnumSet<ExampleEnum, unsigned> enumset;

    enumset.set(A);
    enumset.set(B);
    enumset.set(C);
    enumset.set(D);
    enumset.set(E);
    enumset.set(F);
    enumset.set(G);
    enumset.set(H);
    enumset.set(I);
    enumset.set(J);

    //assert(enumset.has(A));
    //assert(enumset.has(B));
    //assert(enumset.has(C));
    //assert(enumset.has(G));
    //assert(enumset.has(Z));

    cout << "sizeof " << sizeof(enumset) << endl;

    return 0;
}


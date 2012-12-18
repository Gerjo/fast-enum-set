#include <cstdlib>
#include <iostream>
#include <cassert>

#include <unistd.h>

#include "EnumSet.h"
#include "ExampleEnum.h"
#include "Stopwatch.h"

using std::cout;
using std::endl;



int main(int, char**) {
    Stopwatch sw;



    EnumSet<ExampleEnum, unsigned char> enumset;

    sw.start();
    enumset.set(A);
    enumset.set(B);
    enumset.set(C);
    enumset.set(D);
    enumset.set(E);
    enumset.set(F);
    enumset.set(G);
    enumset.set(H);
    enumset.set(I);
    enumset.set(J);sleep(1);
    enumset.set(G);
    enumset.set(Y);
    enumset.set(W);
    enumset.set(Z);
    cout << "Took: " << sw.pause().get() << endl;

    cout << endl;
    assert(enumset.has(A));
    assert(enumset.has(B));
    assert(enumset.has(C));
    assert(enumset.has(D));
    assert(enumset.has(E));
    assert(enumset.has(F));
    assert(enumset.has(G));
    assert(enumset.has(H));
    assert(enumset.has(I));
    assert(enumset.has(J));
    assert(enumset.has(G));
    assert(enumset.has(Y));
    assert(enumset.has(W));
    assert(enumset.has(Z));

    cout << "sizeof " << sizeof(enumset) << endl;

    int a = 9;
    int b = 5;
    int c = a / b;
    cout << c << endl;

    return 0;
}


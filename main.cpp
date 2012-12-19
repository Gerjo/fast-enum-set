#include <cstdlib>
#include <iostream>
#include <cassert>
#include <set>
#include <unistd.h>

#include "EnumSet.h"
#include "ExampleEnum.h"
#include "Stopwatch.h"

using std::cout;
using std::endl;



int main(int, char**) {
    Stopwatch sw;

    EnumSet<ExampleEnum, unsigned char> enumset;
    //std::set<ExampleEnum> enumset;

    sw.start();
    enumset.insert(A);
    enumset.insert(B);
    enumset.insert(C);
    enumset.insert(D);
    enumset.insert(E);
    enumset.insert(F);
    enumset.insert(G);
    enumset.insert(H);
    enumset.insert(I);
    enumset.insert(J);
    enumset.insert(G);
    enumset.insert(Y);
    enumset.insert(W);
    enumset.insert(Z);
    cout << "Setting took: " << sw.pause().get() << endl;

    cout << endl;

    sw.restart();

    cout << "Get assertion took: " << sw.pause().get() << endl;

    cout << "sizeof " << sizeof(enumset) << endl;

    int a = 9;
    int b = 5;
    int c = a / b;
    cout << c << endl;

    return 0;
}


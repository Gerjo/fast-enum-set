#include <cstdlib>
#include <iostream>
#include <cassert>
#include <set>
#include <unistd.h>
#include <array>

#include "EnumSet.h"
#include "ExampleEnum.h"
#include "Stopwatch.h"
#include "Interface.h"

using std::cout;
using std::endl;

struct StopWatchSet {
    Stopwatch orderedInsert;
    Stopwatch clear;
    Stopwatch randomInsert;
    Stopwatch randomGet;
    Stopwatch allocate;
    Stopwatch destruct;
};

// Forward declaration:
template <class T>
StopWatchSet runBenchmark(const int numLimit, const int repetitionCount);

void output(Stopwatch& a, Stopwatch& b, const std::string text) {
    double aDuration = a.get();
    double bDuration = b.get();
    double scale = 0;

    cout << std::fixed;
    cout.precision(5);
    cout << "[" << aDuration << "] vs [" << bDuration << "] ";

    cout.precision(2);
    if(aDuration < bDuration) {
        scale = aDuration / bDuration;
        cout << "EnumSet " << scale << "x faster.";

    } else {
        scale = bDuration / aDuration;
        cout << "EnumSet " << scale << "x faster.";
    }

    cout << " " << text << endl;
}

int main(int, char**) {
    int numLimit        = 1000;
    int repetitionCount = 1000;

    cout << "Test repeated " << repetitionCount << " times using a 0 to " << numLimit << " range of " << numLimit << " numbers." << endl;


    StopWatchSet t1 = runBenchmark<InterfaceEnumSet<int> >(numLimit, repetitionCount);
    StopWatchSet t2 = runBenchmark<InterfaceSet<int> >(numLimit, repetitionCount);

    output(t1.orderedInsert, t2.orderedInsert, "Inserting sequenced numbers");
    output(t1.clear, t2.clear, "clearing sequenced numbers");
    output(t1.randomInsert, t2.randomInsert, "Inserting random numbers");
    output(t1.randomGet, t2.randomGet, "Getting those random numbers");
    output(t1.allocate, t2.allocate, "Construction (new) time");
    output(t1.destruct, t2.destruct, "Destructor (delete) time");


    return 0;
}

template <typename T>
StopWatchSet runBenchmark(const int numLimit, const int repetitionCount) {
    StopWatchSet t;

    srand(73);

    for(int j = 0; j < repetitionCount; ++j) {

        // Build same random data. Fixed seed for deterministic results.
        int randomNums[numLimit];
        for(int i = 0; i < numLimit; ++i) {
            randomNums[i] = rand() % numLimit;
        }

        // bench block:
        t.allocate.start();
        T* meh = new T();
        t.allocate.pause();



        // bench block:
        t.orderedInsert.start();
        for(int i = 0; i < numLimit; ++i) {
            meh->set(i);
        }
        t.orderedInsert.pause();


        // bench block:
        t.clear.restart();
        meh->clear();
        t.clear.pause();


        // bench block:
        t.randomInsert.restart();
        for(int i = 0; i < numLimit; ++i) {
            meh->set(randomNums[i]);
        }
        t.randomInsert.pause();


        // bench block:
        t.randomGet.restart();
        for(int i = 0; i < numLimit; ++i) {
            if(true == meh->has(randomNums[i])) {
                // nop;
            }
        }
        t.randomGet.pause();


        // bench block:
        t.destruct.start();
        delete meh;
        t.destruct.pause();
    }

    return t;
}
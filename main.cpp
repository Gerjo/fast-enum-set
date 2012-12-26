#include <iostream>
#include <vector>

#include "StopwatchTuple.h"
#include "EnumSet.h"
#include "ExampleEnum.h"
#include "Stopwatch.h"
#include "Interface.h"
#include "InterfaceEnumSet.h"
#include "InterfaceStdSet.h"
#include "InterfaceStdMap.h"
#include "InterfaceStdBitSet.h"

using std::cout;
using std::endl;
using std::vector;


// Forward declaration:
template <class T>
void runBenchmark(StopwatchTuple& t, const int numLimit, const int repetitionCount);


int main(int, char**) {

    const int repetitionCount = 100;
    const int increments = 100;
    const int upperlimit = 5000;

    vector<StopwatchTuple> tuples;
    tuples.push_back(StopwatchTuple("EnumSet<int>"));
    tuples.push_back(StopwatchTuple("std::set<int>"));
    tuples.push_back(StopwatchTuple("std::map<int, bool>"));
    tuples.push_back(StopwatchTuple("std::bitset<5000>"));


    bool hasHeader = false;

    for(int numLimit = 0; numLimit < upperlimit; numLimit += increments) {
        for(StopwatchTuple& tuple : tuples) {
            tuple.resetClock();
        }

        {runBenchmark<InterfaceEnumSet<int> >(tuples[0], numLimit, repetitionCount);}
        {runBenchmark<InterfaceStdSet<int> >(tuples[1], numLimit, repetitionCount);}
        {runBenchmark<InterfaceStdMap<int> >(tuples[2], numLimit, repetitionCount);}
        {runBenchmark<InterfaceStdBitSet<int> >(tuples[3], numLimit, repetitionCount);}

        // The headers are only known after running the first time.
        if(!hasHeader) {
            cout << "size" << StopwatchTuple::delimiter << StopwatchTuple::getHeader(tuples);
            hasHeader = true;
        }

        cout << numLimit << StopwatchTuple::delimiter << StopwatchTuple::getRow(tuples);
    }

    return 0;
}

template <typename T>
void runBenchmark(StopwatchTuple& t, const int numLimit, const int repetitionCount) {

    srand(73);

    for(int j = 0; j < repetitionCount; ++j) {

        // Build some random data. Fixed seed for deterministic results.
        int* randomNums = new int[numLimit];
        for(int i = 0; i < numLimit; ++i) {
            randomNums[i] = rand() % numLimit;
        }

        // bench block:
        t["allocate"].resume();
        T* collection = new T();
        t["allocate"].pause();



        // bench block:
        t["orderedInsert"].resume();
        for(int i = 0; i < numLimit; ++i) {
            collection->set(i);
        }
        t["orderedInsert"].pause();


        // bench block:
        t["clear"].restart();
        collection->clear();
        t["clear"].pause();


        // bench block:
        t["randomInsert"].restart();
        for(int i = 0; i < numLimit; ++i) {
            collection->set(randomNums[i]);
        }
        t["randomInsert"].pause();


        // bench block:
        t["randomGet"].restart();
        for(int i = 0; i < numLimit; ++i) {
            if(true != collection->has(randomNums[i])) {
                throw std::string("Assertion failed, expected enum to be present, but it was not.");
            }
        }
        t["randomGet"].pause();

        // bench block:
        t["destruct"].resume();
        delete collection;
        t["destruct"].pause();

        // Tmp data, not interesting for benchmarking:
        delete[] randomNums;
    }
}
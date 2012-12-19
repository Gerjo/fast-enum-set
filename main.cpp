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

    std::string toExcel(const int numTimes = 0) {
        std::stringstream ss;
        ss.precision(5);
        ss << std::fixed;
        ss << numTimes << "\t";
        ss << orderedInsert.get() << "\t";
        ss << clear.get() << "\t";
        ss << randomInsert.get() << "\t";
        ss << randomGet.get() << "\t";
        ss << allocate.get() << "\t";
        ss << destruct.get() << "\t";
        ss << '\n';
        return ss.str();
    }
};

// Forward declaration:
template <class T>
StopWatchSet runBenchmark(const int numLimit, const int repetitionCount);

void output(Stopwatch& a, Stopwatch& b, const std::string text) {
    double aDuration = a.get();
    double bDuration = b.get();
    double ratio = 0;

    cout << std::fixed;
    cout.precision(5);
    cout << "[" << aDuration << "] vs [" << bDuration << "] ";

    cout.precision(2);
    if(aDuration < bDuration) {
        ratio = aDuration / bDuration;
        cout << "EnumSet " << ratio << "x faster.";

    } else {
        ratio = bDuration / aDuration;
        cout << "EnumSet " << ratio << "x faster.";
    }

    cout << " " << text << endl;
}


int main(int, char**) {
    //int limits[] = {0, 1, 10, 100, 1000, 10000};

    const int repetitionCount = 1000;

    std::stringstream excelcolumns;
    excelcolumns << "size";
    excelcolumns << "\t EnumSet-orderedinsert";
    excelcolumns << "\t std::set-orderedinsert";
    excelcolumns << "\t EnumSet-clear";
    excelcolumns << "\t std::set-clear";
    excelcolumns << "\t EnumSet-randomInsert";
    excelcolumns << "\t std::set-randomInsert";
    excelcolumns << "\t EnumSet-randomGet";
    excelcolumns << "\t std::set-randomGet";
    excelcolumns << "\t EnumSet-allocate";
    excelcolumns << "\t std::set-allocate";
    excelcolumns << "\t EnumSet-destruct";
    excelcolumns << "\t std::set-destruct";
    excelcolumns << endl;

    for(int numLimit = 0; numLimit < 5000; numLimit += 100) {
    //for(const int& numLimit : limits) {
        cout << "Test repeated " << repetitionCount << " times using a 0 to " << numLimit << " range of " << numLimit << " number(s)." << endl;

        StopWatchSet t1 = runBenchmark<InterfaceEnumSet<int> >(numLimit, repetitionCount);
        StopWatchSet t2 = runBenchmark<InterfaceSet<int> >(numLimit, repetitionCount);

        // Output per test, human readable:
        output(t1.orderedInsert, t2.orderedInsert, "Inserting sequenced numbers");
        output(t1.clear, t2.clear, "clearing sequenced numbers");
        output(t1.randomInsert, t2.randomInsert, "Inserting random numbers");
        output(t1.randomGet, t2.randomGet, "Getting those random numbers");
        output(t1.allocate, t2.allocate, "Construction (new) time");
        output(t1.destruct, t2.destruct, "Destructor (delete) time");
        cout << endl << endl;


        excelcolumns << numLimit << "\t";
        excelcolumns << t1.orderedInsert.get() << "\t";
        excelcolumns << t2.orderedInsert.get() << "\t";
        excelcolumns << t1.clear.get() << "\t";
        excelcolumns << t2.clear.get() << "\t";
        excelcolumns << t1.randomInsert.get() << "\t";
        excelcolumns << t2.randomInsert.get() << "\t";
        excelcolumns << t1.randomGet.get() << "\t";
        excelcolumns << t2.randomGet.get() << "\t";
        excelcolumns << t1.allocate.get() << "\t";
        excelcolumns << t2.allocate.get() << "\t";
        excelcolumns << t1.destruct.get() << "\t";
        excelcolumns << t2.destruct.get() << "\t";
        excelcolumns << endl;
    }


    cout << excelcolumns.str() << endl;

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
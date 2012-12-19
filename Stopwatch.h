/*
 * File:   Stopwatch.h
 * Author: gerjo
 *
 * Created on December 18, 2012, 9:21 PM
 */

#ifndef STOPWATCH_H
#define	STOPWATCH_H

#include <chrono>
#include <sstream>
#include <string>
#include <ctime>


//#define USE_STD_CLOCK 1

class Stopwatch {
public:
    Stopwatch() : name(""), _elapsed(0), _start(0) {

    }

    Stopwatch(std::string _name) : name(_name), _elapsed(0), _start(0) {

    }

    Stopwatch& start() {
        _start = now();
        return *this;
    }

    Stopwatch& pause() {
        _elapsed += now() - _start;
        return *this;
    }

    Stopwatch& restart() {
        start();
        _elapsed = 0;
        return *this;
    }

    double get() {
        #ifdef USE_STD_CLOCK
            return _elapsed / CLOCKS_PER_SEC;
        #else
            return _elapsed;
        #endif
    }

    std::string name;

private:
    double _elapsed;
    double _start;


    double now() {
        #ifdef USE_STD_CLOCK
            return clock();
        #else
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000000000.0;
        #endif
    }
};


#endif	/* STOPWATCH_H */


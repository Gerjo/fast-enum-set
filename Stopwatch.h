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

#ifdef _WIN32
#include <Windows.h>
#endif

//#define USE_STD_CLOCK 1
//#define USE_QUERY_PERFORMANCE_COUNTER 1

class Stopwatch {
public:
    Stopwatch() : name("unknown"), _elapsed(0), _start(0) {
    #ifdef USE_QUERY_PERFORMANCE_COUNTER
        initializeFrequency();
    #endif
    }

    Stopwatch(std::string _name) : name(_name), _elapsed(0), _start(0) {
    #ifdef USE_QUERY_PERFORMANCE_COUNTER
        initializeFrequency();
    #endif
    }

    Stopwatch& resume() {
        _start = now();
        return *this;
    }

    Stopwatch& pause() {
        _elapsed += now() - _start;
        return *this;
    }

    Stopwatch& restart() {
        resume();
        _elapsed = 0;
        return *this;
    }

    double elapsed() {
        #ifdef USE_STD_CLOCK
            return _elapsed / CLOCKS_PER_SEC;
        #elif USE_QUERY_PERFORMANCE_COUNTER
            return _elapsed / _frequency;
        #else
            return _elapsed;
        #endif
    }

    std::string name;

private:
#ifdef USE_QUERY_PERFORMANCE_COUNTER
    LARGE_INTEGER _startq;
    double _frequency;
#endif
    double _elapsed;
    double _start;

    double now() {
        #ifdef USE_STD_CLOCK
            return clock();
        #elif USE_QUERY_PERFORMANCE_COUNTER
            QueryPerformanceCounter(&_startq);
            return static_cast<double>(_startq.QuadPart);
        #else
            return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000000000.0;
        #endif
    }

#ifdef USE_QUERY_PERFORMANCE_COUNTER
    void initializeFrequency() {
        LARGE_INTEGER freq;
        QueryPerformanceFrequency(&freq);
        _frequency = freq.QuadPart;
    }
#endif
};


#endif	/* STOPWATCH_H */


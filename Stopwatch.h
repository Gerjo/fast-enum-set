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

using namespace std::chrono;

class Stopwatch {
public:

    Stopwatch& start() {
        _start = high_resolution_clock::now().time_point();
        return *this;
    }

    Stopwatch& pause() {
        _elapsed += _start - high_resolution_clock::now().time_point();
        return *this;
    }

    Stopwatch& restart() {
        start();
        _elapsed = high_resolution_clock::time_point(); // duration::zero
        return *this;
    }

    std::string get() {
        milliseconds meh = duration_cast<milliseconds>(_elapsed);

        std::stringstream ss;
        ss << meh.count();
        return ss.str();
    }

private:
    std::time_t _elapsed;
    std::time_t _start;
};


#endif	/* STOPWATCH_H */


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
    Stopwatch() : _elapsed(0), _start(0) {

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

    std::string get() {
        std::stringstream ss;
        ss << std::fixed << _elapsed;
        return ss.str();
    }

private:
    double _elapsed;
    double _start;

    double now() {
        // I couldn't get duration, time_point and clock to work just yet.
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() / 1000000000.0;
    }

};


#endif	/* STOPWATCH_H */


/*
 * File:   StopwatchTuple.h
 * Author: gerjo
 *
 * Created on December 19, 2012, 9:35 PM
 */

#ifndef STOPWATCHTUPLE_H
#define	STOPWATCHTUPLE_H

#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include "Stopwatch.h"

using std::endl;
using std::cout;

struct StopwatchTuple {
    const std::string name;

    StopwatchTuple(const std::string _name) : name(_name) {

    }

    void resetClock() {
        for(std::pair<const std::string, Stopwatch> pair : _stopwatches) {
            pair.second.restart();
        }
    }

    Stopwatch& operator[] (const std::string& key) {
        if(_stopwatches.find(key) == _stopwatches.end()) {
            _stopwatches.insert(Pair(key, Stopwatch(key)));
        }

        return _stopwatches.at(key);
    }

    std::map<std::string, Stopwatch>::iterator begin() {
        return _stopwatches.begin();
    }

    std::map<std::string, Stopwatch>::iterator end() {
        return _stopwatches.end();
    }

    std::string static getHeader(std::vector<StopwatchTuple>& tuples) {
        std::stringstream ss;

        if(!tuples.empty()) {
            for(Pair& stopwatch : tuples[0]) {
                for(StopwatchTuple& tuple : tuples) {
                    ss << stopwatch.first << "(" << tuple.name << ") " << delimiter;
                }
            }
        }

        ss << endl;

        return ss.str();
    }

    std::string static getRow(std::vector<StopwatchTuple>& tuples) {
        std::stringstream ss;

        ss << std::fixed;
        ss.precision(7);

        if(!tuples.empty()) {
            // For each stopwatch, ask each tuple.
            for(Pair& stopwatch : tuples[0]) {
                for(StopwatchTuple& tuple : tuples) {
                    ss << tuple[stopwatch.first].elapsed() << delimiter;
                }
            }
        }

        ss << endl;

        return ss.str();
    }

    static const char delimiter = '\t';

private:
    std::map<const std::string, Stopwatch> _stopwatches;
    typedef std::pair<const std::string, Stopwatch> Pair;
};


#endif	/* STOPWATCHTUPLE_H */


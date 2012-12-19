/*
 * File:   InterfaceStdBitSet.h
 * Author: gerjo
 *
 * Created on December 19, 2012, 7:04 PM
 */

#ifndef INTERFACESTDBITSET_H
#define	INTERFACESTDBITSET_H

#include "Interface.h"
#include <map>

template <class T>
class InterfaceStdMap : public Interface<T> {
public:
    virtual bool has(T item) {
        return _map.find(item) != _map.end();
    }

    virtual void set(T item) {
        _map[item] = true;
    }

    virtual void clear() {
        _map.clear();
    }
private:
    std::map<T, bool> _map;
};

#endif	/* INTERFACESTDBITSET_H */


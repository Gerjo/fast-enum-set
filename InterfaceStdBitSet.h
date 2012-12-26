/*
 * File:   InterfaceStdBitSet.h
 * Author: gerjo
 *
 * Created on December 21, 2012, 11:35 AM
 */

#ifndef INTERFACESTDBITSET_H
#define	INTERFACESTDBITSET_H

#include "Interface.h"
#include <bitset>

template <class T>
class InterfaceStdBitSet : public Interface<T> {
public:
    InterfaceStdBitSet() {

    }

    virtual bool has(T item) {
        return _bitset.test(item);
    }

    virtual void set(T item) {
        _bitset.set(item);
    }

    virtual void clear() {
        _bitset.reset();
    }

    private:
        std::bitset<5000> _bitset;
};

#endif	/* INTERFACESTDBITSET_H */


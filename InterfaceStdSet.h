/*
 * File:   InterfaceStdSet.h
 * Author: gerjo
 *
 * Created on December 19, 2012, 6:58 PM
 */

#ifndef INTERFACESTDSET_H
#define	INTERFACESTDSET_H

#include "Interface.h"
#include <set>

template <class T>
class InterfaceStdSet : public Interface<T> {
public:
    virtual bool has(T item) {
        return _set.find(item) != _set.end();
    }

    virtual void set(T item) {
        _set.insert(item);
    }

    virtual void clear() {
        _set.clear();
    }
private:
    std::set<T> _set;
};

#endif	/* INTERFACESTDSET_H */


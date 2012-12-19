#ifndef INTERFACE_H
#define	INTERFACE_H

#include <set>
#include "EnumSet.h"

template <class T>
class Interface {
public:
    Interface() { }
    virtual ~Interface() { }

    virtual bool has(T item) = 0;
    virtual void set(T item) = 0;
    virtual void clear() = 0;

};



template <class T>
class InterfaceSet : public Interface<T> {
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



template <class T>
class InterfaceEnumSet : public Interface<T> {
public:
    virtual bool has(T item) {
        return _set.has(item);
    }

    virtual void set(T item) {
        _set.set(item);
    }

    virtual void clear() {
        _set.clear();
    }
private:
    EnumSet<T, unsigned> _set;
};

#endif	/* INTERFACE_H */


/*
 * File:   InterfaceEnumSet.h
 * Author: gerjo
 *
 * Created on December 19, 2012, 6:58 PM
 */

#ifndef INTERFACEENUMSET_H
#define	INTERFACEENUMSET_H

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

#endif	/* INTERFACEENUMSET_H */


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

#endif	/* INTERFACE_H */


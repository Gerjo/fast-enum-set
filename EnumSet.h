#ifndef ENUMSET_H
#define	ENUMSET_H

#include <iostream>
#include <cmath>
#include <limits>
using std::endl;
using std::cout;

template <class T, typename T2>
class EnumSet {
public:
    typedef T VALUE_TYPE;
    typedef T2 STORAGE_TYPE;

    EnumSet() : _storage(0), _bitlimit(sizeof(STORAGE_TYPE) * BITS_IN_BYTE) {

    }

    EnumSet& set(VALUE_TYPE item, const bool state = true) {
        STORAGE_TYPE column = pow(2, static_cast<STORAGE_TYPE>(item) - 1);
        STORAGE_TYPE pre = column;
        STORAGE_TYPE row = 0;

        if(column > _bitlimit) {

            int64_t fact = _bitlimit;

            while(column > _bitlimit) {
              
                fact *= 2;
                column -= fact;

                ++row;
            }
        }

        cout << "Row: " << row << " column:" << column << " enum:" << item << endl;

        if(state) {
            _storage |= column;
        } else {
            _storage ^= column;
        }

        return *this;
    }

    bool has(const VALUE_TYPE& item) {
        STORAGE_TYPE column = 1 << static_cast<int>(item);
        return _storage & column;
    }

private:
    STORAGE_TYPE _storage;
    const unsigned _bitlimit;
    static const unsigned char BITS_IN_BYTE = 8;
};

#endif	/* ENUMSET_H */


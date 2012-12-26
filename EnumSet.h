#ifndef ENUMSET_H
#define	ENUMSET_H


#include <cmath>
#include <limits>
#include <cmath>

#include <iostream>
using std::endl;
using std::cout;


template <class T_VALUE, typename T_CONTAINER>
class EnumSet {
public:
    typedef T_VALUE VALUE_TYPE;
    typedef T_CONTAINER STORAGE_TYPE;

    EnumSet() : _allocated(0), _storage(nullptr), _bitlimit(sizeof(STORAGE_TYPE) * BITS_IN_BYTE) {

    }

    ~EnumSet() {
        delete[] _storage;
    }

    EnumSet& set(VALUE_TYPE item) {
        int row    = (item <_bitlimit) ? 0 : item / _bitlimit;
        int column = (row == 0) ? item : item - (row * _bitlimit);
        int bit    = 1 << column;

        if(row >= _allocated) {
            const int newSize = row + 1;
            STORAGE_TYPE* tmp = _storage;

            _storage = new STORAGE_TYPE[newSize];

            while(_allocated-- > 0) {
                _storage[_allocated] = tmp[_allocated];
            }

            delete[] tmp;
            _allocated = newSize;
        }

        _storage[row] |= bit;

        return *this;
    }

    bool has(const VALUE_TYPE& item) {
        int row    = (item <_bitlimit) ? 0 : item / _bitlimit;
        int column = (row == 0) ? item : item - (row * _bitlimit);
        int bit    = 1 << column;

        if(row > _allocated) {
            return false;
        }

        return _storage[row] & bit;
    }

    void clear() {
        delete[] _storage;
        _storage   = nullptr;
        _allocated = 0;
    }

private:
    int _allocated;
    STORAGE_TYPE* _storage;
    const int _bitlimit;
    static const unsigned char BITS_IN_BYTE = 8;
};

#endif	/* ENUMSET_H */


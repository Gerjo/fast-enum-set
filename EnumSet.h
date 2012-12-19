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

    EnumSet() : _storage(0), _bitlimit(sizeof(STORAGE_TYPE) * BITS_IN_BYTE) {
        allocated = 0;
        _storage  = nullptr;

    }

    ~EnumSet() {
        delete[] _storage;
    }

    EnumSet& set(VALUE_TYPE item) {
        STORAGE_TYPE row    = item / _bitlimit;
        STORAGE_TYPE column = item - (row * _bitlimit);
        STORAGE_TYPE bit    = 1 << column;

        if(row >= allocated) {
            //cout << "resize from " << allocated << " to " << (row + 1) << endl;
            const int newSize = row + 1;
            STORAGE_TYPE* tmp = _storage;

            _storage = new STORAGE_TYPE[newSize];

            while(allocated-- > 0) {
                _storage[allocated] = tmp[allocated];
            }

            delete[] tmp;
            allocated = newSize;
        }


        _storage[row] |= bit;

        //dump(_storage[row]);
        //cout << " Enum: " << item << " row: " << (int)row << " bit: " << (int)bit << " column: " << (int)column << endl;

        return *this;
    }

    bool has(const VALUE_TYPE& item) {
        STORAGE_TYPE row    = item / _bitlimit;
        STORAGE_TYPE column = item - (row * _bitlimit);
        STORAGE_TYPE bit    = 1 << column;

        if(row > allocated) {
            cout << "has:: out of bounds. False." << endl;
            return false;
        }

        //dump(_storage[row]);
        //cout << " has:: row: " << (int)row << " column: " << (int)column << " bit " << (int)bit << endl;

        return _storage[row] & bit;
    }

    void clear() {
        delete[] _storage;
        _storage  = nullptr;
        allocated = 0;
    }

private:
    STORAGE_TYPE allocated;
    STORAGE_TYPE* _storage;
    const unsigned _bitlimit;

    static const unsigned char BITS_IN_BYTE = 8;

    void dump(STORAGE_TYPE byte) {
        std::string formatted;

        char mask = 1;

        for (char i = 0; i < _bitlimit; ++i) {
            if (byte & mask) {
                formatted = "1" + formatted;
            } else {
                formatted = "0" + formatted;
            }

            if (i % 4 == 3) {
                formatted = " " + formatted;
            }

            mask <<= 1;
        }

        cout << formatted;
    }
};

#endif	/* ENUMSET_H */


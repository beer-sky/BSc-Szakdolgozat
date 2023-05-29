#ifndef INT_INT_MAP
#define INT_INT_MAP

#include <vector>
#include "lemon/maps.h"

class IntIntMap : public lemon::MapBase<int, int>
{
public:
    ///\e
    typedef int Key;
    ///\e
    typedef int Value;

    /// Constructor
    IntIntMap(int size = 0) { _data.resize(size, -1); }

    /// Gives back a default constructed element.
    Value operator[](const Key &key) const
    {
        return _data[key];
    }
    /// Gives back reference to a default constructed element.
    Value &operator[](const Key &key)
    {
        return _data[key];
    }

    /// Absorbs the value.
    void set(const Key &key, const Value &val)
    {
        if (int(_data.size()) < key)
        {
            _data.resize(key - _data.size(), -1);
        }
        _data[key] = val;
    }

private:
    std::vector<int> _data;
};

#endif // INT_INT_MAP
#ifndef MONOTONE_BUCKET_HEAP_H
#define MONOTONE_BUCKET_HEAP_H

#include <vector>

namespace lemon
{
    template <typename IM>
    class MonotoneBucketHeap
    {

    public:
        /// Type of the item-int map.
        typedef IM ItemIntMap;
        /// Type of the priorities.
        typedef int Prio;
        /// Type of the items stored in the heap.
        typedef typename ItemIntMap::Key Item;
        /// Type of the item-priority pairs.
        typedef std::pair<Item, Prio> Pair;

    public:
        /// \brief Type to represent the states of the items.
        ///
        /// Each item has a state associated to it. It can be "in heap",
        /// "pre-heap" or "post-heap". The latter two are indifferent from the
        /// heap's point of view, but may be useful to the user.
        ///
        /// The item-int map must be initialized in such way that it assigns
        /// \c PRE_HEAP (<tt>-1</tt>) to any element to be put in the heap.
        enum State
        {
            IN_HEAP = 0,   ///< = 0.
            PRE_HEAP = -1, ///< = -1.
            POST_HEAP = -2 ///< = -2.
        };

    public:
        /// \brief Constructor.
        ///
        /// Constructor.
        /// \param map A map that assigns \c int values to the items.
        /// It is used internally to handle the cross references.
        /// The assigned value must be \c PRE_HEAP (<tt>-1</tt>) for each item.
        explicit MonotoneBucketHeap(ItemIntMap &map, int number_of_buckets) : _iim(map), _minimum_key(0), _minimum_bucket(0)
        {
            _buckets.resize(number_of_buckets + 1, -1);
        }

        /// \brief The number of items stored in the heap.
        ///
        /// This function returns the number of items stored in the heap.
        int size() const { return _data.size(); }

        /// \brief Check if the heap is empty.
        ///
        /// This function returns \c true if the heap is empty.
        bool empty() const { return _data.empty(); }

        /// \brief Make the heap empty.
        ///
        /// This functon makes the heap empty.
        /// It does not change the cross reference map. If you want to reuse
        /// a heap that is not surely empty, you should first clear it and
        /// then you should set the cross reference map to \c PRE_HEAP
        /// for each item.
        void clear()
        {
            _data.clear();
            _buckets.clear();
            _minimum_key = 0;
            _minimum_bucket = 0;
        }

    private:
        void relocateLast(int idx)
        {
            if (idx + 1 < int(_data.size()))
            {
                _data[idx] = _data.back(); // ovverrides the idx-th element
                if (_data[idx].prev != -1) // if there is a previous element
                {
                    _data[_data[idx].prev].next = idx; // refresh its index
                }
                else // it is the first element of a bucket
                {
                    _buckets[_data[idx].bucket] = idx; // refresh its index
                }
                if (_data[idx].next != -1) // if there is a subsequent element
                {
                    _data[_data[idx].next].prev = idx; // refresh its index
                }
                _iim[_data[idx].item] = idx; // refresh _iim index
            }
            _data.pop_back();
        }

        void unlace(int idx) // from buckets list
        {
            if (_data[idx].prev != -1)
            {
                _data[_data[idx].prev].next = _data[idx].next;
            }
            else
            {
                _buckets[_data[idx].bucket] = _data[idx].next;
            }
            if (_data[idx].next != -1)
            {
                _data[_data[idx].next].prev = _data[idx].prev;
            }
        }

        void lace(int idx) // put item into the correct bucket
        {
            _data[idx].bucket = (_minimum_bucket + (_data[idx].key - _minimum_key)) % _buckets.size();
            _data[idx].next = _buckets[_data[idx].bucket];
            if (_data[idx].next != -1)
            {
                _data[_data[idx].next].prev = idx;
            }
            _buckets[_data[idx].bucket] = idx;
            _data[idx].prev = -1;
        }
        void find_min()
        {
            while (_buckets[_minimum_bucket] == -1)
            {
                ++_minimum_bucket %= _buckets.size(); // same as code below
                /*
                ++_minimum_bucket;
                if (_minimum_bucket == _bucket.size())
                    _minimum_bucket = 0;
                */
                ++_minimum_key;
            }
        }

    public:
        /// \brief Insert a pair of item and priority into the heap.
        ///
        /// This function inserts \c p.first to the heap with priority
        /// \c p.second.
        /// \param p The pair to insert.
        /// \pre \c p.first must not be stored in the heap.
        void push(const Pair &p)
        {
            push(p.first, p.second);
        }

        /// \brief Insert an item into the heap with the given priority.
        ///
        /// This function inserts the given item into the heap with the
        /// given priority.
        /// \param i The item to insert.
        /// \param p The priority of the item.
        /// \pre \e i must not be stored in the heap.
        void push(const Item &i, const Prio &p)
        {
            int idx = _data.size();
            _iim[i] = idx;
            _data.push_back(BucketItem(i, p));
            lace(idx);
        }

        /// \brief Return the item having minimum priority.
        ///
        /// This function returns the item having minimum priority.
        /// \pre The heap must be non-empty.
        Item top() const
        {
            const_cast<MonotoneBucketHeap<ItemIntMap> &>(*this).find_min();
            return _data[_buckets[_minimum_bucket]].item;
        }

        /// \brief The minimum priority.
        ///
        /// This function returns the minimum priority.
        /// \pre The heap must be non-empty.
        Prio prio() const
        {
            const_cast<MonotoneBucketHeap<ItemIntMap> &>(*this).find_min();
            return _minimum_key;
        }

        /// \brief Remove the item having minimum priority.
        ///
        /// This function removes the item having minimum priority.
        /// \pre The heap must be non-empty.
        void pop()
        {
            find_min();
            int idx = _buckets[_minimum_bucket];
            _iim[_data[idx].item] = -2;
            unlace(idx);
            relocateLast(idx);
        }

        /// \brief Remove the given item from the heap.
        ///
        /// This function removes the given item from the heap if it is
        /// already stored.
        /// \param i The item to delete.
        /// \pre \e i must be in the heap.
        void erase(const Item &i)
        {
            int idx = _iim[i];
            _iim[_data[idx].item] = -2;
            unlace(idx);
            relocateLast(idx);
        }

        /// \brief The priority of the given item.
        ///
        /// This function returns the priority of the given item.
        /// \param i The item.
        /// \pre \e i must be in the heap.
        Prio operator[](const Item &i) const
        {
            int idx = _iim[i];
            return _data[idx].key;
        }

        /// \brief Set the priority of an item or insert it, if it is
        /// not stored in the heap.
        ///
        /// This method sets the priority of the given item if it is
        /// already stored in the heap. Otherwise it inserts the given
        /// item into the heap with the given priority.
        /// \param i The item.
        /// \param p The priority.
        void set(const Item &i, const Prio &p)
        {
            int idx = _iim[i];
            if (idx < 0)
            {
                push(i, p);
            }
            else if (p < _data[idx].key)
            {
                decrease(i, p);
            }
            else if (p > _data[idx].key)
            {
                increase(i, p);
            }
        }

        /// \brief Decrease the priority of an item to the given value.
        ///
        /// This function decreases the priority of an item to the given value.
        /// \param i The item.
        /// \param p The priority.
        /// \pre \e i must be stored in the heap with priority at least \e p.
        void decrease(const Item &i, const Prio &p)
        {
            int idx = _iim[i];
            _data[idx].key = p;
            unlace(idx);
            lace(idx);
        }

        /// \brief Increase the priority of an item to the given value.
        ///
        /// This function increases the priority of an item to the given value.
        /// \param i The item.
        /// \param p The priority.
        /// \pre \e i must be stored in the heap with priority at most \e p.
        void increase(const Item &i, const Prio &p)
        {
            int idx = _iim[i];
            _data[idx].value = p;
            unlace(idx);
            lace(idx);
        }

        /// \brief Return the state of an item.
        ///
        /// This method returns \c PRE_HEAP if the given item has never
        /// been in the heap, \c IN_HEAP if it is in the heap at the moment,
        /// and \c POST_HEAP otherwise.
        /// In the latter case it is possible that the item will get back
        /// to the heap again.
        /// \param i The item.
        State state(const Item &i) const
        {
            int idx = _iim[i];
            if (idx >= 0)
                idx = 0;
            return State(idx);
        }

        /// \brief Set the state of an item in the heap.
        ///
        /// This function sets the state of the given item in the heap.
        /// It can be used to manually clear the heap when it is important
        /// to achive better time complexity.
        /// \param i The item.
        /// \param st The state. It should not be \c IN_HEAP.
        void state(const Item &i, State st)
        {
            switch (st)
            {
            case POST_HEAP:
            case PRE_HEAP:
                if (state(i) == IN_HEAP)
                {
                    erase(i);
                }
                _iim[i] = st;
                break;
            case IN_HEAP:
                break;
            }
        }

    private:
        struct BucketItem
        {
            BucketItem(const Item &_item, int _key)
                : item(_item), key(_key) {}

            Item item;
            int key;
            int prev, next, bucket;
        };

        ItemIntMap &_iim;
        std::vector<int> _buckets;
        std::vector<BucketItem> _data;
        mutable int _minimum_key;
        mutable int _minimum_bucket;
    }; // class MonotoneBucketHeap
} // namespace lemon

#endif // MONOTONE_BUCKET_HEAP
/* -*- mode: C++; indent-tabs-mode: nil; -*-
 *
 */

#ifndef LEMON_RADIX_HEAP_3_H
#define LEMON_RADIX_HEAP_3_H

///\ingroup heaps
///\file
///\brief Radix heap implementation.

#include <vector>
#include <lemon/error.h>
#include <limits>

namespace lemon
{

    /// \ingroup heaps
    ///
    /// \brief Radix heap data structure.
    ///
    /// This class implements the \e radix \e heap data structure.
    /// It practically conforms to the \ref concepts::Heap "heap concept",
    /// but it has some limitations due its special implementation.
    /// The type of the priorities must be \c int and the priority of an
    /// item cannot be decreased under the priority of the last removed item.
    ///
    /// \tparam IM A read-writable item map with \c int values, used
    /// internally to handle the cross references.
    template <typename IM>
    class RadixHeap3
    {

    public:
        /// Type of the item-int map.
        typedef IM ItemIntMap;
        /// Type of the priorities.
        typedef int Prio;
        /// Type of the items stored in the heap.
        typedef typename ItemIntMap::Key Item;

        /// \brief Exception thrown by RadixHeap.
        ///
        /// This exception is thrown when an item is inserted into a
        /// RadixHeap with a priority smaller than the last erased one.
        /// \see RadixHeap
        class PriorityUnderflowError : public Exception
        {
        public:
            virtual const char *what() const throw()
            {
                return "lemon::RadixHeap::PriorityUnderflowError";
            }
        };

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

        const int intsize = sizeof(int) * 8;
        int msb(const int &n) const
        {
            return intsize - __builtin_clz(n);
        }

    private:
        struct RadixItem
        {
            int prev, next, box;
            Item item;
            int prio;
            RadixItem(Item _item, int _prio) : item(_item), prio(_prio) {}
        };

        std::vector<RadixItem> _data;
        std::vector<int> _boxes; // first element of the box
        int _min, _capacity;

        ItemIntMap &_iim;

    public:
        /// \brief Constructor.
        ///
        /// Constructor.
        /// \param map A map that assigns \c int values to the items.
        /// It is used internally to handle the cross references.
        /// The assigned value must be \c PRE_HEAP (<tt>-1</tt>) for each item.
        /// \param minimum The initial minimum value of the heap.
        /// \param capacity The initial capacity of the heap.
        RadixHeap3(ItemIntMap &map, int minimum = 0, int capacity = 0)
            : _iim(map)
        {
            int number_of_boxes = msb(capacity) + 2;
            _boxes.resize(number_of_boxes, -1);
            _min = minimum;
            _capacity = capacity;
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
        /// \param minimum The minimum value of the heap.
        /// \param capacity The capacity of the heap.
        void clear(int minimum = 0, int capacity = 0) // max edge weight <= capacity
        {
            _data.clear();
            _boxes.clear();
            int number_of_boxes = msb(capacity) + 2;
            _boxes.resize(number_of_boxes, -1);
            _min = minimum;
            _capacity = capacity;
        }

    private:
        // Remove item from the box list
        void remove(int index)
        {
            if (_data[index].prev >= 0)
            {
                _data[_data[index].prev].next = _data[index].next;
            }
            else
            {
                _boxes[_data[index].box] = _data[index].next;
            }
            if (_data[index].next >= 0)
            {
                _data[_data[index].next].prev = _data[index].prev;
            }
        }

        // Insert item into the box list
        void insert(int box, int index)
        {
            if (_boxes[box] == -1) // if the box is empty
            {
                _boxes[box] = index;
                _data[index].next = _data[index].prev = -1;
            }
            else
            {
                _data[index].next = _boxes[box];
                _data[_boxes[box]].prev = index;
                _data[index].prev = -1;
                _boxes[box] = index;
            }
            _data[index].box = box;
        }

        int findBox(int pr) const
        {
            if (pr == _min)
                return 0;
            return std::min(msb(pr ^ _min), int(_boxes.size()) - 1);
        }

        void replaceItem(int index)
        {
            remove(index);
            int box = findBox(_data[index].prio);
            insert(box, index);
        }

        // Move an item up into the proper box. (for set and increase)
        void bubbleUp(int index)
        {
            if (_data[index].box > findBox(_data[index].prio))
                return;
            replaceItem(index);
        }

        // Move an item down into the proper box (for set and decrease)
        void bubbleDown(int index)
        {
            if (_data[index].box < findBox(_data[index].prio))
                return;
            if (_data[index].prio < _min)
                throw PriorityUnderflowError();
            replaceItem(index);
        }

        // Find the first non-empty box
        int findFirst()
        {
            int first = 0;
            while (_boxes[first] == -1)
                ++first;
            return first;
        }

        // Gives back the minimum priority of the given box
        int minValue(int box)
        {
            int min = _data[_boxes[box]].prio;
            for (int k = _boxes[box]; k != -1; k = _data[k].next)
            {
                if (_data[k].prio < min)
                    min = _data[k].prio;
            }
            return min;
        }

        // Rearrange the items of the heap and make the first box non-empty
        void moveDown()
        {
            int box = findFirst();
            if (box == 0)
                return;
            _min = minValue(box);

            int curr = _boxes[box], next;
            while (curr != -1)
            {
                next = _data[curr].next;
                replaceItem(curr);
                curr = next;
            }
        }

        // remove the index from _data
        void relocateLast(int index)
        {
            if (index != int(_data.size()) - 1)
            {
                _data[index] = _data.back();
                if (_data[index].prev != -1)
                {
                    _data[_data[index].prev].next = index;
                }
                else
                {
                    _boxes[_data[index].box] = index;
                }
                if (_data[index].next != -1)
                {
                    _data[_data[index].next].prev = index;
                }
                _iim[_data[index].item] = index;
            }
            _data.pop_back();
        }

    public:
        /// \brief Insert an item into the heap with the given priority.
        ///
        /// This function inserts the given item into the heap with the
        /// given priority.
        /// \param i The item to insert.
        /// \param p The priority of the item.
        /// \pre \e i must not be stored in the heap.
        /// \warning This method may throw an \c UnderFlowPriorityException.
        void push(const Item &i, const Prio &p)
        {
            if (p < _min)
                throw PriorityUnderflowError();
            int n = _data.size();
            _iim.set(i, n);
            _data.push_back(RadixItem(i, p));
            int box = findBox(p);
            insert(box, n);
        }

        /// \brief Return the item having minimum priority.
        ///
        /// This function returns the item having minimum priority.
        /// \pre The heap must be non-empty.
        Item top() const
        {
            const_cast<RadixHeap3<ItemIntMap> &>(*this).moveDown();
            return _data[_boxes[0]].item;
        }

        /// \brief The minimum priority.
        ///
        /// This function returns the minimum priority.
        /// \pre The heap must be non-empty.
        Prio prio() const
        {
            const_cast<RadixHeap3<ItemIntMap> &>(*this).moveDown();
            return _data[_boxes[0]].prio;
        }

        /// \brief Remove the item having minimum priority.
        ///
        /// This function removes the item having minimum priority.
        /// \pre The heap must be non-empty.
        void pop()
        {
            moveDown();
            int index = _boxes[0];
            _iim[_data[index].item] = POST_HEAP;
            remove(index);
            relocateLast(index);
        }

        /// \brief Remove the given item from the heap.
        ///
        /// This function removes the given item from the heap if it is
        /// already stored.
        /// \param i The item to delete.
        /// \pre \e i must be in the heap.
        void erase(const Item &i)
        {
            int index = _iim[i];
            _iim[i] = POST_HEAP;
            remove(index);
            relocateLast(index);
        }

        /// \brief The priority of the given item.
        ///
        /// This function returns the priority of the given item.
        /// \param i The item.
        /// \pre \e i must be in the heap.
        Prio operator[](const Item &i) const
        {
            int idx = _iim[i];
            return _data[idx].prio;
        }

        /// \brief Set the priority of an item or insert it, if it is
        /// not stored in the heap.
        ///
        /// This method sets the priority of the given item if it is
        /// already stored in the heap. Otherwise it inserts the given
        /// item into the heap with the given priority.
        /// \param i The item.
        /// \param p The priority.
        /// \pre \e i must be in the heap.
        /// \warning This method may throw an \c UnderFlowPriorityException.
        void set(const Item &i, const Prio &p)
        {
            int idx = _iim[i];
            if (idx < 0)
            {
                push(i, p);
            }
            else if (p >= _data[idx].prio)
            {
                _data[idx].prio = p;
                bubbleUp(idx);
            }
            else
            {
                _data[idx].prio = p;
                bubbleDown(idx);
            }
        }

        /// \brief Decrease the priority of an item to the given value.
        ///
        /// This function decreases the priority of an item to the given value.
        /// \param i The item.
        /// \param p The priority.
        /// \pre \e i must be stored in the heap with priority at least \e p.
        /// \warning This method may throw an \c UnderFlowPriorityException.
        void decrease(const Item &i, const Prio &p)
        {
            int idx = _iim[i];
            _data[idx].prio = p;
            bubbleDown(idx);
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
            _data[idx].prio = p;
            bubbleUp(idx);
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
            int s = _iim[i];
            if (s >= 0)
                s = 0;
            return State(s);
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

    }; // class RadixHeap

} // namespace lemon

#endif // LEMON_RADIX_HEAP_3

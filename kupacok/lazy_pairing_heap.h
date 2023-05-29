#ifndef LEMON_LAZY_PAIRING_HEAP_H
#define LEMON_LAZY_PAIRING_HEAP_H

///\file
///\ingroup heaps
///\brief Pairing heap implementation.

#include <vector>
#include <iostream>

namespace lemon
{

#ifdef DOXYGEN
    template <typename PR, typename IM, typename CMP>
#else
    template <typename PR, typename IM, typename CMP = std::less<PR>>
#endif
    class LazyPairingHeap
    {
    public:
        /// Type of the item-int map.
        typedef IM ItemIntMap;
        /// Type of the priorities.
        typedef PR Prio;
        /// Type of the items stored in the heap.
        typedef typename ItemIntMap::Key Item;
        /// Functor type for comparing the priorities.
        typedef CMP Compare;

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

    private:
        struct Node
        {
            Item name;
            Prio prio;
            int parent;
            int left_child;
            int right_child;

            Node(Item _name, Prio _prio) : parent(-1), left_child(-1), right_child(-1)
            {
                name = _name;
                prio = _prio;
            }
        };

        std::vector<Node> _data; // this is always growing, we never delete from it like in the other heaps with the "relocate_last" method
        Compare _comp;
        ItemIntMap &_iim;
        int _root; // root of the heap tree
        int _min;  // the minimum value. Can be in the aux area
        int _size; // size of the heap

    public:
        /// \brief Constructor.
        ///
        /// Constructor.
        /// \param map A map that assigns \c int values to the items.
        /// It is used internally to handle the cross references.
        /// The assigned value must be \c PRE_HEAP (<tt>-1</tt>) for each item.
        explicit LazyPairingHeap(ItemIntMap &map)
            : _iim(map), _root(0), _min(0), _size(0)
        {
        }

        /// \brief Constructor.
        ///
        /// Constructor.
        /// \param map A map that assigns \c int values to the items.
        /// It is used internally to handle the cross references.
        /// The assigned value must be \c PRE_HEAP (<tt>-1</tt>) for each item.
        /// \param comp The function object used for comparing the priorities.
        LazyPairingHeap(ItemIntMap &map, const Compare &comp)
            : _comp(comp), _iim(map), _root(0), _min(0), _size(0) {}

        /// \brief The number of items stored in the heap.
        ///
        /// This function returns the number of items stored in the heap.
        int size() const { return _size; }

        /// \brief Check if the heap is empty.
        ///
        /// This function returns \c true if the heap is empty.
        bool empty() const { return _size == 0; }

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
            _min = 0;
            _root = 0;
            _size = 0;
        }

        /// \brief Insert an item into the heap with the given priority.
        ///
        /// This function inserts the given item into the heap with the
        /// given priority.
        /// \param item The item to insert.
        /// \param value The priority of the item.
        /// \pre \e item must not be stored in the heap.
        void push(const Item &item, const Prio &value)
        {
            int i = _data.size();
            _iim.set(item, i);
            Node new_node(item, value);
            _data.push_back(new_node);
            if (_size == 0)
            {
                _root = i;
                _min = i;
            }
            else
            {
                add_to_aux(i);
                if (_comp(_data[i].prio, _data[_min].prio))
                    _min = i;
            }

            ++_size;
        }

        /// \brief Return the item having minimum priority.
        ///
        /// This function returns the item having minimum priority.
        /// \pre The heap must be non-empty.
        Item
        top() const
        {
            return _data[_min].name;
        }

        /// \brief The minimum priority.
        ///
        /// This function returns the minimum priority.
        /// \pre The heap must be non-empty.
        const Prio &prio() const { return _data[_min].prio; }

        /// \brief The priority of the given item.
        ///
        /// This function returns the priority of the given item.
        /// \param item The item.
        /// \pre \e item must be in the heap.
        const Prio &operator[](const Item &item) const
        {
            return _data[_iim[item]].prio;
        }

        /// \brief Remove the item having minimum priority.
        ///
        /// This function removes the item having minimum priority.
        /// \pre The heap must be non-empty.
        void pop()
        {
            // if the auxilary area is not empty, fix it
            if (_data[_root].right_child != -1)
            {
                while (_data[_data[_root].right_child].right_child != -1)
                {
                    int node_1 = _data[_root].right_child;
                    // link them pairwise
                    do
                    {
                        int node_2 = _data[node_1].right_child;
                        if (node_2 != -1)
                        {
                            node_1 = _data[link(node_1, node_2)].right_child;
                        }
                        // if the last node doesn't have a pair, then make it the fist node
                        else
                        {
                            _data[_data[node_1].parent].right_child = -1;
                            _data[node_1].parent = _root;
                            _data[node_1].right_child = _data[_root].right_child;
                            _data[_root].right_child = node_1;
                            node_1 = -1;
                        }
                    } while (node_1 != -1);
                }
                // Link the heap and the auxilary area
                _root = link(_root, _data[_root].right_child);
            }
            // fix the heap in 2 phases
            --_size;
            _iim[_data[_root].name] = POST_HEAP;

            if (_size == 0)
                return;
            _root = _data[_root].left_child;
            _data[_root].parent = -1;

            if (_data[_root].right_child != -1)
            {
                // First phase
                int last_node = -1;
                int node_1 = _data[_root].right_child;
                do
                {
                    int node_2 = _data[node_1].right_child;
                    if (node_2 != -1)
                    {
                        last_node = link(node_1, node_2);
                        node_1 = _data[last_node].right_child;
                    }
                    else
                    {
                        last_node = node_1;
                        node_1 = -1;
                    }

                } while (node_1 != -1);

                // Second phase
                while (_data[last_node].parent != _root)
                {
                    last_node = link(_data[last_node].parent, last_node);
                }
                _root = link(_root, _data[_root].right_child);
            }
            _min = _root;
        }

        void decrease(Item item, const Prio &value)
        {
            int i = _iim[item];
            _data[i].prio = value;
            if (_comp(_data[i].prio, _data[_min].prio)) // refresh min
                _min = i;
            if (i == _root) // we can decrease the root
                return;

            if (_comp(value, _data[_data[i].parent].prio)) // if the new priority is less then it's parent's
            {
                cut(i);
                add_to_aux(i);
            }
        }

    private:
        void cut(int i)
        {
            // connect the heap to the right subtree
            int p = _data[i].parent;
            if (i == _data[p].left_child) // if i was a left child
                _data[p].left_child = _data[i].right_child;
            else
                _data[p].right_child = _data[i].right_child;

            // connect the right subtree to the heap
            if (_data[i].right_child != -1)
                _data[_data[i].right_child].parent = _data[i].parent;
        }

        void add_to_aux(int i)
        {
            _data[i].parent = _root;
            _data[i].right_child = _data[_root].right_child;

            if (_data[_root].right_child != -1)
                _data[_data[_root].right_child].parent = i;
            _data[_root].right_child = i;
        }

        int link(int u, int v)
        {
            if (!_comp(_data[v].prio, _data[u].prio)) // if u.prio <= v.prio
            {
                _data[u].right_child = _data[v].right_child;
                if (_data[v].right_child != -1)
                    _data[_data[v].right_child].parent = u;

                _data[v].right_child = _data[u].left_child;
                if (_data[u].left_child != -1)
                    _data[_data[u].left_child].parent = v;

                _data[u].left_child = v;
                _data[v].parent = u;
                return u;
            }
            else
            {
                _data[u].right_child = _data[v].left_child;
                if (_data[v].left_child != -1)
                    _data[_data[v].left_child].parent = u;

                if (_data[u].parent != -1)
                {
                    if (_data[_data[u].parent].right_child == u)
                        _data[_data[u].parent].right_child = v;
                    else
                        _data[_data[u].parent].left_child = v;
                }
                _data[v].parent = _data[u].parent;
                _data[u].parent = v;
                _data[v].left_child = u;
                return v;
            }
        }
    };

} // namespace lemon

#endif // LEMON_LAZY_PAIRING_HEAP_H

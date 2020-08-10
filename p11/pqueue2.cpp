// FILE: pqueue2.cxx
// IMPLEMENTS: PriorityQueue (See pqueue2.h for documentation.)
// INVARIANT for the PriorityQueue Class:
//   1. The member variable many_items is the number of items in the
//      PriorityQueue.
//   2. The items themselves are stored in the member variable heap,
//      which is a partially filled array organized to follow the usual
//      heap storage rules from Chapter 11 of the class notes.
// NOTE: Private helper functions are implemented at the bottom of this
// file along with their precondition/postcondition contracts.
 
#include <cassert>    // Provides assert()
#include <iomanip>    // Provides setw
#include <iostream>   // Provides cin, cout
#include <cmath>      // Provides log2
#include "pqueue2.h"
using namespace std;

PriorityQueue::PriorityQueue() {
    many_items = 0;
}

void PriorityQueue::insert(const Item& entry, unsigned int priority) 
/* Pseudocode for Adding an Entry
1. Place the new entry in the heap in the first available location. This keeps the structure as a
complete binary tree, but it might no longer be a heap since the new entry’s parent might be
less than the new entry.
2. while (the new entry’s parent is less than the new entry) Swap the new entry with its parent.
Notice that the process in Step 2 will stop when the new entry reaches the root, or when the new
entry’s parent is no longer less than the new entry. */
{
    assert(many_items < CAPACITY);
    heap[many_items++] = OneItemInfo(entry, priority);
    for(int i = many_items - 1; i != 0 && priority > parent_priority(i); i = parent_index(i))
        swap_with_parent(i);
}

PriorityQueue::Item PriorityQueue::get_front()
/* Pseudocode for Removing an Entry
1. Copy the entry at the root of the heap to the variable that is used to return a value.
2. Copy the last entry in the deepest level to the root, and then take this last node out of the tree.
This entry is called the “out-of-place” entry.
3. while (the out-of-place entry is less than one of its children) Swap the out-of-place entry with its highest child.
4. Return the answer that was saved in Step 1.
Notice that the process in Step 3 will stop when the out-of-place entry reaches a leaf or when the
out-of-place entry is no longer less than one of its children. */
{
    assert(!is_empty());
    Item front = heap[0].data;
    heap[0] = heap[--many_items];
    for(int i = 0; i < many_items && !is_leaf(i) && heap[i].priority < big_child_priority(i); i = big_child_index(i))
        swap_with_parent(big_child_index(i));
    return front;
}

bool PriorityQueue::is_leaf(size_t i) const
// Precondition: (i < many_items)
// Postcondition: If heap[i] has no children in the heap, then the function
// returns true. Otherwise the function returns false.
{
    assert(i < many_items);
    return 2 * i + 1 >= many_items;
}

size_t PriorityQueue::parent_index(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the index of the parent of heap[i].
{
    assert(i > 0 && i < many_items);
    return (i - 1) / 2;
}

unsigned int PriorityQueue::parent_priority(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the priority of the parent of heap[i].
{
    assert(i > 0 && i < many_items);
    return heap[parent_index(i)].priority;
}

size_t PriorityQueue::big_child_index(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value is the index of one of heap[i]'s children.
// This is the child with the larger priority.
{
    assert(!is_leaf(i));
    size_t left_child = 2 * i + 1, right_child = 2 * i + 2;
    return heap[left_child].priority > heap[right_child].priority ? left_child : right_child;
}

unsigned int PriorityQueue::big_child_priority(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value heap[big_child_index(i)].priority
{
    assert(!is_leaf(i));
    return heap[big_child_index(i)].priority;
}

void PriorityQueue::swap_with_parent(size_t i)
// Precondition: (i > 0) && (i < many_items)
// Postcondition: heap[i] has been swapped with heap[parent_index(i)]
{
    assert(i > 0 && i < many_items);
    OneItemInfo temp = heap[i];
    heap[i] = heap[parent_index(i)];
    heap[parent_index(i)] = temp;
}

void PriorityQueue::print_tree(const char message[ ], size_t i) const
// Postcondition: If the message is non-empty, then that has been written
// to cout. After the message, the portion of the heap with root at node
// node i has been written to the screen. Each node's data is indented
// 4*d, where d is the depth of the node.
// NOTE: The default argument for message is the empty string, and the
// default argument for i is zero. For example, to print the entire
// tree of a PriorityQueue p, with a message of "The tree:", you can call:
//     p.print_tree("The tree:");
// This call uses the default argument i=0, which prints the whole tree.
{
    const char NO_MESSAGE[ ] = "";
    size_t depth;

    if (message[0] != '\0')
        cout << message << endl;

    if (i >= many_items)
        cout << "NO NODES." << endl;
    else
    {
        depth = int(log(double(i+1))/log(2.0));
        cout << setw(depth*4) << "";
        cout << heap[i].data;
        cout << " (priority " << heap[i].priority << ")" << endl;
        if (2*i + 1 < many_items)
            print_tree(NO_MESSAGE, 2*i + 1);
        if (2*i + 2 < many_items)
            print_tree(NO_MESSAGE, 2*i + 2);
    }
}

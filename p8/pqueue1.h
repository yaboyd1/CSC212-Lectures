// FILE: pqueue1.h
// CLASS PROVIDED: PriorityQueue (a priority queue of items)
//
// TYPEDEF for the PriorityQueue class:
//   typedef _____ Item 
//     The type Item is the data type of the items in the Priority Queue.
//     It may be any of the C++ built-in types (int, char, etc.), or a class 
//     with a default constructor, a copy constructor, and assignment operator.
//
// CONSTRUCTOR for the PriorityQueue class:
//   PriorityQueue( )
//     Postcondition: The PriorityQueue has been initialized with no Items.
//
// MODIFICATION MEMBER FUNCTIONS for the PriorityQueue class:
//   void insert(const Item& entry, unsigned int priority)
//     Postcondition: A new copy of entry has been inserted with the specified
//     priority.
//
//   Item get_front( )
//     Precondition: size( ) > 0.
//     Postcondition: The highest priority item has been returned and has been
//     removed from the PriorityQueue. (If several items have equal priority,
//     then the one that entered first will come out first.)
//
// CONSTANT MEMBER FUNCTIONS for the PriorityQueue class:
//   size_t size( ) const
//     Postcondition: Return value is the total number of items in the
//     PriorityQueue.
//
//   bool is_empty( ) const
//     Postcondition: Return value is true if the PriorityQueue is empty.
//
// VALUE SEMANTICS for the PriorityQueue class:
//   Assignments and the copy constructor may be used with
//   PriorityQueue objects

#ifndef PQUEUE_H
#define PQUEUE_H
#include <stdlib.h> // Provides size_t

struct Node; // Node structure for PQ with basic constructor

/* NOTE: I added a few helper functions:
 *   copy()  : Used in copy constructor and assignment operator
 *   clear() : Used in deconstructor and assignment operator
 *   insert_front() : Used in insert()
 *   insert_after() : Used in insert()
 *   remove_front() : Used in clear()
 */

class PriorityQueue {
public:
    // TYPEDEF
    typedef int Item;

    // CONSTRUCTOR and BIG THREE
    PriorityQueue();
    PriorityQueue(const PriorityQueue& source);
    ~PriorityQueue();
    void operator =(const PriorityQueue& source);
    void copy(const PriorityQueue& source); // O(n): Copies items of one PQ to another

    // MODIFICATION MEMBER FUNCTION 
    void insert(const Item& entry, unsigned int priority); // O(n): Inserts item based on priority
    Item get_front(); // O(1): Removes and returns first item

    void insert_front(const Item& entry, unsigned int priority); // O(1): Inserts at the start of the PQ
    void insert_after(Node* prev, const Item& entry, unsigned int priority); // O(1): Inserts after another item

    void remove_front(); // O(1): Removes first item
    void clear(); // O(n): Clears all the items in the PQ

    // CONSTANT MEMBER FUNCTIONS
    size_t size() const {return many_nodes;}
    bool is_empty() const {return head == NULL;}
private:
    Node *head; // Linked List: Highest priority at head, lowest at tail
    size_t many_nodes; // How many nodes there are in the linked list
};

struct Node {
    PriorityQueue::Item data; // Data value of node
    unsigned int priority;    // Priority value of node used to sort PQ
    Node *link;               // Pointer to the next node
    Node(PriorityQueue::Item d = PriorityQueue::Item(), unsigned int p = 0, Node* l = NULL) : data(d), priority(p), link(l) {}
};

#endif
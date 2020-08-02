// FILE: sequence3.h
// CLASS PROVIDED: sequence (part of the namespace main_savitch_5)
// This is the header file for the project described in Section 5.4
// of "Data Structures and Other Objects Using C++"
// This is called "sequence3" because some students already implemented
// sequence1 (with a fixed array) and sequence2 (with a dynamic array).
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class:
//   typedef ____ value_type
//     sequence::value_type is the data type of the items in the sequence. It
//     may be any of the C++ built-in types (int, char, etc.), or a class with a
//     default constructor, an assignment operator, and a copy constructor.
//
//   typedef ____ size_type
//     sequence::size_type is the data type of any variable that keeps track of
//     how many items are in a sequence.
//
// CONSTRUCTOR for the sequence class:
//   sequence( )
//     Postcondition: The sequence has been initialized as an empty sequence.
//
// MODIFICATION MEMBER FUNCTIONS for the sequence class:
//   void start( )
//     Postcondition: The first item on the sequence becomes the current item
//     (but if the sequence is empty, then there is no current item).
//
//   void advance( )
//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
//
//   void insert(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence
//     before the current item. If there was no current item, then the new entry 
//     has been inserted at the front of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void attach(const value_type& entry)
//     Postcondition: A new copy of entry has been inserted in the sequence after
//     the current item. If there was no current item, then the new entry has 
//     been attached to the end of the sequence. In either case, the newly
//     inserted item is now the current item of the sequence.
//
//   void remove_current( )
//     Precondition: is_item returns true.
//     Postcondition: The current item has been removed from the sequence, and
//     the item after this (if there is one) is now the new current item.
//
// CONSTANT MEMBER FUNCTIONS for the sequence class:
//   size_type size( ) const
//     Postcondition: The return value is the number of items in the sequence.
//
//   bool is_item( ) const
//     Postcondition: A true return value indicates that there is a valid
//     "current" item that may be retrieved by activating the current
//     member function (listed below). A false return value indicates that
//     there is no valid current item.
//
//   value_type current( ) const
//     Precondition: is_item( ) returns true.
//     Postcondition: The item returned is the current item in the sequence.
//
// VALUE SEMANTICS for the sequence class:
//    Assignments and the copy constructor may be used with sequence objects.

#ifndef MAIN_SAVITCH_SEQUENCE3_H
#define MAIN_SAVITCH_SEQUENCE3_H
#include <cstdlib>  // Provides size_t
#include "node2.h"  // Provides node class

namespace main_savitch_6B {
    template <class Item>
    class sequence {
    public:
        // TYPEDEFS and MEMBER CONSTANTS
        typedef Item value_type;
        typedef std::size_t size_type;
        // CONSTRUCTORS and DESTRUCTOR
        sequence();
        sequence(const sequence<Item>& source); /* O(n): Copies items into new sequence */
        ~sequence(); /* O(n): Deletes each item one by one */
        // MODIFICATION MEMBER FUNCTIONS
        void start(); /* O(1): Puts cursor at the start of the sequence */
        void advance(); /* O(1): Advance cursor to next item */
        void insert(const value_type& entry); /* O(1): Places item before the cursor */
        void attach(const value_type& entry); /* O(1): Places at item after the cursor */
        void operator =(const sequence<Item>& source); /* O(1): Removes the current item */
        void remove_current( ); /* O(n): Copies item into a sequence */
        // CONSTANT MEMBER FUNCTIONS
        size_type size() const {return many_nodes;}
        bool is_item() const {return cursor != NULL;}
        value_type current() const {return cursor->data();}
    private:
    	node<Item> *head, *tail, *cursor, *precursor; /* First, Last, Current, and Previous Item of the sequence */
    	size_type many_nodes; /* Total number of nodes */
    };
}

#include "sequence4.template"
#endif
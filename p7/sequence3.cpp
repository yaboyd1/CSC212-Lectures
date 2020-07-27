#include <cassert> // Provides assert()
#include <cstdlib> // Provides NULL and size_t
#include "node1.h" // Provides linked list toolkit
#include "sequence3.h"
using namespace std;
using namespace main_savitch_5;

namespace main_savitch_5 {
    // CONSTRUCTORS and DESTRUCTOR
    sequence();
    sequence(const sequence& source);
    ~sequence();

    // MODIFICATION MEMBER FUNCTIONS
    void start();
    void advance();
    void insert(const value_type& entry);
    void attach(const value_type& entry);
    void operator =(const sequence& source);
    void remove_current();

    // CONSTANT MEMBER FUNCTIONS
    value_type current() const;
}
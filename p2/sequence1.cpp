#include <cassert> // Provides assert
#include "sequence1.h"

namespace main_savitch_3 {
	typedef double value_type;
	typedef std::size_t size_type;
	static const size_type CAPACITY = 30;
	// CONSTRUCTOR
	sequence() {
		used = current_index = 0;
	}
	// MODIFICATION MEMBER FUNCTIONS
	void start() {
		if (used != 0) current_index = 0;
	}
	void advance() {
		assert(is_item());
		++current_index;
	}
	void insert(const value_type& entry) {
		assert(size() < CAPACITY);
	}
	void attach(const value_type& entry) {
		assert(size() < CAPACITY);
	}
	void remove_current();
	// CONSTANT MEMBER FUNCTIONS
	size_type size() const {
		assert(is_item());
		return used;
	}
	bool is_item() const {
		return used != 0;
	}
	value_type current() const {
		assert(is_item());
		return data[current_index];
	}
}
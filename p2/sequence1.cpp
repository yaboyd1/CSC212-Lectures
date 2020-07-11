#include <cassert> // Provides assert
#include "sequence1.h"

namespace main_savitch_3 {
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
		if (!is_item()) current_index = 0; /* Insert at the start of the sequence at default */
		for (sequence1::size_type i = used; i > current_index; --i) 
			data[i] = data[i - 1]; /* Shift elements forward to make room */
		data[current_index] = entry;
		++used;
	}

	void attach(const value_type& entry) {
		assert(size() < CAPACITY);
		if (!is_item()) current_index = used - 1; /* Insert at the end of the sequence at default */
		for (sequence1::size_type i = used; i > current_index + 1; --i) 
			data[i] = data[i - 1]; /* Shift elements forward to make room */
		data[++current_index] = entry;
		++used;
	}

	void remove_current() {
		assert(is_item());
		for (sequence1::size_type i = current_index + 1; i < used; ++i) 
			data[i - 1] = data[i]; /* Overwrite the data */
		--used;
	}

	// CONSTANT MEMBER FUNCTIONS
	size_type size() const {
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
#include <cassert> // Provides assert
#include "sequence2.h"

namespace main_savitch_4 {
	// CONSTRUCTOR
	sequence::sequence(size_type initial_capacity = DEFAULT_CAPACITY) {
		used = current_index = 0;
		capacity = initial_capacity;
		data = new sequence::value_type[capacity];
	}

	sequence::sequence(const sequence& source) {

	}

	sequence::~sequence() {

	}

	// MODIFICATION MEMBER FUNCTIONS
	void sequence::start() {
		if (used != 0) current_index = 0;
	}

	void sequence::advance() {
		assert(is_item());
		++current_index;
	}

	void sequence::insert(const value_type& entry) {
		assert(size() < CAPACITY);
		if (!is_item()) current_index = 0; /* Insert at the start of the sequence at default */
		for (sequence1::size_type i = used; i > current_index; --i)
			data[i] = data[i - 1]; /* Shift elements forward to make room */
		data[current_index] = entry;
		++used;
	}

	void sequence::attach(const value_type& entry) {
		assert(size() < CAPACITY);
		if (!is_item()) current_index = used - 1; /* Insert at the end of the sequence at default */
		for (sequence1::size_type i = used; i > current_index + 1; --i)
			data[i] = data[i - 1]; /* Shift elements forward to make room */
		data[++current_index] = entry;
		++used;
	}

	void sequence::remove_current() {
		assert(is_item());
		for (sequence1::size_type i = current_index + 1; i < used; ++i)
			data[i - 1] = data[i]; /* Overwrite the data */
		--used;
	}

	void operator =(const sequence& source) {

	}

	// CONSTANT MEMBER FUNCTIONS
	sequence::size_type sequence::size() const {
		return used;
	}

	bool sequence::is_item() const {
		return used != 0;
	}

	sequence:value_type sequence::current() const {
		assert(is_item());
		return data[current_index];
	}
}
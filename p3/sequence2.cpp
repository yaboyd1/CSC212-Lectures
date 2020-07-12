#include <algorithm> // Provides copy()
#include <cassert>   // Provides assert
#include "sequence2.h"
using namespace std;

namespace main_savitch_4 {
	// CONSTRUCTORS
	sequence::sequence(size_type initial_capacity = DEFAULT_CAPACITY) {
		used = current_index = 0;
		capacity = initial_capacity;
		data = new sequence::value_type[capacity];
	}

	sequence::sequence(const sequence& source) {
		used = source.used;
		current_index = source.current_index;
		capacity = source.capacity;
		data = new sequence::value_type[capacity];
		copy(source.data, source.data + used, data);
	}

	sequence::~sequence() {
		delete [] data;
	}

	// MODIFICATION MEMBER FUNCTIONS
	void sequence::resize(sequence::size_type new_capacity) {
		if (new_capacity == capacity) return;
		if (new_capacity < used) used = new_capacity;
		sequence::value_type *new_data = new sequence::value_type[new_capacity];
		copy(data, data + used, new_data);
		delete [] data;
		data = new_data;
		capacity = new_capacity;
	}

	void sequence::start() {
		if (used != 0) current_index = 0;
	}

	void sequence::advance() {
		assert(is_item());
		++current_index;
	}

	void sequence::insert(const value_type& entry) {
		//assert(size() < CAPACITY);
		if (!is_item()) current_index = 0; /* Insert at the start of the sequence at default */
		for (sequence::size_type i = used; i > current_index; --i)
			data[i] = data[i - 1]; /* Shift elements forward to make room */
		data[current_index] = entry;
		++used;
	}

	void sequence::attach(const value_type& entry) {
		//assert(size() < CAPACITY);
		if (!is_item()) current_index = used - 1; /* Insert at the end of the sequence at default */
		for (sequence::size_type i = used; i > current_index + 1; --i)
			data[i] = data[i - 1]; /* Shift elements forward to make room */
		data[++current_index] = entry;
		++used;
	}

	void sequence::remove_current() {
		assert(is_item());
		for (sequence::size_type i = current_index + 1; i < used; ++i)
			data[i - 1] = data[i]; /* Overwrite the data */
		--used;
	}

	void sequence::operator =(const sequence& source) {
		if (this == &source) return;
		used = source.used;
		current_index = source.current_index;
		capacity = source.capacity;
		data = new sequence::value_type[capacity];
		copy(source.data, source.data + used, data);
	}

	// CONSTANT MEMBER FUNCTIONS
	sequence::size_type sequence::size() const {
		return used;
	}

	bool sequence::is_item() const {
		return used != 0;
	}

	sequence::value_type sequence::current() const {
		return data[current_index];
	}
}

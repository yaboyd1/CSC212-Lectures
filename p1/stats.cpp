#include "stats.h"

namespace main_savitch_2C {
	statistician::statistician() {
		reset();
	}
    // MODIFICATION MEMBER FUNCTIONS
	void statistician::next(double r) {
		if (r < tinyest)
			tinyest = r;
		if (r > largest)
			largest = r;
		total += r;
		++count;
	}
	void statistician::reset() {
		total = count = 0;
	}
    // CONSTANT MEMBER FUNCTIONS
	int statistician::length() const {
		return count;
	}
	double statistician::sum() const {
		return total;
	}
	double statistician::mean() const {
		return (double)total/count;
	}
	double statistician::minimum() const {
		return tinyest;
	}
	double statistician::maximum() const {
		return largest;
	}
    // FRIEND FUNCTIONS
	statistician operator +(const statistician& s1, const statistician& s2);
	statistician operator *(double scale, const statistician& s);

	bool operator ==(const statistician& s1, const statistician& s2);
}
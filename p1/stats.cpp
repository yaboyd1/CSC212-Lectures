#include <cassert> // Provides assert()
#include <climits> // Provides INT_MIN and INT_MAX
#include "stats.h"

namespace main_savitch_2C {
	statistician::statistician() {
		reset();
	}
	statistician::statistician(int c, double t, double min, double max) {
		count = c;
		total = t;
		tinyest = min;
		largest = max;
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
		tinyest = INT_MIN;
		largest = INT_MAX;
	}
    // CONSTANT MEMBER FUNCTIONS
	int statistician::length() const {
		return count;
	}
	double statistician::sum() const {
		return total;
	}
	double statistician::mean() const {
		assert(length() > 0);
		return (double)total/count;
	}
	double statistician::minimum() const {
		assert(length() > 0);
		return tinyest;
	}
	double statistician::maximum() const {
		assert(length() > 0);
		return largest;
	}
    // FRIEND FUNCTIONS
	statistician operator +(const statistician& s1, const statistician& s2);
	statistician operator *(double scale, const statistician& s);

	bool operator ==(const statistician& s1, const statistician& s2);
}
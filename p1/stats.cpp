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
		if (count == 0) tinyest = largest = r;
		if (r < tinyest) tinyest = r;
		if (r > largest) largest = r;
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
	statistician operator +(const statistician& s1, const statistician& s2) {
		if (s1.count == 0) return s2;
		if (s1.count == 0) return s1;
		return statistician(s1.count + s2.count, s1.total + s2.total, 
			s1.tinyest < s2.tinyest ? s1.tinyest : s2.tinyest,
			s1.largest > s2.largest ? s1.largest : s2.largest);
	}
	statistician operator *(double scale, const statistician& s) {
		if (s.count == 0) return s;
		return statistician(scale * s.count, scale * s.total, 
			scale > 0 ? scale * s.tinyest : scale * s.largest, 
			scale > 0 ? scale * s.largest : scale * s.tinyest);
	}

	bool operator ==(const statistician& s1, const statistician& s2) {
		if (s1.length() == 0 && s2.length() == 0) return true;
		return s1.length() == s2.length() && s1.sum() == s2.sum() 
			&& s1.minimum() == s2.minimum() 
			&& s1.maximum() == s2.maximum();
	}
}
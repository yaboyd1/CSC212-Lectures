#include <cassert>   // Provides assert()
#include <algorithm> // Provides fill_n()
#include <climits>   // Provides UINT_MAX
#include <cmath>	 // Provides pow()
using namespace std;
#include "poly0.h"

namespace main_savitch_3
{
	// CONSTANTS
	const unsigned int polynomial::CAPACITY;
	const unsigned int polynomial::MAX_EX;

	// CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent) {
		assert(exponent <= MAX_EX);
		clear();
		current_degree = 0;
		assign_coef(c, exponent);
	}

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::add_to_coef(double amount, unsigned int exponent) {
		assert(exponent <= MAX_EX);
		assign_coef(coef[exponent] + amount, exponent);
	}

	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
		assert(exponent <= MAX_EX);
		coef[exponent] = coefficient;
		/* Set new Current Degree */
		if (exponent > current_degree) current_degree = exponent;
		if (coef[current_degree] == 0) {
			for (unsigned int i = current_degree; i != 0 && coef[i] == 0; --i) {
				current_degree = i - 1;
			}
		}
	}

	void polynomial::clear() {
		fill_n(coef, CAPACITY, 0.0);
		current_degree = 0;
	}

	// CONSTANT MEMBER FUNCTIONS
	double polynomial::coefficient(unsigned int exponent) const {
		if (exponent > MAX_EX) return 0;
		return coef[exponent];
	}

	/* Just for now until I figure this out */
	polynomial polynomial::derivative() const {
		polynomial der;
		for (unsigned int i = degree(); i > 1; --i) {
			der.assign_coef(coefficient(i) * i, i - 1);
		}
		return der;
	}

	double polynomial::eval(double x) const{
		double total = 0;
		for (unsigned int i = 0; i < degree(); ++i) {
			total += coefficient(i) * pow(x, i);
		}
		return total;
	}

	unsigned int polynomial::next_term(unsigned int e) const {
		for (unsigned int i = e + 1; i <= degree(); ++i) {
			if (coefficient(i) != 0) {
				return i;
			}
		}
		return 0;
	}

	unsigned int polynomial::previous_term(unsigned int e) const {
		for (unsigned int i = e - 1; i > 0; --i) {
			if (coefficient(i) != 0) {
				return i;
			}
		}
		return UINT_MAX;
	}

	// NON-MEMBER BINARY OPERATORS
	polynomial operator +(const polynomial& p1, const polynomial& p2) {
		if (p1.degree() == 0) return p2;
		if (p2.degree() == 0) return p1;
		polynomial max, min;
		p1.degree() > p2.degree() ? max = p1, min = p2 : max = p2, min = p1;
		for (unsigned int i = 0; i != min.degree(); ++i) {
			max.add_to_coef(min.coefficient(i), i);
		}
		return max;
	}

	polynomial operator -(const polynomial& p1, const polynomial& p2) {
		if (p1.degree() == 0) return p2;
		if (p2.degree() == 0) return p1;
		polynomial max, min;
		p1.degree() > p2.degree() ? max = p1, min = p2 : max = p2, min = p1;
		for (unsigned int i = 0; i != min.degree(); ++i) {
			max.add_to_coef(-min.coefficient(i), i);
		}
		return max;
	}

	/* Just for now until I figure this out */
	polynomial operator *(const polynomial& p1, const polynomial& p2) {
		assert(p1.degree() + p2.degree() <= polynomial::MAX_EX);
		return polynomial(p1);
	}

	// NON-MEMBER OUTPUT FUNCTIONS

	/* Just for now until I figure this out */
	std::ostream& operator << (std::ostream& out, const polynomial& p) {
		return out << "Hi";
	}

	void make_gif(
		const polynomial& p,
		const char filename[ ],
		double low_x,
		double high_x,
		double low_y,
		double high_y
		);
}

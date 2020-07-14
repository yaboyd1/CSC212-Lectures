#include <cassert>   // Provides assert()
#include <algorithm> // Provides fill_n()
using namespace std;
#include "poly0.h"

namespace main_savitch_3
{
	// CONSTANTS
	static const unsigned int polynomial::CAPACITY;
	static const unsigned int polynomial::MAX_EX = CAPACITY;

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
		/* Current Degree will be done later */
	}
	void polynomial::clear() {
		fill_n(coef, CAPACITY, 0.0);
	}

	// CONSTANT MEMBER FUNCTIONS
	double polynomial::coefficient(unsigned int exponent) const;
	polynomial polynomial::derivative() const;
	double polynomial::eval(double x) const;
	unsigned int polynomial::next_term(unsigned int e) const;
	unsigned int polynomial::previous_term(unsigned int e) const;

	// NON-MEMBER BINARY OPERATORS
	polynomial operator +(const polynomial& p1, const polynomial& p2);
	polynomial operator -(const polynomial& p1, const polynomial& p2);
	polynomial operator *(const polynomial& p1, const polynomial& p2);

	// NON-MEMBER OUTPUT FUNCTIONS
	std::ostream& operator << (std::ostream& out, const polynomial& p);
	void make_gif(
		const polynomial& p,
		const char filename[ ],
		double low_x,
		double high_x,
		double low_y,
		double high_y
		);
}
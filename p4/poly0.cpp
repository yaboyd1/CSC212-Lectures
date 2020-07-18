#include <cassert>   // Provides assert()
#include <algorithm> // Provides fill_n()
#include <climits>   // Provides UINT_MAX
#include <cmath>	 // Provides pow()
using namespace std;
#include "poly0.h"

namespace main_savitch_3 {
	// CONSTANTS
	const unsigned int polynomial::CAPACITY;
	const unsigned int polynomial::MAX_EX;

	// CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent) {
		assert(exponent <= MAX_EX);
		clear();
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
			current_degree = previous_term(current_degree);
			if (current_degree == UINT_MAX) current_degree = 0;
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

	polynomial polynomial::derivative() const {
		polynomial der;
		for (unsigned int i = 1; i != 0; i = next_term(i)) {
			der.assign_coef(coefficient(i) * i, i - 1);
		}
		return der;
	}

	double polynomial::eval(double x) const{
		double total = coefficient(0);
		for (unsigned int i = next_term(0); i != 0; i = next_term(i)) {
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
		if (e == 0) return UINT_MAX;
		for (unsigned int i = e - 1; i >= 0; --i) {
			if (coefficient(i) != 0) {
				return i;
			}
			if (i == 0) break;
		}
		return UINT_MAX;
	}

	// NON-MEMBER BINARY OPERATORS
	polynomial operator +(const polynomial& p1, const polynomial& p2) {
		if (p1.degree() == 0) return p2;
		if (p2.degree() == 0) return p1;
		polynomial sum(p1.coefficient(0) + p2.coefficient(0), 0);
		for(unsigned int i = p1.next_term(0); i != 0; i = p1.next_term(i)) sum.add_to_coef(p1.coefficient(i), i);
		for(unsigned int i = p2.next_term(0); i != 0; i = p2.next_term(i)) sum.add_to_coef(p2.coefficient(i), i);
		return sum;
	}

	polynomial operator -(const polynomial& p1, const polynomial& p2) {
		if (p1.degree() == 0) return p2;
		if (p2.degree() == 0) return p1;
		polynomial difference(p1.coefficient(0) - p2.coefficient(0), 0);
		for(unsigned int i = p1.next_term(0); i != 0; i = p1.next_term(i)) difference.add_to_coef(p1.coefficient(i), i);
		for(unsigned int i = p2.next_term(0); i != 0; i = p2.next_term(i)) difference.add_to_coef(-p2.coefficient(i), i);
		return difference;
	}

	polynomial operator *(const polynomial& p1, const polynomial& p2) {
		assert(p1.degree() + p2.degree() <= polynomial::MAX_EX);
		polynomial product;
		for (unsigned int i = 0; i <= p1.degree(); ++i) {
			for (unsigned int j = 0; j <= p2.degree(); ++j) {
				product.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
			}
		}
		return product;
	}

	// NON-MEMBER OUTPUT FUNCTIONS
	std::ostream& operator << (std::ostream& out, const polynomial& p) {
		if (!p.degree()) return out << 0;
		unsigned int deg = p.degree();
    	out << p.coefficient(deg);
    	if (deg > 0) out << "x";
    	if (deg > 1) out << "^" << deg;
    	for (unsigned int i = p.previous_term(deg); i != UINT_MAX; i = p.previous_term(i)) {
    		double term = p.coefficient(i);
			term > 0 ? out << " + " << term : out << " - " << -term;
			if (i > 0) out << "x";
			if (i > 1) out << "^" << i;
			if (i == 0) break;
		}
		return out << endl;
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

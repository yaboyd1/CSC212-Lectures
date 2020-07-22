#include <cstdlib>   // Provides size_t 
#include <iostream>  // Provides cout
#include <algorithm> // Provides fill_n() and copy()
#include <climits>	 // Provides UINT_MAX
#include <cmath>	 // Provides pow()
using namespace std;
#include "poly1.h"

namespace main_savitch_4 {
	// CONSTANTS	
	const unsigned int polynomial::DEFAULT_CAPACITY;

	// CONSTRUCTORS and DESTRUCTOR
	polynomial::polynomial() {
		current_array_size = DEFAULT_CAPACITY;
		clear();
	}

	polynomial::polynomial(const polynomial& source) {
		current_array_size = source.current_array_size;
		current_degree = source.current_degree;
		coef = new double[current_array_size];
		copy(source.coef, source.coef + current_degree + 1, coef);
	}

	polynomial::polynomial(double c, unsigned int exponent) {
		current_array_size = DEFAULT_CAPACITY;
		clear();
		assign_coef(c, exponent);
	}

	polynomial::~polynomial() {
		delete [] coef;
	}

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::add_to_coef(double amount, unsigned int exponent) {
		assign_coef(coef[exponent] + amount, exponent);
	}

	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
		if (current_degree + 1 == current_array_size) reserve(current_array_size + 1);
		coef[exponent] = coefficient;
		/* Set new current degree */
		if (exponent > current_degree) current_degree = exponent;
		if (coef[current_degree] == 0) {
			current_degree = previous_term(current_degree);
			if (current_degree == UINT_MAX) current_degree = 0;
		}
	}

	void polynomial::clear() {
		fill_n(coef, current_array_size, 0.0);
		current_degree = 0;
	}

	void polynomial::reserve(size_t new_size) {
		if (new_size == current_array_size) return;
		if (new_size < current_degree + 1) new_size = current_degree;
		double *new_coef = new double[new_size];
		copy(coef, coef + current_degree + 1, new_coef);
		delete [] coef;
		coef = new_coef;
		current_array_size = new_size;
	}

	/* Just for now until I figure this out */
	void polynomial::trim() {
		return;
	}

	// MODIFICATION OPERATORS
	polynomial& polynomial::operator =(const polynomial& source) {
		if (this == &source) return *this;
		delete [] coef;
		current_array_size = source.current_array_size;
		current_degree = source.current_degree;
		coef = new double[current_array_size];
		copy(source.coef, source.coef + current_degree + 1, coef);
		return *this;
	}
	
	polynomial& polynomial::operator -=(const polynomial& p);
	polynomial& polynomial::operator +=(const polynomial& p);
	polynomial& polynomial::operator *=(const polynomial& p);
	polynomial& polynomial::operator *=(double c);

	// CONSTANT MEMBER FUNCTIONS
	double polynomial::coefficient(unsigned int exponent) const {
		return coef[exponent];
	}

	double polynomial::definite_integral(double low_bound, double high_bound) const;

	unsigned int polynomial::degree() const {
		return current_degree;
	}

	polynomial polynomial::derivative(unsigned int n) const {
		polynomial der;
		for (unsigned int i = 1; i != 0; i = next_term(i)) {
			der.assign_coef(coefficient(i) * i, i - 1);
		}
		return der;
	}

	double polynomial::eval(double x) const {
		double total = coefficient(0);
		for (unsigned int i = next_term(0); i != 0; i = next_term(i)) {
			total += coefficient(i) * pow(x, i);
		}
		return total;
	}

	void polynomial::find_root(
		double& answer,
		bool& success,
		unsigned int& iterations,
		double guess,
		unsigned int maximum_iterations,
		double epsilon
		) const;

	polynomial polynomial::integral(unsigned int n) const;

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

	double polynomial::numeric_integral(
		double low_bound,
		double high_bound,
		unsigned int many_trapezoids = 100
		) const;

	polynomial polynomial::substitution(const polynomial& p) const;

	// CONSTANT OPERATORS
	polynomial polynomial::operator -() const;

	// NON-MEMBER BINARY OPERATORS
	polynomial operator +(const polynomial& p1, const polynomial& p2) {
		if (p1.degree() == 0) return p2;
		if (p2.degree() == 0) return p1;
		polynomial sum(p1.coefficient(0) + p2.coefficient(0), 0);
		for(unsigned int i = p1.next_term(0); i != 0; i = p1.next_term(i)) sum.add_to_coef(p1.coefficient(i), i);
		for(unsigned int i = p2.next_term(0); i != 0; i = p2.next_term(i)) sum.add_to_coef(p2.coefficient(i), i);
		return sum;
	}

	polynomial operator +(const polynomial& p, double c) {
		p.add_to_coef(c, 0);
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
		/* Reserve function here */
		polynomial product;
		for (unsigned int i = 0; i <= p1.degree(); ++i) {
			for (unsigned int j = 0; j <= p2.degree(); ++j) {
				product.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
			}
		}
		return product;
	}

	polynomial operator *(const polynomial& p, double c) {
		polynomial product(p.coefficient(i) * c, 0);
		for(unsigned int i = p.next_term(0); i != 0; i = p.next_term(i)) 
			product.assign_coef(p.coefficient(i) * c, i);
		return product;
	}

	polynomial operator ^(const polynomial& p, unsigned int n);

	// NON-MEMBER INPUT/OUTPUT FUNCTIONS
	std::istream& operator >> (std::istream& in, polynomial& p);
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
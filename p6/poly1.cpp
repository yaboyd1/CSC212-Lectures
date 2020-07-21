#include <cstdlib>   // Provides size_t 
#include <iostream>  // Provides cout
#include <algorithm> // Provides fill_n() and copy()
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
		if (current_degree + 1 == current_array_size) reserve(current_array_size + 1);
		coef[exponent] += amount;
	}
	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
		if (current_degree + 1 == current_array_size) reserve(current_array_size + 1);
		coef[exponent] = coefficient;
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

	void polynomial::trim();

	// MODIFICATION OPERATORS
	polynomial& polynomial::operator =(const polynomial& source);
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

	polynomial polynomial::derivative(unsigned int n) const;

	double polynomial::eval(double x) const;

	void polynomial::find_root(
	    double& answer,
	    bool& success,
	    unsigned int& iterations,
	    double guess,
	    unsigned int maximum_iterations,
	    double epsilon
	    ) const;

	polynomial polynomial::integral(unsigned int n) const;
	unsigned int polynomial::next_term(unsigned int e) const;
	unsigned int polynomial::previous_term(unsigned int e) const;

	double polynomial::numeric_integral(
	    double low_bound,
	    double high_bound,
	    unsigned int many_trapezoids = 100
	    ) const;

	polynomial polynomial::substitution(const polynomial& p) const;

	// CONSTANT OPERATORS
	double polynomial::operator( ) (double x) const { return eval(x); }
	polynomial polynomial::operator( ) (const polynomial& p) const { return substitution(p); }
	polynomial polynomial::operator -( ) const;
	polynomial polynomial::operator +( ) const { return (*this); };

	// NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2);
    polynomial operator +(const polynomial& p, double c);
    inline
    polynomial operator +(double c, const polynomial& p) { return p + c; };
    polynomial operator -(const polynomial& p1, const polynomial& p2);
    inline
    polynomial operator -(const polynomial& p, double c) { return p + (-c); };
    inline
    polynomial operator -(double c, const polynomial& p) { return p + (-c); };
    polynomial operator *(const polynomial& p1, const polynomial& p2);
    polynomial operator *(const polynomial& p, double c);
    inline
    polynomial operator *(double c, const polynomial& p) { return p * c; };
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
#include <cstdlib>  // Provides size_t 
#include <iostream> // Provides cout
#include "poly1.h"

namespace main_savitch_4 {
	// CONSTRUCTORS and DESTRUCTOR
	polynomial::polynomial();
	polynomial::polynomial(const polynomial& source);
	polynomial::polynomial(double c, unsigned int exponent);
	polynomial::~polynomial();

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::add_to_coef(double amount, unsigned int exponent);
	void polynomial::assign_coef(double coefficient, unsigned int exponent);
	void polynomial::clear();
	void polynomial::reserve(size_t number);
	void polynomial::trim();

	// MODIFICATION OPERATORS
	polynomial& polynomial::operator =(const polynomial& source);
	polynomial& polynomial::operator -=(const polynomial& p);
	polynomial& polynomial::operator +=(const polynomial& p);
	polynomial& polynomial::operator *=(const polynomial& p);
	polynomial& polynomial::operator *=(double c);

	// CONSTANT MEMBER FUNCTIONS
	double polynomial::coefficient(unsigned int exponent) const;
	double polynomial::definite_integral(double low_bound, double high_bound) const;
	unsigned int polynomial::degree() const;
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
// FILE: poly1.h
// CLASS PROVIDED:
//   class polynomial
//     A polynomial has one variable x, real number coefficients, and
//     non-negative integer exponents. Such a polynomial can be viewed
//     as having the form:
//       A[n]*x^n + A[n-1]*x^(n-1) + ... A[2]*x^2 + A[1]*x + A[0]
//     where the A[n] are the real number coefficients and x^i represents
//     the variable x raised to the i power. The coefficient A[0] is
//     called the "constant" or "zeroth" term of the polynomial.
//
// NOTES:
//   This poly1.h version works by storing the coefficients in
//   a dynamic array, as described in Section 4.6 of
//   "Data Structures and Other Objects" (2nd edition) by
//   Michael Main and Walter Savitch
//
// CONSTRUCTORS for the polynomial class
//   polynomial( )
//     POSTCONDITION: This polynomial has been created with all zero
//     coefficients.
//
//   polynomial(double c, unsigned int exponent = 0)
//     POSTCONDITION: This polynomial has been create with all zero
//     coefficients, except for coefficient c for the specified exponent.
//
//   polynomial(const polynomial& source)
//     POSTCONDITION: This polynomial has been created as a copy of the source.
//
// MODIFICATION MEMBER FUNCTIONS for the polynomial class
//   void add_to_coef(double amount, unsigned int exponent)
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.
//
//   void assign_coef(double coefficient, unsigned int exponent)
//     POSTCONDITION: Sets the coefficient for the specified exponent.
//
//   void clear( )
//     POSTCONDITION: All coefficients of this polynomial are set to zero.
//
//   void reserve(size_t number)
//     POSTCONDITION: The size of the array for coefficients has been changed to
//     the requested number (but not less that the size needed to store the
//     current non-zero coefficients). In effect, this guarantees that member
//     functions will not need to allocate new memory for exponents through
//     at least number-1.
//
//   void trim( )
//     POSTCONDITION: Releases dynamic memory as much as possible.
//
// MODIFICATION OPERATORS for the polynomial class
//   polynomial& operator =(const polynomial& source)
//     POSTCONDITION: This polynomial is exactly the same as the
//     parameter. The return value is a reference to this polynomial.
//
//   polynomial& operator =(double c)
//     POSTCONDITION: This polynomial is set to the polynomial with only the
//     constant term c. The other coefficients (for x, x^2, x^3...) are all zero.
//
//   polynomial& operator -=(const polynomial& p)
//     POSTCONDITION: The terms of p have been subtracted from
//     the terms of this polynomial, and the result is stored back in this polynomial.
//     The return value is a reference to this polynomial.
//
//   polynomial& operator -=(double c)
//     POSTCONDITION: The value c has been subtracted from the constant (zeroth)
//     term of this polynomial, and the result is stored back in this polynomial.
//     The return value is a reference to this polynomial.
//
//   polynomial& operator +=(const polynomial& p)
//     POSTCONDITION: The terms of p are added to the terms of this
//     polynomial, and the result is stored back in this polynomial.
//     The return value is a reference to this polynomial.
//
//   polynomial& operator +=(double c)
//     POSTCONDITION: The value c has been added from the constant (zeroth)
//     term of this polynomial, and the result is stored back in this polynomial.
//     The return value is a reference to this polynomial.
//
//   polynomial& operator *=(const polynomial& p)
//     POSTCONDITION: Each term of the this polynomial has been multiplied by
//     each term of p, and this polynomial has been replaced by the sum of all
//     these term-by-term products. For example, if this polynomial is
//     2x^2 + 3x + 4 and p is 5x^2 - 1x + 7, then at the end of this function
//     this polynomial will contain 10x^4 + 13x^3 + 31x^2 + 17x + 28.
//     The return value is a reference to this polynomial.
//
//   polynomial& operator *=(double c)
//     POSTCONDITION: Every coefficient of this polynomial has been multiplied
//     by c and the results stored back in this polynomial.
//     The return value is a reference to this polynomial.
//
// CONSTANT MEMBER FUNCTIONS for the polynomial class
//   double coefficient(unsigned int exponent) const
//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
//
//   double definite_integral(double low_bound, double high_bound) const
//     POSTCONDITION: The value returned is the definite integral from
//     low_bound to high_bound.
//     NOTE: If low_bound is not the smaller of the two bounds, then the answer
//     returned is -1 * definite_integral(high_bound, low_bound).
//
//   unsigned int degree( ) const
//     POSTCONDITION: The function returns the value of the largest exponent
//     with a non-zero coefficient.
//     If all coefficients are zero, then the function returns zero.
//
//   polynomial derivative(unsigned int n = 1) const
//     POSTCONDITION: The return value is the n-th derivative of this polynomial.
//
//   double eval(double x) const
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x.
//
//   void find_root(
//     double& answer,
//     bool& success,
//     unsigned int& iterations,
//     double starting_guess = 0,
//     unsigned int maximum_iterations = 100,
//     double epsilon = 1e-8
//     )
//     const
//     PRECONDITION: epsilon > 0.
//     POSTCONDITION: This function uses Newton's method to search for a root of
//     the polynomial (i.e., a value of x for which the polynomial is zero).
//     The method requires some starting guess for the value of the root. This
//     guess is improved over a series of iterations (with the maximum allowed
//     iterations defined by the parameter maximum_iterations). There are three
//     possible outcomes:
//     1. SUCCESS:
//        The method hits a near-root (a value of x for which the absolute value
//        of the polynomial is no more than epsilon). In this case, the function
//        sets answer to equal this near-root, success is set to true, and
//        iterations is set to the number of iterations required.
//     2. FLAT FAILURE:
//        Newton's method fails because the guess hits a very flat area of the
//        polynomial (a point where first derivative is no more than epsilon).
//        In this case, the function sets answer equal to the guess that caused
//        flat failure, success is set to false, and iterations is the number
//        of iterations carried out (which will be less than maximum_iterations).
//     3. MAXIMUM ITERATIONS REACHED:
//        The maximum number of iterations is reached without success or flat
//        failure. In this case, the function sets answer to the last guess tried,
//        success is set to false, and iterations is set to maximum_iterations.
//
//   polynomial integral(unsigned int n = 1) const
//     POSTCONDITION: The return value is the n-th integral of this polynomial.
//
//   unsigned int next_term(unsigned int e) const
//     POSTCONDITION: If e is less than the degree, then the return value is
//     the next exponent n which is after e such that coefficient(n) != 0.
//     If e is greater than or equal to the degree, then the return value is
//     std::UINT_MAX from <climits>.
//
//   unsigned int previous_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is SMALLER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is UINT_MAX
//     from <climits>.
//
//   double numeric_integral(
//     double low_bound,
//     double high_bound,
//     unsigned int many_trapezoids = 100
//     )
//     const
//     PRECONDITION: many_trapezoids > 0.
//     POSTCONDITION: The value returned is the definite integral from
//     low_bound to high_bound, calculated numerically by the trapezoid method.
//     NOTE: If low_bound is not the smaller of the two bounds, then the answer
//     returned is -1 * numeric_integral(high_bound, low_bound).
//
//   polynomial substitution(polynomial p) const
//     POSTCONDITION: The return value is a polynomial in which the parameter p
//     has been substituted for every value of x in this polynomial.
//
// CONSTANT OPERATORS for the polynomial class
//   double operator( ) (double x) const
//     Same as the eval member function.
//
//   polynomial operator( ) (const polynomial& p) const
//     Same as the substitution function.
//
//   polynomial operator -( ) const
//     POSTCONDITION: The return value is -1 times this polynomial.
//
//   polynomial operator +( ) const
//     POSTCONDITION: The return value is +1 times this polynomial.
//     I can't think of any case where this would be needed, but I put it in for
//     symmetry with the unary operator -.
//
// NON-MEMBER BINARY OPERATORS for the polynomial Class
//   NOTE: For operators - + and *, one of the arguments is allowed
//   to be a double number rather than a polynomial. In this case, the double
//   number is treated as if it was a polynomial with only a constant term
//   equal to the double number (and all coefficients are zero for
//   the terms x, x^2, x^3, ...).  We considered handling this situation
//   with a constructor-generated conversion that would actually convert
//   the double number into a polynomial, but actually going through the
//   conversion and creating an actual polynomial seemed inefficient.
//
//   polynomial operator -(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal the difference of the coefficients of p1 & p2 for any given
//     exponent.
//
//   polynomial operator +(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal the sum of the coefficients of p1 & p2 for any given
//     exponent.
//
//   polynomial operator *(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//     and the answer is the sum of all these term-by-term products.
//     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
//
//   polynomial operator ^(const polynomial& p, unsigned int n)
//     POSTCONDITION: The return value is p raised to the n-th power.
//
// NON-MEMBER INPUT/OUTPUT FUNCTIONS for the polynomial Class
//   istream& operator >> (istream& in, polynomial& p)
//     POSTCONDITION: A polynomial has read from a single line of istream in.
//     Specifically:
//     1. All initial whitespace is read and discarded.
//     2. One or more terms are then read from a single line of input.
//        Each term has the form:
//        a. SIGN: + or -.
//        b. COEF: an unsigned double constant
//        c. VARIABLE: the letter x or X
//        d. CAROT: the character ^
//        e. EXPONENT: an integer
//        Each piece may be preceeded or followed by blanks.
//        Also, some pieces are optional:
//        For the first term or any term preceeded by blanks,
//        any positive SIGN is optional;
//        if at least one of parts c-f is present, then a COEF of 1 is optional;
//        if the EXPONENT is zero, then all of parts c-e may be omitted;
//        if the EXPONENT is one, then all of parts d-e may be omitted.
//     3. The newline at the end of the line is read and discarded.
//
//   ostream& operator << (ostream& out, const polynomial& p)
//     POSTCONDITION: The polynomial has been printed to ostream out, which,
//     in turn, has been returned to the calling function.
//
//   void make_gif(
//     const polynomial& p,
//     const char filename[ ],
//     double low_x,
//     double high_x,
//     double low_y,
//     double high_y
//     )
//     PRECONDITION: filename is a legal filename for a gif file.
//     Also (low_x < high_x) && (low_y < high_y).
//     POSTCONDITION: A gif file has been written to the specified filename
//     with a graphical representation of the polynomial in the specified
//     ranges (low_x...high_x and low_y...high_y).
//
// DYNAMIC MEMORY usage by the polynomial class
//    If there is insufficient dynamic memory, the following functions throw a
//    bad_alloc exception:
//    the constructors, add_to_coef, assign_coef, reserve, trim,
//    derivative, find_root, integral, make_gif, substitution, 
//    and any of the operators with a polynomial parameter.

#ifndef POLY1_H
#define POLY1_H
#include <cstdlib>      // Provides size_t type
#include <iostream>     // Provides istream and ostream 

// If your compiler does not support namespaces, then please delete the
// following line and the set of brackets that follow.
namespace main_savitch_4
{
    
    class polynomial
    {
    public:
	// CONSTRUCTORS and DESTRUCTOR
	polynomial( );
	polynomial(const polynomial& source);
	polynomial(double c, unsigned int exponent = 0);
	~polynomial( );

	// MODIFICATION MEMBER FUNCTIONS
	void add_to_coef(double amount, unsigned int exponent);
	void assign_coef(double coefficient, unsigned int exponent);
	void clear( );
	void reserve(size_t number);
	void trim();
	
	// MODIFICATION OPERATORS
	polynomial& operator =(const polynomial& source);
	polynomial& operator =(double c)
	    { clear( ); assign_coef(c, 0); return *this; }
	polynomial& operator -=(const polynomial& p);
	polynomial& operator -=(double c)
	    { add_to_coef(-c, 0); return *this; };
	polynomial& operator +=(const polynomial& p);
	polynomial& operator +=(double c)
	    { add_to_coef(c, 0); return *this; };
	polynomial& operator *=(const polynomial& p);
	polynomial& operator *=(double c);
	
	// CONSTANT MEMBER FUNCTIONS
	double coefficient(unsigned int exponent) const;
	double definite_integral(double low_bound, double high_bound) const;
	unsigned int degree( ) const;
	polynomial derivative(unsigned int n = 1) const;
	double eval(double x) const;
	void find_root(
	    double& answer,
	    bool& success,
	    unsigned int& iterations,
	    double guess = 0,
	    unsigned int maximum_iterations = 100,
	    double epsilon = 1e-8
	    )
	    const;
	polynomial integral(unsigned int n = 1) const;
	unsigned int next_term(unsigned int e) const;
	unsigned int previous_term(unsigned int e) const;
	double numeric_integral(
	    double low_bound,
	    double high_bound,
	    unsigned int many_trapezoids = 100
	    )
	    const;
	polynomial substitution(const polynomial& p) const;
	
	// CONSTANT OPERATORS
	double operator( ) (double x) const { return eval(x); }
	polynomial operator( ) (const polynomial& p) const { return substitution(p); }
	polynomial operator -( ) const;
	polynomial operator +( ) const { return (*this); };
	
    private:
	size_t current_array_size;
	double *coef;
    };
    
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
#endif
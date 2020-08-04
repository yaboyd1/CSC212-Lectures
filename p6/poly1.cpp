#include <cstdlib>   // Provides size_t 
#include <iostream>  // Provides cout
#include <cassert>   // Provides assert()
#include <algorithm> // Provides fill_n() and copy()
#include <climits>   // Provides UINT_MAX
#include <cmath>     // Provides pow()
using namespace std;
#include "poly1.h"

namespace main_savitch_4 {
	// CONSTANTS	
	const unsigned int polynomial::DEFAULT_CAPACITY;

	// CONSTRUCTORS and DESTRUCTOR
	polynomial::polynomial() {
		coef = new double[current_array_size = DEFAULT_CAPACITY];
		clear();
	}

	polynomial::polynomial(const polynomial& source) {
		current_array_size = source.current_array_size;
		current_degree = source.current_degree;
		coef = new double[current_array_size];
		copy(source.coef, source.coef + current_degree + 1, coef);
	}

	polynomial::polynomial(double c, unsigned int exponent) {
		coef = new double[current_array_size = DEFAULT_CAPACITY];
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
		if (exponent >= current_array_size) reserve(exponent + 1);
		coef[exponent] = coefficient;
		/* Set new current degree */
		if (exponent > current_degree) current_degree = exponent;
		if (coef[current_degree] == 0) {
			current_degree = previous_term(current_degree);
			if (current_degree == UINT_MAX) current_degree = 0;
		}
	}

	void polynomial::clear() {
		fill_n(coef, current_array_size, 0);
		current_degree = 0;
	}

	void polynomial::reserve(size_t new_size) {
		if (new_size == current_array_size) return;
		if (new_size < current_degree + 1) new_size = current_degree;
		double *new_coef = new double[new_size];
		fill_n(new_coef, new_size, 0);
		copy(coef, coef + current_degree + 1, new_coef);
		delete [] coef;
		coef = new_coef;
		current_array_size = new_size;
	}

	void polynomial::trim() {
		reserve(degree() + 1);
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
	
	polynomial& polynomial::operator -=(const polynomial& p) {
		return *this = *this - p;	
	}
	polynomial& polynomial::operator +=(const polynomial& p) {
		return *this = *this + p;
	}
	polynomial& polynomial::operator *=(const polynomial& p) {
		return *this = *this * p;
	}
	polynomial& polynomial::operator *=(double c) {
		return *this = *this * c;
	}

	// CONSTANT MEMBER FUNCTIONS
	double polynomial::coefficient(unsigned int exponent) const {
		if (exponent > degree()) return 0;
		return coef[exponent];
	}

	double polynomial::definite_integral(double low_bound, double high_bound) const {
		if (low_bound > high_bound) return -1 * definite_integral(high_bound, low_bound);
		polynomial integral = this->integral();
		return integral.eval(high_bound) - integral.eval(low_bound);
	}

	unsigned int polynomial::degree() const {
		return current_degree;
	}

	polynomial polynomial::derivative(unsigned int n) const {
		polynomial der;
		der.reserve(degree());
		for (unsigned int i = 1; i != 0; i = next_term(i))
			der.assign_coef(coefficient(i) * i, i - 1);
		return n == 1 ? der : der.derivative(n - 1);
	}

	double polynomial::eval(double x) const {
		double total = coefficient(0);
		for (unsigned int i = next_term(0); i != 0; i = next_term(i))
			total += coefficient(i) * pow(x, i);
		return total;
	}

	void polynomial::find_root(double& answer, bool& success, unsigned int& iterations, double guess, unsigned int maximum_iterations, double epsilon) const {
		assert(epsilon > 0);

		success = false;
		answer = guess;

		polynomial der = derivative();
		double f = eval(answer), fprime = der.eval(answer);

		for (iterations = 0; iterations < maximum_iterations; ++iterations) {
			if (fabs(f) <= epsilon) {
				success = true;
				return;
			}
			else if (fabs(fprime) <= epsilon) {
				success = false;
				return;
			}
			answer = guess = answer - f/fprime;
			f = eval(guess);
			fprime = der.eval(guess);
		}
	}

	polynomial polynomial::integral(unsigned int n) const {
		polynomial integ(coefficient(0), 1);
		integ.reserve(degree() + 1);
		for (unsigned int i = next_term(0); i != 0; i = next_term(i))
			integ.assign_coef(coefficient(i) / (i + 1), i + 1);
		return n == 1 ? integ : integ.integral(n - 1);
	}

	unsigned int polynomial::next_term(unsigned int e) const {
		for (unsigned int i = e + 1; i <= degree(); ++i)
			if (coefficient(i) != 0)
				return i;
		return 0;
	}

	unsigned int polynomial::previous_term(unsigned int e) const {
		if (e == 0) return UINT_MAX;
		for (unsigned int i = e - 1; i >= 0; --i) {
			if (coefficient(i) != 0) return i;
			if (i == 0) break;
		}
		return UINT_MAX;
	}

	double polynomial::numeric_integral(double low_bound, double high_bound, unsigned int many_trapezoids) const {
		assert(many_trapezoids > 0);
		if (low_bound > high_bound) return -1 * numeric_integral(high_bound, low_bound);
		double witdth = (high_bound - low_bound) / (many_trapezoids * 2);
		double answer = eval(low_bound) + eval(high_bound);
		for (double i = witdth; i < high_bound; i += witdth)
			answer += eval(i) * 2;
		return witdth * answer * 0.5;
	}

	polynomial polynomial::substitution(const polynomial& p) const {
		polynomial sub;
		sub.reserve(p.degree() + degree() + 1);
		for (unsigned int i = 0; i <= p.degree(); ++i)
			for (unsigned int j = 0; j <= degree(); ++j)
				sub.add_to_coef(p.coefficient(i) * coefficient(j), i + j);
		return sub;
	}

	// CONSTANT OPERATORS
	polynomial polynomial::operator -() const {
		return *this * -1;
	}

	// NON-MEMBER BINARY OPERATORS
	polynomial operator +(const polynomial& p1, const polynomial& p2) {
		polynomial sum = p1;
		sum.reserve(p2.degree() + 1);
		sum.add_to_coef(p2.coefficient(0), 0);
		for(unsigned int i = p2.next_term(0); i != 0; i = p2.next_term(i)) sum.add_to_coef(p2.coefficient(i), i);
		return sum;
	}

	polynomial operator +(const polynomial& p, double c) {
		polynomial total = p;
		total.add_to_coef(c, 0);
		return total;
	}

	polynomial operator -(const polynomial& p1, const polynomial& p2) {
		polynomial difference = p1;
		difference.reserve(p2.degree() + 1);
		difference.add_to_coef(-p2.coefficient(0), 0);
		for(unsigned int i = p2.next_term(0); i != 0; i = p2.next_term(i)) difference.add_to_coef(-p2.coefficient(i), i);
		return difference;
	}

	polynomial operator *(const polynomial& p1, const polynomial& p2) {
		polynomial product;
		product.reserve(p1.degree() + p2.degree() + 1);
		for (unsigned int i = 0; i <= p1.degree(); ++i)
			for (unsigned int j = 0; j <= p2.degree(); ++j)
				product.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
		return product;
	}

	polynomial operator *(const polynomial& p, double c) {
		polynomial product(p.coefficient(0) * c, 0);
		product.reserve(p.degree() + 1);
		for(unsigned int i = p.next_term(0); i != 0; i = p.next_term(i)) 
			product.assign_coef(p.coefficient(i) * c, i);
		return product;
	}

	polynomial operator ^(const polynomial& p, unsigned int n) {
		polynomial power = p;
		power.reserve(p.degree() * n + 1);
		for (unsigned int i = 1; i < n; ++i)
			power *= p;
		return power;
	}

	// NON-MEMBER INPUT/OUTPUT FUNCTIONS
	std::istream& operator >> (std::istream& in, polynomial& p);
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
}
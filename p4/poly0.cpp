#include "poly0.h"

namespace main_savitch_3
{
	// CONSTRUCTOR
	polynomial::polynomial(double c, unsigned int exponent);

	// MODIFICATION MEMBER FUNCTIONS
	void polynomial::add_to_coef(double amount, unsigned int exponent);
	void polynomial::assign_coef(double coefficient, unsigned int exponent);
	void polynomial::clear();

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
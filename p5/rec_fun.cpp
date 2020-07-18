#include <iostream> // Provides cout
#include <string>   // Provides string
using namespace std;

void triangle(ostream& outs, unsigned int m, unsigned int n) {
	// Precondition: m <= n
	// Postcondition: The function has printed a pattern of 2*(n-m+1) lines
	// to the output stream outs. The first line contains m asterisks, the next 
	// line contains m+1 asterisks, and so on up to a line with n asterisks.
	// Then the pattern is repeated backwards, going n back down to m.
	/* Example output:
	 triangle(cout, 3, 5) will print this to cout:
	 ***
	 ****
	 *****
	 *****
	 ****
	 ***
	*/
	if (m > n) return;
	for (unsigned int i = 0; i < m; ++i) outs << "*";
	cout << endl;
	triangle(outs, m + 1, n);
	for (unsigned int i = 0; i < m; ++i) outs << "*";
	cout << endl;
}

void numbers(ostream& outs, const string& prefix, unsigned int levels) {
	if (levels == 0) {
		outs << prefix << endl;
		return;
	}
	for (unsigned int i = 1; i <= 9; ++i) {
		numbers(outs, prefix + char(i + '0') + '.', levels - 1);
	}
}

int main() {
	triangle(cout, 3, 5);
	numbers(cout, "PREFIX", 2);
	return 0;
}
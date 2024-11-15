#pragma once
#include <iostream>

class Fraction {
	private:
		int numerator;
		int denominator;

		// helper functions
		int gcd() const;

		// functions to make the result pretty
		void reduce();
		void normalize();
	public:
		// constructors
		Fraction();
		Fraction(int, int);
		Fraction(const Fraction&);

		// output
		friend std::ostream& operator<<(std::ostream&, const Fraction&);

		// arithmetic
		void add(const Fraction&);
		Fraction operator+(const Fraction&);
};

#include "fraction.h"

using namespace std;


Fraction::Fraction(): Fraction(0,0) {}

Fraction::Fraction(int n, int d)
{
	numerator = n;
	denominator = d;
}

Fraction::Fraction(const Fraction& other)
{
	this->numerator = other.numerator;
	this->denominator = other.denominator;
}

//GCD = Greatest Common Divisor
int Fraction::gcd() const
{
	int max = (numerator > denominator) ? numerator : denominator;
	int min = (numerator < denominator) ? numerator : denominator;

	while (min) {
		max %= min;

		int swap_hold = max;
		max = min;
		min = swap_hold;
	}
	
	return max;
}

//"Euclidean Algorithm": https://en.wikipedia.org/wiki/Euclidean_algorithm
void Fraction::reduce()
{
	int gcd = this->gcd();

	numerator /= gcd;
	denominator /= gcd;
}

void Fraction::normalize()
{
	if (numerator < 0 and denominator < 0) { //-a/-b -> a/b
		numerator = -numerator;
		denominator = -denominator;
	}
	else if (numerator >= 0 and denominator < 0) { // a/-b -> -a/b
		numerator = -numerator;
		denominator = -denominator;
	}
}

ostream& operator<<(ostream& out, const Fraction& obj)
{
	out << obj.numerator << '/' << obj.denominator;
	return out;
}

void Fraction::add(const Fraction& other)
{
	//a/b + c/d = (ad + cb)/(bd)
	numerator *= other.denominator;
	numerator += other.numerator * denominator;

	denominator *= other.denominator;

	reduce();
	normalize();
}

Fraction Fraction::operator+(const Fraction& other)
{
	Fraction f_new(*this); // copy this obj into new fraction
	f_new.add(other);
	return f_new;
}

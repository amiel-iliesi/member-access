#include "fraction.h"
#include <iostream>

using namespace std;

int main()
{
	Fraction f1(1,2);
	Fraction f2(-3,4);
	
	cout << f1 << " + " << f2 << " = " << f1 + f2 << endl;

	return 0;
}

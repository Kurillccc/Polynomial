#include <iostream>

#include "Polynom.h"

using namespace std;

unsigned int main()
{
	setlocale(LC_ALL, "rus");

	string str1 = "3X1^2X2^3X3^2X4^3 + 2X1^2 + X2^3";
	string str2 = "-2X1^3X2^2X3^3 + X2^3";

	int maxDegree = 5;
	int count = 10;

	Polynom a(str1, maxDegree, count);
	Polynom b(str2, maxDegree, count);
	Polynom c(a);
	Polynom d = a;

	cout << "a: ";
	a.printPolynomial();

	cout << "b: ";
	b.printPolynomial();

	cout << "c(à): ";
	c.printPolynomial();

	cout << "d = a: ";
	d.printPolynomial();

	Polynom sum = a + b;
	cout << "a + b: ";
	sum.printPolynomial();

	Polynom dif = a - b;
	cout << "a - b: ";
	dif.printPolynomial();
	cout << endl;

	Polynom multiplyK = a * 2;
	cout << "a * 2: ";
	multiplyK.printPolynomial();

	Polynom multiply = a * b;
	cout << "a * b: ";
	multiply.printPolynomial();

	system("pause");

	return 0;
}
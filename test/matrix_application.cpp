#include <iostream>
#include "../include/matrix.h"

int main(void){

	// Transpose test
	Matrix<double> m1(3,1);
	m1 = {1,2,3};
	m1.print();

	m1.transpose().print();

	// Norm test
	Matrix<double> m2(3,2);
	m2 = {1,2,3,4,5,6};
	cout << m2.norm() << endl;

	// Summation test
	Matrix<double> m3(3,2);
	m3 = {1,2,3,4,5,6};
	m3.print();
	cout << "Summation each row" << endl;
	m3.sum(1).print();

	cout << "Summation each row" << endl;
	m3.sum(2).print();

	cout << "Summation all" << endl;
	m3.sum(2).sum(1).print();	

	// Max / Min test
	Matrix<double> m4(3,5);
	m4 = range(15);
	m4.print();
	cout << "Max of m4 : " << m4.max() << endl;
	cout << "Min of m4 : " << m4.min() << endl;
	
	// Matrix of ones test
	cout << "Matrix which all values are 1" << endl;
	ones(2,2).print();
	ones(4,3).print();	


	// Random value test
	cout << "random value matrix" << endl;
	random(3,5).print();


}

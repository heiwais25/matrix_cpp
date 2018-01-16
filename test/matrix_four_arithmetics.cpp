#include <iostream>

#include "../include/matrix.h"

/*
	
	This file is intened to test arithmetics of matrix class

 */

void test_addition();
void test_subtraction();
void test_multiplication();
void test_division();
#define MULTIPY_TEST
int main(void){

	// test_addition();
	// test_subtraction();

	// test_multiplication();
	// test_division();


	
}


void test_multiplication(){
	cout << "Multiplication test" << endl;
	// Matrix x scalr
	// Scalar x Matrix
	Matrix<double> m1(2,2);
	m1 = {1,2,3,4};
	m1.print();
	Matrix<double> m2 = m1 * 2;
	m2 = 2 * m1;
	m2.print();


	// Dot product
	Matrix<double> m3(3,2);
	m3 = {1,2,3,4,5,6};
	Matrix<double> m4(2,1);
	m4 = {1,1};
	m3.dot(m4).print();

	// Matrix x Matrix(element wise)
	Matrix<double> m5(2,2);
	m5 = {2,2,2,2};
	(m5 * m1).print();

	// Matrix x vector(broadcast)
	Matrix<double> m6(2,1);
	m6 = {1,2};
	Matrix<double> m7 = m5 * m6;
	m7.print();

	Matrix<double> m8(1,2);
	m8 = {1,2};
	Matrix<double> m9 = m5 * m8;
	m9.print();

	Matrix<double> m10(5,3);
	m10 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	m10 *= 2;
	m10.print();

}

void test_division(){
	cout << "Division test" << endl;
	// Matrix x scalr
	// Scalar x Matrix
	Matrix<double> m1(2,2);
	m1 = {1,2,3,4};
	m1.print();
	Matrix<double> m2 = m1 / 2;
	m2 = 2 / m1;
	m2.print();


	// Dot product
	Matrix<double> m3(3,2);
	m3 = {1,2,3,4,5,6};
	Matrix<double> m4(2,1);
	m4 = {1,1};
	m3.dot(m4).print();

	// Matrix x Matrix(element wise)
	Matrix<double> m5(2,2);
	m5 = {2,2,2,2};
	(m5 / m1).print();

	// Matrix x vector(broadcast)
	Matrix<double> m6(2,1);
	m6 = {1,2};
	Matrix<double> m7 = m5 / m6;
	m7.print();

	Matrix<double> m8(1,2);
	m8 = {1,2};
	Matrix<double> m9 = m5 / m8;
	m9.print();

	Matrix<double> m10(5,3);
	m10 = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	m10 /= 2;
	m10.print();

}

void test_addition(){
	cout << "Addition test" << endl;
	Matrix<int> m1(2,2), m2(2,2);
	m1 = {1,2,3,4};
	m2 = {2,3,4,5};
	Matrix<int> m3 = m1 + m2;
	m3.print();

	Matrix<int> m4(1,2);
	m4 = {1,1};
	m4.print();
	Matrix<int> m5 = m3 + m4;
	m5.print();

	Matrix<int> m6(2,1);
	m6 = {1,1};
	(m3 + m6).print();

	// Matrix + number
	Matrix<int> m7(2,2);
	m7 = {1,2,3,4};
	m7.print();
	cout << " + 3 " << endl;
	m7 = m7 + 3;
	m7.print();
	cout << " + 3 " << endl;
	m7 = 3 + m7;
	m7.print();

	// +=
	Matrix<int> m8(2,2);
	m8 = {1,2,3,4};
	m8.print();
	m8 += m7;
	m8.print();

	Matrix<int> m9(2,2);
	m9 = {1,2,3,4};
	m9.print();
	cout << "+= 5" << endl;
	m9 += 5;
	m9.print();
}

void test_subtraction(){
	cout << "Subtraction test" << endl;
	Matrix<int> m10(2,2), m11(2,2);
	m10 = {1,2,3,4};
	m11 = {2,3,4,5};
	Matrix<int> m12 = m10 - m11;
	m12.print();

	Matrix<int> m13(1,2);
	m13 = {1,1};
	m13.print();
	Matrix<int> m14 = m12 - m13;
	m14.print();

	Matrix<int> m15(2,1);
	m15 = {1,1};
	(m12 - m15).print();

	// Matrix + number
	Matrix<int> m16(2,2);
	m16 = {1,2,3,4};
	m16.print();
	cout << " - 3 " << endl;
	m16 = m16 - 3;
	m16.print();
	cout << " - 3 " << endl;
	m16 = 3 - m16;
	m16.print();

	// +=
	Matrix<int> m17(2,2);
	m17 = {1,2,3,4};
	m17.print();
	m17 -= m16;
	m17.print();

	Matrix<int> m18(2,2);
	m18 = {1,2,3,4};
	m18.print();
	cout << "-= 5" << endl;
	m18 -= 5;
	m18.print();	
}
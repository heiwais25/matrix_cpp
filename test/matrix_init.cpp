#include <iostream>
#include <vector>
#include "../include/matrix.h"

using std::vector;
/*
	
	This file is intened to test Initialization of matrix

 */
// #define INIT_TEST
#define SUBS_TEST

int main(void){
#ifdef INIT_TEST
	// Dimension init test
	Matrix<int> m0;
	m0.dims().print(); // 1x1
	
	Matrix<int> m1(2,2);
	m1.dims().print(); // 2x2

	vector<int> v1 = {2,1};
	Matrix<int> m2(v1); // 2x1
	m2.dims().print();
#endif
#ifdef SUBS_TEST
	// Matrix substitution test
	vector<int> v2(9,1);
	Matrix<int> m3(1,1);
	m3 = v2; // vector substitution
	m3.print();

	m3 = {1,2,3,4,5,6,7,8,9}; // Initializer list substitution	
	m3.print();

	Matrix<int> m4(2,2);
	m4 = {1,2,3,4};
	m3 = m4;
	m3.print();
#endif
}
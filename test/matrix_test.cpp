#include "matrix.h"

int main(void){
	Matrix<double> matrix(5,2);
	Matrix<double> matrix2(5,2);
	cout << (matrix == matrix2) << endl;
	cout.setf(std::ios::left);


	// Scalar product test
	cout.fill('=');
	cout << std::setw(50) << "=" << endl;
	cout << "Matrix scalar production test" << endl;

	matrix(1,1) = 5;
	matrix2(4,1) = 6;

	Matrix<double> m = matrix + matrix2;
	m.print();
	double t = 2;
	m = m*t;
	m.print();
	
	// Addition example
	
	cout.setf(std::ios::left);
	cout.fill('=');
	cout << std::setw(50) << "=" << endl;
	cout << "Matrix addition test" << endl;
	
	Matrix<double> v(5,1);	
	v = {1,2,3,4,5};
	m.print();
	cout << "Plus" << endl;
	v.print();
	m = m + v;
	cout << "Result" << endl;
	m.print();

	// Dot example
	cout.setf(std::ios::left);
	cout.fill('=');
	cout << std::setw(50) << "=" << endl;
	cout << "Dot product test" << endl;
	Matrix<double> m1(1,3), m2(3,1);
	std::vector<double> v1 = {1,2,3}, v2 = {1,2,1};
	m1 = v1;
	m2 = v2;
	m1.print();
	cout << "dot" << endl;
	m2.print();
	cout << "Result : " << m1.dot(m2)[0] << endl;

	// Reshape example
	cout << std::setw(50) << "=" << endl;
	cout << "Reshape test" << endl;
	Matrix<double> m3(3,5);
	cout << "before" << endl;
	m3 = std::vector<double>{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	m3.print();
	cout << "after" << endl;
	m3.reshape(5,3).print();

	// Norm example
	cout << std::setw(50) << "=" << endl;
	cout << "Norm test" << endl;
	Matrix<double> m4(2,2);
	m4 = std::vector<double>{1,2,3,4};
	m4.print();
	cout << "Norm : " << m4.norm() << endl;

	// Max, min example
	cout << std::setw(50) << "=" << endl;
	cout << "Max/Min test" << endl;
	Matrix<double> m5(2,2);
	m5 = std::vector<double>{1,2,3,4};
	m5.print();
	cout << "Max : " << m5.max() << " Min : " << m5.min() << endl;

	// Max, min example
	cout << std::setw(50) << "=" << endl;
	cout << "Entrywise product test" << endl;
	Matrix<double> m6(2,2), m7(2,2);
	m6 = std::vector<double>{1,2,3,4};
	m7 = std::vector<double>{1,2,3,4};
	m6.print();
	m7.print();
	cout << "Result" << endl;
	(m6*m7).print();


	return 0;

	// Max example
}


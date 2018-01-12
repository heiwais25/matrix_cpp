#ifndef MATRIX_
#define MATRIX_

#include <valarray>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <iomanip>
#include <cmath>
using std::cerr;
using std::endl;
using std::cout;

struct MatrixSizeException{};
struct OutOfIndexException{};
template <class element_type>
class Matrix{
	public:
		Matrix(void):
			m_height(1), m_stride(1), m_storage(1)
			{};

		Matrix(size_t height, size_t width):
			m_height(height), m_stride(width), m_storage(width * height)
			{};

		element_type & operator()(size_t row, size_t column);
		element_type & operator[](size_t num);
		bool operator==(Matrix & m); // Return true if all element is same
		Matrix operator*(Matrix & m); // Calculate elementwise product
		Matrix operator+(Matrix & m);	

		template <typename T>
		Matrix operator*(T val);

		// Init matrix by vector
		template <typename T>
		void operator=(const std::vector<T> & v);

		// Return norm of the matrix
		double norm(void);

		// Return max / min value of this matrix
		element_type max(void);
		element_type min(void);		

		// Return total size of m_storage(m_height x m_stride)
		size_t size();

		// Return reshaped matrix
		Matrix reshape(size_t new_height, size_t new_stride);


		// Calculate dot product
		Matrix dot(Matrix &m);

		// Print all element with its dimension
		void print(void);
		
		// Return dimension matrix
		Matrix dims(void);
		
		// Sum direction (1 : sum each row, 2 : sum each cloumn)
		Matrix sum(char direction);
		

	private:
		std::valarray<element_type> m_storage;
		size_t m_stride;
		size_t m_height;
};

#endif 

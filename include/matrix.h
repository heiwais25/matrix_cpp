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

/*
	XXX 
	1. Can we make iterator of horizontal and vertical separately?
		- It seems we don't need that feature
*/

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

		template <typename T>
		void operator=(const std::initializer_list<T> l);

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
		struct MatrixSizeException{};
		struct OutOfIndexException{};

};

/* =======================================================================

	Operator overloading

======================================================================= */

template <class element_type>
element_type & Matrix<element_type>::operator()(size_t row, size_t column){
	if(row >= m_height || column >= m_stride){
		cerr << "Check matrix dimension" << endl;
		this->dims().print();
		throw OutOfIndexException();
	}
	return m_storage[row * m_stride + column]; // column major
}

template <class element_type>
element_type & Matrix<element_type>::operator[](size_t num){
	if(m_stride > 1 || num >= m_height){
		throw OutOfIndexException();
	}
	return m_storage[num]; // column major
}

template <class element_type>
Matrix<element_type> Matrix<element_type>::operator*(Matrix & m){
	if(m.m_stride != m_stride || m.m_height != m_height){
		throw MatrixSizeException();
	}

	Matrix ret(m_height, m_stride);
	for(auto i=0;i<m_height;i++){
		for(auto j=0;j<m_stride;j++){
			ret(i,j) = (*this)(i,j) * m(i,j);
		}
	}
	return ret;
}

template <class element_type>
template <typename T>
void Matrix<element_type>::operator=(const std::vector<T> & v){
	if(v.size() != m_storage.size())
		throw MatrixSizeException();

	for(auto i=0;i<m_height;i++){
		for(auto j=0;j<m_stride;j++){
			(*this)(i,j) = v[i * m_stride + j];
		}
	}
}

template <class element_type>
template <typename T>
void Matrix<element_type>::operator=(const std::initializer_list<T> l){
	if(l.size() != m_storage.size())
		throw MatrixSizeException();

	std::copy(l.begin(), l.end(), begin(m_storage));

}

template<class element_type>
bool Matrix<element_type>::operator==(Matrix & m){
	if(m.m_height == m_height && m.m_stride == m_stride){
		int count_error = 0;
		for(auto i=0;i<m_height;i++)
			for(auto j=0;j<m_stride;j++)
				if(m(i, j) != (*this)(i,j))
					return false;
		return true;
	}
	else{
		return false;
	}
}

template<class element_type>
Matrix<element_type> Matrix<element_type>::operator+(Matrix & m){
	Matrix ret(m_height,m_stride);
	if(this->size() == m.size())
		ret.m_storage = m.m_storage + m_storage;
	else if(m_height == m.dims()[0] && m.dims()[1] == 1){
		for(int i=0;i<m_height;i++)
			for(int j=0;j<m_stride;j++)
				ret(i,j) = (*this)(i,j) + m[i];
	}
	else{
		throw MatrixSizeException();
	}
	return ret;
}

template <class element_type>
template <typename T>
Matrix<element_type> Matrix<element_type>::operator*(T val){
	this->m_storage *= val;
	return *this;
}

/* =======================================================================

	Method overloading

======================================================================= */
template <class element_type>
Matrix<element_type> Matrix<element_type>::reshape(size_t new_height, size_t new_stride){
	if(new_height * new_stride != m_storage.size())
		throw MatrixSizeException();

	Matrix ret(new_height, new_stride);
	for(int i=0;i<new_height;i++){
		for(int j=0;j<new_stride;j++){
			ret(i,j) = m_storage[i * new_stride + j]; 
		}
	}
	return ret;
}

template<class element_type>
Matrix<element_type> Matrix<element_type>::dot(Matrix &m){
	Matrix ret(m_height,m.m_stride);
	// Check dimension
	if(m_stride == m.m_height){
		for(int hi=0;hi<m_height;hi++){
			for(int wi=0;wi<m.m_stride;wi++){
				for(int j=0;j<m_stride;j++){
					ret(hi,wi) += (*this)(hi, j) * m(j,wi);
				}
			}
		}
	}
	else{
		throw MatrixSizeException();
	}
	return ret;
}

// Print all element with its dimension
template<class element_type>
void Matrix<element_type>::print(void){
	//cout << m_height << " x " << m_stride << endl;
	if(m_stride == 1){
		for(int i=0;i<m_storage.size();i++){
			cout << m_storage[i] << " " ;
			if(((i+1) % m_stride) == 0) cout << endl;
		}	
	} 
	else if(m_height == 1){
		for(int i=0;i<m_storage.size();i++)
			cout << m_storage[i] << " " ;
		cout << endl;
	}
	else{
		for(int i=0;i<m_storage.size();i++){
			cout << m_storage[i] << " " ;
			if(((i+1) % m_stride) == 0) cout << endl;
		}	
	}
}

template <class element_type>
Matrix<element_type> Matrix<element_type>::sum(char direction){
	size_t length;
	Matrix ret;
	if(direction == 1){ // Sum each row
		length = m_height;
		ret = Matrix(length, 1);
		for(size_t i=0;i<m_height;i++){
			std::valarray<element_type> one_row(
					m_storage[std::slice(m_stride * i, m_stride, 1)]
					);
			ret[i] = one_row.sum();
		}
	} 
	else if(direction == 2){
		length = m_stride;
		ret = Matrix(1, length);
		for(size_t i=0;i<m_stride;i++){
			std::valarray<element_type> one_column(
					m_storage[std::slice(i, m_height, m_stride)]
					);
			ret[i] = one_column.sum();
		}
	}
	else{
		std::cerr << "Please enter correct direction" << std::endl;
	}
	return ret;
}

template <class element_type>
Matrix<element_type> Matrix<element_type>::dims(void){
	Matrix ret(2,1);
	ret(0,0) = m_height, ret(1,0) = m_stride;
	return ret;
}

template <class element_type>
double Matrix<element_type>::norm(void){
	return std::sqrt(std::pow(m_storage,2.0).sum());
}

template <class element_type>
element_type Matrix<element_type>::max(void){
	return m_storage.max();
}

template <class element_type>
element_type Matrix<element_type>::min(void){
	return m_storage.min();
}

template <class element_type>
size_t Matrix<element_type>::size(){
	return m_storage.size();
}


#endif 

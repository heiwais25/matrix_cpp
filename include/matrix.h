#ifndef MATRIX_
#define MATRIX_

#include <valarray>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
using std::cerr;
using std::endl;
using std::cout;
using std::vector;
/*
	XXX 
	1. Can we make iterator of horizontal and vertical separately?
		- It seems we don't need that feature
*/



template <class element_type>
class Matrix{
	public:
		~Matrix(void){};
		Matrix(void):
			m_height(1), m_stride(1), m_storage(1)
			{};

		Matrix(size_t height, size_t width):
			m_height(height), m_stride(width), m_storage(width * height)
			{};

		template <typename T>
		Matrix(std::vector<T> dims){
			if(dims.size() != 2){
				throw MatrixSizeException();
			}
			m_height = dims[0];
			m_stride = dims[1];
			m_storage = std::valarray<element_type>(m_stride * m_height);
		}

		template <typename T>
		Matrix(Matrix<T> ref){
			*this = ref;
		}

		element_type & operator()(size_t row, size_t column);
		element_type & operator[](size_t num);
		bool operator==(Matrix & m); // Return true if all element is same

		Matrix operator+(Matrix & m);	
		template <typename T>
		Matrix operator+(T val);
		
		Matrix & operator+=(Matrix & ref);
		template <typename T>
		Matrix & operator+=(T val);

		Matrix operator-(Matrix & m);	
		template <typename T>
		Matrix operator-(T val);
		
		Matrix & operator-=(Matrix & ref);
		template <typename T>
		Matrix & operator-=(T val);

		template <typename T>
		Matrix operator*(T val);
			
		Matrix operator*(Matrix & m); // Calculate elementwise product
		template <typename T>
		Matrix & operator*=(T val);

		template <typename T>
		Matrix operator/(T val);
			
		Matrix operator/(Matrix & m); // Calculate elementwise product
		template <typename T>
		Matrix & operator/=(T val);

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
		
		Matrix transpose(void);


	private:
		std::valarray<element_type> m_storage;
		size_t m_stride;
		size_t m_height;
		struct MatrixSizeException{};
		struct OutOfIndexException{};

};

// template<typename T>
Matrix<double> ones(size_t height, size_t stride);

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
template <typename T>
void Matrix<element_type>::operator=(const std::vector<T> & v){
	if(m_storage.size() == 1){ // Defualt
		Matrix<element_type> ret(v.size(), 1);
		ret = v;
		*this = ret;
	}
	else{
		if(v.size() != m_storage.size())
			throw MatrixSizeException();
		std::copy(v.begin(), v.end(), begin(m_storage));
	}	
}

template <class element_type>
template <typename T>
void Matrix<element_type>::operator=(const std::initializer_list<T> l){
	if(m_storage.size() == 1){ // Defualt
		Matrix<element_type> ret(l.size(), 1);
		ret = l;
		*this = ret;
	}
	else{
		if(l.size() != m_storage.size())
			throw MatrixSizeException();
		std::copy(l.begin(), l.end(), begin(m_storage));
	}
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

// ========================================================================
// Addition method
// ========================================================================
template<class element_type>
Matrix<element_type> Matrix<element_type>::operator+(Matrix & m){
	Matrix ret(m_height,m_stride);
	if(m.size() == 1)
		ret.m_storage = m_storage + m[0];
	else if(this->size() == m.size()){
		ret.m_storage = m.m_storage + m_storage;
	}
	// Broadcast case
	else if(m.dims()[0] == m_height && m.dims()[1] == 1){
		for(int i=0;i<m_height;i++)
			for(int j=0;j<m_stride;j++)
				ret(i,j) = (*this)(i,j) + m(i,0);
	}
	else if(m.dims()[0] == 1 && m.dims()[1] == m_stride){
		for(int j=0;j<m_stride;j++)
			for(int i=0;i<m_height;i++)
				ret(i,j) = (*this)(i,j) + m(0,j);
	}
	else{
		throw MatrixSizeException();
	}
	return ret;
}

template<class element_type>
template<typename T>
Matrix<element_type> Matrix<element_type>::operator+(T val){
	Matrix ret(*this);
	for(int i=0;i<ret.m_height;i++){
		for(int j=0;j<ret.m_stride;j++){
			ret(i,j) = ret(i,j) + val;
		}
	}
	return ret;
}

template<class element_type, typename T>
Matrix<element_type> operator+(T val, Matrix<element_type> ref){
	Matrix<element_type> ret(ref);
	for(int i=0;i<ref.dims()[0];i++){
		for(int j=0;j<ref.dims()[1];j++){
			ret(i,j) = ref(i,j) + val;
		}
	}
	// ret.m_storage += val;
	return ret;
}

template<class element_type>
Matrix<element_type> & Matrix<element_type>::operator+=(Matrix & ref){
	*this = *this + ref;
	return *this;
};

template<class element_type>
template<typename T>
Matrix<element_type> & Matrix<element_type>::operator+=(T val){
	this->m_storage += val;
	return *this;
};

// ========================================================================
// Subtract method
// ========================================================================
template<class element_type>
Matrix<element_type> Matrix<element_type>::operator-(Matrix & m){
	Matrix ret(m_height,m_stride);
	if(m.size() == 1){
		ret.m_storage = m_storage - m[0];
	}
	else if(this->size() == m.size()){
		ret.m_storage = m_storage - m.m_storage;
	}
	else if(m.dims()[0] == m_height && m.dims()[1] == 1){
		for(int i=0;i<m_height;i++)
			for(int j=0;j<m_stride;j++)
				ret(i,j) = (*this)(i,j) - m(i,0);
	}
	else if(m.dims()[0] == 1 && m.dims()[1] == m_stride){
		for(int j=0;j<m_stride;j++)
			for(int i=0;i<m_height;i++)
				ret(i,j) = (*this)(i,j) - m(0,j);
	}
	else{
		throw MatrixSizeException();
	}
	return ret;
}

template<class element_type>
template<typename T>
Matrix<element_type> Matrix<element_type>::operator-(T val){
	Matrix ret(*this);
	for(int i=0;i<ret.m_height;i++){
		for(int j=0;j<ret.m_stride;j++){
			ret(i,j) = ret(i,j) - val;
		}
	}
	return ret;
}

template<class element_type, typename T>
Matrix<element_type> operator-(T val, Matrix<element_type> ref){
	Matrix<element_type> ret(ref);
	for(int i=0;i<ref.dims()[0];i++){
		for(int j=0;j<ref.dims()[1];j++){
			ret(i,j) = val - ref(i,j);
		}
	}
	return ret;
}

template<class element_type>
Matrix<element_type> & Matrix<element_type>::operator-=(Matrix & ref){
	*this = *this - ref;
	return *this;
};

template<class element_type>
template<typename T>
Matrix<element_type> & Matrix<element_type>::operator-=(T val){
	this->m_storage -= val;
	return *this;
};

// ========================================================================
// Multiplication method
// ========================================================================
template <class element_type>
Matrix<element_type> Matrix<element_type>::operator*(Matrix & m){
	Matrix ret(m_height, m_stride);
	if(m.dims()[0] == 1 && m.dims()[1] == m_stride){
		for(int i=0;i<m_height;i++){
			for(int j=0;j<m_stride;j++){
				ret(i,j) = (*this)(i,j) * m(0, j);
			}
		}
	}
	else if(m.dims()[0] == m_height && m.dims()[1] == 1){
		for(int j=0;j<m_stride;j++){
			for(int i=0;i<m_height;i++){
				ret(i,j) = (*this)(i,j) * m(i, 0);
			}
		}
	}
	else if(m.size() == this->size()){
		for(auto i=0;i<m_height;i++){
			for(auto j=0;j<m_stride;j++){
				ret(i,j) = (*this)(i,j) * m(i,j);
			}
		}
	}
	else{
		throw MatrixSizeException();
	}
	return ret;
}


template <class element_type>
template <typename T>
Matrix<element_type> Matrix<element_type>::operator*(T val){
	Matrix ret(m_height, m_stride);
	ret.m_storage = m_storage;
	ret.m_storage *= (double)val;
	return ret;
}

template <class element_type, typename T>
Matrix<element_type> operator*(T val, Matrix<element_type> & ref){
	Matrix<element_type> ret(ref);
	for(int i=0;i<ref.dims()[0];i++){
		for(int j=0;j<ref.dims()[1];j++){
			ret(i,j) = ret(i,j) * val;
		}
	}
	return ret;
}

template<class element_type>
template<typename T>
Matrix<element_type> & Matrix<element_type>::operator*=(T val){
	this->m_storage *= val;
	return *this;
};

// ========================================================================
// Division method
// ========================================================================
template <class element_type>
Matrix<element_type> Matrix<element_type>::operator/(Matrix & m){
	Matrix ret(m_height, m_stride);
	if(m.dims()[0] == 1 && m.dims()[1] == m_stride){
		for(int i=0;i<m_height;i++){
			for(int j=0;j<m_stride;j++){
				ret(i,j) = (*this)(i,j) / m(0, j);
			}
		}
	}
	else if(m.dims()[0] == m_height && m.dims()[1] == 1){
		for(int j=0;j<m_stride;j++){
			for(int i=0;i<m_height;i++){
				ret(i,j) = (*this)(i,j) / m(i, 0);
			}
		}
	}
	else if(m.size() == this->size()){
		for(auto i=0;i<m_height;i++){
			for(auto j=0;j<m_stride;j++){
				ret(i,j) = (*this)(i,j) / m(i,j);
			}
		}
	}
	else{
		throw MatrixSizeException();
	}
	return ret;
}


template <class element_type>
template <typename T>
Matrix<element_type> Matrix<element_type>::operator/(T val){
	Matrix ret(m_height, m_stride);
	ret.m_storage = m_storage;
	ret.m_storage /= (double)val;
	return ret;
}

template <class element_type, typename T>
Matrix<element_type> operator/(T val, Matrix<element_type> & ref){
	Matrix<element_type> ret(ref);
	for(int i=0;i<ref.dims()[0];i++){
		for(int j=0;j<ref.dims()[1];j++){
			ret(i,j) = ret(i,j) / (double)val;
		}
	}
	return ret;
}

template<class element_type>
template<typename T>
Matrix<element_type> & Matrix<element_type>::operator/=(T val){
	this->m_storage /= (double)val;
	return *this;
};



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
	cout << "( " << m_height << " x " << m_stride << " )" << endl;
	for(int i=0;i<m_storage.size();i++){
		cout << m_storage[i] << " " ;
		if(((i+1) % m_stride) == 0) cout << endl;
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
			ret(0, i) = one_column.sum();
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
Matrix<element_type> Matrix<element_type>::transpose(void){
	Matrix ret(m_stride, m_height);
	for(int i=0;i<m_height;i++){
		for(int j=0;j<m_stride;j++){
			ret(j, i) = (*this)(i,j);
		}
	}
	return ret;
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

// Global functions
// template<typename T>
Matrix<double> ones(size_t height, size_t stride){
	Matrix<double> ret(height, stride);
	ret = vector<double>(height * stride, 1);
	return ret;
}

Matrix<double> range(size_t start, size_t end, double step_size){
	Matrix<double> ret((int)(((double)(end-start))/step_size), 1);
	for(int i=0;i<(int)(((double)(end-start))/step_size);i++){
		ret(i, 0) = start + step_size * i;
	}
	return ret;
}

Matrix<double> range(size_t start, size_t end){
	Matrix<double> ret(end-start, 1);
	for(int i=0;i<end-start;i++){
		ret(i, 0) = start + i;
	}
	return ret;
}

Matrix<double> range(size_t end){
	Matrix<double> ret(end, 1);
	for(int i=0;i<end;i++){
		ret(i, 0) = i;
	}
	return ret;
}

Matrix<double> random(size_t height, size_t width, int seed = 1){
	Matrix<double> ret(height, width);
	srand((unsigned int)time(NULL) * seed);
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			ret(i, j) = (double)(rand() % 100000) / (double)100000;
		}
	}
	return ret;
}

#endif 

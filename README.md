This is matrix implementation by cpp.
If you include matrix.h in the include directory, you can use matrix simliart with numpy in python.

## Initialization
- Matrix(void) : Set 1x1 dimension matrix
- Matrix(row, column) : Set row x cloumn matrix
- operator(=) : from vector or initializer list. Before use this, dimension need to be set

## Reference
- operator(row, column) : Return or set value at this position
- operator[num] : Return or set value at that index in 1D vector(column = 1)

## Calculation
- operator(*) : Calculation elementwise product
- operator(==) : Return true if all matrix element are same
- operator(+) : Calculate addition of matrix. If one is matrix and one is vector and vector length is same with matrix height, vector will be broadcast and addition will be done
- norm() : Return the magnitude of matrix
- max / min : Return max or min value of matrix
- size : Return total length of matrix(height x stride)
- dot : do dot product
- sum : Return matrix as a summation of matrix along the direction(1 : sum each row, 2 : sum each column)
- dims : Return the dimension of matrix as a 2x1 vector
- reshape : Return the modified height x stride matrix
- print : Print the all element of matrix


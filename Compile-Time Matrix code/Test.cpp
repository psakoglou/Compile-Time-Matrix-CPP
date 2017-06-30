/*
*	© Superharmonic Technologies
*	Pavlos Sakoglou
*
*  ===================================================
*
*	Compile-Time Matrix class Test
*
*/

#include <iostream>

#include "Matrix.hpp"

int main() {
	
	// Basic tests

	Matrix<int, 3, 3> matrix1, matrix2;
	Matrix<int, 3, 3> matrix3(matrix2);

	// Randomize
	matrix1.randomize(0, 2);
	matrix2.randomize(0, 2);
	matrix3.randomize(0, 2);

	// Print
	matrix1.print();
	matrix2.print();
	matrix3.print();

	// Operations
	(matrix1 + matrix2).print();
	(matrix1 - matrix2).print();
	(matrix1 * matrix2).print();

	matrix3 += matrix1;
	matrix3 -= matrix1;
	matrix3 *= 10;
	matrix3 /= 10;
	matrix3 += 10;
	matrix3 -= 10;

	matrix3 = matrix2;

	matrix2.print();
	(matrix2 + 10).print();
	(matrix2 - 10).print();
	(matrix2 / 10).print();
	(matrix2 * 10).print();

	std::cout << "\nFirst element of matrix 2: " << matrix2(0, 0) << "\n\n";

	// Make matrix 1 the identity matrix
	matrix1.print();
	matrix1.makeIdentity();
	matrix1.print();

	// Transpose of matrix 2
	matrix2.print();
	matrix2.transpose();
	matrix2.print();

	// Trace of matrix 3
	std::cout << "\n\nThe trace of matrix 3 is: " << matrix3.trace() << "\n\n";

	// Happy coding! :)
	
	return 0;
}
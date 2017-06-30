/*
*	© Superharmonic Technologies
*	Pavlos Sakoglou
*
*  ===================================================
*
*	Matrix class implementation
*
*/

// Multiple include guards
#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "Matrix.hpp"

#include <iostream>
#include <chrono>
#include <random>

// Constructors and Destructor

// Default
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC>::Matrix() {
	m_matrix = new T * [NR];
	for (unsigned int i = 0; i < NR; i++)
		m_matrix[i] = new T[NC];
}

// Parameter:
// Initialize all entries of the matrix to a given value
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC>::Matrix(T val) {
	m_matrix = new T *[NR];
	for (unsigned int i = 0; i < NR; i++)
		m_matrix[i] = new T[NC];

	for (unsigned int i = 0; i < NR; i++)
		for (unsigned int j = 0; j < NC; j++)
			m_matrix[i][j] = val;
}

// Copy
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC>::Matrix(const Matrix<T, NR, NC> & matrix) {
	m_matrix = new T *[NR];
	for (unsigned int i = 0; i < NR; i++)
		m_matrix[i] = new T[NC];

	for (unsigned int i = 0; i < NR; i++)
		for (unsigned int j = 0; j < NC; j++)
			m_matrix[i][j] = matrix.m_matrix[i][j];
}

// Destructor 
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC>::~Matrix() {
	for (unsigned int i = 0; i < NR; i++)
		delete[] m_matrix[i];
	delete[] m_matrix;
}

/*************************************************************************************/

// Operator overloading -- pertaining the properties of a vector space N*M

// Modifying operators

// Assignment operator
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::operator=(const Matrix<T, NR, NC> & matrix) {
	if (this != &matrix) {
		for (unsigned int i = 0; i < NR; i++) {
			for (unsigned int j = 0; j < NC; j++) {
				m_matrix[i][j] = matrix.m_matrix[i][j];
			}
		}
	}
	return *this;
}

// Access and modify
template <typename T, std::size_t NR, std::size_t NC>
T Matrix<T, NR, NC>::operator()(int i, int j) {			
	return m_matrix[i][j];
}

// Matrix Addition
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::operator+=(const Matrix<T, NR, NC> & matrix) {
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			m_matrix[i][j] += matrix.m_matrix[i][j];
		}
	}
	return *this;
}

// Matrix Subtraction
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::operator-=(const Matrix<T, NR, NC> & matrix) {
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			m_matrix[i][j] -= matrix.m_matrix[i][j];
		}
	}
	return *this;
}

// Scalar Multiplication
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::operator*=(const T scalar) {
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			m_matrix[i][j] *= scalar;
		}
	}
	return *this;
}

// Scalar Addition
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::operator+=(const T scalar) {
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			m_matrix[i][j] += scalar;
		}
	}
	return *this;
}

// Scalar Subtraction
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::operator-=(const T scalar) {
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			m_matrix[i][j] -= scalar;
		}
	}
	return *this;
}

// Scalar Division
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::operator/=(const T scalar) {
	if (scalar != 0) {
		for (unsigned int i = 0; i < NR; i++) {
			for (unsigned int j = 0; j < NC; j++) {
				m_matrix[i][j] /= scalar;
			}
		}
	}
	return *this;
}

// Non-modifying operators

// Get an element
template <typename T, std::size_t NR, std::size_t NC>
const T Matrix<T, NR, NC>::operator()(int i, int j) const {
	return m_matrix[i][j];
}

// Matrix Addition
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> Matrix<T, NR, NC>::operator+(const Matrix<T, NR, NC> & matrix) const {
	Matrix<T, NR, NC> temp;
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			temp.m_matrix[i][j] = m_matrix[i][j] + matrix.m_matrix[i][j];
		}
	}
	return temp;
}

// Matrix Subtraction
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> Matrix<T, NR, NC>::operator-(const Matrix<T, NR, NC> & matrix) const {
	Matrix<T, NR, NC> temp;
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			temp.m_matrix[i][j] = m_matrix[i][j] - matrix.m_matrix[i][j];
		}
	}
	return temp;
}

// Matrix Multiplication -- O(n^3)
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> Matrix<T, NR, NC>::operator*(const Matrix<T, NC, NR> & matrix) const {
	T sum = 0;
	Matrix<T, NR, NC> product;
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			for (unsigned int k = 0; k < NC; k++) {
				sum += m_matrix[i][k] * matrix.m_matrix[k][j];
			}
			product.m_matrix[i][j] = sum;
			sum = 0;
		}
	}
	return product;
}

// Scalar Multiplication
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> Matrix<T, NR, NC>::operator*(const T scalar) const {
	Matrix<T, NR, NC> temp;
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			temp.m_matrix[i][j] = m_matrix[i][j] * scalar;
		}
	}
	return temp;
}

// Scalar Addition
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> Matrix<T, NR, NC>::operator+(const T scalar) const {
	Matrix<T, NR, NC> temp;
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			temp.m_matrix[i][j] = m_matrix[i][j] + scalar;
		}
	}
	return temp;
}

// Scalar Subtraction
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> Matrix<T, NR, NC>::operator-(const T scalar) const {
	Matrix<T, NR, NC> temp;
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			temp.m_matrix[i][j] = m_matrix[i][j] - scalar;
		}
	}
	return temp;
}

// Scalar Division
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> Matrix<T, NR, NC>::operator/(const T scalar) const {
	Matrix<T, NR, NC> temp;
	if (scalar == 0) {
		std::cout << "Exception! You cannot divide by zero!\n";
		return temp;
	}
	else {
		for (unsigned int i = 0; i < NR; i++) {
			for (unsigned int j = 0; j < NC; j++) {
				temp.m_matrix[i][j] = m_matrix[i][j] / scalar;
			}
		}
		return temp;
	}
}

/*************************************************************************************/

// Utility

// Print member function
template <typename T, std::size_t NR, std::size_t NC>
const void Matrix<T, NR, NC>::print() const {
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			std::cout << m_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

/*************************************************************************************/

// Linear Algebra functionality

// Transpose
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> Matrix<T, NR, NC>::transpose() {
	Matrix<T, NR, NC> temp = *this;
	T t;
	if (NR == NC) {
		for (unsigned int i = 0; i < NR; i++) {
			for (unsigned int j = i; j < NR; j++) {
				t = temp.m_matrix[i][j];
				temp.m_matrix[i][j] = temp.m_matrix[j][i];
				temp.m_matrix[j][i] = t;				
			}
		}
	}
	else {
		std::cout << "This method does not support non-square matrix transpose!\n";
	}
	return temp;
}

// Randomize the matrix
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::randomize(T start_range, T end_range) {
	std::uniform_int<int> dist(start_range, end_range);
	std::mt19937 eng;
	for (unsigned int i = 0; i < NR; i++) {
		for (unsigned int j = 0; j < NC; j++) {
			eng.seed((double)(std::chrono::system_clock::now().time_since_epoch().count()));
			m_matrix[i][j] = dist(eng);
		}
	}
	return *this;
}

	
// Identity
template <typename T, std::size_t NR, std::size_t NC>
Matrix<T, NR, NC> & Matrix<T, NR, NC>::makeIdentity() {
	if (NR == NC) {
		for (unsigned int i = 0; i < NR; i++) {
			for (unsigned int j = 0; j < NC; j++) {
				if (i == j) m_matrix[i][j] = 1;
				else m_matrix[i][j] = 0;
			}
		}
	}
	else {
		std::cout << "The identity matrix does not exist for the " << NR << "x" << NC << " case.\n";
	}
	return *this;
}

// Trace
template <typename T, std::size_t NR, std::size_t NC>
T Matrix<T, NR, NC>::trace() const {
	T trace = 0;
	if (NC == NR) {
		for (unsigned int i = 0; i < NR; i++)
			trace += m_matrix[i][i];
	}
	else {
		std::cout << "The trace is defined for NxN matrices only!\n";
	}
	return trace;
}

#endif // !MATRIX_CPP
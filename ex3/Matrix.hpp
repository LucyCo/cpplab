/**
 * hpp file for generic matrix class.
 */
#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <thread>
#include "Complex.h"

//error macros
#define ERR_DIFF_DIMENTIONS "This operation requires two operand matrices to be of similar dimensions."
#define ERR_MULT_DIMENSIONS	"Multiplication requires number of rows first matrix to be equal to\
                            number of cols in second matrix."
#define ERR_SQUARED	"Trace requires the matrix to be squared"
#define ERR_OUT_OF_RANGE "Row or Col values are out of range required range."
#define ERR_ILL_REFERENCE "The number of values in the given reference should match the size of the matrix."
//message for parallel mode change
#define PARALLEL_MODE(param)  "Generic Matrix mode changed to " << param << " mode."

using namespace std;

/**
 * Matrix class is a generic matrix and contains functions and operator overloading for basic arithmetic
 * operations.
 */
template <class T> class Matrix
{
private:
	vector<T> _data;
	size_t _rows;
	size_t _cols;
	static bool isParallel;
	
public:
    //====== constructors ======
    
    /**
     * Constructor - new generic matrix of the given rows and cols size, uninitialized.
     */
    Matrix(size_t rows, size_t cols)
    {
        _data = vector<T>(rows * cols);
        _rows = rows;
        _cols = cols;
    }
    
	/**
	 * Default constructor - will construct a new generic matrix of size 1.
	 */
    Matrix()
    {
        Matrix(1, 1);
    }

	/**
	 * Copy constructor - will construct a copy of the given matrix reference.
	 */
	Matrix(const Matrix& copy)
	{
		*(this) = copy;
	}

	/**
	 * Constructor - new generic matric of the given rows and cols size, assigns the given data reference
     * to the matrix's private data value.
	 */
	Matrix(const size_t rows, const size_t cols, const vector<T>& data)
	{
		if ((rows * cols) != data.size())
		{
			throw invalid_argument(ERR_ILL_REFERENCE);
		}
		_data = data;
		_rows = rows;
		_cols = cols;
	}

	/**
	 * Destructor - default destructor.
	 */
	~Matrix() {}
    
    //====== iterator overloading ======
    
    /**Iterator for generic vectors typename.*/
    typedef typename vector<T>::iterator iterator;
    /**Constant iterator for generic vectors typename.*/
    typedef typename vector<T>::const_iterator const_iterator;
    
    /**
     * Overrides the begin function for iterator, returns iterator for the beginning of the generic
     * vector.
     */
    iterator begin()
    {
        return _data.begin();
    }
    
    /**
     * Overrides the end function for iterator, returns iterator for the last item of the generic
     * vector.
     */
    iterator end()
    {
        return _data.end();
    }
    
    /**
     * Overrides the begin function for const iterator, returns iterator for the beginning of the generic
     * vector.
     */
    const_iterator begin() const
    {
        return _data.begin();
    }
    
    /**
     * Overrides the end function for const iterator, returns iterator for the last item of the generic
     * vector.
     */
    const_iterator end() const
    {
        return _data.end();
    }
    
    //====== sequential arithmetic calculator functions ======
    
private:
    
    /**
     * Calculates addition between matrices. will be used on parallel mode by creating multiple threads.
     */
     static void _addition(const_iterator start_first, const_iterator end_first,
                           const_iterator start_second, iterator res)
    {
        while (start_first != end_first)
        {
            *res = *start_first + *start_second;
            start_first++, start_second++, res++;
        }
    }
    
    /**
     * Calculates multiplication between matrices. will be used on parallel mode by creating multiple
     * threads to calculate inner product for each vector in the result matrix at the same time.
     * Will be used on sequential mode to calculate inner profuct for each vector in the result matrix
     * at a sequential timeframe.
     */
    static void _multiplication(const_iterator start_first, const_iterator end_first,
                                const Matrix& tranMatrix, iterator res)
    {
        for (size_t transRows = 0; (transRows < tranMatrix.rows()); transRows++)
        {
            const_iterator temp = start_first;
            const_iterator start_second = (transRows * tranMatrix.cols()) + tranMatrix.begin();
            /* using inner product from numeric to calculate the inner product of every vector in the
             result matrix */
            *(res + transRows) = inner_product(temp, end_first, start_second, T());
        }
    }
    
public:
    
    //====== basic generic Matrix methods ======
    
    /**
     * Returns true if this matrix is squared, otherwise returns false.
     */
    bool isSquareMatrix() const
    {
        return (rows() == cols());
    }
    
    /**
     * Getter for the number of rows in this matrix.
     */
    size_t rows() const
    {
        return _rows;
    }
    
    /**
     * Getter for the number of columns in this matrix.
     */
    size_t cols() const
    {
        return _cols;
    }
    
    /**
     * When called upon, setParallel changes the current "Parallel Mode". When parallel mode
     * is used, multiplication or addition operands will be calculated each row in the result matrix
     * in a different thread at the same time.
     */
    static bool setParallel(bool param)
    {
        if (param != isParallel)
        {
            isParallel = param;
            if (isParallel)
            {
                cout << PARALLEL_MODE("parallel") << endl;
            }
            else
            {
                cout << PARALLEL_MODE("non-parallel") << endl;
            }
        }
        return false;
    }
    
    //====== operator overloading ======
    
    /**
     * Overloads the assignment operator. Will return an instance of a copy of the given matrix reference.
     */
    Matrix& operator=(const Matrix& matrix)
    {
        if (this != &matrix)
        {
            _rows = matrix.rows();
            _cols = matrix.cols();
            _data = vector<T>(matrix._data);
        }
        return (*this);
    }
    
	/**
	 * Addition operator overloading.
     * Calculates addition between two matrices.
     * If isParallel is true, then creates threads for calculating addition for each row at parallel time.
	 */
	Matrix operator+(const Matrix& matrix) const
	{
        if (rows() != matrix.rows() || cols() != matrix.cols())
        {
            throw invalid_argument(ERR_DIFF_DIMENTIONS);
        }
		Matrix result(rows(), cols());
		if (isParallel)
		{
			vector<thread> threadList;
			threadList.reserve(rows());
			for (size_t row = 0; row < rows(); row++)
			{
				threadList.push_back(thread(_addition, begin() + row * cols(), begin() + row * cols() + cols(), matrix.begin() + row * cols(), result.begin() + row * cols()));
			}
            for (int i = 0; i < threadList.size(); i++)
            {
                threadList[i].join();
            }
		}
		else
		{
			transform(begin(), end(), matrix.begin(), result.begin(), plus<T>());
		}
		return result;
	}

	/**
     * Substruction operator overloading.
     * Calculates substruction between two matrices.
	 */
	Matrix operator-(const Matrix& matrix) const
	{
		if (rows() != matrix.rows() || cols() != matrix.cols())
		{
			throw invalid_argument(ERR_DIFF_DIMENTIONS);
		}
		Matrix result(rows(), cols());
        transform(begin(), end(), matrix.begin(), result.begin(), minus<T>());
		return result;
	}

    /**
     * Multiplication operator overloading.
     * Calculates multiplication between two matrices.
     * If isParallel is true, then creates threads for calculating inner product for each row at parallel
     * time. else, will use the same method, only it will be done in a linear timeframe.
     */
	Matrix operator*(const Matrix& matrix) const
	{
		if (rows() != matrix.cols())
		{
			throw invalid_argument(ERR_MULT_DIMENSIONS);
		}
		Matrix result(rows(), matrix.cols());
		if (isParallel)
		{
			vector<thread> threads;
			threads.reserve(rows());
			for (size_t row = 0; row < rows(); row++)
			{
				threads.push_back(thread(_multiplication, begin() + row * cols(),
                begin() + row * cols() + cols(), matrix.trans(),
                result.begin() + row * result.cols()));
			}
            for (int i = 0; i < threads.size(); i++)
            {
                threads[i].join();
            }
		}
		else
		{
			for (size_t row = 0; row < rows(); row++)
			{
				_multiplication(begin() + row * cols(), begin() + row * cols() + cols(),
                matrix.trans(), result.begin() + row * result.cols());
			}
		}
		return result;
	}

	/**
	 * Comparison equals overloading.
	 * Returns true of the given matrix is equal to the current one.
	 */
	bool operator==(const Matrix& matrix) const
	{
		if (*this == matrix)
		{
			return true;
		}
		if (cols() != matrix.cols() || rows() != matrix.rows() || !equal(begin(), end(), matrix.begin()))
		{
			return false;
		}
        return true;
	}

    /**
     * Comparison not-equals overloading.
     * Returns true of the given matrix is not equal to the current one.
     */
	bool operator!=(const Matrix& matrix) const
	{
		return ((*this) != matrix);
	}

	/**
	 * Transpose calculator - returns the transposed matrix of the current matrix.
	 */
	Matrix trans() const
	{
        Matrix result(cols(), rows());
        for (size_t row = 0; row < rows(); row++)
        {
            for (size_t col = 0; col < cols(); col++)
            {
                result(col, row) = (*this)(row, col);
            }
        }
        return result;
	}

	/**
	 * Trace of generic matrix - returns a generic value representing the trace of this matrix.
	 */
	T trace() const
	{
        //must be squared in order to calculate.
		if (!isSquareMatrix())
		{
			throw invalid_argument(ERR_SQUARED);
		}
		T result = T();
		for (size_t row = 0; row < rows(); row++)
		{
			result += (*this)(row, row);
		}
		return result;
	}
    
    /**
     * Function call operator - Returns the value of given cell in the matrix.
     */
    T operator()(const size_t row, const size_t col) const
    {
        return _data[(row * _cols) + col];
    }
    
    /**
     * Function call operator - Returns reference to the value of given cell in the matrix.
     */
    T& operator()(const size_t row, const size_t col)
    {
        return _data[(row * _cols) + col];
    }

};

//templates for generic functions
/**
 * Set the isParallel value to false in default.
 */
template <typename T> bool Matrix<T>::isParallel = false;

/**
 * Generic matrix ostream operator overloading.
 */
template <typename T> ostream& operator<<(ostream& os, const Matrix<T>& matrix)
{
	for (size_t row = 0; row < matrix.rows(); row++)
	{
		for (size_t col = 0; col < matrix.cols(); col++)
		{
            os << matrix(row, col);
            os << "\t";
			if ((col + 1) >= matrix.cols())
			{
                os << endl;
			}
		}
	}
	return os;
}

/**
 * Calculate conjugate transpose for complex matrix.
 */
template <> Matrix<Complex> Matrix<Complex>::trans() const
{
	Matrix<Complex> result(cols(), rows());
	for (size_t row = 0; row < rows(); row++)
	{
		for (size_t col = 0; col < cols(); col++)
		{
			result(col, row) = (*this)(row, col).conj();
		}
	}
	return result;
}

#endif

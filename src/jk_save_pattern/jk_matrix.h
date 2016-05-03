#ifndef __JK_MATRIX_HPP_INCLUDED__
#define __JK_MATRIX_HPP_INCLUDED__

#include <ostream>
#include <vector>

#include "jk_assert.hpp"

namespace jk {

// Two-dimensional rectangular matrix.
template <typename T>
class matrix {
  public:
	typedef unsigned size_type;

	matrix(size_type num_rows, size_type num_cols)
		: rows_(num_rows), cols_(num_cols), data_(num_rows * num_cols)
	{
		JK_TEST_ASSERT(num_rows > 0, 
			"Number of rows in a matrix must be positive");
		JK_TEST_ASSERT(num_cols > 0, 
			"Number of columns in a matrix must be positive");
	}

	matrix(size_type num_rows, size_type num_cols, const T& init_value)
		: rows_(num_rows), cols_(num_cols), data_(num_rows * num_cols, init_value)
	{
		JK_TEST_ASSERT(num_rows > 0, "Number of rows in a matrix must be positive");
		JK_TEST_ASSERT(num_cols > 0, "Number of columns in a matrix must be positive");
	}

	size_type num_rows() const { return rows_; }
	size_type num_cols() const { return cols_; }

	// Accessors: return element by row and column.
	T& operator() ( size_type row, size_type col )
	{
		return data_[ index( row, col ) ];
	}

	const T& operator() ( size_type row, size_type col ) const
	{
		return data_[ index( row, col ) ];
	}

  private:
	size_type rows_, cols_;
	std::vector<T> data_;

	size_type index(size_type row, size_type col) const {
		JK_TEST_ASSERT(row < rows_, "Row " << row  << " must be less than " << rows_);
 		JK_TEST_ASSERT(col < cols_, "Column " << col  << " must be less than " << cols_);
		return cols_ * row + col;
	}
};

}  // namespace jk

template <typename T>
inline
std::ostream& operator << (std::ostream& os, const jk::matrix<T>& m) {
	for( unsigned r =0; r<m.num_rows(); ++r ) {
		for( unsigned c=0; c<m.num_cols(); ++c ) {
			os << m(r,c);
			if( c + 1 < m.num_cols() )
				os << "\t";
		}
		os << "\n";
	}
	return os;
}

#endif // __JK_MATRIX_HPP_INCLUDED__


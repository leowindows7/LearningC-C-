#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix();
  Matrix(int r, int c);
  Matrix(const Matrix & rhs);
  Matrix & operator=(const Matrix & rhs);
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix & rhs) const;
  Matrix operator+(const Matrix & rhs) const;
  int getRows() const;
  int getColumns() const;
  template<typename U>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs);
};

template<typename T>
Matrix<T>::Matrix() : numRows(0), numColumns(0), rows(0) {
}

template<typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c) {
  rows.resize(r);
  typename std::vector<std::vector<T> >::iterator myIt = rows.begin();
  while (myIt != rows.end()) {
    (*myIt).resize(c);
    ++myIt;
  }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns) {
  rows = rhs.rows;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = rhs.rows;
  return *this;
}

template<typename T>
int Matrix<T>::getRows() const {
  return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert((0 <= index) && (index < numRows));
  return rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert((index >= 0) && (index < numRows));
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns) || (rows != rhs.rows)) {
    return false;
  }
  return true;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  Matrix<T> result(numRows, numColumns);
  typename std::vector<std::vector<T> >::const_iterator this_it = rows.begin();
  typename std::vector<std::vector<T> >::const_iterator rhs_it = rhs.rows.begin();
  typename std::vector<std::vector<T> >::iterator result_it = result.rows.begin();
  while (result_it != result.rows.end()) {
    typename std::vector<T>::iterator result_it_it = (*result_it).begin();
    typename std::vector<T>::const_iterator this_it_it = (*this_it).begin();
    typename std::vector<T>::const_iterator rhs_it_it = (*rhs_it).begin();
    while (result_it_it != (*result_it).end()) {
      *result_it_it = *this_it_it + *rhs_it_it;
      ++result_it_it;
      ++this_it_it;
      ++rhs_it_it;
    }

    ++rhs_it;
    ++this_it;
    ++result_it;
  }
  return result;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  typename std::vector<std::vector<T> >::const_iterator it;
  for (it = rhs.rows.begin(); it != rhs.rows.end(); ++it) {
    if (it != rhs.rows.begin()) {
      s << ",\n";
    }
    s << "{";
    typename std::vector<T>::const_iterator it_it;
    for (it_it = (*it).begin(); it_it != (*it).end(); ++it_it) {
      if (it_it != (*it).begin()) {
        s << ", ";
      }
      s << *it_it;
    }
    s << "}";
  }
  s << " ]";
  return s;
}
#endif

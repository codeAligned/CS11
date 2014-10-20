#include "Matrix.hh"
#include <cassert>

// Default constructor:  initializes a 0x0 matrix.
Matrix::Matrix() {
  mRows = 0;
  mColumns = 0;
  mElems = NULL;
}

// Copy constructor: deep copy a matrix.
Matrix::Matrix(const Matrix &m) {
  
  copy(m);  // simply call helper function to copy
}

// Initializes the a matrix of size rows by columns.
Matrix::Matrix(int rows, int columns) {
  assert (rows >= 0);
  assert (columns >= 0);
  mRows = rows;
  mColumns = columns;
  int numValues = rows * columns;
  mElems = new int[numValues]; // array is uninitialized

  for (int i = 0; i < numValues; i++) {
    mElems[i] = 0; // initialize the new array to all 0's
  }
}


// Destructor - Clean up the allocated array.
Matrix::~Matrix() {
  cleanup();  // simply call cleanup function to deallocate
}

// Private helper functions for constructors/destructors/assignemnt operator

// copy contents of m into the object
void Matrix::copy(const Matrix &m) {

  mRows = m.getrows();
  mColumns = m.getcols();

  int numElems = (m.getrows() * m.getcols());
  // DON'T just copy the pointer value
  mElems = new int[numElems];  // Allocate space

  for (int i = 0; i < numElems; i++) {
      mElems[i] = m.mElems[i];  // Copy the data over
  }

}

// clean up the current contents of the object
void Matrix::cleanup() {
  delete[] mElems;
}

// Operators

// Assignment operator that checks for self-assignment
Matrix & Matrix::operator=(const Matrix &rhs) {
  // Only do assignment if RHS is a different object from this.
  if (this != &rhs) {
    // Deallocate, allocate new space, copy values...
    cleanup();
    copy(rhs);
  }

  return *this;
}

// add a matrix to self
Matrix & Matrix::operator+=(const Matrix &rhs) {

  assert(mRows == rhs.getrows());   // rhs must be same size as matrix
  assert(mColumns == rhs.getcols());

  for (int i = 0; i < (mRows * mColumns); i++) {
      mElems[i] += rhs.mElems[i];  // add the value of each element
  }

  return *this;
}

// subtract a matrix from self
Matrix & Matrix::operator-=(const Matrix &rhs) {

  assert(mRows == rhs.getrows());   // rhs must be same size as matrix
  assert(mColumns == rhs.getcols());

  for (int i = 0; i < (mRows * mColumns); i++) {
      mElems[i] -= rhs.mElems[i];  // subtract the value of each element
  }

  return *this;
}

// multiply self by another matrix (must be of compatible dimensions) to 
// create a new matrix object
Matrix & Matrix::operator*=(const Matrix &rhs) {

  assert(mColumns == rhs.getrows()); // matrix multiplication is only defined if
                                    // rows in rhs are equal to columns in self

  Matrix tempResult(mRows, rhs.getcols()); // temp matrix with correct dimensions 

  for (int row = 0; row < mRows; row++) {
    for (int col = 0; col < rhs.getcols(); col++) {
      // Multiply the row of self by the column of rhs to get the row, column of product.
      int value = 0;
      for (int inner = 0; inner < mColumns; inner++) {
        value += getelem(row, inner) * rhs.getelem(inner, col);
      }
      tempResult.setelem(row, col, value);
    }
  }

  *this = tempResult; // Assign result to self
  return *this;
}

// add operation to create a new matrix object
const Matrix Matrix::operator+(const Matrix &m) const {

  Matrix result(*this);   // make a copy of self
  result += m; // add the RHS to the result.
  return result;
}

// subtract operation to create a new matrix object
const Matrix Matrix::operator-(const Matrix &m) const {

  Matrix result(*this);  // make a copy of self
  result -= m;  // subtract the RHS from the result
  return result;
}  

// multiply operation to create a new matrix objct
const Matrix Matrix::operator*(const Matrix &m) const {

  Matrix result(*this);  // make a copy of self
  result *= m;  // subtract the RHS from the result
  return result;
}

// return true iff each element of self is equal to argument matrix
bool Matrix::operator==(const Matrix &other) const {
  // Compare the values, and return a bool result.
  if (mRows != other.getrows()) {
    return false;
  };
  if (mColumns != other.getcols()) {
    return false;
  };

  for (int i = 0; i < (mRows * mColumns); i++) {
    if (mElems[i] != other.mElems[i]) { // if an element doesn't match, not equal
      return false;
    }
  }

  return true;
} 

// return true iff at least 1 element of self does not match argument matrix
bool Matrix::operator!=(const Matrix &other) const {
  return !(*this == other);  // must be opposite of == operator.
}  

// Mutators:

// sets the element at location [row, column] to have a value "elem"
void Matrix::setelem(int row, int column, int elem) {
  int index = (row * mColumns) + column;
  assert(index >= 0);
  assert(index <= (mRows * mColumns));
  mElems[index] = elem;
}

// Accessors:

// get the number of rows in the matrix
int Matrix::getrows() const {
  return mRows;
}

// get the number of columns in the matrix
int Matrix::getcols() const {
  return mColumns;
}

// return the element at a specific [row, column] location
int Matrix::getelem(int row, int column) const {
  int index = (row * mColumns) + column;
  assert(index >= 0);
  assert(index <= (mRows * mColumns));
  int value = mElems[index];
  return value;
}



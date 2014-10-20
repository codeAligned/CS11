#include "Matrix.hh"
#include <cassert>


// Default constructor:  initializes a 0x0 matrix.
Matrix::Matrix() {
  mRows = 0;
  mColumns = 0;
  mElems = NULL;
}

// Copy constructor: deep copy a matrix.
Matrix::Matrix(Matrix &m) {
  
  mRows = m.getrows();
  mColumns = m.getcols();

  int numElems = (m.getrows() * m.getcols());
  // DON'T just copy the pointer value
  mElems = new int[numElems];  // Allocate space

  for (int i = 0; i < numElems; i++) {
      mElems[i] = m.mElems[i];  // Copy the data over
  }
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
  delete[] mElems;
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
int Matrix::getrows() {
  return mRows;
}

// get the number of columns in the matrix
int Matrix::getcols() {
  return mColumns;
}

// return the element at a specific [row, column] location
int Matrix::getelem(int row, int column) {
  int index = (row * mColumns) + column;
  assert(index >= 0);
  assert(index <= (mRows * mColumns));
  int value = mElems[index];
  return value;
}

// Member functions;

// adds a matrix to self
// (note that the matrices must be the same size)
void Matrix::add(Matrix &m) {
  assert(mRows == m.getrows());
  assert(mColumns == m.getcols());

  for (int i = 0; i < (mRows * mColumns); i++) {
      mElems[i] += m.mElems[i];  // add the value of each element
  }

}

// subtracts a matrix from self
// (note that the matrices must be the same size)
void Matrix::subtract(Matrix &m) {
  assert(mRows == m.getrows());
  assert(mColumns == m.getcols());

  for (int i = 0; i < (mRows * mColumns); i++) {
      mElems[i] -= m.mElems[i];  // subtract the value of each element
  }

}

// returns true iff each element from the matrix matches each element
// of self.
// (note that if the matrices are different sizes, they cannot be equal)
bool Matrix::equals(Matrix &m) {
  if (mRows != m.getrows()) {
    return false;
  };
  if (mColumns != m.getcols()) {
    return false;
  };

  for (int i = 0; i < (mRows * mColumns); i++) {
    if (mElems[i] != m.mElems[i]) { // if an element doesn't match, not equal
      return false;
    }
  }

  return true;
}

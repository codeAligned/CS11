// A 2-dimensional Matrix class!
// Elements of the matrix are integers.

class Matrix {

private:
  int mRows;
  int mColumns;
  int *mElems;

  void copy(const Matrix &m);
  void cleanup();

public:
  // Constructors
  Matrix();                      // default constructor
  Matrix(const Matrix &m);             // copy constructor
  Matrix(int rows, int columns);    // 2-argument constructor

  // Destructor
  ~Matrix();

  // Operators
  Matrix & operator=(const Matrix &rhs);

  Matrix & operator+=(const Matrix &rhs);
  Matrix & operator-=(const Matrix &rhs);
  Matrix & operator*=(const Matrix &rhs);

  const Matrix operator+(const Matrix &m) const;
  const Matrix operator-(const Matrix &m) const;
  const Matrix operator*(const Matrix &m) const;

  bool operator==(const Matrix &other) const;
  bool operator!=(const Matrix &other) const;

  // Mutator methods
  void setelem(int row, int column, int elem);

  // Accessor methods
  int getrows() const;
  int getcols() const;
  int getelem(int row, int column) const;

};

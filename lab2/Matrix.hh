// A 2-dimensional Matrix class!
// Elements of the matrix are integers.

class Matrix {

private:
  int mRows;
  int mColumns;
  int *mElems;

public:
  // Constructors
  Matrix();                      // default constructor
  Matrix(Matrix &m);             // copy constructor
  Matrix(int rows, int columns);    // 2-argument constructor

  // Destructor
  ~Matrix();

  // Mutator methods
  void setelem(int row, int column, int elem);

  // Accessor methods
  int getrows();
  int getcols();
  int getelem(int row, int column);

  // Member functions
  void add(Matrix &m);
  void subtract(Matrix &m);
  bool equals(Matrix &m);
};

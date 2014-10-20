// A Sparse Vector class!
// Stores nonzero integer values of a vector which is sparsely populated

class SparseVector {

private:

  // A linked-list node for our sparse vector elements.
  struct node {
    int index;   // Element number, in the range [0, size)
    int value;   // The value of this element.
    node *next;    // A pointer to the next node in the linked-list.

    // Node constructor - simply initializes the data-members.
    node(int index, int value, node *next = 0) : index(index), value(value), next(next) { }
  };

  int mSize;
  node *mStart;

  void copyList(const SparseVector &sv);
  void clear();

  void removeElem(int index);
  void setNonzeroElem(int index, int value);

  void addSubVector(const SparseVector &other, bool add);
  void removeZeros();

  void checkListOrder() const;
  bool checkZeros() const;

public:
  // Constructors

  SparseVector();        // default constructor
  SparseVector(int size);    // 1-argument constructor
  SparseVector(const SparseVector &sv);  // copy constructor

  // Destructor
  ~SparseVector();

  // Accessors
  int getSize() const;
  int getElem(int idx) const;

  // Mutators
  void setElem(int index, int value);


  // Operators
  SparseVector & operator=(const SparseVector &rhs);

  SparseVector & operator+=(const SparseVector &rhs);
  SparseVector & operator-=(const SparseVector &rhs);

  const SparseVector operator+(const SparseVector &sv) const;
  const SparseVector operator-(const SparseVector &sv) const;

  bool operator==(const SparseVector &other) const;
  bool operator!=(const SparseVector &other) const;


};

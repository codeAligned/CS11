#include "SparseVector.hh"
#include <cassert>
#include <iostream>

// Default constructor:  initializes a Sparse Vector of size 0
SparseVector::SparseVector() {
  mSize = 0;
  mStart = 0;
}

// Copy constructor: deep copy a sparse vector
SparseVector::SparseVector(const SparseVector &sv) {
  copyList(sv);  // simply call helper function to copy
}

// Initializes the a Sparse Vector of a given size
SparseVector::SparseVector(int size) {
  assert (size >= 0);
  mSize = size;

  mStart = 0;  // the linked list is initially empty
}


// Destructor - Clean up the  linked list
SparseVector::~SparseVector() {
  clear();  // simply call clear function to empty linked list
}

// Private helper functions for constructors/destructors/assignemnt operator

// copy contents of sv into the object
void SparseVector::copyList(const SparseVector &sv) {

  mSize = sv.getSize();


  // Get a pointer to other list's first node
  node *otherCurr = sv.mStart;
  if (otherCurr == 0) {  // if empty, return early
    mStart = 0;
    return;
  }

  // Use prev and curr to create the copy
  node *prev = 0;
  node *curr;

  while (otherCurr != 0) {
    // Copy other list's current node
    curr = new node(otherCurr->index, otherCurr->value);
    if (prev == 0) {
      mStart = curr;      // curr is the first node in our copy!
    }
    else {
      prev->next = curr; // Make previous node point to current
    }
    prev = curr;                  // Done with current node!
    otherCurr = otherCurr->next;  // Move to next node to copy
  }

  checkListOrder();
}

// clean up the linked list by deleting every element
void SparseVector::clear() {
  node *curr = mStart;
  while (curr != 0) {
    node *next = curr->next; // Get what is next, before deleting curr.
    delete curr;   // Delete this node.
    curr = next;   // Go to next node in list
  }
  mStart = 0;   // indicate that the list is empty
}

// Operators

// Assignment operator that checks for self-assignment
SparseVector & SparseVector::operator=(const SparseVector &rhs) {
  // Only do assignment if RHS is a different object from this.
  if (this != &rhs) {
    // empty the linked list, and create a new one and copy values...
    clear();  
    copyList(rhs);
  }

  return *this;
}

// add a sparse vector to self
SparseVector & SparseVector::operator+=(const SparseVector &rhs) {

  assert(mSize == rhs.getSize());   // the sparse vectors must be the same size

  addSubVector(rhs, true);  // call helper function to add rhs to this

  removeZeros();

  assert(checkZeros());

  return *this;
}

// subtract a sparse vector from self
SparseVector & SparseVector::operator-=(const SparseVector &rhs) {

  assert(mSize == rhs.getSize());   // the sparse vectors must be the same size

  addSubVector(rhs, false);  // call helper function to subtract rhs from this

  removeZeros();

  assert(checkZeros());

  return *this;
}

// add operation to create a new sparse vector object
const SparseVector SparseVector::operator+(const SparseVector &sv) const {

  SparseVector result(*this);   // make a copy of self
  result += sv; // add the RHS to the result.
  return result;
}

// subtract operation to create a new sparse vector object
const SparseVector SparseVector::operator-(const SparseVector &sv) const {

  SparseVector result(*this);   // make a copy of self
  result -= sv; // add the RHS to the result.
  return result;
}

// return true iff each node of this is exactly equal to each corresponding
// not of other SparseVector
bool SparseVector::operator==(const SparseVector &other) const {
  // Compare the nodes, and return a bool result.
  if (mSize != other.getSize()) {
    return false;
  }

  node *curr = mStart;
  node *otherCurr = other.mStart;

  // if we find a node that has a different index or value, the linked lists
  // are not equal
  while (curr != 0 && otherCurr != 0) {
    if ((curr->index != otherCurr->index) || (curr->value != otherCurr->value)) {
      return false;
    }
    curr = curr->next;
    otherCurr = otherCurr->next;
  }

  // if we reached the end of one linked list before the other, the linked lists 
  // are not equal.  If this happens, one linked list will be at at 0 node
  // while the other is still at a valid node.
  if ((curr == 0 && otherCurr != 0) || (curr != 0 && otherCurr == 0)) {
    return false;
  }

  return true;
} 

// return true iff at least 1 node of this does not other SparseVector
bool SparseVector::operator!=(const SparseVector &other) const {
  return !(*this == other);  // must be opposite of == operator.
}  

// Private helper functions

void SparseVector::addSubVector(const SparseVector &other, bool add) {

  int sign = (add ? 1 : -1);  // sign value to help with add vs subtract

  node *prev = 0;
  node *curr = mStart;
  node *otherCurr = other.mStart;
  while (curr != 0 && otherCurr != 0) {
    int i = curr->index;
    int j = otherCurr->index;
    if (i == j) {
      // if have a node from both lists at this an index, add the value from
      // other list's node to this list's node.
      curr->value += sign * otherCurr->value;
      prev = curr;
      curr = curr->next;
      otherCurr = otherCurr->next;
    } else if (i < j) {
      // this has an node at the index, but other doesn't.
      // no change, just move to next node of this.
      prev = curr;
      curr = curr->next;
    } else {
      // this has no node at the index, but other does.
      // need to an a new node into this.
      node *insertNode = new node(otherCurr->index, sign * otherCurr->value);
      if (prev == 0) { // if we are inserting the first node, update start
        mStart = insertNode;
        mStart->next = curr;
        prev = mStart;
      } else {    // else, fix linking by skipping over curr
        prev->next = insertNode;
        insertNode->next = curr;
        prev = insertNode;
      }
      otherCurr = otherCurr->next;  // advance other's node
    }
  }

  // if we reached the end of our list first, we need to add the rest of the 
  // other nodes.
  while (curr == 0 && otherCurr != 0) {
    node *insertNode = new node(otherCurr->index, sign * otherCurr->value);
    if (prev == 0) { // if we are copying to the first node, update start
      mStart = insertNode;
      prev = mStart;
    } else {    // else, add to the end
      prev->next = insertNode;
      prev = insertNode;
    }
    otherCurr = otherCurr->next;
  }
}

void SparseVector::removeZeros() {

  // Use prev and curr to keep track of nodes
  node *prev = 0;
  node *curr = mStart;

  checkListOrder();
  while (curr != 0) {
    if (curr->value == 0) {    // if the value of the node is 0, remove it
      node *nextNode = curr->next;
      if (prev == 0) { // if we are removing the first node, update start
        mStart = nextNode;
      } else {    // else, fix linking by skipping over curr
        prev->next = nextNode;
      }
      delete curr;  // remove the node with zero value
      curr = nextNode; // move to next node (note that prev is not changed)
    } else {
      prev = curr;    // Done with current node!
      curr = curr->next;  // Move to next node
    }
  }

  checkListOrder();
}

// look for node with the right index, and set it to value.
// if we can't find the right index, insert a new node in the right place
void SparseVector::setNonzeroElem(int index, int value) {
  assert(value != 0);

  // Use prev and curr to keep track of nodes
  node *prev = 0;
  node *curr = mStart;

  // find the node we need to insert in front of.
  while (curr != 0 && curr->index <= index) {
    if (curr->index == index) {
      curr->value = value;  // if we found the index, set new value. Done.
      return;
    }
    prev = curr;         // Done with current node!
    curr = curr->next;  // Move to the next node
  }

  node *insertNode = new node(index, value);

  // If curr != 0, we found a place to insert in front of.  We have already 
  // created the node, but we need its next to point to the current node to 
  // correctly link it up.
  if (curr != 0) { 
    insertNode->next = curr;
  }

  // update the previous node, depending on whether we are trying to add to the
  // beginning of the list or not.
  if (prev != 0) {     // add correct link to new node if we are not at start
    prev->next = insertNode;
  } else {
    mStart = insertNode;  // if we are at beginning of list, update start.
  }


  checkListOrder(); // make sure we didn't mangle list
}

// if set value to 0, remove the node at the given index
void SparseVector::removeElem(int index) {
  node *prev = 0;
  node *curr = mStart;

  // try to find the correct node to remove
  while (curr != 0) {
    if (curr->index == index) {  // we found the correct node
      break;
    }
    if (curr->index > index) { 
      return;  // if we passed it, return early
    }
    prev = curr;
    curr = curr->next; // Go to the next node

  }

  if (curr == 0) {  // if we didn't find index, nothing to remove
    return;
  }

  if (curr == mStart) {  // if we remove start node, update start
    mStart = curr->next;
  }

  if (prev != 0) {   // fix the linked list to skip over the removed node
    prev->next = curr->next;
  }

  delete curr;  // remove the node

  checkListOrder();  // make sure we didn't mangle list
}

// private debugging functions

// loop through all nodes of linked list, print some debugging output if
// indices somehow get out of order.
void SparseVector::checkListOrder() const{
  if (mStart == 0) {
    return;
  }
  node *prev = 0;
  node *curr = mStart;

  while (curr != 0) {
    if ((prev != 0) && (curr->index <= prev->index)) {

      std::cout << "-------------------------------------" << std::endl;
      std::cout << "Nodes are our of order!" << std::endl;

      std::cout << "Previous Index: " << prev->index << std::endl;
      std::cout << "Previous Value: " << prev->value << std::endl;

      std::cout << "Current Index: " << curr->index << std::endl;
      std::cout << "Current Value: " << curr->value << std::endl;

      node *next = curr->next;
      if (next != 0) {
        std::cout << "Next Index: " << next->index << std::endl;
        std::cout << "Next Value: " << next->value << std::endl;
      }

      assert (0 > 1); // trip an assertion so we know where we messed up
    }

    prev = curr;
    curr = curr->next;  // go to the next node
  }
}

// returns true if there are no nodes with value 0.
bool SparseVector::checkZeros() const{
  if (mStart == 0) {
    return true;
  }
  node *prev = 0;
  node *curr = mStart;
  bool flag = true;

  while (curr != 0) {
    if (curr->value == 0) {
      std::cout << "-------------------------------------" << std::endl;
      std::cout << "There is still a ZERO node!" << std::endl;

      std::cout << "Current Index: " << curr->index << std::endl;
      std::cout << "Current Value: " << curr->value << std::endl;

      flag = false;
    }

    prev = curr;
    curr = curr->next;  // go to the next node
  }

  return flag;
}

// Accessors:

// get the size of the Sparse Vector
int SparseVector::getSize() const {
  return mSize;
}

// return the value corresponding to the index in the linked list.
// if the index is not in the linked list, return 0
int SparseVector::getElem(int idx) const {
  checkListOrder();  // make sure we aren't trying to traverse a mangled list
  node *curr = mStart;
  while (curr != 0) {
    if (curr->index == idx) {
      return curr->value;
    }
    if (curr->index > idx) {  // if index bigger, can't find
      return 0;  
    }
    curr = curr->next; // Go to the next node
  }
  return 0;  // reached the end of the list.
}


// Mutators

void SparseVector::setElem(int index, int value) {

  if (value == 0) {
    removeElem(index);
  } else {
    setNonzeroElem(index, value);
  }

  assert(checkZeros());

}

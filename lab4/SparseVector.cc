#include "SparseVector.hh"
#include <cassert>
#include <iostream>

// Default constructor:  initializes a Sparse Vector of size 0
SparseVector::SparseVector() {
  mSize = 0;
  mStart = NULL;
}

// Copy constructor: deep copy a sparse vector
SparseVector::SparseVector(const SparseVector &sv) {
  copyList(sv);  // simply call helper function to copy
}

// Initializes the a Sparse Vector of a given size
SparseVector::SparseVector(int size) {
  assert (size >= 0);
  mSize = size;

  mStart = NULL;  // the linked list is initially empty
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
  if (otherCurr == NULL) {  // if empty, return early
    mStart = NULL;
    return;
  }

  // Use prev and curr to create the copy
  node *prev = NULL;
  node *curr;

  while (otherCurr != NULL) {
    // Copy other list's current node
    curr = new node(otherCurr->index, otherCurr->value);
    if (prev == NULL) {
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
  while (curr != NULL) {
    node *next = curr->next; // Get what is next, before deleting curr.
    delete curr;   // Delete this node.
    curr = next;   // Go to next node in list
  }
  mStart = NULL;   // indicate that the list is empty
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

// private helper functions for setElem

// look for node with the right index, and set it to value.
// if we can't find the right index, insert a new node in the right place
void SparseVector::setNonzeroElem(int index, int value) {
  assert(value != 0);

  // Use prev and curr to keep track of nodes
  node *prev = NULL;
  node *curr = mStart;

  // find the node we need to insert in front of.
  while (curr != NULL && curr->index <= index) {
    if (curr->index == index) {
      curr->value = value;  // if we found the index, set new value. Done.
      return;
    }
    prev = curr;         // Done with current node!
    curr = curr->next;  // Move to the next node
  }


  node *insertNode = new node(index, value);

  // If curr != NULL, we found a place to insert in front of.  We have already 
  // created the node, but we need its next to point to the current node to 
  // correctly link it up.
  if (curr != NULL) { 
    insertNode->next = curr;
  }

  // update the previous node, depending on whether we are trying to add to the
  // beginning of the list or not.
  if (prev != NULL) {     // add correct link to new node if we are not at start
    prev->next = insertNode;
  } else {
    mStart = insertNode;  // if we are at beginning of list, update start.
  }


  checkListOrder(); // make sure we didn't mangle list
}

// if set value to 0, remove the node at the given index
void SparseVector::removeElem(int index) {
  node *prev = NULL;
  node *curr = mStart;

  // try to find the correct node to remove
  while (curr != NULL) {
    if (curr->index == index) {  // we found the correct node
      break;
    }
    if (curr->index > index) { 
      return;  // if we passed it, return early
    }
    prev = curr;
    curr = curr->next; // Go to the next node

  }

  if (curr == NULL) {  // if we didn't find index, nothing to remove
    return;
  }

  if (curr == mStart) {  // if we remove start node, update start
    mStart = curr->next;
  }

  if (prev != NULL) {   // fix the linked list to skip over the removed node
    prev->next = curr->next;
  }

  delete curr;  // remove the node

  checkListOrder();  // make sure we didn't mangle list
}

// private debugging function
// loop through all nodes of linked list, print some debugging output if
// indices somehow get out of order.
void SparseVector::checkListOrder() const{
  if (mStart == NULL) {
    return;
  }
  node *prev = NULL;
  node *curr = mStart;

  while (curr != NULL) {
    if ((prev != NULL) && (curr->index <= prev->index)) {

      std::cout << "-------------------------------------" << std::endl;
      std::cout << "Nodes are our of order!" << std::endl;

      std::cout << "Previous Index: " << prev->index << std::endl;
      std::cout << "Previous Value: " << prev->value << std::endl;

      std::cout << "Current Index: " << curr->index << std::endl;
      std::cout << "Current Value: " << curr->value << std::endl;

      node *next = curr->next;
      if (next != NULL) {
        std::cout << "Next Index: " << next->index << std::endl;
        std::cout << "Next Value: " << next->value << std::endl;
      }

      assert (0 > 1); // trip an assertion so we know where we messed up
    }

    prev = curr;
    curr = curr->next;  // go to the next node
  }

  // we finished, nodes are in correct order
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
  while (curr != NULL) {
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

}

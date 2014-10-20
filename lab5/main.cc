#include <iostream>
#include <string>

#include "heap.hh"

// This test constructs of heap of ints of max size 4, and then tests whether
// overflow and underflow exceptions are correctly thrown.
void test_exceptions() {
  int i;
  double lastval;

  Heap<double, 4> h;

  /* Use a seed so that the sequence of random values
   * is always the same.
   */
  srand(11);

  /* Fill up the heap with random values. */
  for (i = 0; i < 4; i++)
    h.add_value((rand() % 1000));

  // TEST: overflow exception is thrown correctly
  try {
    // add another value even though the heap is full. expect an overflow exception
    h.add_value((rand() % 1000));
    std::cout << "ERROR - didn't catch overflow exception!" << std::endl;
  }
  catch (std::overflow_error &e) {
    // enter this catch block if we caught correct exception
    std::cout << "OK - caught overflow exception!" << std::endl;
  }
  catch (...) {
    // If the function throws something other than what we expected,
    // this catch-block will run.
    std::cout << "ERROR - overflow caused unknown exception!" << std::endl; 
  }

  /*
   * Print out the results.  If anything is out of order,
   * flag it.  (Pull the very first value separately so that
   * we don't have to set lastval to something strange just
   * to get the test to work...)
   */

  lastval = h.get_first_value();
  std::cout << "Value 0 = " << lastval << std::endl;

  for (i = 1; i < 4; i++)
  {
    double val = h.get_first_value();

    std::cout << "Value " << i << " = " << val << std::endl;
    if (val < lastval)
      std::cout << "  ERROR:   OUT OR ORDER." << std::endl;

    lastval = val;
  }

  // TEST: underflow exception is thrown correctly
  try {
    // try to get first value, even though heap is empty. expect an underflow exception
    h.get_first_value();
    std::cout << "ERROR - didn't catch underflow exception!" << std::endl;
  }
  catch (std::underflow_error &e) {
    // enter this catch block if we caught correct exception
    std::cout << "OK - caught underflow exception!" << std::endl;
  }
  catch (...) {
    // If the function throws something other than what we expected,
    // this catch-block will run.
    std::cout << "ERROR - underflow caused unknown exception!" << std::endl; 
  }
}

// This test constructs of heap of 10 strings, proving that we have a working template
// for the heap, as all that is needed is the < operator, which strings do have.
// overflow and underflow exceptions are correctly thrown.
void test_stringHeap() {
  int i;
  std::string lastStr;

  Heap<std::string, 10> h;

  /* Add 10 strings to the heap in unsorted order */
  h.add_value(std::string("red"));
  h.add_value(std::string("yellow"));
  h.add_value(std::string("orange"));
  h.add_value(std::string("gold"));
  h.add_value(std::string("silver"));
  h.add_value(std::string("green"));
  h.add_value(std::string("blue"));
  h.add_value(std::string("gray"));
  h.add_value(std::string("black"));
  h.add_value(std::string("pink"));


  /*
   * Print out the results.  If anything is out of order,
   * flag it.  (Pull the very first value separately so that
   * we don't have to set lastval to something strange just
   * to get the test to work...)
   */

  lastStr = h.get_first_value();
  std::cout << "Value 0 = " << lastStr << std::endl;

  for (i = 1; i < 10; i++)
  {
    std::string currentStr = h.get_first_value();

    std::cout << "Value " << i << " = " << currentStr << std::endl;
    if (currentStr < lastStr)
      std::cout << "  ERROR:   OUT OR ORDER." << std::endl;

    lastStr = currentStr;
  }
}

/* Test the heap. */
int main(int argc, char **argv)
{
  test_exceptions();
  test_stringHeap();

  return 0;
}
/* Unit testing for the fermat factoring project.
Andrew Shallue, June 2025
*/

#ifndef UNITTEST_H
#define UNITTEST_H

#include <vector>
#include <iostream>
#include "int.h"
#include "primetest.h"

using std::vector;

// test the fermat function.  Checking base 2 psp (those not prime) against OEIS list
bool fermata_test_base2();
bool fermat1_test_base2();

// test that the list of all strong bases is a subset of all fermat bases


#endif
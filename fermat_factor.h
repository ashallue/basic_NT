/* Factoring via the Fermat test.  Key result is that if a is a fermat base 
but not a strong base, we can use a to split n.
Andrew Shallue, June 2025
*/

#ifndef FERMATFACTOR_H
#define FERMATFACTOR_H

#include "int.h"
#include "primetest.h"
#include <vector>
#include <algorithm>

using std::vector;

// functions that loop up to n, pushing all bases found in the vector bases
// for all_fermat_bases I use fermata, so includes a which are not relatively prime
void all_fermat_bases(int64 n, vector<int64>& bases);
void all_strong_bases(int64 n, vector<int64>& bases);

// given n, count a in F(n) - R(n), and calculate prob a^{n'} = 1 mod p 
// return type is a pair, #a that satisfy equation then #a total, which gives probability
pair<int64, int64> prob_fermat_split(int64 n, int64 p);

// given n, count a in F(n) - R(n), and calculate prob a^{n'} = 1 mod p for two primes
// return type is a pair, #a that satisfy equation then #a total, which gives probability
pair<int64, int64> prob_fermat_twosplit(int64 n, int64 p, int64 q);

// given n and a factor m of n, compare sets in various ways
void compare_set_factor(int64 n, int64 m, int64 test_pow);

#endif
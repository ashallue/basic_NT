#include <iostream>
#include <fstream>
#include <vector>
#include "math.h"
#include "bigint.h"
#include "primetest.h"
#include "fermat_factor.h"
#include "test_functions.h"
#include <chrono>

using namespace std::chrono;


// expecting two arguments: 1) thread number for this instance, 2) total thread count
int main(int argc, char* argv[]) {
  std::cout << "Hello World! argc has value " << argc << "\n";

  long thread = 0;
  long num_threads = 1;
  string cars_file = "cars.txt";
  string none_file = "cars_none.txt"; 
 
  if(argc == 3){
    cout << "Two arguments given\n";
    cout << "Argument 1: " << argv[1] << "\n";
    cout << "Argument 2: " << argv[2] << "\n";
  
    // retrieve thread number and total from input
    thread = atoi(argv[1]);
    num_threads = atoi(argv[2]);
  
    // create file names for carmichaels, and admissable pre-products w/o carmichaels
    cars_file = "cars" + to_string(thread) + ".txt";
    none_file = "cars_none" + to_string(thread) + ".txt";
    
    cout << "This is thread " << thread << " of " << num_threads << "total\n";
  }

  int64 n = 45890209;  // 29 53 73 409
  int64 p = 73;
  int64 q = 29;
  pair<int64, int64> prob = prob_fermat_twosplit(n, p, q);
  std::cout << "prob is " << prob.first << " " << prob.second << "\n";

  bool test1 = fermata_test_base2();
  bool test2 = fermat1_test_base2();
  std::cout << "result of tests: " << test1 << " " << test2 << "\n";

  // testing pushing

  /*

  // number to try to factor
  // 290100025217620801 19 31 937 6553 8161 9829
  // n = 2^6 * 4532812894025325
  int64 n = 290100025217620801;
  int16 e = 6;
  int64 u = 4532812894025325;
  // check if 2 is a fermat/strong base
  bool fermat2 = fermata(2, n);
  bool strong2 = strong(2, n, u, e);

  int64 test = powmod(2, n-1, n);
  std::cout << "test = " << test << "\n";

  std::cout << "2 a fermat base: " << fermat2 << "\n";
  std::cout << "2 a strong base: " << strong2 << "\n";

  int64 x = powmod(2, u, n);
  int64 factor = gcd(n, x+1);
  // 2 is a fermat base but not a strong base, use it to factor
  for(int16 i = 0; i < e; i++){
    std::cout << "x = " << x << "\n";
    std::cout << "factor = " << factor << "\n";

    x = 2 * x % n;
    factor = gcd(n, x+1);
  }

  // this gives me 31.  Compute cofactor m
  int64 m = n / 31;
  int16 me = 1;
  int64 mu = (m - 1) / 2;

  std::cout << "m = " << m << "\n";
  int64 g = gcd(m-1, n-1);
  std::cout << "g = " << g << "\n";
  // new base is a^(n-1)/g mod m
  int64 b = powmod(2, (n-1)/g, m);
  std::cout << "b = " << b << "\n";

  bool fermatb = fermata(b, m);
  bool strongb = strong(b, m, mu, me);

  std::cout << "fermatb = " << fermatb << "\n";
  std::cout << "strongb = " << strongb << "\n";

  */


}

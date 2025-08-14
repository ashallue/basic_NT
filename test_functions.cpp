/* Unit testing for the fermat factoring project.
Andrew Shallue, June 2025
*/

#include "test_functions.h"

// test the fermat function.  Checking base 2 psp against OEIS list
bool fermata_test_base2(){
    // we will test against psp less than 10000
    vector<int64> oeis = {341, 561, 645, 1105, 1387, 1729, 1905, 2047, 2465,
                          2701, 2821, 3277, 4033, 4369, 4371, 4681, 5461, 6601, 
                          7957, 8321, 8481, 8911};

    // generate test list of pseudoprimes
    vector<int64> test;
    for(int64 n = 2; n < 10000; ++n){

        // keep those which base the fermat-a test and are not prime
        if( fermata(2, n) && !primetest(n) ){
            test.push_back(n);
        }
    }

    // now check that these two vectors match.
    bool match = true;
    if( oeis.size() != test.size() ){
        match = false;
    }
    for(int64 i = 0; i < test.size(); ++i){
        if( oeis.at(i) != test.at(i) ){
            match = false;
        }
    }
    return match;
}


bool fermat1_test_base2(){
    // we will test against psp less than 10000
    vector<int64> oeis = {341, 561, 645, 1105, 1387, 1729, 1905, 2047, 2465,
                          2701, 2821, 3277, 4033, 4369, 4371, 4681, 5461, 6601, 
                          7957, 8321, 8481, 8911};

    // generate test list of pseudoprimes
    vector<int64> test;
    for(int64 n = 2; n < 10000; ++n){

        // keep those which base the fermat-1 test and are not prime
        if( fermat1(2, n) && !primetest(n) ){
            test.push_back(n);
        }
    }

    // now check that these two vectors match.
    bool match = true;
    if( oeis.size() != test.size() ){
        match = false;
    }
    for(int64 i = 0; i < test.size(); ++i){
        if( oeis.at(i) != test.at(i) ){
            match = false;
        }
    }
    return match;
}
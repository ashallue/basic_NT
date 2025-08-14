/* Factoring via the Fermat test.  Key result is that if a is a fermat base 
but not a strong base, we can use a to split n.
Andrew Shallue, June 2025
*/

#include "fermat_factor.h"

// functions that loop up to n, pushing all bases found in the vector bases
// for all_fermat_bases I use fermata, so includes a which are not relatively prime
void all_fermat_bases(int64 n, vector<int64>& bases){
    bases.clear();
    for(int64 i = 1; i < n; ++i){
        if(fermat1(i, n)){
            bases.push_back(i);
        }
    }
}

// functions that loop up to n, pushing all bases found in the vector bases
void all_strong_bases(int64 n, vector<int64>& bases){
    bases.clear();

    // calculate u, e such that n-1 = 2^e * u with u odd
    int64 u;
    int64 nminus = n - 1;
    int64 e = 0;
    while(nminus % 2 == 0){
        e++;
        nminus = nminus / 2;
    }
    u = nminus;

    for(int64 i = 1; i < n; ++i){
        if(strong(i, n, u, e)){
            bases.push_back(i);
        }
    }
}

// given n, count a in F(n) - R(n), and calculate prob a^{n'} = 1 mod p for p | n
// return type is a pair, #a that satisfy equation then #a total, which gives probability
pair<int64, int64> prob_fermat_split(int64 n, int64 p){
    pair<int64, int64> prob;
    int64 m, e;  // for decomposing n-1 = m * 2^e where m odd
    int64 tempn;

    // counts
    int64 count_bases = 0;
    int64 count_solns = 0;

    // counts for strong liars
    int64 count_fermat = 0;
    int64 count_rabin = 0;
    int64 count_p_satisfy = 0;
    int64 count_rabin_and_p = 0;

    // loop over all bases a up to n, keeping those in F(n) - R(n)
    for(int64 a = 1; a < n; ++a){
        e = 0;
        tempn = n-1;
        while(tempn % 2 == 0){
            e++;
            tempn = tempn / 2;
        }
        m = tempn;

        if(fermat1(a, n)){
            count_fermat++;
        }
        if(strong(a, n, m, e)){
            count_rabin++;
        }
        if(strong(a, n, m, e) && powmod(a, m, p) == 1){
            count_rabin_and_p++;
        }
        if(fermat1(a, n) && powmod(a, m, p) == 1){
            count_p_satisfy++;
        }

        if(fermat1(a, n) && !strong(a, n, m, e)){
            count_bases++;
            if(powmod(a, m, p) == 1){
                count_solns++;
            }
        }
    }
    std::cout << "\n";
    std::cout << "Count of fermat liars: " << count_fermat << "\n";
    std::cout << "Count of strong liars: " << count_rabin << "\n";
    std::cout << "Count of fermat liars that satisfy equation: " << count_p_satisfy << "\n";
    std::cout << "Count of strong liars that satisfy: " << count_rabin_and_p << "\n";
    std::cout << "\n";
    
    // actual output
    prob.first = count_solns;
    prob.second = count_bases;
    return prob;
}

// given n, count a in F(n) - R(n), and calculate prob a^{n'} = 1 mod p for two primes
// return type is a pair, #a that satisfy equation then #a total, which gives probability
pair<int64, int64> prob_fermat_twosplit(int64 n, int64 p, int64 q){
    pair<int64, int64> prob;
    int64 m, e;  // for decomposing n-1 = m * 2^e where m odd
    int64 tempn;

    // counts
    int64 count_bases = 0; 
    int64 count_solns = 0; // satisfies both equations

    // counts for strong liars
    int64 count_fermat = 0;
    int64 count_rabin = 0;
    int64 count_p_satisfy = 0;
    int64 count_q_satisfy = 0;
    int64 count_rabin_and_p = 0;

    // loop over all bases a up to n, keeping those in F(n) - R(n)
    for(int64 a = 1; a < n; ++a){
        e = 0;
        tempn = n-1;
        while(tempn % 2 == 0){
            e++;
            tempn = tempn / 2;
        }
        m = tempn;

        if(fermat1(a, n)){
            count_fermat++;
        }
        if(strong(a, n, m, e)){
            count_rabin++;
        }
        if(strong(a, n, m, e) && powmod(a, m, p) == 1){
            count_rabin_and_p++;
        }
        if(fermat1(a, n) && powmod(a, m, p) == 1){
            count_p_satisfy++;
        }
        if(fermat1(a, n) && powmod(a, m, q) == 1){
            count_q_satisfy++;
        }

        if(fermat1(a, n) && !strong(a, n, m, e)){
            count_bases++;
            if(powmod(a, m, p) == 1 && powmod(a, m, q) == 1){
                count_solns++;
            }
        }
    }
    std::cout << "\n";
    std::cout << "Count of fermat liars: " << count_fermat << "\n";
    std::cout << "Count of strong liars: " << count_rabin << "\n";
    std::cout << "Count of fermat liars that satisfy p equation: " << count_p_satisfy << "\n";
    std::cout << "Count of fermat liars that satisfy q equation: " << count_q_satisfy << "\n";
    std::cout << "Count of strong liars that satisfy: " << count_rabin_and_p << "\n";
    std::cout << "\n";
    
    // actual output
    prob.first = count_solns;
    prob.second = count_bases;
    return prob;
}

// given n and a factor m of n, compare sets in various ways
void compare_set_factor(int64 n, int64 m, int64 test_pow){
    // make sure m divides n
    if(n % m != 0){
        std::cout << "Error: " << m << " not a factor of " << n << "\n";
    }

    // find all fermat bases of m
    vector<int64> m_fermat_bases;
    all_fermat_bases(m, m_fermat_bases);

    // find all strong bases of m
    vector<int64> m_strong_bases;
    all_strong_bases(m, m_strong_bases);

    // find all fermat bases of n
    vector<int64> n_fermat_bases;
    all_fermat_bases(n, n_fermat_bases);

    // for each a, calculate and store a^pow mod m.
    vector<int64> created_bases;
    for(int64 i = 0; i < n_fermat_bases.size(); ++i){
        int64 a = n_fermat_bases.at(i);
        int64 new_m_base = powmod(a, test_pow, m);

        // call find to see if this base is already in the list.  Add if not
        vector<int64>::iterator found = find(created_bases.begin(), created_bases.end(), new_m_base);
        if( found == created_bases.end() ){
            created_bases.push_back(new_m_base);
        }
        
    }
    std::cout << "original n bases:\n";
    for(int i = 0; i < n_fermat_bases.size(); ++i){
        std::cout << n_fermat_bases.at(i) << " ";
    }
    std::cout << "\n";

    std::cout << "original m bases:\n";
    for(int i = 0; i < m_fermat_bases.size(); ++i){
        std::cout << m_fermat_bases.at(i) << " ";
    }
    std::cout << "\n";
    std::cout << "new m bases:\n";
    for(int i = 0; i < created_bases.size(); ++i){
        std::cout << created_bases.at(i) << " ";
    }
    std::cout << "\n";
  
    std::cout << "strong m bases:\n";
    for(int i = 0; i < m_strong_bases.size(); ++i){
        std::cout << m_strong_bases.at(i) << " ";
    }
    std::cout << "\n";
}
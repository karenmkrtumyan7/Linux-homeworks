#include <iostream>
#include "big_integer.hpp"

BigUnsigned::BigUnsigned(string & s) {
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0; i--) {
        digits.push_back(s[i] - '0');
    }
}

BigUnsigned operator+(BigUnsigned &a, BigUnsigned &b){ 
    // logic
    return BigUnsigned;
}

BigUnsigned operator*(BigUnsigned&a, BigUnsigned&b){
    // logic
    return BigUnsigned;
}

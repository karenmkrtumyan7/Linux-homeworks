#include <iostream>
#include "big_integer.hpp"
#include <string>

BigUnsigned::BigUnsigned(const std::string s) {
    this->digits = stoi(s);
}

BigUnsigned operator+(BigUnsigned a, BigUnsigned b){ 
   a.digits += b.digits;
   return a;
}

BigUnsigned operator*(BigUnsigned a, BigUnsigned b){
    a.digits *= b.digits;
    return a;
}

#ifndef BIG
#define BIG
#include <iostream> 
class BigUnsigned {
public:
	std::string digits = "";
	BigUnsigned(const string&s){};
	friend BigUnsigned operator+(BigInt &, BigInt &);
	friend BigUnsigned operator*(BigUnsigned &, BigUnsigned &);
}

#ifndef BIG
#define BIG
#include <string>
class BigUnsigned {
public:
	unsigned long long digits = 0;
	BigUnsigned(const std::string s);
	friend BigUnsigned operator+(BigUnsigned, BigUnsigned);
	friend BigUnsigned operator*(BigUnsigned, BigUnsigned);
};
#endif

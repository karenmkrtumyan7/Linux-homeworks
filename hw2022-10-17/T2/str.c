#include "str.h"

int string_length(const char * str){
	int i = 0;
	while(*str != '\0'){
		i++;
		str++;
	}
	return i;
}

int num_digits(const char * str){
	int j = 0;
	for(int i = 0; i < string_length(str); i++){
		if (str[i] >= '0' && str[i] <= '9') j++;
	}
	return j;
}

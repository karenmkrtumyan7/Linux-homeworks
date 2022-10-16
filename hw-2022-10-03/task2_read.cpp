#include <stdio.h>
#include "task2_read.hpp"

void read_and_invert(){
  char str[80];
  char letter;
  int length = 0;
  while(letter != '\n') {
    letter = getchar();
    str[length] = letter;
    length++;
  }

  for(int i = 0; i < length; i++){
    putchar(str[length - i - 1]);
  }
}

#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int number;
  char letter;
}Test;

void call(Test* given);

void call(Test* given){
  printf("%d",(*given).number);
  (*given).number=3;

}

int main(){
  Test test;
  test.number=2;
  call(&test);
  printf("%d",test.number);
  return 0;
}

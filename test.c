#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int number;
  char letter;
}Test;

void call(char);

void call(char test){
  printf("%s",test);

}

int main(){
  Test test;
  Test test2;
  test.number=1;
  test2.number=2;
  Test temp;
  temp=test;
  test=test2;
  test2=temp;
  printf("%d\n",test.number);
}

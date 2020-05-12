#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *books;
  char test;
  int num;
  books=fopen("C:\\Users\\NovaGamma\\github\\Projet-library\\books.txt","r");
  fscanf(books,"%d %c",&num,&test);
  fclose(books);
  printf("num = %d test = %c",num,test);
  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "book.h"

void addBook(Library* library){//in order to add a book to the library, since we allocate dynamically the array, we need to allocate more space to it (the space for 1 book)
  (*library).nBooks++;
  realloc((*library).list,(*library).nBooks*sizeof(Book));
  getBook(&((*library).list[(*library).nBooks-1]));
}


void getBook(Book* book){
  char theme[3];
  printf("Please give the title of the book (max 100 characters) : ");
  fgets((*book).title,sizeof((*book).title),stdin);
  int i=0;
  while(((*book).title)[i]!='\n' && i<100){
    i++;}
  ((*book).title)[i]=' ';
  printf("Please give the name of the author (max 50 characters) : ");
  fgets((*book).author,sizeof((*book).author),stdin);
  i=0;
  while(((*book).author)[i]!='\n' && i<50){
    i++;}
  ((*book).author)[i]=' ';
  printf("Please give the theme of the book (ex : CAR for cartoon) : ");
  fgets(theme,sizeof(theme),stdin);
  while ((getchar()) != '\n');//clearing the buffer input
  printf("Please give the number of copies of the book : ");
  scanf("%d",&(*book).nCopies);
  (*book).nAvailableCopies=(*book).nCopies;
}

void displayBook(Book* book){
  printf("\nTitle : %s\nAuthor : %s\nCode : %s\nNumber of copies availables : %d\nTotal number of copies : %d\n",book->title,book->author,book->code,book->nAvailableCopies,book->nCopies);
}

void saveBook(Book* book){
  FILE *books;
  books=fopen("C:\\Users\\NovaGamma\\github\\Projet-library\\books2.txt","a");
  fprintf(books,"%s/%s/%s/%d/%d\n",book->title,book->author,book->code,book->nAvailableCopies,book->nCopies);
  fclose(books);
}

void saveBooks(Library* library){
  FILE *books;
  books=fopen("C:\\Users\\NovaGamma\\github\\Projet-library\\books2.txt","w");
  fprintf(books,"%d\n",(*library).nBooks);
  fclose(books);
  for(int i=0;i<(*library).nBooks;i++)
    saveBook(&((*library).list[i]));

}

void readBook(Book* book,int index){
  FILE *books;
  char test[100];
  books=fopen("C:\\Users\\NovaGamma\\github\\Projet-library\\books.txt","r");
  for(int i=0;i<=index;i++)
    fgets(test,100,books);
  fscanf(books,"%[^/]/%[^/]/%[^/]/%d/%d\n",&book->title,&book->author,&book->code,&book->nAvailableCopies,&book->nCopies);
  //fscanf(books,"%[^/]/%[^/]/%[^/]/%d/%d\n",&title,&author,&code,&nAvailableCopies,&nCopies);
  //printf("\nTitle : %s\nAuthor : %s\nCode : %s\nNumber of copies availables : %d\nTotal number of copies : %d\n",title,author,code,nAvailableCopies,nCopies);
  fclose(books);
}

void readBooks(Library* library){
  FILE *books;
  books=fopen("C:\\Users\\NovaGamma\\github\\Projet-(*library)\\books.txt","r");
  fscanf(books,"%d",(*library).nBooks);
  fclose(books);
  (*library).list=(Book*)malloc((*library).nBooks*sizeof(Book));
  for(int i=0;i<(*library).nBooks;i++){
    readBook(&((*library).list[i]),i);}
}

void displayBooks(Library* library){
for(int i=0;i<(*library).nBooks;i++)
  displayBook(&((*library).list[i]));
}

int main(){
  Book test;
  Library library;
  library.nBooks=2;
  readBooks(&library);
  addBook(&library);
  //readBook(&listOfBooks[0]);
  displayBooks(&library);
  saveBooks(&library);
  return 0;
}

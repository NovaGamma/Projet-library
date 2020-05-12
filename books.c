#include <stdio.h>
#include <stdlib.h>
#include "book.h"

/*void addBook(Book* book){
  char theme[3];
  printf("Please give the title of the book (max 100 characters) : ");
  fgets(&book->title,sizeof((*book).title),stdin);
  int i=0;
  while((book->title)[i]!='\n' && i<100){
    i++;}
  (book->title)[i]=' ';
  printf("Please give the name of the author (max 50 characters) : ");
  fgets(&book->author,sizeof((*book).author),stdin);
  i=0;
  while((book->author)[i]!='\n' && i<50){
    i++;}
  (book->author)[i]=' ';
  printf("Please give the theme of the book (ex : CAR for cartoon) : ");
  fgets(theme,sizeof(theme),stdin);
  while ((getchar()) != '\n');//clearing the buffer input
  printf("Please give the number of copies of the book : ");
  scanf("%d",&book->nCopies);
  book->nAvailableCopies=book->nCopies;
}*/

void displayBook(Book* book){
  printf("\nTitle : %s\nAuthor : %s\nCode : %s\nNumber of copies availables : %d\nTotal number of copies : %d\n",book->title,book->author,book->code,book->nAvailableCopies,book->nCopies);
}

void saveBook(Book* book){
  FILE *books;
  books=fopen("C:\\Users\\NovaGamma\\github\\Projet-library\\books2.txt","a");
  fprintf(books,"%s/%s/%s/%d/%d\n",book->title,book->author,book->code,book->nAvailableCopies,book->nCopies);
  fclose(books);
}

void saveBooks(Book *listOfBook,int nBooks){
  FILE *books;
  books=fopen("C:\\Users\\NovaGamma\\github\\Projet-library\\books2.txt","w");
  fprintf(books,"%d\n",nBooks);
  fclose(books);
  for(int i=0;i<nBooks;i++)
    saveBook(listOfBook+i);

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

Book* readBooks(Book *listOfBook){
  FILE *books;
  int nBooks=0;
  books=fopen("C:\\Users\\NovaGamma\\github\\Projet-library\\books.txt","r");
  fscanf(books,"%d",&nBooks);
  fclose(books);
  listOfBook=(Book*)malloc(nBooks*sizeof(Book));
  for(int i=0;i<nBooks;i++){
    readBook(listOfBook+i,i);}
  return listOfBook;
}

void displayBooks(Book *listOfBook,int nBooks){
for(int i=0;i<nBooks;i++)
  displayBook(listOfBook+i);
}

int main(){
  Book test;
  Book *listOfBooks;
  int nBooks=2;
  listOfBooks=readBooks(listOfBooks);
  //addBook(&test);
  //readBook(&listOfBooks[0]);
  displayBooks(listOfBooks,nBooks);
  saveBooks(listOfBooks,nBooks);
  return 0;
}

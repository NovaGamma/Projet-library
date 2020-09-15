#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

void addBook(Library* library){//in order to add a book to the library, since we allocate dynamically the array, we need to allocate more space to it (the space for 1 book)
  (*library).nBooks++;
  (*library).list=realloc((*library).list,(*library).nBooks*sizeof(Book));
  getBook(library,&((*library).list[(*library).nBooks-1]));
}

int getCode(Library* library,char theme[3]){
  int nBooks=0;
  for(int i=0;i<(*library).nBooks;i++){
    if(strcmp((*library).list[i].theme,theme)==0)
      nBooks++;
  }
  return nBooks+1;
}

void getBook(Library* library,Book* book){
  char theme[3];
  char strCode[3];
  int code;
  printf("Please give the title of the book (max 100 characters) : ");
  fgets((*book).title,sizeof((*book).title),stdin);
  int i=0;
  while(((*book).title)[i]!='\n' && i<100){//getting the string until we reach the 100 char limit or a \n character
    i++;}
  ((*book).title)[i]=' ';//then we remove the last character that is a \n
  printf("Please give the name of the author (max 50 characters) : ");
  fgets((*book).author,sizeof((*book).author),stdin);
  i=0;
  while(((*book).author)[i]!='\n' && i<50){//getting the string until we reach the 100 char limit or a \n character
    i++;}
  ((*book).author)[i]=' ';//then we remove the last character that is a \n
  printf("Please give the theme of the book (ex : CAR for cartoon) : ");
  fgets((*book).theme,sizeof((*book).theme),stdin);
  code=getCode(library,theme);
  itoa(code,strCode,10);//using the function int to integer
  strcat((*book).code,(*book).theme);
  strcat((*book).code,"-");
  strcat((*book).code,strCode);
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
  books=fopen("db-Book.txt","a");
  fprintf(books,"%s/%s/%s/%d/%s/%d\n",book->title,book->author,book->code,book->nAvailableCopies,book->theme,book->nCopies);
  fclose(books);
}

void saveBooks(Library* library){
  FILE *books;
  int i=0;
  printf("Saving the Books...");
  books=fopen("db-Book.txt","w");
  fprintf(books,"%d\n",(*library).nBooks);
  fclose(books);
  for(i=0;i<(*library).nBooks;i++){
    printf("book number : %d\n",i);
    saveBook(&((*library).list[i]));
  }
}

void readBook(Book* book,int index){
  FILE *books;
  char test[100];
  books=fopen("db-Book.txt","r");
  for(int i=0;i<=index;i++)
    fgets(test,100,books);
  fscanf(books,"%[^/]/%[^/]/%[^/]/%d/%[^/]/%d\n",&book->title,&book->author,&book->code,&book->nAvailableCopies,&book->theme,&book->nCopies);
  fclose(books);
}

void readBooks(Library* library){
  FILE *books;
  int i=0;
  books=fopen("db-Book.txt","r");
  fscanf(books,"%d\n",&(*library).nBooks);
  fclose(books);
  (*library).list=(Book*)malloc((*library).nBooks*sizeof(Book));
  printf("Loading Books...\n");
  for(i=0;i<(*library).nBooks;i++){
    readBook(&((*library).list[i]),i);
  }
  printf("Finished loading Book %d loaded\n",i);
}

void displayBooks(Library* library){
  printf("%d books in the library\n",(*library).nBooks);
  for(int i=0;i<(*library).nBooks;i++)
    displayBook(&((*library).list[i]));
}

void deleteBook(Library* library){//here index is the index of the book that we want to delete
//first we need to exchange the last book with the one that we want to deleteBook
int index;
//and we will ask for the book to check if it exist
  int exist=0;
  int try=0;
  char code[7];
  do{
    printf("Please give the code of the book : \n");
    gets(code);
    index=-1;
    do{
      index++;
      if(strcmp((*library).list[index].code,code)==0) exist=1;
    }while(index<(*library).nBooks-1 && exist==0);
    if(exist==0){
    printf("The given code doesn't correspond to any book in the library, please try again\n");
    try++;}
    if(try==3){
      printf("You did too many tries, your maybe stuck, you've been sent back in the menu\n");
      return;
    }
  }while(exist==0);
  if((*library).list[index].nAvailableCopies!=(*library).list[index].nCopies){
    printf("The book doesn't have all it's copied returned, you can't delete it, you'll be sent back to the menu");
    return;
  }
  if (index!=(*library).nBooks-1){
    Book temp;
    temp=(*library).list[index];
    (*library).list[index]=(*library).list[(*library).nBooks-1];
    (*library).list[(*library).nBooks-1]=temp;
  }
  (*library).nBooks--;
  (*library).list=realloc((*library).list,(*library).nBooks*sizeof(Book));
}

void bookSearch(Library* library,int type){
  Library result;
  int i;
  char name[100];
  result.list=(Book*)malloc(sizeof(Book));
  result.nBooks=0;
  if(type==1){
    char name[7];
    printf("Please give the code of the Book (in form CAR-001) : ");
    gets(name);
    search(library,&result,type,name);
  }
  else
    if(type==2){
      char name[100];//100 characters because it's the limit defined in the Book struct
      printf("Please give the title of the book : ");
      gets(name);
      search(library,&result,type,name);
  }
  else
    if(type==3){
      char name[50];//50 characters because it's the limit defined in the Book struct
      printf("Please give the name of the author : ");
      gets(name);
      search(library,&result,type,name);
    }
    else
      if(type==4){
        char name[3];//3 characters because it's the limit defined in the Book struct
        printf("Please give the theme of the book (ex : SFX) : ");
        gets(name);
        search(library,&result,type,name);
      }

      printf("Found %d books corresponding\n",result.nBooks);
      for(i=0;i<result.nBooks;i++){
        printf("\nTitle : %s\nAuthor : %s\nCode : %s\nNumber of copies availables : %d\nTotal number of copies : %d\n",result.list[i].title,result.list[i].author,result.list[i].code,result.list[i].nAvailableCopies,result.list[i].nCopies);
  }
}

int testBook(Book* book,int type,char name[]){
  switch (type){
    case 1:
      return strcmp((*book).code,name);
    case 2:
      return strcmp((*book).title,name);
    case 3:
      return strcmp((*book).author,name);
    case 4:
      return strcmp((*book).theme,name);
    default:
      printf("ERROR");
  }
}

void search(Library* library,Library* result,int type, char name[]){
  printf("%d\n",strlen(name));
  for(int i=0;i<(*library).nBooks;i++){
    if(testBook(&(*library).list[i],type,name)==0){//  testBook(&(*library).list[i],type,name)
      (*result).nBooks++;
      if((*result).nBooks>1){
        (*result).list=realloc((*result).list,((*result).nBooks)*sizeof(Book));
      }
    (*result).list[(*result).nBooks-1]=(*library).list[i];
    }
  }
}


void sortTheme(Library* library){
  Book temp;
  for(int i=0;i<(*library).nBooks;i++)
  {
    for(int j=0;j<(*library).nBooks;j++)
    {
      if ((*library).list[j].theme > (*library).list[j+1].theme)
      {
          temp = (*library).list[j+1];
          (*library).list[j+1] = (*library).list[j];
          (*library).list[j] = temp;
      }
    }
  }
}

void sortCode(Library* library){
  Book temp;
  for(int i=0;i<(*library).nBooks;i++)
  {
    for(int j=0;j<(*library).nBooks;j++)
    {
      if ((*library).list[j].code > (*library).list[j+1].code)
      {
          temp = (*library).list[j+1];
          (*library).list[j+1] = (*library).list[j];
          (*library).list[j] = temp;
      }
    }
  }
}

void sortAuthor(Library* library){
  Book temp;
  for(int i=0;i<(*library).nBooks;i++)
  {
    for(int j=0;j<(*library).nBooks;j++)
    {
      if ((*library).list[j].author > (*library).list[j+1].author)
      {
          temp = (*library).list[j+1];
          (*library).list[j+1] = (*library).list[j];
          (*library).list[j] = temp;
      }
    }
  }
}

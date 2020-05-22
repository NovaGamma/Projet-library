#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "books.c"

void init(Library* library){
  readBooks(&(*library));
}


void readOnlyAccessServiceMenu(Library* library)
{
  char choice;
  printf("Make your choice between:");
  printf("To view the list of members: press a");
  printf("To view the list of books: press b");
  printf("To view information about a book: press c");
  printf("To view the list of borrowed books: press d");

  getLetter(&choice, "Your choice: ", 4);

  switch (choice)
  {
    case 'a':
      //listOfMembers();
      break;

    case 'b':
      displayBooks(library);
      break;

    case 'c':
      //informationAboutABook();
      break;

    case 'd':
      //listOfBorrowedBooks();
      break;

    default:
      printf("ERROR");
  }
}

void interfacesWithTheLibrarianMenu(Library* library)
{
  char choice;
  printf("Make your choice between:");
  printf("To add a new member: press a");
  printf("To add a new books: press b");
  printf("To delet an adherent or a book: press c");
  printf("To save a new loan: press d");
  printf("To take into account the restitution of a book: press e");

  getLetter(&choice, "Your choice: ", 5);

  switch (choice)
  {
    case 'a':
      //addMember();
      break;

    case 'b':
      addBook();
      break;

    case 'c':
      //deletDB();
      break;

    case 'd':
      //addLoan();
      break;

    case 'e':
      //restitutionBook();
      break;

    default:
      printf("ERROR");
  }
}

void getLetter(char *chr, char *message, int nbChoice)
{
    int n,ch;
    do{
        printf("%s", message);
        n = scanf("%c", chr);
        while ((ch = (int)getchar()) != '\n' && ch != EOF);
    } while (n!=1 || (n==1 && (*chr < 97 || *chr > 97+nbChoice-1)));
}

int main(){
  Library library;
  init(&library);
  /*
  char choice;

  printf("Make your choice between:\n");
  printf("To view the list of members: press a\n");
  printf("To view the list of books: press b\n");
  printf("To view information about a book: press c\n");
  printf("To view the list of borrowed books: press d\n");

  getLetter(&choice, "Your choice: ", 4);

  switch (choice)
  {
    case 'a':
      printf("aaaa");
      break;

    case 'b':
      printf("bbbb");
      break;

    case 'c':
      printf("cccc");
      break;

    case 'd':
      printf("dddd");
      break;

    default:
      printf("ERROR");
  }*/
  //saveAll();
  return 0;
}

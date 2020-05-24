#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "member.h"
#include "book.h"


void readOnlyAccessServiceMenu(Library* library, Community* community){
  char choice;
  printf("\nMake your choice between:\n");
  printf("To view the list of members: press a\n");
  printf("To view the list of books: press b\n");
  printf("To search for a book: press c\n");
  printf("To view the list of borrowed books: press d\n");

  getLetter(&choice, "Your choice : \n", 4);

  switch (choice)
{
    case 'a':
      displayMembers(community);
      break;

    case 'b':
      menuDisplayBooks(library);
      break;

    case 'c':
      searchBook(library);
      break;

    case 'd':
      //listOfBorrowedBooks();
      break;

    default:
      printf("ERROR");
  }
}

void menuDisplayBooks(Library* library){
  char choice;
  printf("\nMake your choice between :\n");
  printf("View the books alphabetically sorted : a\n");
  printf("View the books sorted by theme : b\n");
  printf("View the books sorted by author : c\n");

  getLetter(&choice, "Your choice : \n",3);
  switch(choice){
    case 'a':
      sortAlpha(library);
      break;

    case 'b':
      sortTheme(library);
      break;

    case 'c':
      sortAuthor(library);

    default:
      printf("ERROR");
  }
  displayBooks(library);
}

void searchBook(Library* library){
  char choice;
  printf("\nMake you choice between :\n");
  printf("Search using the name : a\n");
  printf("Search using the code : b\n");
  printf("Search using the author : c\n");
  printf("Search using the theme : d\n");

  getLetter(&choice, "Your choice : \n",4);
  switch(choice){
    case 'a':
      bookSearch(library,1);
      break;

    case 'b':
      bookSearch(library,2);
      break;

    case 'c':
      bookSearch(library,3);
      break;

    case 'd':
      bookSearch(library,4);
      break;

    default:
      printf("ERROR");
  }

}

void interfacesWithTheLibrarianMenu(Library* library,Community* community){
  char choice;
  printf("\nMake your choice between:\n");
  printf("To add a new member: press a\n");
  printf("To add a new books: press b\n");
  printf("To delete an adherent or a book: press c\n");
  printf("To save a new loan: press d\n");
  printf("To take into account the restitution of a book: press e\n");

  getLetter(&choice, "Your choice : \n", 5);

  switch (choice){
    case 'a':
      addMember(community);
      break;

    case 'b':
      addBook(library);
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

void getLetter(char *chr, char *message, int nbChoice){
    int n,ch;
    do{
        printf("%s", message);
        n = scanf("%c", chr);
        while ((ch = (int)getchar()) != '\n' && ch != EOF);
    } while (n!=1 || (n==1 && (*chr < 97 || *chr > 97+nbChoice-1)));
}

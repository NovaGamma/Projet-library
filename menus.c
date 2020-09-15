#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "member.h"
#include "book.h"


int readOnlyAccessServiceMenu(Library* library, Community* community,ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  char choice;
  printf("\nMake your choice between:\n");
  printf("To view the list of members: press a\n");
  printf("To view the list of books: press b\n");
  printf("To search for a book: press c\n");
  printf("To view the list of borrowed books: press d\n");
  printf("To change mode: press e\n");
  printf("To exit the programm: press f\n");

  getLetter(&choice, "Your choice : \n", 6);

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
      displayLoans(activeLoans);
      break;

    case 'e':
      return 2;

    case 'f':
      return 0;

    default:
      printf("ERROR");
  }
  return 1;
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
      sortCode(library);
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
  printf("Search using the code : a\n");
  printf("Search using the name : b\n");
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

int interfacesWithTheLibrarianMenu(Library* library,Community* community,ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  char choice;
  printf("\nMake your choice between:\n");
  printf("To add a new member: press a\n");
  printf("To add a new book: press b\n");
  printf("To delete an adherent: press c\n");
  printf("To delete a book: press d\n");
  printf("To save a new loan: press e\n");
  printf("To take into account the restitution of a book: press f\n");
  printf("To change mode: press g\n");
  printf("To exit the programm: press h\n");

  getLetter(&choice, "Your choice : \n", 8);

  switch (choice){
    case 'a':
      addMember(community);
      break;

    case 'b':
      addBook(library);
      break;

    case 'c':
      deleteMember(community);
      break;

    case 'd':
      deleteBook(library);
      break;

    case 'e':
      addLoan(library,community,activeLoans,totalLoans);
      break;

    case 'f':
      finishLoan(library,community,activeLoans,totalLoans);
      break;

    case 'g':
      return 2;

    case 'h':
      return 0;

    default:
      printf("ERROR");
  }
  return 1;
}

void getLetter(char *chr, char *message, int nbChoice){
    int n,ch;
    do{
        printf("%s", message);
        n = scanf("%c", chr);
        while ((ch = (int)getchar()) != '\n' && ch != EOF);
    } while (n!=1 || (n==1 && (*chr < 97 || *chr > 97+nbChoice-1)));
}

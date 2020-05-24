#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.c"
#include "members.c"
#include "books.c"

void init(Library* library,Community* community){
  readBooks(library);
  readMembers(community);
}

void saveAll(Library* library,Community* community){
  saveBooks(library);
  saveMembers(community);
}

int getMode(){
  char choice;
  printf("\nMake your choice between : \n");
  printf("Member mode : a\n");
  printf("Librarion mode : b\n");

  getLetter(&choice, "Your choice : \n",2);
  if(choice=='a') return 1;
  else if(choice=='b') return 2;
}

int main(){
  Library library;
  Community community;
  ListOfLoans activeLoans;
  ListOfLoans totalLoans;
  int mode;
  int on=1;
  printf("Initializing...\n");
  init(&library,&community);
  printf("Loading Complete\n");
  displayBook(&(library.list[0]));
  printf("%s\n",library.list[0].theme);
  mode=getMode();
  while(on==1){
    if(mode==1) readOnlyAccessServiceMenu(&library,&community);
    else if(mode==2) interfacesWithTheLibrarianMenu(&library,&community);
  }
  free(library.list);
  free(community.list);
  printf("Quiting");
  saveAll(&library,&community);
  free(library.list);
  free(community.list);
  return 0;
}

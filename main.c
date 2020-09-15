#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.c"
#include "members.c"
#include "loans.c"
#include "books.c"

void init(Library* library,Community* community,ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  readBooks(library);
  readMembers(community);
  readLoans(activeLoans,totalLoans);
}

void saveAll(Library* library,Community* community,ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  saveBooks(library);
  saveMembers(community);
  saveLoans(activeLoans,totalLoans);
}

int getMode(){
  char choice;
  printf("\nMake your choice between : \n");
  printf("Member mode : a\n");
  printf("Librarian mode : b\n");

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
  init(&library,&community,&activeLoans,&totalLoans);
  printf("Loading Complete\n");
  mode=getMode();
  while(on==1){
    if(mode==1) on=readOnlyAccessServiceMenu(&library,&community,&activeLoans,&totalLoans);
    else if(mode==2) on=interfacesWithTheLibrarianMenu(&library,&community,&activeLoans,&totalLoans);
    if(on==2){
      on=1;
      mode=getMode();
    }
  }
  printf("Quiting\n");
  saveAll(&library,&community,&activeLoans,&totalLoans);
  free(library.list);
  free(community.list);
  free(activeLoans.list);
  free(totalLoans.list);
  return 0;
}

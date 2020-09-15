#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "member.h"
#include "book.h"

int readOnlyAccessServiceMenu(Library*,Community*,ListOfLoans*,ListOfLoans*);
int interfacesWithTheLibrarianMenu(Library*,Community*,ListOfLoans*,ListOfLoans*);
void menuDisplayBooks(Library*);
void getLetter(char *chr, char *message, int nbChoice);
#endif

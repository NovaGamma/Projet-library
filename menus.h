#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include "member.h"
#include "book.h"

void readOnlyAccessServiceMenu(Library*,Community*);
void interfacesWithTheLibrarianMenu(Library*,Community*);
void menuDisplayBooks(Library*);
void getLetter(char *chr, char *message, int nbChoice);
#endif

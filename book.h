#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

typedef struct {
char title[100];
char author[50];
char code[7];
int nCopies;
char theme[3];
int nAvailableCopies;
//ptr loaners*; //will contain members who have borrowed a copy of this book

}Book;

typedef struct {
Book* list;
int nBooks;
//ptr loaners*; //will contain members who have borrowed a copy of this book
}Library;

void getBook(Library*,Book*);
void addBook(Library*);
void displayBook(Book*);
void readBooks(Library*);
void readBook(Book*,int);
void displayBooks(Library*);
void saveBook(Book*);
void saveBooks(Library*);
void deleteBook(Library*,int);
void searchBook(Library*);
int getCode(Library*,char[]);
void bookSearch(Library*,int);
void search(Library*,Library*,int, char[]);
int testBook(Book*,int,char[]);
void sortTheme(Library*);
void sortAlpha(Library*);
void sortAuthor(Library*);

#endif

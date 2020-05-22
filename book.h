typedef struct {
char title[100];
char author[50];
char code[7];
char theme[3];
int nCopies;
int nAvailableCopies;
//ptr loaners*; //will contain members who have borrowed a copy of this book

}Book;

typedef struct {
Book* list;
int nBooks;
//ptr loaners*; //will contain members who have borrowed a copy of this book
}Library;

void getBook(Book*);
void addBook(Library*);
void displayBook(Book*);
void readBooks(Library*);
void readBook(Book*,int);
void displayBooks(Library*);
void saveBook(Book*);
void saveBooks(Library*);

typedef struct {
char title[100];
char author[50];
char code[7];
char theme[3];
int nCopies;
int nAvailableCopies;
//ptr loaners*; //will contain members who have borrowed a copy of this book

}Book;

void addBook(Book*);
void displayBook(Book*);
Book* readBooks(Book *listOfBook);
void readBook(Book* book,int index);
void displayBooks(Book *listOfBook,int nBooks);
void saveBook(Book* book);
void saveBooks(Book *listOfBook,int nBooks);

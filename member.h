#ifndef MEMBER_H_INCLUDED
#define MEMBER_H_INCLUDED

#include "book.h"

typedef struct
{
  int day;
  int month;
  int year;
}Date;

typedef struct
{
  Date borrow_date;
  char memberfName[100];
  char memberlName[100];
  char bookCode[7];
}Borrow;

typedef struct
{
  char fName[100];
  char lName[100];
  char mAddress[100];
  char eMail[100];
  char function[100];
  Borrow listborrowed[3];
  int loan;
  int sanction;
}Member;

typedef struct
{
  Borrow* list;
  int nBorrowed;
}ListOfLoans;

typedef struct
{
  Member* list;
  int nMembers;
}Community;

void getDate(Date*);

void verifMember(Community*);
void addMember(Community*);
void getMember(Member*);
void displayMember(Member*);
void saveMember(Member*);
void saveMembers(Community*);
void readMember(Member*,int);
void readMembers(Community*);
void displayMembers(Community*);

void addLoan(Library*,Community*, ListOfLoans*,ListOfLoans*);
void addBorrow(ListOfLoans*,Date,Member*,Book*);
void finishLoan(Library*,Community*, ListOfLoans*,ListOfLoans*);
void saveLoans(ListOfLoans*,ListOfLoans*);
void saveActiveLoan(Borrow*);
void saveTotalLoan(Borrow*);
void readLoans(ListOfLoans*,ListOfLoans*);
void readActiveLoan(Borrow*,int);
void readTotalLoan(Borrow*,int);

#endif

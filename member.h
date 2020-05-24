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
  Date return_date;
  char memberfName[100];
  char memberlName[100];
  Book book;
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
  Member* list;
  int nMembers;
}Community;

typedef struct
{
  Borrow* list;
  int nBorrowed;
}ListOfLoans;




void verifMember(Community*);
void addMember(Community*);
void getMember(Member*);
void addLoan(Member*, ListOfLoans*);
void finishLoan(Library*, Member*, ListOfLoans*);
void displayMember(Member*);
void saveMember(Member*);
void saveMembers(Community*);
void readMember(Member*,int);
void readMembers(Community*);
void displayMembers(Community*);

#endif

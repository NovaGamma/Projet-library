#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"
#include "book.h"

void addBorrow(ListOfLoans* loans,Date* date,Member* member,Book* book){
  (*loans).nBorrowed++;
  (*loans).list=realloc((*loans).list,(*loans).nBorrowed*sizeof(Borrow));
  (*loans).list[(*loans).nBorrowed-1].borrow_date=(*date);
  strcpy((*loans).list[(*loans).nBorrowed-1].bookCode,(*book).code);
  strcpy((*loans).list[(*loans).nBorrowed-1].memberfName,(*member).fName);
  strcpy((*loans).list[(*loans).nBorrowed-1].memberlName,(*member).lName);
}

void addLoan(Library* library,Community* community,ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  char lName[100];
  char fName[100];
  char code[7];
  int i,j;
  int exist=0;
  int try=0;
  Date temp;
  do{
    printf("Please give the first name of the member who is taking the loan : \n");
    gets(fName);
    printf("Please give the last name of the member : \n");
    gets(lName);
    i=-1;;
    do{
      i++;
      if(strcmp((*community).list[i].fName,fName)==0 && strcmp((*community).list[i].lName,lName)==0) exist=1;
    }while(i<(*community).nMembers-1 && exist==0);
    if(exist==0){
    printf("The given member doesn't exist, please try again\n");
    try++;}
    if(try==3){
      printf("You did too many tries, your maybe stuck, you've been sent back in the menu\n");
      return;
    }
  }while (exist==0);
  //here i will be the index where the member is in the community list

  if((*community).list[i].loan >= 0 && (*community).list[i].loan < 3) //here we check that the member still has a free space for a loan
  {//and we will ask for the book to check if it exist
    exist=0;
    try=0;
    do{
    printf("Please give the code of the book : \n");
    gets(code);
    j=-1;
    do{
      j++;
      if(strcmp((*library).list[j].code,code)==0) exist=1;
    }while(i<(*library).nBooks-1 && exist==0);
    if(exist==0){
    printf("The given code doesn't correspond to any book in the library, please try again\n");
    try++;}
    if(try==3){
      printf("You did too many tries, your maybe stuck, you've been sent back in the menu\n");
      return;
    }
  }while(exist==0);
  if((*library).list[j].nAvailableCopies==0){
    printf("The book doesn't have any copies left, you'll be sent back to the menu");
    return;
  }
  //if we arrive were, it means that the member exist and the book exist
    getDate(&temp);
    addBorrow(activeLoans,&temp,&((*community).list[i]),&((*library).list[j]));
    addBorrow(totalLoans,&temp,&((*community).list[i]),&((*library).list[j]));
    displayLoans(activeLoans);
    //add the borrow directly for the member
    (*community).list[i].listborrowed[(*community).list[i].loan].borrow_date=temp;
    strcpy((*community).list[i].listborrowed[(*community).list[i].loan].bookCode,(*library).list[j].code);
    (*community).list[i].loan++;
    (*library).list[j].nAvailableCopies--;
  }
  else
  {
    printf("You can't borrow a book because you have already borrowed 3 books at the same time.");
  }
}

void finishLoan(Library* library,Community* community,ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  int index=-1;
  int exist=0;
  int try=0;
  Library bookFound;
  bookFound.list=(Book*)malloc(sizeof(Book));
  bookFound.nBooks=0;
  char code[7];
  char lName[100];
  char fName[100];
  int i,number;
  Date date;
  do{
    printf("Please give the first name of the member who is retrieving the loan : \n");
    gets(fName);
    printf("Please give the last name of the member : \n");
    gets(lName);
    i=-1;;
    do{
      i++;
      if(strcmp((*community).list[i].fName,fName)==0 && strcmp((*community).list[i].lName,lName)==0) exist=1;
    }while(i<(*community).nMembers-1 && exist==0);
    if(exist==0){
    printf("The given member doesn't exist, please try again\n");
    try++;}
    if(try==3){
      printf("You did too many tries, your maybe stuck, you've been sent back in the menu\n");
      return;
    }
  }while (exist==0);
  if((*community).list[i].loan==0){
    printf("this member currently doesn't have any loan, you'll be sent back to the menu\n");
    return;
  }

  for(int j=0;j<(*community).list[i].loan;j++){
    printf("%d)  %s  borrowed on the %d/%d/%d\n",j+1,(*community).list[i].listborrowed[j].bookCode,(*community).list[i].listborrowed[j].borrow_date.day,(*community).list[i].listborrowed[j].borrow_date.month,(*community).list[i].listborrowed[j].borrow_date.year);
  }
  do{
  printf("Please choose the book that is being returned :");
  scanf("%d",&number);
}while(number<0 || number>(*community).list[i].loan);
  strcpy(code,(*community).list[i].listborrowed[number-1].bookCode);// we copy the code of the book which is being returned
  do
  {
    index++;
  } while((index<=(*activeLoans).nBorrowed-1) && strcmp((*activeLoans).list[index].bookCode,code)!=0);
  if (index!=(*activeLoans).nBorrowed-1)
  {
    Borrow temp;
    temp=(*activeLoans).list[index];
    (*activeLoans).list[index]=(*activeLoans).list[(*activeLoans).nBorrowed-1];
    (*activeLoans).list[(*activeLoans).nBorrowed-1]=temp;
  }
  (*activeLoans).nBorrowed--;
  (*activeLoans).list=realloc((*activeLoans).list,(*activeLoans).nBorrowed*sizeof(Borrow));
  getDate(&date);
  Date temp=(*community).list[i].listborrowed[number].borrow_date;
  if((date.day > (temp.day +15)) || (date.month > (temp.month +1)) || (date.year > (temp.year +1)) || ((date.month > temp.month) && ((30 - date.day +temp.day) > 15)) || ((date.year > temp.year) && (date.month > 1)) || ((date.year > temp.year) && ((31 - date.day +temp.day) > 15))) {
    (*community).list[i].sanction++;
    printf("You are too late from: \n");
    printf("%d year(s)", (date.year - temp.year));
    printf("%d month(s)", (date.month - temp.month -1));
    printf("%d day(s)", (15 - temp.day + date.day));
  }
  (*community).list[i].loan --;
  free(bookFound.list);
}

void saveLoans(ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  FILE *loans;
  FILE *loans2;
  printf("Saving the loans\n");
  loans=fopen("db-Loan.txt","w");
  fprintf(loans,"%d\n",(*activeLoans).nBorrowed);
  fclose(loans);
  for(int i=0;i<(*activeLoans).nBorrowed;i++){
    printf("loans number : %d\n",i);
    saveActiveLoan(&((*activeLoans).list[i]));
  }
  loans2=fopen("db-TotalLoan.txt","w");
  fprintf(loans2,"%d\n",(*totalLoans).nBorrowed);
  fclose(loans2);
  for(int i=0;i<(*totalLoans).nBorrowed;i++){
    printf("loans number : %d\n",i);
    saveTotalLoan(&((*totalLoans).list[i]));
  }
}

void saveActiveLoan(Borrow* loan){
  FILE *loans;
  loans=fopen("db-Loan.txt","a");
  fprintf(loans,"%s/%s/%s/%d/%d/%d\n",(*loan).memberfName,(*loan).memberlName,(*loan).bookCode,(*loan).borrow_date.day,(*loan).borrow_date.month,(*loan).borrow_date.year);
  fclose(loans);
}

void saveTotalLoan(Borrow* loan){
  FILE *loans;
  loans=fopen("db-TotalLoan.txt","a");
  fprintf(loans,"%s/%s/%s/%d/%d/%d\n",(*loan).memberfName,(*loan).memberlName,(*loan).bookCode,(*loan).borrow_date.day,(*loan).borrow_date.month,(*loan).borrow_date.year);
  fclose(loans);
}

void readLoans(ListOfLoans* activeLoans, ListOfLoans* totalLoans){
  FILE *loans;
  int i=0;
  printf("Loadind loans...\n");
  loans=fopen("db-Loan.txt","r");
  fscanf(loans,"%d\n",&(*activeLoans).nBorrowed);
  fclose(loans);
  (*activeLoans).list=(Borrow*)malloc((*activeLoans).nBorrowed*sizeof(Borrow));
  for(int i=0;i<(*activeLoans).nBorrowed;i++){
    readActiveLoan(&((*activeLoans).list[i]),i);
  }
  loans=fopen("db-TotalLoan.txt","r");
  fscanf(loans,"%d\n",&(*totalLoans).nBorrowed);
  fclose(loans);
  (*totalLoans).list=(Borrow*)malloc((*totalLoans).nBorrowed*sizeof(Borrow));
  for(i=0;i<(*totalLoans).nBorrowed;i++){
    readTotalLoan(&((*totalLoans).list[i]),i);
  }
  printf("Finished loading loans %d loaded\n",i);

}
void readActiveLoan(Borrow* loan,int index){
  FILE *loans;
  char test[100];
  loans=fopen("db-Loan.txt","r");
  for(int i=0;i<=index;i++)
    fgets(test,100,loans);
  fscanf(loans,"%[^/]/%[^/]/%[^/]/%d/%d/%d\n",&(*loan).memberfName,&(*loan).memberlName,&(*loan).bookCode,&(*loan).borrow_date.day,&(*loan).borrow_date.month,&(*loan).borrow_date.year);
  fclose(loans);
}

void readTotalLoan(Borrow* loan,int index){
  FILE *loans;
  char test[100];
  loans=fopen("db-TotalLoan.txt","r");
  for(int i=0;i<=index;i++)
    fgets(test,100,loans);
  fscanf(loans,"%[^/]/%[^/]/%[^/]/%d/%d/%d\n",&(*loan).memberfName,&(*loan).memberlName,&(*loan).bookCode,&(*loan).borrow_date.day,&(*loan).borrow_date.month,&(*loan).borrow_date.year);
  fclose(loans);
}

void displayLoans(ListOfLoans* activeLoans){
  int i;
  for(i=0;i<(*activeLoans).nBorrowed;i++){
    printf("%s Borrowed by %s %s the %d/%d/%d\n",(*activeLoans).list[i].bookCode,(*activeLoans).list[i].memberfName,(*activeLoans).list[i].memberlName,(*activeLoans).list[i].borrow_date.day,(*activeLoans).list[i].borrow_date.month,(*activeLoans).list[i].borrow_date.year);
  }
}

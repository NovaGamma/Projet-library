#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"
#include "book.h"

void addBorrow(ListOfLoans* list,Date* date,Member* member,Book* book){
  (*list).nBorrowed++;
  realloc((*list).list,(*list).nBorrowed*sizeof(Borrow));
  (*list).borrow_date=date;
  strcpy((*list).bookCode,(*book).code);
  strcpy((*list).memberfName,(*member).fName);
  strcpy((*list).memberlName,(*member).lName);
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
      if((*community).list[i].fName==fName && (*community).list[i].lName==lName) exist=1;
    }while(i<(*community).nMembers && exist==0);
    printf("The given member doesn't exist, please try again\n");
    try++;
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
    printf("Please give the code of the book : \n")
    gets(code);
    j=-1;
    do{
      j++;
      if((*library).list[i].code==code) exist=1;
    }while(i<(*library).nBooks && exist==0);
    printf("The given code doesn't correspond to any book in the library, please try again\n");
    try++;
    if(try==3){
      printf("You did too many tries, your maybe stuck, you've been sent back in the menu\n");
      return;
    }
  }while(exist==0);
  //if we arrive were, it means that the member exist and the book exist
    getDate(temp);
    addBorrow(activeLoans,&temp,&((*community).list[i]),&((*library).list[j]));
    addBorrow(totalLoans,&temp,&((*community).list[i]),&((*library).list[j]));

    //add the borrow directly for the member
    scanf("%d/%d/%d",&(*member).listborrowed[(*member).loan].borrow_date.day,&(*member).listborrowed[(*member).loan].borrow_date.month,&(*member).listborrowed[(*member).loan].borrow_date.year);
    (*member).loan ++;
  }
  else
  {
    printf("You can't borrow a book because you have already borrowed 3 books at the same time.");
  }
}

void finishLoan(Library* library,Community* community,ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  int index=0;
  Library bookFound;
  bookFound.list=(Book*)malloc(sizeof(Book));
  bookFound.nBooks=0;
  char code[7];
  printf("Please give the code of the book (in form CAR-001) : ");
  gets(code);
  search(library,&bookFound,1,code);
  do
  {
    index++;
  } while((index<(*listOfLoans).nBorrowed) && ((*listOfLoans).list[index].bookCode!=bookFound.list[0].code));
  if (index!=(*listOfLoans).nBorrowed-1)
  {
    Borrow temp;
    temp=(*listOfLoans).list[index];
    (*listOfLoans).list[index]=(*listOfLoans).list[(*listOfLoans).nBorrowed-1];
    (*listOfLoans).list[(*listOfLoans).nBorrowed-1]=temp;
  }
  (*listOfLoans).nBorrowed--;
  realloc((*listOfLoans).list,(*listOfLoans).nBorrowed*sizeof(Borrow));

  printf("give the date of today day/month/year, please.\n");
  scanf("%d/%d/%d",&(*member).listborrowed[(*member).loan].return_date.day,&(*member).listborrowed[(*member).loan].return_date.month,&(*member).listborrowed[(*member).loan].return_date.year);
  int numberOfDays;
  //Il faut ici calculer le nombre de jour qui se sont écoulés entre la date d'emprunt et la date de retour et si ce nombre est supérieur à 15 jours alors il y a sanction
  if(numberOfDays > 15)
  {
    (*member).sanction++;
    printf("You return this book %d days too late.\nACHTUNG you were late %d time(s)", numberOfDays-15, (*member).sanction);
  }

  (*member).loan --;
  free(bookFound.list);
}

void saveLoans(ListOfLoans* activeLoans,ListOfLoans* totalLoans){
  FILE *loans;
  loans=fopen("db-Loan.txt","w");
  fprintf(loans,"%d\n",(*activeLoans).nBorrowed);
  fclose(loans);
  (*activeLoans).list=(Borrow*)malloc((*activeLoans).nBorrowed*sizeof(Borrow));
  for(int i=0;i<(*activeLoans).nBorrowed;i++){
    saveActiveLoan(&((*activeLoans).list[i]));
  }
  loans=fopen("db-TotalLoan.txt","w");
  fprintf(loans,"%d\n",(*totalLoans).nBorrowed);
  fclose(loans);
  (*totalLoans).list=(Borrow*)malloc((*totalLoans).nBorrowed*sizeof(Borrow));
  for(int i=0;i<(*totalLoans).nBorrowed;i++){
    saveTotalLoan(&((*totalLoans).list[i]));
  }
}

void saveActiveLoan(Borrow* loan){
  FILE *loans;
  loans=fopen("db-Loan.txt","a");
  fprintf(loans,"%d/%d/%d/%s/%s/%s\n",(*loan).borrow_date.day,(*loan).borrow_date.month,(*loan).borrow_date.year,(*loan).memberfName,(*loan).memberlName,(*loan).bookCode);
  fclose(loans);
}

void saveTotalLoan(Borrow* loan){
  FILE *loans;
  loans=fopen("db-TotalLoan.txt","a");
  fprintf(loans,"%d/%d/%d/%s/%s/%s\n",(*loan).borrow_date.day,(*loan).borrow_date.month,(*loan).borrow_date.year,(*loan).memberfName,(*loan).memberlName,(*loan).bookCode);
  fclose(loans);
}

void readLoans(ListOfLoans* activeLoans, ListOfLoans* totalLoans){
  FILE *loans;
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
  for(int i=0;i<(*totalLoans).nBorrowed;i++){
    readTotalLoan(&((*totalLoans).list[i]),i);
  }


}
void readActiveLoan(Borrow* loan,int index){
  FILE *loans;
  char test[100];
  loans=fopen("db-Loan.txt","r");
  for(int i=0;i<=index;i++)
    fgets(test,100,loans);
  fscanf(loans,"%d/%d/%d/%[^/]/%[^/]/%[^/]\n",&(*loan).borrow_date.day,&(*loan).borrow_date.month,&(*loan).borrow_date.year,&(*loan).memberfName,&(*loan).memberlName,&(*loan).bookCode);
  fclose(loans);
}

void readTotalLoan(Borrow* loan,int index){
  FILE *loans;
  char test[100];
  loans=fopen("db-TotalLoan.txt","r");
  for(int i=0;i<=index;i++)
    fgets(test,100,loans);
  fscanf(loans,"%d/%d/%d/%[^/]/%[^/]/%[^/]\n",&(*loan).borrow_date.day,&(*loan).borrow_date.month,&(*loan).borrow_date.year,&(*loan).memberfName,&(*loan).memberlName,&(*loan).bookCode);
  fclose(loans);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"
#include "book.h"

void addMember(Community* community)
{
  int i=0;
  int alreadyExists = 0;
  char firstName[100];
  char lastName[100];
  printf("\nPlease give your first name (max 100 characters) : ");
  scanf("%s", firstName);
  while(firstName[i]!='\n' && i<100){
    i++;}
  firstName[i]=' ';
  printf("\nPlease give your last name  (max 100 characters) : ");
  scanf("%s", lastName);
  i=0;
  while(lastName[i]!='\n' && i<100){
    i++;}
  lastName[i]=' ';
  for(i=0; i<(*community).nMembers;i++)
  {
    if ((firstName == (*community).list[i].fName) && (lastName == (*community).list[i].lName))
    {
      alreadyExists = 1;
    }
  }
  if(alreadyExists == 1)
  {
    printf("%s %s already exists as a member in the library", firstName, lastName);
  }
  else
  {
    (*community).nMembers++;
    realloc((*community).list,((*community).nMembers)*sizeof(Member));
    strcpy((*community).list[((*community).nMembers-1)].fName,firstName);
    strcpy((*community).list[((*community).nMembers-1)].lName,lastName);
    getMember(&((*community).list[(*community).nMembers-1]));
    //sortListOfMembers(community);
  }
  printf("Then");
}


void getMember(Member* member)
{
  int i;
  while ((getchar()) != '\n');
  printf("\nPlease give your mailing address  (max 100 characters) : ");
  fgets((*member).mAddress,sizeof((*member).mAddress),stdin);
  i=0;
  while(((*member).mAddress)[i]!='\n' && i<100){
    i++;}
  ((*member).mAddress)[i]=' ';
  printf("\nPlease give your e-mail address (max 100 characters) : ");
  fgets((*member).eMail,sizeof((*member).eMail),stdin);
  i=0;
  while(((*member).eMail)[i]!='\n' && i<100){
    i++;}
  ((*member).eMail)[i]=' ';
  printf("\nPlease give your member function (max 100 characters) : ");
  fgets((*member).function,sizeof((*member).function),stdin);
  i=0;
  while(((*member).function)[i]!='\n' && i<100){
    i++;}
  ((*member).function)[i]=' ';
  (*member).loan = 0;
  (*member).sanction = 0;
  printf("Finished !");
}


void addLoan(Member* member, ListOfLoans* listOfLoans)
{
  if((*member).loan >= 0 && (*member).loan < 3)
  {
    (*listOfLoans).nBorrowed++;
    printf("give the date of today day/month/year, please.\n");
    scanf("%d/%d/%d",&(*member).listborrowed[(*member).loan].return_date.day,&(*member).listborrowed[(*member).loan].return_date.month,&(*member).listborrowed[(*member).loan].return_date.year);
    (*member).loan ++;
  }
  else
  {
    printf("You can't borrow a book because you have already borrowed 3 books at the same time.");
  }
}

void finishLoan(Library* library, Member* member, ListOfLoans* listOfLoans)
{
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
  } while((index<(*listOfLoans).nBorrowed) && ((*listOfLoans).list[index].book.code!=bookFound.list[0].code));
  if (index!=(*listOfLoans).nBorrowed-1)
  {
    Book temp;
    temp=(*listOfLoans).list[index].book;
    (*listOfLoans).list[index].book=(*listOfLoans).list[(*listOfLoans).nBorrowed-1].book;
    (*listOfLoans).list[(*listOfLoans).nBorrowed-1].book=temp;
  }
  (*listOfLoans).nBorrowed--;
  realloc((*listOfLoans).list,(*listOfLoans).nBorrowed*sizeof(Book));

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


void displayMember(Member* member)
{
  printf("\nFirst name : %s\nLast name : %s\nMailing address : %s\nE-mail : %s\nMember function : %s\n",member->fName,member->lName,member->mAddress,member->eMail,member->function);
  if((*member).loan > 0)
  {
    printf("First loan: %s  borrowed on the %d/%d/%d\n",member-> listborrowed[0].book.code,member-> listborrowed[0].return_date.day,member-> listborrowed[0].return_date.month,member-> listborrowed[0].return_date.year);
    if((*member).loan > 1)
    {
      printf("Second loan: %s  borrowed on the %d/%d/%d\n",member-> listborrowed[1].book.code,member-> listborrowed[1].return_date.day,member-> listborrowed[1].return_date.month,member-> listborrowed[1].return_date.year);
      if((*member).loan > 2)
      {
        printf("Second loan: %s  borrowed on the %d/%d/%d\n",member-> listborrowed[2].book.code,member-> listborrowed[2].return_date.day,member-> listborrowed[2].return_date.month,member-> listborrowed[2].return_date.year);
      }
    }
  }
}


void saveMember(Member* member)
{
  FILE *members;
  members=fopen("members2.txt","a");
  fprintf(members,"%s/%s/%s/%s/%s/%s/%d/%d/%d/%s/%d/%d/%d/%s/%d/%d/%d\n",member->fName,member->lName,member->mAddress,member->eMail,member->function,member-> listborrowed[0].book.code,member-> listborrowed[0].return_date.day,member-> listborrowed[0].return_date.month,member-> listborrowed[0].return_date.year,member-> listborrowed[1].book.code,member-> listborrowed[1].return_date.day,member-> listborrowed[1].return_date.month,member-> listborrowed[1].return_date.year,member-> listborrowed[2].book.code,member-> listborrowed[2].return_date.day,member-> listborrowed[2].return_date.month,member-> listborrowed[2].return_date.year);
  fclose(members);
}


void saveMembers(Community* community)
{
  FILE *members;
  members=fopen("members2.txt","w");
  fprintf(members,"%d\n",(*community).nMembers);
  fclose(members);
  for(int i=0;i<(*community).nMembers;i++)
    saveMember(&(*community).list[i]);
}


void readMember(Member* member,int index)
{
  FILE *members;
  char test[100];
  members=fopen("members2.txt","r");
  for(int i=0;i<=index;i++)
    fgets(test,100,members);
  fscanf(members,"%[^/]/%[^/]/%[^/]/%[^/]/%[^/]\n",&member->fName,&member->lName,&member->mAddress,&member->eMail,&member->function,&member-> listborrowed[0].book.code,&member-> listborrowed[0].return_date.day,&member-> listborrowed[0].return_date.month,&member-> listborrowed[0].return_date.year,&member-> listborrowed[1].book.code,&member-> listborrowed[1].return_date.day,&member-> listborrowed[1].return_date.month,&member-> listborrowed[1].return_date.year,&member-> listborrowed[2].book.code,&member-> listborrowed[2].return_date.day,&member-> listborrowed[2].return_date.month,&member-> listborrowed[2].return_date.year);
  //fscanf(books,"%[^/]/%[^/]/%[^/]/%d/%d\n",&title,&author,&code,&nAvailableCopies,&nCopies);
  //printf("\nTitle : %s\nAuthor : %s\nCode : %s\nNumber of copies availables : %d\nTotal number of copies : %d\n",title,author,code,nAvailableCopies,nCopies);
  fclose(members);
}


void readMembers(Community* community)
{
  FILE *members;
  members=fopen("members2.txt","r");
  fscanf(members,"%d\n",&(*community).nMembers);
  fclose(members);
  (*community).list=(Member*)malloc((*community).nMembers*sizeof(Member));
  for(int i=0;i<(*community).nMembers;i++){
    readMember(&((*community).list[i]),i);
  }
}

void sortListOfMembers(Community* community){
  Member temp;
  printf("%d members in the community\n",(*community).nMembers);
  for(int i=0;i<(*community).nMembers;i++)
  {
    for(int j=0;j<(*community).nMembers;j++)
    {
      if ((*community).list[j].lName > (*community).list[j+1].lName)
      {
          temp = (*community).list[j+1];
          (*community).list[j+1] = (*community).list[j];
          (*community).list[j] = temp;
      }
      else
        if ((*community).list[j].lName  == (*community).list[j+1].lName)
      {
        if ((*community).list[j].fName > (*community).list[j+1].fName)
        {
          temp = (*community).list[j+1];
          (*community).list[j+1] = (*community).list[j];
          (*community).list[j] = temp;
        }
      }
    }
  }
}

void displayMembers(Community* community){
  for(int k=0;k<(*community).nMembers;k++)
    displayMember(&(*community).list[k]);
}

/*
int main(){
  Member test;
  Community community;
  (*community).nMembers=2;
  readBooks(&community);
  //addBook(&test);
  //readBook(&listOfBooks[0]);
  displayMembers(&community);
  saveMembers(&community);
  return 0;
}
*/

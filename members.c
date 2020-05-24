#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"
#include "book.h"

void getDate(Date* date){
  int day;
  int month;
  int year;
  do{
  printf("Please give the date (day/month/year) :\n");
  scanf("%d/%d/%d\n");
}while(day<1 || day>31 || month<1 || month>12);
(*date).day=day;
(*date).month=month;
(*date).year=year;
}


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
}

void displayMember(Member* member)
{
  printf("\nFirst name : %s\nLast name : %s\nMailing address : %s\nE-mail : %s\nMember function : %s\n",member->fName,member->lName,member->mAddress,member->eMail,member->function);
  if((*member).loan > 0)
  {
    printf("First loan: %s  borrowed on the %d/%d/%d\n",member-> listborrowed[0].bookCode,member-> listborrowed[0].borrow_date.day,member-> listborrowed[0].borrow_date.month,member-> listborrowed[0].borrow_date.year);
    if((*member).loan > 1)
    {
      printf("Second loan: %s  borrowed on the %d/%d/%d\n",member-> listborrowed[1].bookCode,member-> listborrowed[1].borrow_date.day,member-> listborrowed[1].borrow_date.month,member-> listborrowed[1].borrow_date.year);
      if((*member).loan > 2)
      {
        printf("Second loan: %s  borrowed on the %d/%d/%d\n",member-> listborrowed[2].bookCode,member-> listborrowed[2].borrow_date.day,member-> listborrowed[2].borrow_date.month,member-> listborrowed[2].borrow_date.year);
      }
    }
  }
}


void saveMember(Member* member)
{
  FILE *members;
  members=fopen("members2.txt","a");
  fprintf(members,"%s/%s/%s/%s/%s/%s/%d/%d/%d/%s/%d/%d/%d/%s/%d/%d/%d\n",member->fName,member->lName,member->mAddress,member->eMail,member->function,member-> listborrowed[0].bookCode,member-> listborrowed[0].borrow_date.day,member-> listborrowed[0].borrow_date.month,member-> listborrowed[0].borrow_date.year,member-> listborrowed[1].bookCode,member-> listborrowed[1].borrow_date.day,member-> listborrowed[1].borrow_date.month,member-> listborrowed[1].borrow_date.year,member-> listborrowed[2].bookCode,member-> listborrowed[2].borrow_date.day,member-> listborrowed[2].borrow_date.month,member-> listborrowed[2].borrow_date.year);
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
  fscanf(members,"%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%d/%d/%d/%[^/]/%d/%d/%d/%[^/]/%d/%d/%d\n",&member->fName,&member->lName,&member->mAddress,&member->eMail,&member->function,&member-> listborrowed[0].bookCode,&member-> listborrowed[0].borrow_date.day,&member-> listborrowed[0].borrow_date.month,&member-> listborrowed[0].borrow_date.year,&member-> listborrowed[1].bookCode,&member-> listborrowed[1].borrow_date.day,&member-> listborrowed[1].borrow_date.month,&member-> listborrowed[1].borrow_date.year,&member-> listborrowed[2].bookCode,&member-> listborrowed[2].borrow_date.day,&member-> listborrowed[2].borrow_date.month,&member-> listborrowed[2].borrow_date.year);
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

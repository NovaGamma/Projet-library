#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"
#include "book.h"

void getDate(Date* date){
  int day;
  int month;
  int year;
  printf("Please give the date (day/month/year) :\n");
  scanf("%d/%d/%d",&day,&month,&year);
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
    if(strcmp((*community).list[i].fName,firstName)==0 && strcmp((*community).list[i].lName,lastName)==0)
    {
      alreadyExists = 1;
    }
  }
  if(alreadyExists == 1)
  {
    printf("%s %s already exists as a member in the library", firstName, lastName);
    return;
  }
  else
  {
    (*community).nMembers++;
    (*community).list=realloc((*community).list,((*community).nMembers)*sizeof(Member));
    strcpy((*community).list[((*community).nMembers-1)].fName,firstName);
    strcpy((*community).list[((*community).nMembers-1)].lName,lastName);
    getMember(&((*community).list[(*community).nMembers-1]));
    Date date;
    date.day=0;
    date.month=0;
    date.year=0;
    char fNameTemp[100]="None";
    char lNameTemp[100]="None";
    char tempCode[7]="AAA-000";
    for(int k=0;k<3;k++){
    (*community).list[(*community).nMembers-1].listborrowed[k].borrow_date=date;
    strcpy((*community).list[(*community).nMembers-1].listborrowed[k].memberfName,fNameTemp);
    strcpy((*community).list[(*community).nMembers-1].listborrowed[k].memberlName,lNameTemp);
    strcpy((*community).list[(*community).nMembers-1].listborrowed[k].bookCode,tempCode);
    }
    sortListOfMembers(community);

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
  members=fopen("db-Member.txt","a");
  fprintf(members,"%s/%s/%s/%s/%s/%s/%d/%d/%d/%s/%d/%d/%d/%s/%d/%d/%d/%d/%d\n",member->fName,member->lName,member->mAddress,member->eMail,member->function,member-> listborrowed[0].bookCode,member-> listborrowed[0].borrow_date.day,member-> listborrowed[0].borrow_date.month,member-> listborrowed[0].borrow_date.year,member-> listborrowed[1].bookCode,member-> listborrowed[1].borrow_date.day,member-> listborrowed[1].borrow_date.month,member-> listborrowed[1].borrow_date.year,member-> listborrowed[2].bookCode,member-> listborrowed[2].borrow_date.day,member-> listborrowed[2].borrow_date.month,member-> listborrowed[2].borrow_date.year,member -> loan,member->sanction);
  fclose(members);
}


void saveMembers(Community* community)
{
  FILE *members;
  members=fopen("db-Member.txt","w");
  fprintf(members,"%d\n",(*community).nMembers);
  fclose(members);
  for(int i=0;i<(*community).nMembers;i++)
    saveMember(&(*community).list[i]);
}


void readMember(Member* member,int index)
{
  FILE *members;
  char test[1000];
  members=fopen("db-Member.txt","r");
  for(int i=0;i<=index;i++)
    fgets(test,1000,members);
  fscanf(members,"%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%[^/]/%d/%d/%d/%[^/]/%d/%d/%d/%[^/]/%d/%d/%d/%d/%d\n",&member->fName,&member->lName,&member->mAddress,&member->eMail,&member->function,&member-> listborrowed[0].bookCode,&member-> listborrowed[0].borrow_date.day,&member-> listborrowed[0].borrow_date.month,&member-> listborrowed[0].borrow_date.year,&member-> listborrowed[1].bookCode,&member-> listborrowed[1].borrow_date.day,&member-> listborrowed[1].borrow_date.month,&member-> listborrowed[1].borrow_date.year,&member-> listborrowed[2].bookCode,&member-> listborrowed[2].borrow_date.day,&member-> listborrowed[2].borrow_date.month,&member-> listborrowed[2].borrow_date.year,&member->loan,&member->sanction);
  fclose(members);
}

void readMembers(Community* community)
{
  FILE *members;
  int i=0;
  printf("Loading Members...\n");
  members=fopen("db-Member.txt","r");
  fscanf(members,"%d\n",&(*community).nMembers);
  fclose(members);
  (*community).list=(Member*)malloc((*community).nMembers*sizeof(Member));
  for(i=0;i<(*community).nMembers;i++){
    readMember(&((*community).list[i]),i);
  }
  printf("Finished loading Members %d loaded\n",i);
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
        if (strcmp((*community).list[j].lName,(*community).list[j+1].lName)==0)
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

void deleteMember(Community* community){
  char lName[100];
  char fName[100];
  int i;
  int exist=0;
  int try=0;
  do{
    printf("Please give the first name of the member that you want to delete : \n");
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
  if (i!=(*community).nMembers-1){
    Member temp;
    temp=(*community).list[i];
    (*community).list[i]=(*community).list[(*community).nMembers-1];
    (*community).list[(*community).nMembers-1]=temp;
  }
  (*community).nMembers--;
  (*community).list=realloc((*community).list,(*community).nMembers*sizeof(Member));

}

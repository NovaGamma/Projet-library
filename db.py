import os

class Book():
    def __init__(self,title,author,code,theme,nBooksAvailable,nBooksTotal):
        self.title=title
        self.author=author
        self.code=code
        self.theme=theme
        self.nBooksAvailable=nBooksAvailable
        self.nBooksTotal=nBooksTotal


list=[]
with open("db-Book.txt",'w') as FILE:
    FILE.write('308\n')

with open("lives_generer.txt",'r') as File:
    for line in File:
        print(line)
        print(len(list))
        temp=line.split('/')
        title=temp[1]
        author=temp[2]
        code=temp[0]
        temp2=code.split('-')
        theme=temp2[0]
        nBooks=temp[3].split(' ')
        nBooksTotal=nBooks[0]
        nBooksAvailable=nBooks[1].rstrip('\n')
        book=Book(title,author,code,theme,nBooksAvailable,nBooksTotal)
        with open("db-Book.txt",'a') as FILE:
            FILE.write(book.title+'/'+book.author+'/'+book.code+'/'+book.nBooksAvailable+'/'+book.theme+'/'+book.nBooksTotal+'\n')

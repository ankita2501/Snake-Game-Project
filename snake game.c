#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
struct snake
{
int x,y;
char val;
struct snake *next;
};
struct snake *head=NULL;

struct food
{
int x,y;
char val;
};
struct snake* create(int x1,int y1,char n)
{
    struct snake *ptr=(struct snake*)malloc(sizeof(struct snake)*1);
    ptr->x=x1;
    ptr->y=y1;
    ptr->val=n;
    ptr->next=NULL;
    return ptr;
}
void insertTail(int x1,int y1,char a)
{
    struct snake * t,*temp;
    temp=create(x1,y1,a);
    if(head==NULL)
        head=temp;
    else
    {
      t=head;
    while(t->next!=NULL)
        t=t->next;
        t->next=temp;

    }
}

void show_on_board(char b[30][60],struct food *f,struct food *p)
{
  struct snake *t=head;
while(t!=NULL)
{
    b[t->x][t->y]=t->val;
  t=t->next;
}

b[f->x][f->y]=f->val;

b[p->x][p->y]=p->val;
}
void show(char b[30][60],struct food *f,struct food *p)
{

int i,j;

show_on_board(b,f,p);

    for(i=0;i<30;i++)
   {
       for(j=0;j<60;j++)
    printf("%c",b[i][j]);
   printf("\n");
   }
}
void recur(struct snake *t,int m, char board[30][60])
{
if(t->next==NULL)
{
    if(m==1)
    {insertTail(t->x,t->y,'T');
   if(t->val!='H')
    t->val='#';
    }
    else
 board[t->x][t->y]=' ';
return;
}
recur(t->next,m,board);
t->next->x=t->x;
t->next->y=t->y;
}
void move(int x1,int y1,int m,char board[30][60])
{struct snake *t;

recur(head,m,board);
 head->x=x1;
    head->y=y1;

}
void changePos(struct food *f)
{int x,y;
struct snake *t;
t=head;
while(1)
{
   x=rand()%29;
y=rand()%59;
if(x!=0 && y!=0)
{
    while(t!=NULL)
    {
      if(t->x==x && t->y==y)
         break;
        t=t->next;
    }
    if(t==NULL)
    {f->x=x;
        f->y=y;
        return;
    }
}
}
}

int deletetail(char brd[30][60])
{struct snake *t=head;

if(t->next==NULL)
    {
        head=NULL;
        free(t);

        return 1;
    }
    else
    {

    while( t->next->next!=NULL)
{
    t=t->next;
}
brd[t->next->x][t->next->y]=' ';
if(t->val!='H')
    t->val='T';

      free(t->next);

    t->next=NULL;

return 0;
}

}
struct food *createSeed(int x,int y,char a)
{
    struct food *f;
    f=(struct food*)malloc(sizeof(struct food)*1);
    f->x=x;
    f->y=y;
    f->val=a;

    return f;
}
void loadGame(struct food **f1,struct food **p1)
{
    struct food *f,*p;
   int x1,y1,n;
   char a;
   f=createSeed(3,3,'O');
*f1=f;

p=createSeed(15,8,'X');
*p1=p;

    n=3;
x1=9;
y1=6;
a='H';
insertTail(x1,y1,a);
a='#';
while(n)
{
    y1=y1+1;
  insertTail(x1,y1,a);
    n--;
}
a='T';
y1=y1+1;
insertTail(x1,y1,a);
}
void writeObject(FILE *fptr,struct food *f,char sc)
{
  if(sc=='F' || sc=='P')
    {fputc(sc,fptr);
        fprintf(fptr,"%d,%d,%c$",f->x,f->y,f->val);
    }
else
{
    struct snake *s=head;
    fputc(sc,fptr);
       while(s->next!=NULL)
    {
         fprintf(fptr,"%d,%d,%c*",s->x,s->y,s->val);
        s=s->next;
    }
     fprintf(fptr,"%d,%d,%c",s->x,s->y,s->val);
    fputc('$',fptr);
}

}
void saveToFile(struct food *f1,struct food *p1)
{
    FILE *fptr;

    fptr=fopen("game.txt","w");
writeObject(fptr,f1,'F');
writeObject(fptr,p1,'P');
writeObject(fptr,f1,'S');
fclose(fptr);
printf("\n\nyour game has been saved!!!!");

}


int readFromFile(struct food **f1,struct food **p1)
{FILE *fptr;
struct snake *s=head;
char ch,c;
int a,b;
fptr=fopen("game.txt","r");
if(fptr==NULL)
    {
        printf("you have no saved game\n");
    return 1;
    }
else
    {

while((ch=fgetc(fptr))!=EOF)
{
switch(ch)
{
   case 'F':
    {
        fscanf(fptr,"%d,%d,%c$",&a,&b,&c);
  *f1=createSeed(a,b,c);
    break;
    }
case 'P':
 {fscanf(fptr,"%d,%d,%c$",&a,&b,&c);
  *p1=createSeed(a,b,c);
    break;
 }
case 'S':
{
  do
  {
    fscanf(fptr,"%d,%d,%c",&a,&b,&c);
    insertTail(a,b,c);

}while(fgetc(fptr)!='$');

ch=fgetc(fptr);
break;
}
}

}
fclose(fptr);

}
return 0;
}


int movement(struct food *f1,struct food *p1,char board[30][60])
{
   char a,b;
int x1,y1,m;
   while(1)
{
    fflush(stdin);
a=getche();
if(a=='e')
{system("cls");
    printf("are u sure u want to exit game???\n");
    b=getch();
    if(b=='y')
        return 0;
        else
        {
            system("cls");
            show(board,f1,p1);
        }
}


x1=head->x;
y1=head->y;
m=0;
while(!kbhit())
{
switch(a)
{
  case 75:
{y1=y1-1;

        if(y1==0)
            y1=58;


break;
}
case 77:
{
    y1=y1+1;

        if(y1==59)
            y1=1;


break;
}
case 72:
{x1=x1-1;

        if(x1==0)
            x1=28;

break;
}
case 80:
{x1=x1+1;

        if(x1==29)
            x1=1;

break;
}
}
if(shouldMove(x1,y1)) //new pos clash with its one previous part || press wrong key in both condition snake dont move
  {
m=0;
      if(isEatSeed(x1,y1,f1)) //food
            {
                changePos(f1);

                m=1; //indicate to insert
            }
            else
                if(isEatSeed(x1,y1,p1)) //poison
            {
                changePos(p1);
                if(deletetail(board)==1)
                        return 1;
            }
            else
            if(isSelfCollision(x1,y1))
            {
                return 1;
            }
            move(x1,y1,m,board);
  }
else
    break;
system("cls");
show(board,f1,p1);
}

}

}
isEatSeed(int x1,int y1,struct food *f1)
{
    if(x1==f1->x && y1==f1->y)
        return 1;
    else
        return 0;
}
int isSelfCollision(int x,int y)
{
    struct snake *s=head->next;
    while(s!=NULL)
    {
        if(x==s->x && y==s->y)
            return 1;
        s=s->next;
    }
    return 0;

}
int shouldMove(int x1,int y1)
{
    if(head->next==NULL)
        return 1;
if(x1==head->x && y1==head->y)
return 0;
else
    if(head->next->x==x1 && head->next->y==y1)
        return 0;
    else
        return 1;
}







//***********************
int main()
{
printf("\t\t\t\t\t\tWelcome to Snake Game\n\n");
printf("Instructions-\n\n");
printf("1.Use arrow keys to move your snake.\n\n");
printf("2.Eat the 'O' that is food and do not eat 'X' that is poision.\n\n");
printf("3.Press 'e' to exit.\n\n");
printf("4.Save the game to resume the game next time.\n\n");

    struct food *f1,*p1;
char a,c;
struct snake *s1;

int choice,i,j;
char board[30][60]={' '};

 for(i=0;i<60;i++)
      board[0][i]='.';
    for(i=0;i<30;i++)
        board[i][59]='.';
        for(i=0;i<60;i++)
            board[29][i]='.';
            for(i=0;i<30;i++)
             board[i][0]='.';

printf("1. START NEW GAME\n\n2. RESUME\n");
scanf("%d",&choice);
if(choice ==1)
{
    remove("game.txt");

    loadGame(&f1,&p1);

}
else
{
    if(readFromFile(&f1,&p1)==1)
return 0;
}
system("cls");
show(board,f1,p1);

if(movement(f1,p1,board)==1)
{
   system("cls");
   printf("game over");
   remove("game.txt");
}
else
{
   printf("whether u want to save game or not (y or n)\n");
   scanf("%c",&a);
    if(a=='y')
{
saveToFile(f1,p1);
}
else
{
    printf("your all progress is erased !!!");
    remove("game.txt");
}


}

}

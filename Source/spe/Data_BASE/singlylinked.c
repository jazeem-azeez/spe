#include <stdio.h>
#include <malloc.h>
struct record
{
int num;
struct record *ptr;
};

record *first,*head,*temp,*insert;
int nu;

insert_at_begin(string msg)
{
insert=(record *)malloc(sizeof(record));
strcpy(&insert->str,msg);
insert->ptr=first;
first=insert;
}
insert_at_middle()
{
record *p;
p=first;
insert=(record *)malloc(sizeof(record));
printf("\n Insertion in the middle \n Enter Data after which you want to insert");
scanf("%d",&nu);
printf("\n Insertion in the middle \n Enter Data to be inserted");
scanf("%d",&insert->num);
while(strcmp(p->num!=nu)
 {
   p=p->ptr;
 }
   insert->ptr=p->ptr;
   p->ptr=insert;
}
insert_at_end()
{
record *p;
p=first;
insert=(record *)malloc(sizeof(record));
printf("\n Insertion in the end \n Enter Data to be inserted");
scanf("%d",&insert->num);
insert->ptr='\0';
while(p->ptr!='\0')
 {
  p=p->ptr;
 }
p->ptr=insert;
}
delete_record()
{
record *p;
printf("\n Enter data to be deleted");
scanf("%d",&nu);
insert=first;
if (nu==insert->num)
 {
  first=insert->ptr;
  free(insert);
  return;
 }
while (nu!=insert->num)
 {
  p=insert;
  insert=insert->ptr;
 }
 p->ptr=insert->ptr;
 free(insert);
}

disp()
{
int count=0;
int r=0;
int i;
int arr[10];
int k;
printf("\n record info");
temp=first;
while(temp!='\0')
{
printf("\n %d",temp->num);
count++;
temp=temp->ptr;
}
printf("\n %d",count);
r=count;
temp=first;
while(temp!='\0')
 {
  for(i=1;i<=r;i++)
   {
  arr[i]=temp->num;
  temp=temp->ptr;
 	}
 }
for(i=r;i>=1;i--)
{
printf("\n %d",arr[i]);
}
printf("\n %d",r);
}

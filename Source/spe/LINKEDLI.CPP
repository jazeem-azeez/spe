#include <malloc.h>
#include <stdio.h>
#include <conio.h>

int cnt;
class node
{
public:
int node_count;
int information;

void getinfo()
{
printf("Enter the node count and info");
node_count=cnt,information=cnt;
cnt++;
//scanf("%d %d",&node_count,&information);
}

void identify()
{
printf("node count %d,information %d",node_count,information);
}
node *nextnode;
}
*base,*pointer,*temp;

void traversal()
{
pointer =base;
	while(pointer!=NULL)
	{pointer->identify();
	pointer=pointer->nextnode;
	}

}

void newnode()
{
	if(cnt==0)
	    {	base=(node *) malloc(sizeof(node));
		base->getinfo();
		base->nextnode=NULL;
	    }

	else
	    {	if((temp =(node *) malloc(sizeof(node)))==NULL);
			printf("error in mem");
		temp->getinfo();
//		temp->nextnode=NULL;
		pointer =base->nextnode;
		while(pointer!=NULL)
		{
		pointer=pointer->nextnode;
		}
		pointer=temp;
		pointer->nextnode=NULL;
	     }
}
void close()
{
	pointer =base;
		while(pointer!=NULL)
		{
		temp=pointer;
		pointer=pointer->nextnode;
		temp->identify();
		free(temp);
		}


}

void main()
{
cnt=0;
newnode();
newnode();
newnode();
newnode();
newnode();
newnode();
traversal();
getch();
close();
getch();
}
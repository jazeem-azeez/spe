//# include <gui.h>
# include <obj.cpp>
	
time_t first, second;
class world

{
public:
	
	//attributes
	int no_obj; 
	/*
	object *obj,*next,*base;	//for linkedlist implimentation
	*/
	object obj[10];

	//operations
	int newobject();
	int deleteobj();
	int modifyobject();
	int simulate ();
	
	world()
	{ 
		//next=NULL;
		//obj=next;
		//base=obj;
	}

	~world()
	{
	  //free(obj);
	}
};

int world :: newobject()

{
	switchpage(1,1);
	no_obj++; 	
	if (no_obj>=10)
	{	dispaly_err("The maximum object limit has reached");
		return 1;
	}	
	else
		obj[no_obj].load(no_obj);
}

int world :: deleteobject()

{	int delkey=0,flag==0;

	switchpage(1,1);
	outtext("Enter the key of object");
	delkey=(int )gcin(msg);	


	for(int i=0;i<no_obj;i++)
	{
		if(obj[i].key==delkey)
			flag==1;
		if(flag==1)
			obj[i]=obj[i+1];
	}
	if (flag==1)
		no_obj--;
}
/*
int world :: newobject()

{
object *p;
p=obj;
next=(object *)malloc(sizeof(object));
next->next=NULL;
while(p->next!=NULL)
 {
  p=p->next;
 }
p->next=next;
}

int world ::deleteobj()// pos 0n

{
object *p=obj,temp*;
int key;
switchpage(1,1);
outtextxy("\n Enter Key");
key=(int )gcin(msg);
if (nu==p->num)
 {
  obj=p->ptr;
  free(p);
  return;
 }
while (key!=p->key)
 {
  temp=p;
  p=p->ptr;
 }
 temp->ptr=p->ptr;
 free(p);
}
  */

int world :: modifyobject()

{	int key;
  switchpage(1,1);
	outtext("Enter the key of object");
	key=(int )gcin(msg);	
	obj[key].p1.getdata();

}

int world :: listobjects()

{	 int xs=220,ys=180;
	for(int i=0,j=0;i<no_obj;i++)
		{
		display_icon(xs,ys,itoa(obj[i].key));
		}

}

int world :: simulate ()

{
	setcolor(GREEN);
	setbkcolor(BLACK);
	clearveiwport();  
	int i=0,j=0,k=0;
	
	for(;;)

	{   
		 //draw
		for(i=0;i<obj[i];i++)
			obj[i].show();
		//calculate the step
		first = time(NULL);
		for(i=0;i<no_obj;i++)
		{
			obj[i].calc();
		}
		//check for collision
			for(i=0;i<no_obj;i++)
		{		for(j=0;j<no_obj;j++)
		{
			collision(obj[i],obj[j]);
		}

		}

		second = time(NULL);
	
		difftime(second,first);
		}

}



//main

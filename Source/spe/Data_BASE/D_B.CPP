//Database in C
//Program created by jazeem and crew
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<dir.h>

#define MAX_NAME 80
#define MAX_CHARS 1024

struct Record_Type
{
	char name[MAX_NAME+1];
	char type;
    void *value;
    size_t maxchars;//extra for char due to the way storage is
	struct Record_Type *next;
};

typedef struct Record_Type rec;
typedef rec *link_rec;

link_rec head_rec;//head pointer
char filename[MAXPATH];//MAX_PATH_

void Main_Menu(void);
void add_rec_link(link_rec *headptr/*,tail_rec*/,char buf[],char ch,size_t maxchars);//alloc mem
void write_val(FILE *file,link_rec headptr);
void read_val(link_rec headptr,FILE *file);
size_t search_field(char fieldname[],char buf[],link_rec headptr,FILE *file,size_t rec_start,size_t num_records);
void ask_values(link_rec headptr);
void clear_list_rec(link_rec headptr);//to delete complete linked list
void show_val(link_rec headptr);


int main(void)
{
	head_rec=NULL;//initialize
	Main_Menu();
	return EXIT_SUCCESS;
}

int getint(void)
{
	char num[20];
	fgets(num,19,stdin);
	return(atoi(num));//alpha to int
}

void etc(void)//enter to continue
{
	printf("\npress any key to continue.");
getch();
}

void add_rec_link(link_rec *headptr/*,tail_rec*/,char buf[],char ch,size_t maxchars)//alloc mem
{
    link_rec tailptr;

    if (*headptr==NULL)
    {
	*headptr=(Record_Type *)malloc(sizeof(rec));
	tailptr=*headptr;
    }
    else
    {
	tailptr=*headptr;
	while(tailptr->next!=NULL)
	{
	    tailptr=tailptr->next;
	}
	tailptr->next=(Record_Type *)malloc(sizeof(rec));
	//return error & exit if null &clear list already allocated
	tailptr=tailptr->next;
    }
    if (tailptr==NULL){printf("\nMemory allocation error\n");exit(1);}
    tailptr->next=NULL;
    strcpy(tailptr->name,buf);
    tailptr->maxchars=maxchars;
    tailptr->type=ch;
    switch(ch)
    {
    case 't':
	{
	    tailptr->value=malloc(maxchars+1);
	    break;
	}
    case 'i':
	{
	    tailptr->value=malloc(sizeof(int));
	    break;
	}
    case 'r':
	{
	    tailptr->value=malloc(sizeof(double));
	    break;
	}
    }//switch

}//addlink

void clear_list_rec(link_rec headptr)
{
	link_rec currentptr;

	currentptr=headptr;
	while(headptr!=NULL)
	{
		currentptr=headptr->next;
	if (headptr->value!=NULL){free(headptr->value);headptr->value=NULL;}
		free(headptr);
		headptr=currentptr;
	}
}

void write_val(FILE *file,link_rec headptr)
{
    //link_rec tailptr=headptr;
    //link_rec headptr is pointer passed byval hence pointer value doen't change
    size_t sz;

    //tailptr=headptr;
    while (headptr!=NULL)
    {
	switch(headptr->type)
	{
	case 't':
	    {
		sz=headptr->maxchars+1;
		break;
	    }
	case 'i':
	    {
		sz=sizeof(int);
		break;
	    }
	case 'r':
	    {
		sz=sizeof(double);
		break;
	    }
	}//switch
	fwrite(headptr->value,sz,1,file);

	headptr=headptr->next;
    }//while
}//write_val

void read_val(link_rec headptr,FILE *file)
{
    size_t sz;

    while(headptr!=NULL)
    {
	switch(headptr->type)
	{
	case 't':
	    {
		sz=headptr->maxchars+1;
		break;
	    }
	case 'i':
	    {
		sz=sizeof(int);
		break;
	    }
	case 'r':
	    {
		sz=sizeof(double);
		break;
	    }
	}//switch
	fread(headptr->value,sz,1,file);

	headptr=headptr->next;
    }//while
}

void ask_values(link_rec headptr)
{
    char buf[4],tem[MAX_CHARS+4];

    while(headptr!=NULL)
    {
	switch(headptr->type)
	{
	case 't':
	    {
		strcpy(buf,"%s");
		printf("\nMaximum Character Count=%u",(headptr->maxchars));
		printf("\nEnter value for field %s, type \'%c\':",headptr->name,headptr->type);
		fgets(tem,MAX_CHARS+3,stdin);//maxchars+1?
		tem[strlen(tem)-1]='\0';
		tem[headptr->maxchars]='\0';
		fflush(stdin);
		strcpy((char *)headptr->value,tem);
//                ((char *)headptr->value)[strlen((char*)headptr->value)-1]='\0';
		break;
	    }
	case 'i':
	    {
		strcpy(buf,"%d");
	    printf("\nEnter value for field %s, type \'%c\':",headptr->name,headptr->type);
	    scanf(buf,headptr->value);fflush(stdin);
		break;
	    }
	case 'r':
	    {
		strcpy(buf,"%lf");
	    printf("\nEnter value for field %s, type \'%c\':",headptr->name,headptr->type);
	    scanf(buf,headptr->value);fflush(stdin);
		break;
	    }
	}//switch
//        printf("\nEnter value for field %s, type \'%c\':",headptr->name,headptr->type);
//        scanf(buf,headptr->value);fflush(stdin);

	headptr=headptr->next;
    }//while
}//ask_values

void show_val(link_rec headptr)
{
    char buf[4];

    while(headptr!=NULL)
    {
	printf("\nvalue for field %s, type \'%c\' is :",headptr->name,headptr->type);
	switch(headptr->type)
	{
	case 't':
	    {
		strcpy(buf,"%s");
	printf(buf,((char *)headptr->value));
		break;
	    }
	case 'i':
	    {
		strcpy(buf,"%d");
	printf(buf,*((int *)headptr->value));
		break;
	    }
	case 'r':
            {
                strcpy(buf,"%lf");
        printf(buf,*((double *)headptr->value));
                break;
            }
        }//switch
printf("\n");
        headptr=headptr->next;
    }//while
}

size_t search_field(char fieldname[],char buf[],link_rec headptr,FILE *file,size_t rec_start,size_t num_records)
{
    int i;
    double d;
    int done=0;
    link_rec temp;
    char ch;
    size_t loop;

    temp=headptr;

    //search for matching fieldname
    if (headptr==NULL) return 0;
    while((headptr!=NULL)&&(strcmp(fieldname,headptr->name)!=0))//error fixed
    {
        headptr=headptr->next;
    }//while
    if (headptr==NULL) return 0;
    fseek(file,rec_start,SEEK_SET);
    for (loop=1;loop<=num_records;loop++)
    {
     read_val(temp,file);
    switch (headptr->type)
    {
        case 't':
	    {
                if(strcmp(buf,(char *)headptr->value)==0)done=1;

                break;
            }
        case 'i':
            {
                i=atoi(buf);
                if (i==*((int *)headptr->value)) done=1;
                break;
            }
        case 'r':
            {
                d=atof(buf);
                if (d==*((double *)headptr->value)) done=1;
                break;
            }
      }//switch
    if(done)
    {
	    done=0;//error found here
        printf("\nRecord Number=%u",loop);
        show_val(temp);
        printf("\nSearch Another(y/n)?");
        ch=getchar();fflush(stdin);
        if (ch=='n'||ch=='N')break;//exit for

    }
    }//for
    if (loop>num_records) return 0;else return(loop);


}

void Create()
{
    char fieldname[MAX_NAME+1],buf[MAX_NAME+1];
	char ch;
	FILE *file;
	int num_fields,i;
    unsigned int maxchars;
    size_t num_records;

	fflush(stdin);
	printf("\nCreate\n");
	printf("Enter database file name:");
	//printf("%d",sizeof(filename));
	fgets(filename,MAXPATH,stdin);
i=strlen(filename);
if (i<1) return;
filename[i-1]='\0';//remove \n
file=fopen(filename,"wb");
	if (file==NULL)
	{
		printf("\nerror: could not open file for writing named:%s",filename);
		etc();
        return;
	}

	strcpy(buf,"DAT");
	fwrite(buf,sizeof(char),3,file);//write file header

	do{
		printf("\nEnter no of fields required per record(>=1):");
		num_fields=getint();
	}while(num_fields<1);
	fwrite(&num_fields,sizeof(num_fields),1,file);//number of fields

	
	printf("\nEnter field details(t=text field,i=integer field, r=real number field)\n");
	for (i=0;i<num_fields;i++)
	{
		
		do{
		printf("\nEnter field name(1..max 80 chars) for field %d:",i+1);
		fgets(fieldname,MAX_NAME,stdin);//later check for blank string input
		}while(strlen(fieldname)<2);
		fieldname[strlen(fieldname)-1]='\0';
		fwrite(fieldname,sizeof(char),MAX_NAME+1,file);//write record name
		//can use sizeof(fieldname)

		do{
			printf("\nEnter the type of field(t,i,r) for field %s:",fieldname);
			scanf("%c",&ch);fflush(stdin);
		}while(!(ch=='t' || ch=='i' || ch=='r'));
		fwrite(&ch,sizeof(char),1,file);
        if (ch=='t')
        {
            do{
                printf("\nEnter maximum number of characters in text(1 to %d):",MAX_CHARS-1);
                maxchars=abs(getint());
            }while(maxchars<1||maxchars>MAX_CHARS-1);
            //maxchars++;
            fwrite(&maxchars,sizeof(maxchars),1,file);
        }
        

	}//for
    num_records=0;
    fwrite(&num_records,sizeof(size_t),1,file);
	fclose(file);
	printf("\nFile created, goto load database file to edit records");
    etc();

}

void Load()
{
    FILE *file;
    char buf[MAX_NAME+1];
    char ch;
    char exitcode;
    size_t fileread;
    int num_fields;
    unsigned int maxchars;
    int i;
    char fieldname[MAX_NAME+1];

    size_t rec_start,rec_size, file_pos, num_records,num_rec_pos, current_record_no;

    fflush(stdin);
    file_pos=0;//will check later for file_pos=0 & compare with ftell result
	printf("\nLoad\n");
	printf("Enter database filename to load:");
	fgets(filename,MAXPATH,stdin);
	filename[strlen(filename)-1]='\0';
    if ((file=fopen(filename,"rb"))==NULL)
    {
        printf("\nerror:opening file");
        etc();
        return;
    }
    //fseek(file,0,SEEK_SET);
    fileread=fread(buf,1,3,file);
    if (fileread!=3) {printf("\nIncorrect file");fclose(file);etc;return;}
    buf[3]='\0';
    if (strcmp(buf,"DAT")!=0)
    {
	printf("\nerror:incorrect file:1");
        fclose(file);
	etc();
        return;
    }
    file_pos+=3;

    fileread=fread(&num_fields,sizeof(num_fields),1,file);
    if ((fileread!=1)||(num_fields<1))
    {
        printf("\nerror:incorrect file:2");
        fclose(file);
        etc();
        return ;
    }
    file_pos+=sizeof(num_fields);

    //now read field names & types & create a record type
    rec_size=0;
    for (i=0;i<num_fields;i++)
    {
        fileread=fread(buf,sizeof(char),MAX_NAME+1,file);
	if (fileread!=MAX_NAME+1)
        {
            printf("\nerror:incorrect file:3");
            fclose(file);
            etc();
            return;
        }
        file_pos+=(MAX_NAME+1);

        fileread=fread(&ch,sizeof(char),1,file);
        if ((fileread!=1)||(!(ch=='t'||ch=='i'||ch=='r')))
        {
            printf("\nerror:incorrect file:4 .. read: %u .. field: %d",fileread,i+1);
            fclose(file);
            etc();
            return;
        }
        file_pos+=1;

        switch (ch)
	{
        case 't':
        {
            fileread=fread(&maxchars,sizeof(size_t),1,file);

            if ((fileread!=1)||(maxchars>(MAX_CHARS-1) || maxchars<1))
            {
                printf("\nerror:incorrect file:5");
                fclose(file);
                etc();
                return;
            }  
            rec_size+=((maxchars+1)*(sizeof(char)));
            file_pos+=sizeof(size_t);//unsigned int
                break; 
        }//if ch==t
        case 'i':
            {
		rec_size+=sizeof(int);
                break;
	    }
        case 'r':
            {
                rec_size+=sizeof(double);//float,double %f,%lf
                break;
            }
        }//switch
        add_rec_link(&head_rec/*,tail_rec*/,buf,ch,maxchars);

    }//for
    num_rec_pos=ftell(file);//same as file_pos
    fileread=fread(&num_records,sizeof(size_t),1,file);
            if (fileread!=1)
            {
                printf("\nerror:incorrect file:6");
                fclose(file);
                etc();
                return ;
	    }
    rec_start=ftell(file);//check with file_pos if adds to end of file
    printf("\n%u -file position-%u \n",rec_start,file_pos);
    fclose(file);
    //open file again
    if ((file=fopen(filename,"r+b"))==NULL)//check here to see if file is open
    {
        printf("\nerror:opening file for reading & writing");
        etc();
        return ;
    }
    fseek(file,rec_start,SEEK_SET);
    current_record_no=0;
    if (num_records>0) current_record_no=1;
    printf("\nFile Loaded\n");
    while(exitcode!=0)
    {
    if (current_record_no==0)
        printf("\nno records in file"); 
        else
	printf("\ncurrent record no.=%u",current_record_no);
    printf("\ntotal tecords=%u",num_records);
    printf("\n1.Add record to file");
    printf("\n2.search for a record");
    printf("\n3.select record from record number");
    printf("\n4.insert a record");
    printf("\n5.delete current record");
//    printf("\n6.edit current record");
    printf("\n6.view current record");
    printf("\n0.exit this menu\n\n:");
    exitcode=abs(getint());
    fflush(stdin);
    switch (exitcode)
    {
    case 0:
         {
         fclose(file);
         break;
         }
    case 1://add record
	{
            ask_values(head_rec);
	    fseek(file,0,SEEK_END);
            //for check maybe wrong//fseek(file,1,SEEK_CUR);//append
            write_val(file,head_rec);
            fseek(file,num_rec_pos,SEEK_SET);
            num_records+=1;
            if(current_record_no==0) current_record_no=1;
            fwrite(&num_records,sizeof num_records,1,file);//write number of records
            break;

        }
    case 2://search for record
        {
            int found=0;

            if (current_record_no==0) break;
            printf("\nEnter Field Name:");
            fgets(fieldname,MAX_NAME,stdin);
            fieldname[strlen(fieldname)-1]='\0';
	    printf("\nEnter Value to search for:");
            fgets(buf,MAX_NAME,stdin);
	    buf[strlen(buf)-1]='\0';
            /*
            ch=get_field_type(fieldname,head_rec);
            if (ch==0)
            {
                printf("\nNo such field name");
                etc();
                break;
            }//if
            */

            found=search_field(fieldname,buf,head_rec,file,rec_start,num_records);
            if (found==0)
            { 
                printf("matching record not found");etc();
            }
            else
                current_record_no=found;

            fseek(file,rec_start+((current_record_no-1)*rec_size),SEEK_SET);
	    break;
        }
    case 3://select record number
        {
            size_t rec_num;

            printf("\nEnter record number:");
            rec_num=abs(getint());
            if ((rec_num>num_records)|| (rec_num<1))
            {
                printf("error:record number should be b/w 1 & total number of records:");
                etc();
                break;//error solved
            }
            current_record_no=rec_num;
            fseek(file,rec_start+((current_record_no-1)*rec_size),SEEK_SET);
            break;
        }

    case 4://insert record
	{
            printf("\nuse add record option instead");
            etc();
            break;
        }
    case 5://delete record
        {
	    char fname[MAXPATH];
            char *buff;
            FILE *fl;
            int i,num_recs_left;

            if (current_record_no==0) break;
            tmpnam(fname);
            if((fl=fopen(fname,"wb"))==NULL)
            {
                printf("can't open a temp file");
                break;
	    }
	    buff=(char *)malloc(file_pos+sizeof(size_t));
	    if (buff==NULL)
            {
                printf("can't allocate space %u bytes",file_pos);
                break;
            }
            fseek(file,0,SEEK_SET);//is this ok?
            fread(buff,1,file_pos+sizeof(size_t),file);
            fwrite(buff,1,file_pos+sizeof(size_t),fl);//file_pos+ sizeof(size_t)
            free(buff);
            buff=NULL;
	    buff=(char *)malloc(rec_size);
            for (i=1;i<=current_record_no-1;i++)
            {
                fread(buff,rec_size,1,file);
                fwrite(buff,rec_size,1,fl);
            }
                fread(buff,rec_size,1,file);//waste this
            num_recs_left=num_records-current_record_no;
		for (i=1;i<=num_recs_left;i++)
                {
		    fread(buff,rec_size,1,file);
                    fwrite(buff,rec_size,1,fl);
                }
            fclose(fl);
            fclose(file);
            remove(filename);
            rename(fname,filename);
            file=fopen(filename,"r+b");
            fseek(file,num_rec_pos,SEEK_SET);
            num_records-=1;
	    fwrite(&num_records,sizeof(num_records),1,file);
            if (num_records==0) current_record_no=0; else current_record_no=1;
            break;
        }//case
    case 6://view record
        {
            if (current_record_no==0)break;
            fseek(file,rec_start+((current_record_no-1)*rec_size),SEEK_SET);
	    read_val(head_rec,file);
            show_val(head_rec);
	    etc();
            break;
        }
    default:
        {
        }
    }//switch

    }//while
}

void Main_Menu(void)
{
	unsigned char exitcode=0;
	char ch;
	while (!exitcode)
	{
		if(head_rec!=NULL) {clear_list_rec(head_rec);head_rec=NULL;}
	printf("\n\n Main Menu\n");
	printf("1. Create a new database file\n");
	printf("2. Load an existing database file\n");
	printf("0. Exit\n:");
	//ch=getche();
	//ch=getchar();
	scanf("%c",&ch);fflush(stdin);
	switch (ch)
	{
	case '1':
	{
		Create();
		break;
	}
	case '2':
		{
			Load();
			break;
		}
	case '0':
		{
			exitcode=1;
			break;
		}
	default:
		{
			printf("\nplease enter valid code\n");
		}
	}//switch

	}//while
}//main menu

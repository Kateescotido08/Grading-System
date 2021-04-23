#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

struct studData{
        float s1,s2,s3,s4;
        char name[100];

}a;
FILE *scores;

void login()
{
	int a=0,i=0;
    char uname[10],c=' ';
    char pword[10],code[10];
    char user[10]="user";
    char pass[10]="pass";
    do
{

    printf("\n  ::::::::::::::::::::::::::  LOGIN FORM  ::::::::::::::::::::::::::  ");
    printf(" \n                       ENTER USERNAME:-");
	scanf("%s", &uname);
	printf(" \n                       ENTER PASSWORD:-");
	while(i<10)
	{
	    pword[i]=getch();
	    c=pword[i];
	    if(c==13) break;
	    else printf("*");
	    i++;
	}
	pword[i]='\0';
	i=0;
		if(strcmp(uname,"user")==0 && strcmp(pword,"pass")==0)
	{
	printf("  \n\n\n       WELCOME TO EMPLOYEE RECORD MANAGEMENT SYSTEM !!!! LOGIN IS SUCCESSFUL");
	    printf("\n LOADING PLEASE WAIT... \n");
    for(i=0; i<3; i++)
    {
        printf(".");
        sleep(500);
    }
	printf("\n\n\n\t\t\t\tPress any key to continue...");
	getch();//holds the screen
	break;
	}
	else
	{
		printf("\nSORRY !!!!  LOGIN IS UNSUCESSFUL");
		a++;

		getch();//holds the screen
	}
}
	while(a<=2);
	if (a>2)
	{
		printf("\nSorry you have entered the wrong username and password for four times!!!");

		getch();

    }
		system("cls");
}

int cFile()
{
    scores = fopen("data.txt","rb+");
     if(scores == NULL)
    {
        scores = fopen("data.txt","wb+");
        if(scores == NULL)
        {
            printf("Cannot open file");
            exit(1);
        }
    }
    return 0;

}

void newStud()
{
    char ch;
    char sav;
    long int recsize;
    recsize=sizeof(a);
    system("cls");

            ch = 'y';
            while(ch == 'y')
    {
        printf("ENTER STUDENT NAME:");
       scanf(" %[^\n]s",a.name);

       printf("ENTER SCORE 1: ");
       scanf("%f",&a.s1);

       printf("ENTER SCORE 2: ");
       scanf("%f",&a.s2);

       printf("ENTER SCORE 3: ");
       scanf("%f",&a.s3);

       printf("ENTER SCORE 4: ");
       scanf("%f",&a.s4);

       printf("\nSAVE THIS RECORD? y/n:");
       scanf("%s",&sav);

                   if (sav=='y')
                    {

                       fwrite(&a,recsize,1,scores);
                        printf("Saving this record....");
                    }
                    else
                    {
                        printf("SAVING CANCELLED");
                    }

       printf("\n\nDO YOU WANT TO ADD ANOTHER?[Y/N]: ");
       scanf("%s",&ch);
    }
}
void edStud()
{
    char sname[100];
    char edit,ch;
    int test=0,i=0;
    long int recsize;
    recsize=sizeof(a);

     system("cls");
            do
            {
                printf("SEARCH STUDENT NAME: ");

                scanf("%s",&sname);
                rewind(scores);
                while(fread(&a,recsize,1,scores)==1)  /// fetch all record from file
                {
                    if(strcmp(a.name,sname) == 0)  ///if entered name matches with that in file
                    {
                        printf("SCORE 1:%.2f   SCORE 2: %.2f    SCORE 3:%.2f    SCORE 4:%.2f",a.s1,a.s2,a.s3,a.s4);

                        printf("\nWhich scores would you like to EDIT[1/2/3/4]?:");
                        scanf("%s",&edit);
                        switch (edit)
                        {
                        case '1':
                        printf("\nENTER NEW GRADE 1:");
                        scanf("%f",&a.s1);
                        break;

                        case '2':
                        printf("\nENTER NEW GRADE 2:");
                        scanf("%f",&a.s2);
                        break;

                        case '3':
                        printf("\nENTER NEW GRADE 3:");
                        scanf("%f",&a.s3);
                        break;

                       case '4':
                        printf("\nENTER NEW GRADE 4:");
                        scanf("%f",&a.s4);
                        break;
                    }
                        fseek(scores,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                        fwrite(&a,recsize,1,scores);/// override the record
                        test+=2;
                        break;
                    }
                i+=1;
                }
                if (i>test)
                {
                        printf("RECORD DOES NOT EXIST");
                }
                printf("i=%d",i);
                printf("test=%d",test);

                printf("\nModify another record(y/n)?:");
                scanf("%s",&ch);
            }
            while (ch=='y'||ch=='Y');
}

void delStud()
{
    char ch;
    char sname[100];
    long int recsize;
    FILE *ft;
    recsize = sizeof(a);
    system("cls");

            ch = 'y';
            while(ch == 'y')
            {
                printf("\nEnter name of employee to delete: ");
                scanf("%s",sname);
                ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                rewind(scores); /// move record to starting of file
                while(fread(&a,recsize,1,scores) == 1)  /// read all records from file
                {
                    if(strcmp(a.name,sname) != 0)  /// if the entered record match
                    {
                        fwrite(&a,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }
                fclose(scores);
                fclose(ft);
                remove("data.txt"); /// remove the orginal file
                rename("Temp.dat","data.txt"); /// rename the temp file to original file name
                scores = fopen("data.txt", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                ch = getche();
            }
}
void sStud()
{
    char sname[100];
    long int recsize;
    recsize=sizeof(a);

    printf("Search Student:");
                scanf("%s",&sname);
                rewind(scores);
                while(fread(&a,recsize,1,scores)==1)  /// fetch all record from file
                {
                    if(strcmp(a.name,sname) == 0)  ///if entered name matches with that in file
                    {
                         printf("\n%s\t%.2f\t%.2f\t%.2f\t%.2f\n\n",a.name,a.s1,a.s2,a.s3,a.s4);
                    }
                }
}

void dStud()
{
    long int recsize;
    recsize=sizeof(a);

            system("cls");
            printf("STUDENTS's RECORD LIST)");
            rewind(scores); ///this moves file cursor to start of the file
            while(fread(&a,recsize,1,scores)==1)  /// read the file and fetch the record one record per fetch
            {
                printf("\n%s\t%.2f\t%.2f\t%.2f\t%.2f",a.name,a.s1,a.s2,a.s3,a.s4);
            }
    getch();
}

int main()
{
  // login();
    float s1,s2,s3,s4;
    char sname[20],name[100];
    int menu,passed,failed;
    char sav;
    char ch;
    char edit,type;
    float average;
    long int recsize;
    struct studData a;
    float a1,a2,a3,a4;

    FILE* scores;
    FILE* ft;
    FILE *dat;

    recsize=sizeof(a);
    while(1)
    {
        printf("\t\n\tMAIN MENU\t");
        printf("\n\tWANT DO YOU WANT TO DO?\n");
        printf("\n1.] Add New Student \t\n2.] Edit Student \t\n3.] Delete Student \t\n4.] Display Student \t\n5.] Display All \t\n6.] Compute Grade \t\n7.] Exit\n");

        printf("\nEnter Choice [1/2/3/4/5/6] :");
        scanf("%d",&menu);

        switch (menu)
        {
            case 1:
                   newStud();
                   break;

            case 2:
                    edStud();
                    break;

            case 3:
                    delStud();
                    break;

            case 4:
                    sStud();
                    break;
            case 5:
                    dStud();
                    break;

            case 7:
                    exit(0);
        }
    }
    return 0;
}



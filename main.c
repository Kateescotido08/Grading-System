#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h> //HEADER FILE FOR gotoxy
#include <conio.h> //FUNCTION FOR getch()
#include <mmsystem.h> //HEADER FILE FOR PLAYSOUND

COORD coord = { 0, 0 }; //GLOBAL VARIABLE, CENTER OF AXIS IS SET TO THE TOP LEFT CORNER OF THE OUTPUT SCREEN

void Print();
void load();
int compGrade(FILE* grades,char name[30],float grade1,float grade2,float grade3,float grade4);

void gotoxy(int x, int y)
{
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Print()
{
   gotoxy(50,10);
   printf("WELCOME!\n\n\t\t\t\tPress Any key to see the Grades of the Students\n");

//PlaySound(TEXT("C:\\Users\\escot\\OneDrive\\Desktop\\FILE HANDLING\\welcome.wav"),NULL,SND_SYNC);

    getch();
    system("cls");

    gotoxy(30,10);
    printf("PROGRAMMERS: JAMIEL R. SUMERACRUZ and KATE FEBE B. ESCOTIDO");

     //PlaySound(TEXT("C:\\Users\\escot\\OneDrive\\Desktop\\FILE HANDLING\\programmers.wav"),NULL,SND_SYNC);

     if(getch()==27)
   exit(0);
}

void load()
{
    system("cls");
    int r,q;

    gotoxy(30,26);
    printf("LOADING...");

    gotoxy(45,26);
    for(r=0;r<=20;r++)
    {
        for(q=1;q<=100000000;q++);
        printf("%c",177);
    }
    //PlaySound(TEXT("C:\\Users\\escot\\OneDrive\\Desktop\\FILE HANDLING\\loading.wav"),NULL,SND_SYNC);
}
//MAIN PROGRAM
int main (void)
{
    system("color 5D");
    Print();
    load();

    float grade1,grade2,grade3,grade4;
    char name[30];

        FILE *grades;
    FILE *printNew;

    grades=fopen("average.txt","r");
    printNew=fopen("GRADE.txt","w");

    if (grades==NULL)
        {
            printf("\nERROR READING FILE");
            return 0;
        }
    if (printNew==NULL)
        {
            printf("\nERROR WRITING FILE");
            return 1;
        }

    compGrade(grades,name,grade1,grade2,grade3,grade4);

    fclose(grades);

    printf("\n\n\t\tA = 90>\n\t\tB = 81-90 \n\t\tC = 75-80 \n\t\tF = <75\n\n\n");

    //PlaySound(TEXT("C:\\Users\\escot\\OneDrive\\Desktop\\FILE HANDLING\\beep.wav"),NULL,SND_SYNC);

    return 0;
}

 int compGrade(FILE* grades,char name[30],float grade1,float grade2,float grade3,float grade4)
 {
    double average;
    int passed=0, failed=0;
    char type;
    FILE *printNew;

    printNew=fopen("GRADE.txt","w");

    gotoxy(17 , 5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 GRADES PROGRAM \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(17, 26);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(5, 6);
    printf("============================================================================");

    gotoxy(12, 7);
    printf("STUDENT NAME\t\tGWA\t\tGRADE LETTER ");

    gotoxy(5, 8);
    printf("============================================================================\n");

    fprintf(printNew,"===================================================================");
    fprintf(printNew,"\nSTUDENT NAME\t\tGWA\t\t\tGRADE LETTER\n");
    fprintf(printNew,"===================================================================");

    while(fscanf(grades,"%s %f %f %f %f",name,&grade1,&grade2,&grade3,&grade4)!=EOF)
    {
          average=(grade1+grade2+grade3+grade4)/4;

     if(average>=90)
    {
        type='A';
        passed++;
    }
    else if((average>=81)&&(average<=91))
    {
        type='B';
        passed++;
    }
    else if((average>=75)&&(average<=80))
    {
        type='C';
        failed++;
    }
    else if(average<75)
    {
        type='F';
        failed++;
    }

    printf("\n\t\t%s\t\t\t%.2f \t\t%c",name,average,type);
    fprintf(printNew,"\n%s\t\t\t%.2f\t\t\t%c",name,average,type);
    }

       printf("\n\n\t\tTOTAL PASSED : %d",passed);
       printf("\n\t\tTOTAL FAILED : %d",failed);

        fprintf(printNew,"\n\nTOTAL PASSED: %d",passed);
        fprintf(printNew,"\nTOTAL FAILED: %d",failed);
        fprintf(printNew,"\n\nA = 90>\nB = 81-90 \nC = 75-80 \nF = <75\n");

    return 0;
 }

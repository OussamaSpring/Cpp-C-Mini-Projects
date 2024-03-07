#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_STRING_SIZE 50 // This for solving the problem of reading the student record

typedef struct
{
    char ID[MAX_STRING_SIZE];
    char First_Name[MAX_STRING_SIZE];
    char Last_Name[MAX_STRING_SIZE];
    char Birth_Date[MAX_STRING_SIZE];
    char Address[MAX_STRING_SIZE];
    char Class[MAX_STRING_SIZE];
    char eContact[MAX_STRING_SIZE];
    float Average;
} Student_Info;

Student_Info Student_Records[100], New_Record;
float Mark_Matrix[100][4];
int Nbr_Records = 0, Record_Index = 0, UserChoice;

void ShowMainMenue(); // Declaration of a procedure so I can call it even if the original one is below the call.

int ReadUserChoice()
{
    int choice = 0;
    do
    {
        printf("Please enter your choice [1-7]: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 7);
    return choice;
}

// This function return the Record_Index of the student record and return -1 if it doesn't exist.
int Search(Student_Info Student_Records[100], int Nbr_Records, char First_Name[15], char Last_Name[15])
{
    for (int i = 0; i < Nbr_Records; i++)
    {
        if (strcmp(Student_Records[i].First_Name, First_Name) == 0 &&
            strcmp(Student_Records[i].Last_Name, Last_Name) == 0)
        {
            return i;
        }
    }
    return -1;
}

Student_Info ReadStudentRecord()
{
    Student_Info Student;
    printf("\nEnter ID: ");
    scanf("%s", &Student.ID);

    printf("Enter First Name: ");
    scanf("%s", &Student.First_Name);

    printf("Enter Last Name: ");
    scanf("%s", &Student.Last_Name);

    printf("Enter Birth Date (DD/MM/YYYY): ");
    scanf("%s", &Student.Birth_Date);

    printf("Enter Address: ");
    scanf("%s", &Student.Address);

    printf("Enter Class: ");
    scanf("%s", &Student.Class);

    printf("Enter Emergency Contact: ");
    scanf("%s", &Student.eContact);

    Student.Average = -1;

    return Student;
}

// This function return the number of records after adding new record to the array
int Add(Student_Info Student_Records[100], int Nbr_Records, Student_Info New_Record)
{
    if (Nbr_Records < 100)
    {
        Student_Records[Nbr_Records] = New_Record;
        return Nbr_Records + 1;
    }
    else
    {
        printf("Error: Maximum number of records reached.\n");
        return Nbr_Records;
    }
}

void AddStudentScreen()
{
    printf("\n---------------------------------------------\n");
    printf("\t  Add a Student Screen");
    printf("\n---------------------------------------------\n");
    char choice = 'y';
    while (choice == 'y' || choice == 'Y')
    {
        New_Record = ReadStudentRecord();
        Nbr_Records = Add(Student_Records, Nbr_Records, New_Record);
        if (!(Nbr_Records < 100))
        {
            break;
        }
        printf("\nStudent added successfully! Do you want to add another student? (y/n)? ");
        scanf("%s", &choice);
    }
}

void Display_Record(Student_Info Record)
{
    printf("\n---------------------------------------------\n");
    printf("\t%s %s's Data:", Record.First_Name, Record.Last_Name);
    printf("\n---------------------------------------------");
    printf("\nID        : %s", Record.ID);
    printf("\nBirth Date: %s", Record.Birth_Date);
    printf("\nAddress   : %s", Record.Address);
    printf("\nClass     : %s", Record.Class);
    printf("\neContact  : %s", Record.eContact);
    if (Record.Average != -1)
    {
        printf("\nAverage   : %.2f", Record.Average);
    }
}

void DisplayStudentRecordScreen()
{
    printf("\n---------------------------------------------\n");
    printf("\tDisplay Student Record Screen");
    printf("\n---------------------------------------------\n");
    char choice = 'y';
    char First_Name[MAX_STRING_SIZE], Last_Name[MAX_STRING_SIZE];
    while (choice == 'y' || choice == 'Y')
    {
        printf("\nEnter First Name : ");
        scanf("%s", &First_Name);
        printf("Enter Last Name: ");
        scanf("%s", &Last_Name);

        Record_Index = Search(Student_Records, Nbr_Records, First_Name, Last_Name);
        if (Record_Index != -1)
            Display_Record(Student_Records[Record_Index]);
        else
            printf("\nThe student [%s %s] doesn't exist!", First_Name, Last_Name);
        printf("\n\nDo you want to dislpay another student's record? (y/n)? ");
        scanf("%s", &choice);
    }
}

int Delete(Student_Info Student_Records[100], int Nbr_Records, int Record_Index, float Mark_Matrix[100][4])
{
    if (Nbr_Records > 0 && Record_Index >= 0 && Record_Index < Nbr_Records)
    {
        for (int i = Record_Index; i < Nbr_Records - 1; i++)
        {
            Student_Records[i] = Student_Records[i + 1];

            for (int j = 0; j < 4; j++)
                Mark_Matrix[i][j] = Mark_Matrix[i + 1][j];
        }
        return Nbr_Records - 1;
    }
    else
    {
        printf("Error: Invalid record index.\n");
        return Nbr_Records;
    }
}

void DeleteStudentRecordScreen()
{
    printf("\n---------------------------------------------\n");
    printf("\tDelete Student Record Screen");
    printf("\n---------------------------------------------\n");
    char choice = 'y', confirm = 'y';
    char First_Name[15], Last_Name[15];
    while (choice == 'y' || choice == 'Y')
    {
        printf("\nEnter First Name : ");
        scanf("%s", &First_Name);
        printf("Enter Last Name: ");
        scanf("%s", &Last_Name);

        Record_Index = Search(Student_Records, Nbr_Records, First_Name, Last_Name);
        if (Record_Index != -1)
        {
            printf("\nAre you sure you want to delete this student's record? (y/n)? ");
            scanf("%s", &confirm);
            if (confirm == 'y')
            {
                Nbr_Records = Delete(Student_Records, Nbr_Records, Record_Index, Mark_Matrix);
                printf("\nStudent's record deleted successfully!");
            }
        }
        else
        {
            printf("\nThe student [%s %s] doesn't exist!", First_Name, Last_Name);
        }
        printf("\n\nDo you want to delete another student's record? (y/n)? ");
        scanf("%s", &choice);
    }
}

// Fill student marks and return the avrage
float ReadMark(char Subject[])
{
    float Mark;
    scanf("%f", &Mark);
    if (Mark < 0)
    {
        printf("\nError: A mark cannot be lower than zero.\n");
        while (Mark < 0)
        {
            printf("Enter %s mark: ", Subject);
            scanf("%f", &Mark);
        }
    }
    return Mark;
}

float Fill_Marks(float Mark_Matrix[100][4], int Record_Index)
{
    printf("\nEnter Physics mark: ");
    Mark_Matrix[Record_Index][0] = ReadMark("Physics");
    printf("Enter Maths mark: ");
    Mark_Matrix[Record_Index][1] = ReadMark("Math");
    printf("Enter Arabic mark: ");
    Mark_Matrix[Record_Index][2] = ReadMark("Arabic");
    printf("Enter English mark: ");
    Mark_Matrix[Record_Index][3] = ReadMark("English");

    float Avr = (Mark_Matrix[Record_Index][0] +
                 Mark_Matrix[Record_Index][1] +
                 Mark_Matrix[Record_Index][2] +
                 Mark_Matrix[Record_Index][3]) /
                4;
    return Avr;
}

void FillInMarksScreen()
{
    printf("\n---------------------------------------------\n");
    printf("\tFill Student Marks Screen");
    printf("\n---------------------------------------------\n");
    char choice = 'y';
    char First_Name[15], Last_Name[15];
    while (choice == 'y' || choice == 'Y')
    {
        printf("\nEnter First Name : ");
        scanf("%s", &First_Name);
        printf("Enter Last Name: ");
        scanf("%s", &Last_Name);

        Record_Index = Search(Student_Records, Nbr_Records, First_Name, Last_Name);
        if (Record_Index != -1)
            Student_Records[Record_Index].Average = Fill_Marks(Mark_Matrix, Record_Index);
        else
            printf("\nThe student [%s %s] doesn't exist!", First_Name, Last_Name);
        printf("\n\nDo you want to fill another student's marks? (y/n)? ");
        scanf("%s", &choice);
    }
}

int ReadUserChoice2()
{
    int choice = 0;
    do
    {
        printf("Please enter your choice [1-6]: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 6);
    return choice;
}

void Display_By_Critiria(Student_Info Student_Records[100], int Nbr_Records)
{
    char String[MAX_STRING_SIZE];
    int Num;

    printf("\nPlease enter a search word: ");
    scanf("%s", &String);
    Num = atoi(String);

    for (int i = 0; i < Nbr_Records; i++)
    {
        if (strcmp(String, Student_Records[i].ID) == 0)
            Display_Record(Student_Records[i]);
    }

    for (int i = 0; i < Nbr_Records; i++)
    {
        if (strcmp(String, Student_Records[i].First_Name) == 0)
            Display_Record(Student_Records[i]);
    }

    for (int i = 0; i < Nbr_Records; i++)
    {
        if (strcmp(String, Student_Records[i].Last_Name) == 0)
            Display_Record(Student_Records[i]);
    }

    for (int i = 0; i < Nbr_Records; i++)
    {
        if (strcmp(String, Student_Records[i].Birth_Date) == 0)
            Display_Record(Student_Records[i]);
    }

    for (int i = 0; i < Nbr_Records; i++)
    {
        if (strcmp(String, Student_Records[i].Address) == 0)
            Display_Record(Student_Records[i]);
    }

    for (int i = 0; i < Nbr_Records; i++)
    {
        if (strcmp(String, Student_Records[i].Class) == 0)
            Display_Record(Student_Records[i]);
    }

    for (int i = 0; i < Nbr_Records; i++)
    {
        if (Num == (int)Student_Records[i].Average)
            Display_Record(Student_Records[i]);
    }
}

void DisplayByCritiriaScreen()
{
    char Choice = 'y';
    while (Choice == 'y' || Choice == 'Y')
    {

        printf("\n---------------------------------------------\n");
        printf("\tDisplay By Critiria Screen");
        printf("\n---------------------------------------------");
        Display_By_Critiria(Student_Records, Nbr_Records);
        printf("\n\nDo you want to search again? (y/n)? ");
        scanf("%s", &Choice);
    }
}

void Display_Report_Card(Student_Info Record, int Record_Index, float Mark_Matrix[100][4])
{
    Record_Index = 0;
    if (Record.Average == -1)
        printf("\nError, unable to find the the student's data!");
    else
    {
        printf("\n---------------------------------------------\n");
        printf("\t%s %s's Report Card", Record.First_Name, Record.Last_Name);
        printf("\n---------------------------------------------\n");
        printf("ID: %s\t\t\tClass: %s\n", Record.ID, Record.Class);
        printf("\nPhysics: %.2f\t\tMath   : %.2f\nArabic : %.2f\t\tEnglish: %.2f",
               Mark_Matrix[Record_Index][0], Mark_Matrix[Record_Index][1],
               Mark_Matrix[Record_Index][2], Mark_Matrix[Record_Index][3]);
        printf("\n---------------------------------------------\n");
        printf("Avrage: \t\t\t%.2f", Record.Average);
        printf("\n---------------------------------------------\n");
    }
}

void DisplayReportCardStreen()
{
    printf("\n---------------------------------------------\n");
    printf("\tDisplay Report Card Screen");
    printf("\n---------------------------------------------\n");
    char choice = 'y';
    char First_Name[MAX_STRING_SIZE], Last_Name[MAX_STRING_SIZE];
    while (choice == 'y' || choice == 'Y')
    {
        printf("\nEnter First Name : ");
        scanf("%s", &First_Name);
        printf("Enter Last Name: ");
        scanf("%s", &Last_Name);

        Record_Index = Search(Student_Records, Nbr_Records, First_Name, Last_Name);
        if (Record_Index != -1)
            Display_Report_Card(Student_Records[Record_Index], Record_Index, Mark_Matrix);
        else
            printf("\nThe student [%s %s] doesn't exist!", First_Name, Last_Name);
        printf("\n\nDo you want to dislpay another student's record? (y/n)? ");
        scanf("%s", &choice);
    }
}

void ExitScreen()
{
    printf("\n---------------------------------------------\n");
    printf("\t\t Exit Screen");
    printf("\n---------------------------------------------\n");
    printf("Project done by: Oussama Azzouz\n\n");
}

void PerformMainMenueOptions(int UserChoice)
{
    switch (UserChoice)
    {
    case 1:
        AddStudentScreen();
        ShowMainMenue();
        break;
    case 2:
        DisplayStudentRecordScreen();
        ShowMainMenue();
        break;
    case 3:
        DeleteStudentRecordScreen();
        ShowMainMenue();
        break;
    case 4:
        FillInMarksScreen();
        ShowMainMenue();
        break;
    case 5:
        DisplayByCritiriaScreen();
        ShowMainMenue();
        break;
    case 6:
        DisplayReportCardStreen();
        ShowMainMenue();
        break;
    case 7:
        ExitScreen();
        break;
    default:
        break;
    }
}

void ShowMainMenue()
{
    printf("\n===========================================================\n");
    printf("\t\t\tMain Menue");
    printf("\n===========================================================\n");
    printf("\n\t(1) Add a new student record.");
    printf("\n\t(2) Display a student record.");
    printf("\n\t(3) Delete a student record.");
    printf("\n\t(4) Fill in the marks of a student record.");
    printf("\n\t(5) Search for a student.");
    printf("\n\t(6) Display a report card of a specific student.");
    printf("\n\t(7) Exit the program.\n");
    printf("\n===========================================================\n");
    PerformMainMenueOptions(ReadUserChoice());
}

int main()
{
    ShowMainMenue();
    return 0;
}

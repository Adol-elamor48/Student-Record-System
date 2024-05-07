#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#define MAX_PASSWORD_LENGTH 30
#define MAX_PASSWORD_ATTEMPTS 3
static char AdminPassword[MAX_PASSWORD_LENGTH] = "1234";

typedef struct student
{
    int rno;
    int age;
    char name[20];
    char gender[20];
    int total;
    float pre;
    struct subject
    {
        int scode;
        char sname[20];
        int mark;
    } sub[3];

} student;

int Validate_Admin_Password()
{
    char adminPassword[MAX_PASSWORD_LENGTH];
    int attempts = 0;
    do
    {
        printf("Enter Your password: ");
        fgets(adminPassword, sizeof(adminPassword), stdin);
        adminPassword[strcspn(adminPassword, "\n")] = '\0';
        if (strcmp(adminPassword, AdminPassword) == 0)
        {
            return 1;
            break;
        }
        else
        {
            printf("Invalid password. %d attempts remaining.\n", MAX_PASSWORD_ATTEMPTS - attempts - 1);
            attempts++;
        }
    } while (attempts < MAX_PASSWORD_ATTEMPTS);
    return 0;
}

void Edit_Admin_Password()
{
    char newPassword[MAX_PASSWORD_LENGTH];
    printf("Enter The New Password: ");
    fflush(stdin); fflush(stdout);
    fgets(newPassword, sizeof(newPassword), stdin);
    fflush(stdin); fflush(stdout);
    newPassword[strcspn(newPassword, "\n")] = '\0';
    strncpy(AdminPassword, newPassword, MAX_PASSWORD_LENGTH);
    Motion();
    printf("Your password updated successfully.\n");
}

void Motion(void)
{
    printf("Please wait ");
    for (int UserPassIndex = 0; UserPassIndex < 15; UserPassIndex++)
    {
        printf(".");
        Sleep(100);
    }
    printf("!!\n\n");
}
void create()
{
    student *s;
    FILE *fp;
    int n, i, j;
    printf("How many student you want to enter : ");
    scanf("%d", &n);

    s = (student *)calloc(n, sizeof(student));
    fp = fopen("mystudents.txt", "a");
    for (i = 0; i < n; i++)
    {
        s[i].total = 0;
        s[i].pre = 0;
        printf("Student%d \n", i + 1);
        printf("Enter ID: ");
        scanf("%d", &s[i]);

        fflush(stdin);
        printf("Enter Name : ");
        scanf("%[^\n]s", s[i].name);
        for (j = 0; j < 3; j++)
        {
            printf("Enter Marks of subject%d : ", j + 1);
            scanf("%d", &s[i].sub[j].mark);
            s[i].total += s[i].sub[j].mark;
        }
        s[i].pre = s[i].total / 3.0;
        printf("Enter age: ");
        scanf("%d", &s[i].age);
        fwrite(&s[i], sizeof(student), 1, fp);
    }
    fclose(fp);
}
void display()
{

    student s1;
    FILE *fp;
    fp = fopen("mystudents.txt", "r");
    while (fread(&s1, sizeof(student), 1, fp))
    {

        printf("\n%d_%-20s   Age=%d ", s1.rno, s1.name ,s1.age);
        for (int j = 0; j < 3; j++)
        {
            printf(" sub%d=%d   ", j + 1, s1.sub[j].mark);
        }
        printf("total_degree=%d   the_percentage=%.f%%   \n", s1.total, s1.pre);
    }

    fclose(fp);
}
void search()
{
    student s1;
    FILE *fp;
    int rol, found = 0;
    fp = fopen("mystudents.txt", "r");
    printf("Enter the RollNo : ");
    scanf("%d", &rol);
    while (fread(&s1, sizeof(student), 1, fp))
    {
        if (s1.rno == rol)
        {
            found = 1;
            printf("\n%d_%-20s", s1.rno, s1.name);
            for (int j = 0; j < 3; j++)
            {
                printf("sub%d=%d   ", j + 1, s1.sub[j].mark);
            }
            printf("total__degree=%d   the_percentage=%.f%%   \n", s1.total, s1.pre);
        }
        if (!found)
        {
            printf("\n the RollNo not found\n ");
        }
    }

    fclose(fp);
}
void update()
{
    student s1;
    FILE *fp, *fp1;
    int rol, found = 0, j;
    fp = fopen("mystudents.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Enter the RollNo to update: ");
    scanf("%d", &rol);
    while (fread(&s1, sizeof(student), 1, fp))
    {
        if (s1.rno == rol)
        {
            s1.total = 0;
            s1.pre = 0;
            found = 1;
            fflush(stdin);
            for (j = 0; j < 3; j++)
            {
                printf("Enter New Marks of subject%d : ", j + 1);
                scanf("%d", &s1.sub[j].mark);
                s1.total += s1.sub[j].mark;
            }
            s1.pre = s1.total / 3.0;
        }
        fwrite(&s1, sizeof(student), 1, fp1);
    }
    fclose(fp1);
    fclose(fp);
    if (found)
    {
        fp1 = fopen("temp.txt", "r");
        fp = fopen("mystudents.txt", "w");
        while (fread(&s1, sizeof(student), 1, fp1))
        {
            fwrite(&s1, sizeof(student), 1, fp);
        }

        fclose(fp1);
        fclose(fp);
    }
}
void update_name()
{
    student s1;
    FILE *fp, *fp1;
    int rol, found = 0, j;
    fp = fopen("mystudents.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Enter the RollNo to update: ");
    scanf("%d", &rol);
    while (fread(&s1, sizeof(student), 1, fp))
    {
        if (s1.rno == rol)
        {
            found = 1;
            fflush(stdin);
            printf("Enter the name : ");
            scanf("[^\n]s", s1.name);
        }
        fwrite(&s1, sizeof(student), 1, fp1);
    }
    fclose(fp1);
    fclose(fp);
    if (found)
    {
        fp1 = fopen("temp.txt", "r");
        fp = fopen("mystudents.txt", "w");
        while (fread(&s1, sizeof(student), 1, fp1))
        {
            fwrite(&s1, sizeof(student), 1, fp);
        }

        fclose(fp1);
        fclose(fp);
    }
}
void chang_pass(long long *r)
{
    int p;
    printf("Enter the new password : ");
    scanf("%d", &p);
    *r = p;
    printf("Your new password is  : %d  \n", *r);
}
void clearScreen()
{
    system("cls");
}
void delay(int milliseconds)
{
    usleep(milliseconds * 1000);
}
void delete_reco()
{
    student s1;
    FILE *fp, *fp1;
    int rol, found = 0, j;
    fp = fopen("mystudents.txt", "r");
    fp1 = fopen("temp.txt", "w");
    printf("Enter the RollNo to update: ");
    scanf("%d", &rol);
    while (fread(&s1, sizeof(student), 1, fp))
    {
        if (s1.rno == rol)
        {
            found = 1;
        }
        else
            fwrite(&s1, sizeof(student), 1, fp1);
    }
    fclose(fp1);
    fclose(fp);
    if (found)
    {
        fp1 = fopen("temp.txt", "r");
        fp = fopen("mystudents.txt", "w");
        while (fread(&s1, sizeof(student), 1, fp1))
        {
            fwrite(&s1, sizeof(student), 1, fp);
        }

        fclose(fp1);
        fclose(fp);
    }
    else
    {
        printf("\n Record Not Found\n");
    }
}
int main()
{
    int ch, o, y;
    char str[20];
    printf("\n                                   ***** Welcome to the Student Record System! *****\n\n");

    while (1)
    {
        printf("Please select your role:\n");
        printf("1. Admin\n");
        printf("2. Student\n");
        printf("Enter your choice: ");
        scanf("%d", &o);
        clearScreen();
        if (o == 1)
        {

            printf("\nEnter Your Password : ");
            scanf("%d", &y);
            // Using snprintf to convert int to string
            snprintf(str, sizeof(str), "%d", y);
            if (!strcmp(str ,AdminPassword))
            {
                do
                {
                    printf("\n1.Add student record");
                    printf("\n2.View all records");
                    printf("\n3.View student record");
                    printf("\n4.Edit student grade");
                    printf("\n5.Remove student record");
                    printf("\n6.UPDATE PASSWORD");
                    printf("\n0.EXIT \n");

                    printf("Enter your choice  : ");
                    scanf("%d", &ch);
                    clearScreen();
                    switch (ch)
                    {
                        case 1:
                            Motion();
                            delay(500);
                            create();
                            clearScreen();
                            break;
                        case 2:
                            Motion();
                            delay(500);
                            display();
                            break;
                        case 3:
                            clearScreen();
                            Motion();
                            delay(500);
                            search();
                            break;
                        case 4:
                            clearScreen();
                            Motion();
                            delay(500);
                            update();
                            break;
                        case 5:
                            clearScreen();
                            Motion();
                            delay(500);
                            delete_reco();
                            break;
                        case 6:
                            clearScreen();
                            Motion();
                            delay(500);
                            Edit_Admin_Password();
                            break;
                        case 0:
                            break;
                    }
                } while (ch != 0);
            }
            else
            {
                printf("The pass word uncorrect \n");
            }
        }
        else if (o == 2)
        {
            printf("Enter Your Password : ");
            scanf("%d", &y);
            snprintf(str, sizeof(str), "%d", y);
            if (!strcmp(str ,AdminPassword))
            {
                delay(50);

                do
                {
                    printf("\n1.SEARCH");
                    printf("\n2.Edit your password.");
                    printf("\n3.Edit your name");
                    printf("\n0.EXIT \n");

                    printf("Enter your choice  : ");
                    scanf("%d", &ch);
                    clearScreen();
                    switch (ch)
                    {
                        case 1:
                            clearScreen();
                            Motion();
                            delay(500);
                            search();
                            break;
                        case 2:
                            clearScreen();
                            Motion();
                            delay(500);
                            Edit_Admin_Password();
                            break;
                        case 3:
                            clearScreen();
                            Motion();
                            delay(500);
                            update_name();
                            break;
                    }
                } while (ch != 0);
            }
            else
            {
                printf("The password not correct \n");
            }
        }
    }
    return 0;
}

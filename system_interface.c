//
// Created by Eslam Walid on 2020-09-07.
//

#include "system_interface.h"

static void print_str(const char *str);
static void print_int(const int integer);

void system_init()
{
    set_admin_password();
    printf("Welcome the Student Records system!\n");
}

void system_run()
{
    int systemMode;
    printf("Select the mode:\n");
    printf("1-Admin Mode.\n");
    printf("2-User Mode.\n");

    scanf("%d",&systemMode);
    while (systemMode != ADMIN_MODE && systemMode != USER_MODE)
    {
        printf("Wrong mode, try again!\n");
        scanf("%d",&systemMode);
    }
    switch (systemMode)
    {
        case 1:
            admin_mode();
            break;

        case 2:
            user_mode();
            break;
    }
}

void admin_mode()
{
    char passwordBuf[MAX_LENGTH];
    printf("You entered admin mode.\n");
    printf("Enter admin password:\n");
    fflush(stdin);
    gets(passwordBuf);
    admin_login(passwordBuf);
    admin_menu();
    admin_action();
}

void admin_login(char *adminPassword)
{
    while (!check_admin_password(adminPassword))
    {
        printf("Wrong password, try again!\n");
        fflush(stdin);
        gets(adminPassword);
    }
}

void admin_menu()
{
    printf("Enter the number of operation you need:\n");
    printf("1-Change admin password.\n");
    printf("2-Add new student.\n");
    printf("3-Edit student name.\n");
    printf("4-Edit student password.\n");
    printf("5-Edit student degree.\n");
    printf("6-View student info.\n");
    printf("7-Remove student.\n");
    printf("8-Return to main menu\n");
}

void admin_action()
{
    int adminFunction;
    int degree,ID;
    char dummy[2];  //Capacity for newline
    char studentName[MAX_LENGTH];
    char studentPassword[MAX_LENGTH];
    char adminPassword[MAX_LENGTH];

    scanf("%d",&adminFunction);
    while (!(adminFunction >= 1 && adminFunction <= 8))
    {
        printf("Wrong operation number, try a valid one!\n");
        scanf("%d",&adminFunction);
    }

    switch (adminFunction)
    {
        case 1:
            printf("Enter the new password:\n");
            fflush(stdin);
            gets(adminPassword);
            modify_admin_password(adminPassword);
            printf("Password has changed successfully.\n");
            break;

        case 2:
            printf("Enter student name:\n");
            fflush(stdin);
            gets(studentName);
            printf("Enter student password:\n");
            fflush(stdin);
            gets(studentPassword);
            printf("Enter student degree:\n");
            scanf("%d",&degree);
            if (add_new_record(studentName,studentPassword,degree))
            {
                printf("Student has been added successfully!\n");
            }
            else
            {
                printf("There is no capacity for a new student!\n");
            }
            break;

        case 3:
            printf("Enter student name:\n");
            fflush(stdin);
            gets(studentName);
            printf("Enter student ID:\n");
            scanf("%d",&ID);
            if (modify_student_name(ID, studentName))
            {
                printf("Name has been changed successfully!\n");
            }
            else
            {
                printf("You entered invalid ID\n");
            }
            break;

        case 4:
            printf("Enter student password:\n");
            fflush(stdin);
            gets(studentPassword);
            printf("Enter student ID:\n");
            scanf("%d",&ID);
            if (modify_student_password(ID, studentPassword))
            {
                printf("Password has been changed successfully!\n");
            }
            else
            {
                printf("You entered invalid ID\n");
            }
            break;

        case 5:
            printf("Enter student degree:\n");
            scanf("%d",&degree);
            printf("Enter student ID:\n");
            scanf("%d",&ID);
            if (modify_degree(ID,degree))
            {
                printf("Degree has been changed successfully!\n");
            }
            else
            {
                printf("You entered invalid ID\n");
            }
            break;

        case 6:
            printf("Enter student ID:\n");
            scanf("%d",&ID);
            if (!traverse_record(ID,print_int,print_str))
            {
                printf("You entered invalid ID\n");
            }
            break;

        case 7:
            printf("Enter student ID:\n");
            scanf("%d",&ID);
            if (remove_record(ID))
            {
                printf("Student removed successfully!");
            }
            else
            {
                printf("You entered invalid ID\n");
            }
            break;

        case 8:
            system_run();
            break;
    }
    printf("Enter \"C\" to continue...\n");
    scanf("%s",dummy);
    admin_menu();
    admin_action();
}

void user_mode()
{
    int ID;
    char passwordBuf[MAX_LENGTH];
    printf("You entered user mode.\n");
    printf("Enter your ID:\n");
    scanf("%d",&ID);
    printf("Enter your password:\n");
    fflush(stdin);
    gets(passwordBuf);
    user_login(&ID,passwordBuf);
    user_menu();
    user_action(ID);
}

void user_login(int *ID,char *userPassword)
{
    while (!check_user_ID_password(*ID,userPassword))
    {
        printf("You entered wrong ID or password\n");
        printf("Enter your ID:\n");
        scanf("%d",ID);
        printf("Enter your password:\n");
        fflush(stdin);
        gets(userPassword);
    }
}

void user_menu()
{
    printf("Enter the number of operation you need:\n");
    printf("1-View your info.\n");
    printf("2-Change your password.\n");
    printf("3-Return to main menu.\n");
}

void user_action(int ID)
{
    int userFunction;
    char dummy[2];  //Capacity for newline
    char studentPassword[MAX_LENGTH];
    scanf("%d",&userFunction);
    while (!(userFunction >= 1 && userFunction <= 3))
    {
        printf("Wrong operation number, try a valid one!\n");
        scanf("%d",&userFunction);
    }
    switch (userFunction)
    {
        case 1:
            traverse_record(ID,print_int,print_str);
            break;

        case 2:
            printf("Enter your new password:\n");
            fflush(stdin);
            gets(studentPassword);
            modify_student_password(ID, studentPassword);
            break;

        case 3:
            system_run();
            break;
    }
    printf("Enter \"C\" to continue...\n");
    scanf("%s",dummy);
    user_menu();
    user_action(ID);
}

static void print_str(const char *str)
{
    printf("%s\n",str);
}

static void print_int(const int integer)
{
    printf("%d\n",integer);
}
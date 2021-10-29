#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 4

// Signal if instruction was to delete an account
bool delete_signal = false;

char record[60];
char mail[35];
char pwd[20];

// Prototypes
void instruction();
void create();
void login();
void delete_acc();
bool check_credentials(FILE *file);
void change_pass();

void main(void)
{
    int choice;
    do
    {
        instruction();
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                login();
                break;

            case 2:
                create();
                break;

            case 3:
                change_pass();
                break;

            case 4:
                delete_acc();
                break;

            case 5:
                break;

            default:
                printf("Invalid Choice\n");
                break;
        }
    }
    while (choice != 5);
}

void instruction()
{
    printf("What you want to do?\n");
    printf("---------------------------------------------------------\n");
    printf("\t1 - Login to your account\n\t2 - Create an account\n\t3 - Change your password\n\t4 - Delete your account\n\t5 - Exit\n");
    printf("---------------------------------------------------------\n");
}

void create()
{
    int num = 0;
    FILE *f = fopen("records.txt", "w+");
    if (f == NULL)
    {
        return;
    }
    while (!feof(f))
    {
        fscanf(f, "%d %s\t%s", &num, mail, pwd);
    }
    if (num == MAX)
    {
        printf("Sorry! Cannot create more than 4 accounts\n");
        fclose(f);
        return;
    }
    fclose(f);
    FILE *write = fopen("records.txt", "a");
    if (write == NULL)
    {
        return;
    }
    fseek(write, 0, SEEK_END);
    printf("Enter your mail id: ");
    scanf("%s", record);
    num++;
    fprintf(write, "\n%d %s\t" , num, record);
    printf("Enter password: ");
    scanf("%s", record);
    fprintf(write, "%s", record);
    printf("Account created!\n");
    fclose(write);
}

void login()
{
    FILE *file = fopen("records.txt", "r");
    if (file == NULL)
    {
        return;
    }
    if (check_credentials(file))
    {
        printf("Loging you in... Successfully logged in\n");
    }
    else
    {
        printf("Incorrect information!\n");
    }
    fclose(file);
}

void delete_acc()
{
    char *old_name = "records.txt";
    char *new_name = "newrecords.txt";
    delete_signal = true;
    FILE *f1 = fopen("records.txt", "r");
    if (f1 == NULL)
    {
        return;
    }
    if (!check_credentials(f1))
    {
        printf("Provided data is incorrect OR Account doesn't exist.\n");
    }
    else
    {
        printf("Account deleted successfully.\n");
    }
    delete_signal = false;
    fclose(f1);
    remove(old_name);
    int value = rename(new_name, old_name);
    return;
}

bool check_credentials(FILE *file)
{
    int num = 0, cmpnum = 0;
    bool found = false;
    char cmp[35];
    printf("Enter mail ID: ");
    scanf("%s", record);
    while (!feof(file))
    {
        fscanf(file, "%d %s\t%s", &num, mail, pwd);
        if (strcmp(mail, record) == 0)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        return false;
    }
    printf("Enter password: ");
    scanf("%s", cmp);
    rewind(file);
    while (!feof(file))
    {
        fscanf(file, "%d %s\t%s", &cmpnum, mail, pwd);
        if (num != cmpnum)
        {
            continue;
        }
        else if (strcmp(pwd, cmp) == 0)
        {
            found = true;
            break;
        }
        else
        {
            found = false;
            break;
        }
    }
    if (!found)
    {
        return false;
    }
    if (delete_signal)
    {
        bool signal_del = false;
        FILE *f2 = fopen("newrecords.txt", "w");
        if (f2 == NULL)
        {
            return false;
        }
        rewind(file);
        while (!feof(file))
        {
            fscanf(file, "%d %s\t%s", &cmpnum, mail, pwd);
            if (num != cmpnum)
            {
                if (!signal_del)
                {
                    fprintf(f2, "\n%d %s\t%s", cmpnum, mail, pwd);
                }
                else
                {
                    fprintf(f2, "\n%d %s\t%s", cmpnum - 1, mail, pwd);
                }
            }
            else
            {
                signal_del = true;
            }
        }
        fclose(file);
        fclose(f2);
    }
    return true;
}

void change_pass()
{
    // Not secure i know
    int num = 0;
    char tmp3[20];
    char tmp4[20];
    FILE *file = fopen("records.txt", "r");
    FILE *file2 = fopen("newrecords.txt", "w");
    if (file == NULL || file2 == NULL)
    {
        return;
    }
    printf("Enter mail ID: ");
    scanf("%s", record);
    printf("Enter old password: ");
    scanf("%s", pwd);
    printf("Enter new password: ");
    scanf("%s", tmp4);
    while (!feof(file))
    {
        fscanf(file, "%d %s\t%s", &num, mail, tmp3);
        if (strcmp(record, mail) == 0 && strcmp(pwd, tmp3) == 0)
        {
            fprintf(file2, "\n%d %s\t%s", num, mail, tmp4);
        }
        else
        {
            fprintf(file2, "\n%d %s\t%s", num, mail, tmp3);
        }
    }
    printf("Required operation is done.\n");
    fclose(file);
    fclose(file2);
    remove("records.txt");
    rename("newrecords.txt", "records.txt");
    return;
}

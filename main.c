#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void mainMenu(char[]);
void accountMenu();
int login(char[], char[]);
int validateMenuSelection(char[], int, int);
int checkUserExists(void);
void writeUserToFile(char[], char[]);
void writeDiaryEntryToFile(char[]);
void createEntry(void);

char *userDir = "user.txt";
char *userName;

void writeUserToFile(char name[], char pw[])
{
    FILE *file = fopen(userDir, "w");

    if (file == NULL)
    {
        perror("file can't be opened \n");
        exit(0);
    }
    else
    {
        fprintf(file, "%s%s", name, pw);
        fclose(file);
        printf("%s\n", "Account created :)");
        accountMenu();
    }
}

void writeDiaryEntryToFile(char entry[])
{
    char path[] = "entries/";
    time_t mytime;
    mytime = time(NULL);
    char *ct = ctime(&mytime);
    ct[strcspn(ct, "\n")] = '\0';
    while (ct[strcspn(ct, ":")] != NULL)
    {
        ct[strcspn(ct, ":")] = '-';
    }
    while (ct[strcspn(ct, " ")] != NULL)
    {
        ct[strcspn(ct, " ")] = '-';
    }
    strcat(path, ct);
    strcat(path, ".txt");
    printf("%s\n", path);
    FILE *file2 = fopen(path, "w");

    if (file2 == NULL)
    {
        perror("file can't be opened");
        // exit(0);
    }
    else
    {
        fprintf(file2, "%s", entry);
        fclose(file2);
        mainMenu(userName);
    }
}

int login(char name[], char pw[])
{
    FILE *file = fopen(userDir, "r");
    char fileContents[2][20];

    int i = 0;
    if (file == NULL)
    {
        perror("file can't be opened \n");
        //exit(0);
    }
    else
    {
        char line[100];
        int i = 0;
        while (fgets(line, sizeof(line), file))
        {
            strcpy(fileContents[i], line);
            i++;
        }

        if (strcmp(fileContents[0], name) == 0 && strcmp(fileContents[1], pw) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int checkUserExists(void)
{
    FILE *file = fopen(userDir, "r");
    char ch;

    if (file == NULL)
    {
        perror("file can't be opened \n");
        exit(0);
    }
    else
    {
        char line[100];
        int i = 0;
        while (fgets(line, sizeof(line), file))
        {
            i++;
        }

        fclose(file);

        if (i >= 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int validateMenuSelection(char selection[], int num, int numSelections)
{
    if (strlen(selection) != 2)
    {
        num = 0;
    }

    if (sscanf(selection, "%d", &num) != 1)
    {
        num = 0;
    }

    if (num > numSelections || num < 1)
    {
        num = 0;
    }

    if (num == 0)
    {
        printf("%s\n", "Invalid input try again:\n");
    }
    return num;
}

void createEntry(void)
{
    char entry[100];
    printf("%s\n", "Enter Diary Entry Below:");
    fgets(entry, 99, stdin);
    writeDiaryEntryToFile(entry);
}

void mainMenu(char name[])
{
    char selection[64];
    int num = 0;

    while (num == 0)
    {
        name[strcspn(name, "\n")] = 0;
        printf("---------------Hi %s---------------\n", name);
        printf("%s\n", "Main Menu");
        printf("%s\n", "1: Read");
        printf("%s\n", "2: Write");
        printf("%s\n", "3: Exit");
        fgets(selection, 63, stdin);
        num = validateMenuSelection(selection, num, 3);
    }

    switch (num)
    {
    case 1:
        printf("Diary Entries");
        break;

    case 2:
        createEntry();
        break;

    case 3:
        exit(0);
        break;

    default:
        break;
    }
}

void accountMenu(void)
{
    char selection[64];
    int num = 0;
    int checkUser = checkUserExists();
    while (num == 0)
    {
        printf("%s\n", "1: Create Account");
        if (checkUser == 1)
        {
            printf("%s\n", "2: Login");
        }
        printf("%s\n", "0: Exit");
        fgets(selection, 63, stdin);
        num = validateMenuSelection(selection, num, 2);
        if (checkUser == 1 && num == 1)
        {
            printf("%s\n", "An account already exists!");
            num = 0;
        }
    }

    switch (num)
    {
    case 1:
        char name[20];
        char pw[20];
        printf("%s\n", "Enter new username:");
        fgets(name, 19, stdin);
        printf("%s\n", "Enter new password:");
        fgets(pw, 19, stdin);
        writeUserToFile(name, pw);
        break;
    case 2:
        int checkLog = 0;
        do
        {
            printf("%s\n", "Enter username:");
            fgets(name, 19, stdin);
            printf("%s\n", "Enter password:");
            fgets(pw, 19, stdin);
            checkLog = login(name, pw);
            if (checkLog == 1)
            {
                userName = name;
                mainMenu(name);
            }
            else
            {
                printf("%s\n", "Incorrect login details. Try again:");
            }
        } while (checkLog == 0);
        break;
    case 0:
        printf("Goodbye!");
        exit(0);
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    printf("%s\n", "---------------WELCOME TO DIARY BEE---------------");
    printf("\n");
    printf("%s\n", "           __         .' '.");
    printf("%s\n", "        _//__)        .   .       .");
    printf("%s\n", "       (8|)_}}- .      .        .");
    printf("%s\n", "        `\\__)   '. . ' ' .  . ");
    printf("\n");
    accountMenu();
}
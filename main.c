#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainMenu(void);
void login(void);
int validateMenuSelection(char[], int, int);

void mainMenu(void){
    printf("%s\n", "Main Menu");
    printf("%s\n", "1: Read");
    printf("%s\n", "2: Write");
    printf("%s\n", "3: Exit");
    int selection;

    switch (selection){
    case 1:
        printf("Diary Entries");
        break;

    case 2:
        printf("New Diary Entry");
        break;
    default:
        break;
    }
}

void login(void){
    char selection[64];
    int num = 0;

    while (num == 0){
        printf("%s\n", "1: Login");
        printf("%s\n", "2: Create Account");
        fgets(selection, 63, stdin);
        num = validateMenuSelection(selection, num, 2);
    }

    switch (num){
    case 1:
        printf("%s\n", "Enter username:");
        break;

    case 2:
        printf("Enter new username");
        break;
    default:
        break;
    }
}

int validateMenuSelection(char selection[], int num, int numSelections){
    if (strlen(selection) != 2){
        num = 0;
    }

    if (sscanf(selection, "%d", &num) != 1){
        num = 0;
    }

    if (num > numSelections || num < 1){
        num = 0;
    }

    if (num == 0){
        printf("%s\n", "Invalid input try again:\n");
    }
    return num;
}

int main(int argc, char *argv[]){
    printf("%s\n", "---------------WELCOME TO DIARY BEE---------------");
    printf("\n");
    printf("%s\n", "           __         .' '.");
    printf("%s\n", "        _//__)        .   .       .");
    printf("%s\n", "       (8|)_}}- .      .        .");
    printf("%s\n", "        `\\__)   '. . ' ' .  . ");
    printf("\n");
    login();
}
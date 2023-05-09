#include "PPMReader.h"
#include "huffman.h"
#include <stdio.h>

int main() {
    char filename[100];
    int choice = 0;
    while (choice != 3)
    {
        // Clear the console screen
        printf("\033[2J\033[1;1H");

        // Print the title
        printf("  _  _       __  __                    ___         _     \n");
        printf(" | || |_  _ / _|/ _|_ __  __ _ _ _    / __|___  __| |___ \n");
        printf(" | __ | || |  _|  _| '  \\/ _` | ' \\  | (__/ _ \\/ _` / -_)\n");
        printf(" |_||_|\\_,_|_| |_| |_|_|_\\__,_|_||_|  \\___\\___/\\__,_\\___|\n");

        // Print the menu options
        printf("\n\n");
        printf("\t\t\t1. Encode\n");
        printf("\t\t\t2. Decode\n");
        printf("\t\t\t3. Quit\n");

        // Wait for user input

        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        // Handle the user's choice
        switch (choice)
        {
        case 1:
            printf("\n\t\t\tWrite the file name : ");
            scanf("%s", &filename);
            printf("\t\t\tLoading...\n");
            Encode(filename);
            printf("\t\t\tEncode Finish, press any key to continue...");
            break;
        case 2:
            printf("\n\t\t\tWrite the file name : ");
            scanf("%s", &filename);
            printf("\t\t\tLoading...\n");
            Decode(filename);
            printf("\t\t\tDecode Finish, press any key to continue...");
            break;
        case 3:
            printf("\n\t\t\tPress any key to exit...");
            break;
        default:
            printf("\n\t\t\tInvalid choice.\n");
            break;
        }
        getchar();
        getchar();
    }
    return 0;
}


/*	Program		: main_huffman.cpp
	Deskripsi	: Driver / main program untuk ADT Huffman Code pada kompresi gambar
	Dibuat oleh :
                - Farhan Muhammad Lutfhi 	(221524039) 
                - Faris Abulkhoir 		    (221524040) 
                - Mahardika Pratama 		(221524044)
    Kelompok	: A1
	Kelas		: 1B
    Jurusan     : Teknik Komputer dan Informatika
    Prodi       : D4 Teknik Informatika
    Angkatan    : 2022/2023
	Tanggal		: 15 Mei 2023
	===============================================*/

#include "PPMReader.h"
#include "huffman.h"
#include <stdio.h>

int main()
{
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
        printf("\n");
        printf("Kompresi File Gambar Berformat PPM dengan Metode Huffman Coding\n");
        printf("\t\tPPM to TXT & TXT to PPM\n");
        printf("Oleh : Farhan Muhammad Luthfi, Faris Abulkhoir, Mahardika Pratama");
        printf("\n\tJurusan Teknik Komputer dan Informatika\n");
        printf("\t\tPoliteknik Negeri Bandung\n");
        printf("\t\t\tAngkatan 22\n");

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
            if (FILE *file = fopen(filename, "rb"))
            {
                fclose(file);
                printf("\t\t\tLoading...\n");
                Encode(filename);
                printf("\t\t\tEncode Finish, press any key to continue...");
            }
            else
            {
                printf("\n\t\t\tFile not found, press any key to continue...");
            }
            break;
        case 2:
            printf("\n\t\t\tWrite the file name : ");
            scanf("%s", &filename);
            if (FILE *file = fopen(filename, "rb"))
            {
                printf("\t\t\tLoading...\n");
                Decode(filename);
                printf("\t\t\tDecode Finish, press any key to continue...");
            }
            else
            {
                printf("\n\t\t\tFile not found, press any key to continue...");
            }
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

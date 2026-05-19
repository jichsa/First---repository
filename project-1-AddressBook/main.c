/*
  Description
  Name: JICHSA TOLLY
  Date: 11-12-2025
  Program: ADDRESSBOOK PROJECT 
*/
#include <stdio.h>
#include <unistd.h>
#include "contact.h"

int main() {
    int choice,sortcriteria;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:                
                printf("...........................................\n");
                printf(".       ENTERED INTO SEARCH CONTACT       .\n");
                printf("...........................................\n"); 
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook,sortcriteria);
                break;
            case 6:
                for(int i=0;i<100;i++)
                {
                printf("saving......>%d%%\r",i+1);
                fflush(stdout);
                usleep(5000);
                }
                saveContactsToFile(&addressBook);
                break;   
            case 7:
                for(int i=0;i<100;i++)
                {
                printf("EXITING---->%d%%\r",i+1);
                fflush(stdout);
                usleep(5000);
                }
                printf("\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}


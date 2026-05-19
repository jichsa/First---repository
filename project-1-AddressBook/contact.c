#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include  <ctype.h>

void listContacts(AddressBook *addressBook,int sortcriteria ) 
{
    /* Sort contacts based on the chosen criteria */

    printf("...........................................\n");
    printf(".        ENTERED INTO LIST CONTACT        .\n");
    printf("...........................................\n");
    int i,j; 

    do{
    printf("Sort Contact By:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice: ");
    scanf("%d",&sortcriteria);
    if(sortcriteria!=1 && sortcriteria!=2 && sortcriteria!=3)
    {
        printf("Invalid Choice\n");
    }
    }while(sortcriteria!=1 && sortcriteria!=2 && sortcriteria!=3);

    //Sorting based on Name using bubble sort 
    if(sortcriteria==1)
    {
        for(i=0;i<addressBook->contactCount-1;i++)
        {
        for(j=0;j<(addressBook->contactCount-1-i);j++)
        {
            int ret=strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);  
        if(ret>0)
        {
            Contact temp=addressBook->contacts[j];
            addressBook->contacts[j]=addressBook->contacts[j+1];
            addressBook->contacts[j+1]=temp;
        }
        }
        }
        printf(".............................................................\n");
        printf("NAME\t\t     PHONE NO\t\t  EMAIL  \n");
        printf(".............................................................\n");
        for(i=0;i<addressBook->contactCount;i++)
        {           
        printf("%-20s %-20s %-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }

    //Sorting of phone number based on bubble sort
    if(sortcriteria==2)
    {
        for(i=0;i<addressBook->contactCount-1;i++)
        {
        for(j=0;j<(addressBook->contactCount-1-i);j++)
        {
        int ret=strcasecmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
        if(ret>0)
        {
            Contact temp=addressBook->contacts[j];
            addressBook->contacts[j]=addressBook->contacts[j+1];
            addressBook->contacts[j+1]=temp;
        }
        }
        }
        printf(".............................................................\n");
        printf("NAME\t\t     PHONE NO\t\t  EMAIL  \n");
        printf(".............................................................\n");
        for(i=0;i<addressBook->contactCount;i++)
        {
            printf("%-20s %-20s %-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }

    //Sorting of email based on bubble sort
    if(sortcriteria==3)
    {
        for(i=0;i<addressBook->contactCount-1;i++)
        {
        for(j=0;j<(addressBook->contactCount-1-i);j++)
        {
        int ret=strcasecmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email);
        if(ret>0)
        {
            Contact temp=addressBook->contacts[j];
            addressBook->contacts[j]=addressBook->contacts[j+1];
            addressBook->contacts[j+1]=temp;
        }
        }
        }
        printf(".............................................................\n");
        printf("NAME\t\t     PHONE NO\t\t  EMAIL  \n");
        printf(".............................................................\n");
        for(i=0;i<addressBook->contactCount;i++)
        {
        printf("%-20s %-20s %-20s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
    }    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int valid_name(char *s)
{
    //check name is valid
    int i=0;
    while(s[i])
    {
        if( !(isalpha(s[i]) || s[i]==' ' || s[i] =='.' ) )    //checks if the name has only alphabets,space,dot 
        {
        return 0;
        }
    i++;
    }
    return 1;  
}

int valid_phone(char*s)
{   
    //checks if phone number is valid
    int len=strlen(s);
    if(len!=10)
    {     
    return 0;   
    }    
    int i=0;
    while(s[i])
    {
        if( !(s[i]>='0' && s[i]<='9') )   //phone number must be 10 digits
        {
        return 0;
        }        
    i++;
    }return 1;   
}

int valid_email(char *s)
{ 
    //checks if email is valid    
    if (!strchr(s, '@')) 
    return 0;

    if (!strstr(s, ".com")) 
    return 0;
    
    if (strchr(s, ' ')) 
    return 0;

    //  Only alphanumeric + '@' + '.'
    for (int i = 0; s[i]; i++) 
    {
        if (!(isalnum(s[i]) || s[i] == '@' || s[i] == '.'))
        {
            return 0;
        }
    }

    return 1; 

}

int previously_present_phone(AddressBook *addressBook,char *string_phone)
{
    //Checking if the phone number is previously present
    for(int i=0;i<addressBook->contactCount;i++)
    {
      int ret=strcmp(addressBook->contacts[i].phone,string_phone);
      if(ret==0)
      {
        return 1;
      }      
    }return 0;
}

int previously_present_email(AddressBook *addressBook,char *string_email)
{
    //Checking if the email is previously present
    for(int i=0;i<addressBook->contactCount;i++)
    {
      int ret=strcmp(addressBook->contacts[i].email,string_email);
      if(ret==0)
      {
        return 1;
      }      
    }return 0;
}

void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    printf("...........................................\n");
    printf(".       ENTERED INTO CREATE CONTACT       .\n");
    printf("...........................................\n");  
    
    char string_name[50]; 
    char string_phone[20];
    char string_email[50];

    do{ 
        printf("Enter the Name: \n");
        getchar();
        scanf(" %[^\n]",string_name);
        if(!valid_name(string_name))
        {
        printf("Invalid Name\n");                  
        }
    }while(!valid_name(string_name));   //checks if the name is valid
    
    do{      
        printf("Enter Phone number: \n");
        getchar();
        scanf(" %[^\n]",string_phone);
        if(!valid_phone(string_phone))
        {
        printf("Invalid Phone number\n");
        }
        if(previously_present_phone(addressBook,string_phone))
        {
        printf("Phone number previously present\n");
        }
        //checks if phone number is valid and not previously present
    }while(!valid_phone(string_phone) || previously_present_phone(addressBook,string_phone)); 

    do{
        printf("Enter the Email: \n");
        getchar();
        scanf(" %[^\n]",string_email);
        if(!valid_email(string_email))
        {
        printf("Invalid Email\n");
        }
        if(previously_present_email(addressBook,string_email))
        {
        printf("Email previously present\n");
        }
        //checks if email is valid and not previously present     
    }while(!valid_email(string_email) || previously_present_email(addressBook,string_email)); 

    //if name,phone,email valid then store the data
    strcpy(addressBook->contacts[addressBook->contactCount].name,string_name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,string_phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,string_email); 
    
    addressBook->contactCount++;  //increase the contactcount
}
int searchContact(AddressBook *addressBook) 
{
        /* Define the logic for search */

        int choice;
        int dup_count=0;
        int i;
        int index;
        int option;
        int arr[addressBook->contactCount];    
        do
        {        
        printf("Search Contact By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            printf("Enter the Name: \n");
            break;

            case 2:
            printf("Enter Phone number: \n");
            break;

            case 3:
            printf("Enter the Email: \n");
            break;

            default:
            printf("Enter a valid number.\nplease try again.\n");
            break;
        }
        }while(choice!=1 && choice!=2 && choice!=3);
        
        //search contact by name
        if(choice==1)
        {            
            char string_name[100];
            getchar();
            scanf(" %[^\n]",string_name);      

            for(i=0;i<addressBook->contactCount;i++)
            {
                //condition to check if the name present in contacts
                char *ptr=strcasestr(addressBook->contacts[i].name,string_name); 
                if(ptr!=NULL)
                {            
                printf("%d. %s\t%s\t%s\n",dup_count+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                arr[dup_count]=i;   //if condition true store i value in an array
                dup_count++;
                }               
            } 
            if(dup_count==0)
            {
                printf("..........................\n");
                printf(".   CONTACT NOT FOUND    .\n");
                printf("..........................\n");
                return -1;
            }
            else if(dup_count==1)
            {   
                //condition if duplicate names are not present
                index=arr[0];   
                return index;
            }
            else
            {   
                //condition if duplicate names are present 
                printf("Enter your choice: ");
                scanf("%d",&option);
                index=arr[option-1];
                printf("1. %s\t%s\t%s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                return index;
            }
        }
        //search contact by phone number
        if(choice==2)
        {   
            char string_phone[100];
            getchar();
            scanf(" %[^\n]",string_phone);

            // check exact phone number present then print the contact
            for(i=0;i<addressBook->contactCount;i++)
            {
                int ret=strcmp(addressBook->contacts[i].phone,string_phone); 
                if(ret==0)
                {
                printf("1. %s\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                index=i;
                dup_count++;
                return index;                    
                }               
            }
            //condition if contact not found
            if(dup_count==0)
            {
                printf("...........................\n");
                printf(".    CONTACT NOT FOUND    .\n");
                printf("...........................\n");
                return -1;
            }
        }
        if(choice==3)
        {   
            //search contact by email
            char string_email[100];
            getchar();
            scanf(" %[^\n]",string_email);
            //check if the exact email is present
            for(i=0;i<addressBook->contactCount;i++)
            {
                int ret=strcmp(addressBook->contacts[i].email,string_email); 
                if(ret==0)
                {
                printf("1. %s\t%s\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                index=i;
                dup_count++;
                return index;
                }               
            }        
            if(dup_count==0)
            {
                printf("...........................\n");
                printf(".    CONTACT NOT FOUND    .\n");
                printf("...........................\n");
                return -1;
            }
        }
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    int choice;
    int option=searchContact(addressBook); //calling search function to edit the contact

    //if contact not found
    if (option==-1)     
    {
        printf("\n");
        printf("EDITING TERMINATED\n");
    }
    else
    {
        printf("...........................................\n");
        printf(".        ENTERED INTO EDIT CONTACT        .\n");
        printf("...........................................\n"); 

        printf("Edit Contact By:\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);    
       
        if(choice==1)  //condition for editing name
        { 
            char string_name[50];
            do{
                printf("Enter the new Name: ");
                getchar();
                scanf(" %[^\n]",string_name);
                if(!valid_name(string_name))  //checks if the contact name is valid
                {
                printf("Invalid name\n");
                }        
            }while(!valid_name(string_name));

            strcpy(addressBook->contacts[option].name,string_name); //if valid name then edit the contact
        }
        if(choice==2) //editing using phone number
        {   
            char string_phone[20];
            do{   
                printf("Enter the new Phone Number: ");
                getchar();
                scanf(" %[^\n]",string_phone);
                if(!valid_phone(string_phone))
                {
                printf("Invalid number\n");
                }
                if(previously_present_phone(addressBook,string_phone))
                {
                printf("Phone Number is previously present\n");
                }
                //checks till the phone number is valid and not present previously
            }while(!valid_phone(string_phone) || previously_present_phone(addressBook,string_phone));  

            strcpy(addressBook->contacts[option].phone,string_phone); //edit the phone number by copying the phone to contacts
        }        
        if(choice==3)  //edit using email
        {  
            char string_email[50];
            do{
                printf("Enter new Email: ");
                getchar();
                scanf(" %[^\n]",string_email);
                if(!valid_email(string_email))
                {
                printf("Invalid Email\n");
                }  
                if(previously_present_email(addressBook,string_email))
                {
                printf("Email is previously present\n");
                } 
                //checks the email is valid and not previously present 
            }while(!valid_email(string_email) || previously_present_email(addressBook,string_email)); 

            strcpy(addressBook->contacts[option].email,string_email);     //editing the email
        }
    }
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice;
    char ch;
    printf("...........................................\n");
    printf(".       ENTERED INTO DELETE CONTACT       .\n");
    printf("...........................................\n"); 

    int option=searchContact(addressBook);  //calling search function

    if (option==-1) //if the contact not found
    {
        printf("\n");
        printf("DELETING TERMINATED\n");
    }
    else
    {
        printf("Do you want to delete this contact,Y/N?: \n"); //asking for reconfirmation
        scanf(" %c",&ch);   

        if(ch=='N' || ch=='n') 
        {
            printf("\n");
            printf("DELETING TERMINATED\n");
        }
        else if(ch=='y'||ch=='Y')
        {    
            for(int i=option;i<addressBook->contactCount;i++)
            {
                addressBook->contacts[i]=addressBook->contacts[i+1]; //overwriting the contact with the next contact
            }        
            addressBook->contactCount--; // decrement the count
        }
        else
        {
            printf("Invalid input\n");
            printf("Please try again\n"); //if other charaters given
        }     
    }    
}
    


    



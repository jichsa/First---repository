#include <stdio.h>
#include "file.h"
#include <unistd.h>

void saveContactsToFile(AddressBook *addressBook)
 {
    FILE*fp;
    if((fp=fopen("contact.csv","w"))==NULL)  // file open in write 
    {
        fprintf(stderr,"File not found\n");
        return ;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name, 
                                addressBook->contacts[i].phone,
                                addressBook->contacts[i].email); 
    }  
    fclose(fp);  // file close
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE*fp;
    if((fp=fopen("contact.csv","r"))==NULL) 
    {
        fprintf(stderr,"File not found\n");
        return ;
    }
    while((fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->contactCount].name,
                                            addressBook->contacts[addressBook->contactCount].phone,
                                            addressBook->contacts[addressBook->contactCount].email))==3) 
                                            //scan the contacts for 3 details
    {
        addressBook->contactCount++;
    }
    fclose(fp); //file close
}

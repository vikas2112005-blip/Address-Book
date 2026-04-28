#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  FILE *fp=fopen("contact.txt","w");
  fprintf(fp,"#%d\n",addressBook->contactCount);
  for(int i=0;i<addressBook->contactCount;i++){
    fprintf(fp,"%-10d %s,%s,%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }
  fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) {
    int sl;
    FILE *fp=fopen("contact.txt","r");
    fscanf(fp,"#%d\n",&addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++){
    fscanf(fp,"%d %[^,],%[^,],%[^\n]",&sl,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
}

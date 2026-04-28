#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
// #include "populate.h"
int arr[100]; 
int mapcount = 0;   

void listContacts(AddressBook *addressBook) // Displays all contacts in a formatted table
{   printf("\n-----------------------------------------------------------------\n");
    printf("%-5s %-20s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------------\n");
    
    for(int i = 0; i < addressBook->contactCount; i++)
   
       {
        printf("%-5d %-20s %-15s %-30s\n",
               i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    printf("-----------------------------------------------------------------\n");
    }

void printcontact(int s,Contact *c) //Prints a searched contacts with serial number
{
     printf("%d. Name: %s | Phone: %s | Email: %s\n",s+1,c->name,c->phone,c->email);
}

void initialize(AddressBook *addressBook) // Initializes address book and loads contacts from file
{
    addressBook->contactCount = 0;
    
    
    loadContactsFromFile(addressBook);
}

// void saveAndExit(AddressBook *addressBook) {
//     saveContactsToFile(addressBook); // Save contacts to file
//     exit(EXIT_SUCCESS); // Exit the program
// }
int isvalidname(char *name)// Validates that name contains only alphabets and spaces
{
    if(strlen(name)<4)
    {
         printf("Error: Name must contain at least 4 characters\n");
        return 0;
    }
    for(int i = 0; i < strlen(name); i++)
    {
        if(!isalpha(name[i]))
        {
            printf("Error: Name should contain only alphabets (A-Z, a-z)\n");
            return 0;
        }
    }
   return 1;
}
int isvalidphone(char *phone)// Validates phone number (10 digits, starts with 6-9)
{
    int len=strlen(phone);
    if(len!=10)
    {printf("ERROR:phone number must be 10 digits");
     return 0;
    }

    if(phone[0]<'6'||phone[0]>'9'){
     printf("Error: First digit must be between 6 and 9\n");
    return 0;
    }
    for(int i=0;i<len;i++){
        if(phone[i] >= '0' && phone[i] <= '9')
            continue;

        if((phone[i] >= 'A' && phone[i] <= 'Z') || (phone[i] >= 'a' && phone[i] <= 'z'))
        {printf("Error: Alphabets are not allowed in phone number\n");
            return 0;
        }
        else
        {printf("Error: Symbols are not allowed in phone number\n");
            return 0;
        }
    }
    return 1;
}    
int isphoneunique(char *phone, AddressBook *addressBook)// Checks if the phone number is unique in address book
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {if(strcmp(phone, addressBook->contacts[i].phone) == 0)
       return 0;
    }
    return 1;
}

int isvalidemail(char*email)// Validates email format (single '@', ends with .com)
{
     int len = strlen(email);
    int at_count = 0, dot_count = 0;
    int at_index = -1, last_dot = -1;

    for(int i = 0; i < len; i++)
    {
        if(email[i] == '@')
        {
            at_count++;
            at_index = i;
        }
        else if(email[i] == '.')
        {
            dot_count++;
            last_dot = i;
        }
        else if(!isalnum(email[i]))
        {
            printf("Error: Invalid symbol in email\n");
            return 0;
        }
    }

    if(at_count == 0)
    {
        printf("Error: Missing '@' symbol\n");
        return 0;
    }
    if(at_count > 1)
    {
        printf("Error: Multiple '@' symbols are not allowed\n");
        return 0;
    }

    if(dot_count == 0)
    {
        printf("Error: Email must contain at least one '.'\n");
        return 0;
    }

    if(last_dot < at_index)
    {
        printf("Error: '.' must appear after '@'\n");
        return 0;
    }

    if(last_dot == at_index + 1)
    {
        printf("Error: Domain missing between '@' and '.'\n");
        return 0;
    }

    for(int i = at_index + 1; i < last_dot; i++)
    {
        if(!isalnum(email[i]))
        {
            printf("Error: Domain must contain only alphabets or digits\n");
            return 0;
        }
    }

    for(int i = last_dot + 1; i < len; i++)
    {
        if(!isalpha(email[i]))
        {
            printf("Error: Only alphabets allowed after final '.'\n");
            return 0;
        }
    }

return 1;
}
int isphoneexist(AddressBook *addressBook,char *phone)// Checks if given phone number already exists
{
for (int i = 0; i < addressBook->contactCount; i++) {
    if (strcmp(addressBook->contacts[i].phone,phone) == 0) {   
        return 1;
    }
}
  return 0;
}
int isemailexist(AddressBook *addressBook,char *email)// Checks if given email already exists
{
for (int i = 0; i < addressBook->contactCount; i++) {
    if (strcmp(addressBook->contacts[i].email,email) == 0) {   
        return 1;
    }
}
  return 0;
}
void createContact(AddressBook *addressBook)// Creates a new contact with validation and adds to address book
{   Contact newcontact;
    int attempts;
    attempts=0;
    while(attempts<3){
    printf("Enter the Name: ");
    scanf(" %[^\n]",newcontact.name);
    if(isvalidname(newcontact.name))
    break;

    attempts++;
    }
    if(attempts==3){
        printf("Too many invalid attempts.creation cancelled\n");
        return;
    }

    attempts=0;
    while(attempts<3){
    printf("Enter phone number: ");
    scanf("%s",newcontact.phone);
    if(!(isvalidphone(newcontact.phone)))
    {printf("Invalid phone format!\n");
    }
    else if(!isphoneunique(newcontact.phone, addressBook))
    {printf("phone already exists!\n");
    }
    else
    {break; 
    }
      attempts++;
     }
    if(attempts==3){
        printf("Too many invalid attempts.creation cancelled\n");
        return;
    }

    attempts=0;
    while(attempts<3){
    printf("Enter the email: ");
    scanf("%s",newcontact.email);
    if(isvalidemail(newcontact.email))
    break;

    printf("Invalid email!\n");
    attempts++;
    }
    if(attempts==3){
        printf("Too many invalid attempts.creation cancelled\n");
        return;
    }

    addressBook->contacts[addressBook->contactCount]=newcontact;
    addressBook->contactCount++;

    printf("Contact added successfully!\n");
    
};

void searchContact(AddressBook *addressBook) // Displays search menu and calls respective search function
{ 
    printf("1.search by name.\n");
    printf("2.search by phone no.\n");
    printf("3.search by email.\n");
    printf("4.exit!\n");
    int choice;
    printf("Enter the choice:");
    if(scanf("%d", &choice)!=1)
     {printf("Invalid input! Enter the number\n");
        while(getchar()!='\n');
        return;
    }

    switch(choice)
    {
        case 1:
            searchbyname(addressBook);
            break;
        case 2:
            searchbyphone(addressBook);
            break;
        case 3:
            searchbyemail(addressBook);
            break;
        case 4:
            return;

        default:
            printf("Invalid choice!\n");

    }
}

void searchbyname(AddressBook *addressBook)// Searches contacts by name and stores matching indices
{
    char name[50];
    int attempts = 0;
    mapcount = 0;  

    while(attempts < 3)
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", name);

        if(isvalidname(name))
            break;

        printf("Invalid name!\n");
        attempts++;
    }

    if(attempts == 3)
        return;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(name, addressBook->contacts[i].name) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            arr[mapcount] = i;
            mapcount++;
        }
    }

    if(mapcount == 0)
        printf("Contact not found!\n");
}
void searchbyphone(AddressBook *addressBook)// Searches contacts by phone number and stores matching indices
{
    char phone[20];
    int attempts = 0;
    mapcount = 0;  

    while(attempts < 3)
    {
        printf("Enter phone no: ");
        scanf(" %[^\n]", phone);

        if(isvalidphone(phone))
            break;

        printf("Invalid phone no!\n");
        attempts++;
    }

    if(attempts == 3)
        return;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            arr[mapcount] = i;
            mapcount++;
        }
    }

    if(mapcount == 0)
        printf("Contact not found!\n");
}
void searchbyemail(AddressBook *addressBook)// Searches contacts by email and stores matching indices
{
    char email[50];
    int attempts = 0;
    mapcount = 0;  

    while(attempts < 3)
    {
        printf("Enter email: ");
        scanf(" %[^\n]",email);

        if(isvalidemail(email))
            break;

        printf("Invalid email!\n");
        attempts++;
    }

    if(attempts == 3)
        return;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(email, addressBook->contacts[i].email) == 0)
        {
            printcontact(mapcount, &addressBook->contacts[i]);
            arr[mapcount] = i;
            mapcount++;
        }
    }

    if(mapcount == 0)
        printf("Contact not found!\n");
}
void editContact(AddressBook *addressBook)// Edits selected contact details (name, phone, or email)
{
    searchContact(addressBook);
    if(mapcount==0)
    return; 
    int attempts=0;
    int serial;
    while(attempts<3){
    printf("Enter serial number to edit: ");
       if(scanf("%d", &serial) != 1)
        {
            printf("Invalid input!\n");
            while(getchar() != '\n');
            attempts++;
            continue;
        }

        if(serial >= 1 && serial <= mapcount)
            break;

        printf("Invalid selection!\n");
        attempts++;
    }
    if(attempts == 3)
    {
        printf("Too many invalid attempts!\n");
        return;
    }
    int index = arr[serial - 1];
    int choice;
    while(1){
    printf("\nEdit Menu:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    if(scanf("%d", &choice)!=1)
     {printf("Invalid input! Enter the number\n");
        while(getchar()!='\n');
        continue;
    }
    break;
}
   attempts=0;

   switch(choice)
   {
    case 1:{
        char name[50];
            while(attempts < 3)
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", name);

                if(isvalidname(name))
                {
                    strcpy(addressBook->contacts[index].name, name);
                    printf("Name updated successfully!\n");
                    return;
                }
                printf("Invalid name!\n");
                attempts++;
            }
            break;
    }
    case 2:{
        char phone[20];
        while(attempts<3)
        {
            printf("enter new phone no: ");
            scanf("%s",phone);
            if(isvalidphone(phone))
            { if(isphoneexist(addressBook,phone))
                {
                    printf("phone no exist already!");
                    return;
                }else{
                strcpy(addressBook->contacts[index].phone,phone);
                printf("phone no is updated successfully\n");
                return;}

            }
            printf("invalid phone no!\n");
            attempts++;
        }
        break;
    }
    case 3:{
        char email[50];
            while(attempts < 3)
            {
                printf("Enter new email: ");
                scanf("%s", email);

                if(isvalidemail(email))
                {if(isemailexist(addressBook,email))
                    {
                      printf("email exist already!");
                      return;
                    }else{
                    strcpy(addressBook->contacts[index].email, email);
                    printf("Email updated successfully!\n");
                    return;
                    }
                }
                printf("Invalid email!\n");
                attempts++;
            }
            break;
    }
    case 4:
       return;

    default:
     printf("Invalid choice!\n");
      return;
   }
    printf("Too many invalid attempts!\n");
    
}

void deleteContact(AddressBook *addressBook)// Deletes selected contact from address book
{
	searchContact(addressBook);
    if(mapcount==0)
    return;

    int serial,attempts=0;
    while(attempts<3){
        printf("enter the serial number to delete: ");
        if(scanf("%d", &serial) != 1)
        {
            printf("Invalid input!\n");
            while(getchar() != '\n');
            attempts++;
            continue;
        }
        if(serial >= 1 && serial <= mapcount)
            break;

        printf("Invalid selection!\n");
        attempts++;
    }
    if(attempts == 3)
    {
        printf("Too many invalid attempts!\n");
        return;
    }

    int index = arr[serial - 1];  
    for(int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully!\n");
   
}

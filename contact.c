#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"


/* ---------- NAME VALIDATION ---------- */

int validateName(char name[])
{
    int i = 0;

    if (name[0] == '\0')
        return 0;

    while (name[i] != '\0')
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') ||
              (name[i] >= 'a' && name[i] <= 'z') ||
              name[i] == ' '))
        {
            return 0;
        }

        i++;
    }

    return 1;
}


/* ---------- PHONE VALIDATION ---------- */

int validatePhone(char phone[])
{
    int i = 0;

    /* First digit must be 6, 7, 8 or 9 */
    if (phone[0] < '6' || phone[0] > '9')
        return 0;

    while (phone[i] != '\0')
    {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;

        i++;
    }

    /* Exactly 10 digits */
    if (i != 10)
        return 0;

    return 1;
}


/* ---------- EMAIL VALIDATION ---------- */

int validateEmail(char email[])
{
    int i;
    int at_count = 0;
    int at_position = -1;
    int length = strlen(email);

    /* Check spaces and @ */
    for (i = 0; i < length; i++)
    {
        if (email[i] == ' ')
            return 0;

        if (email[i] == '@')
        {
            at_count++;
            at_position = i;
        }
    }

    /* Exactly one @ */
    if (at_count != 1)
        return 0;

    /* First character cannot be @ */
    if (at_position == 0)
        return 0;

    /* Must have something between @ and .com */
    if (at_position + 1 >= length - 4)
        return 0;

    /* Must end with .com */
    if (strcmp(&email[length - 4], ".com") != 0)
        return 0;

    return 1;
}


/* ---------- CREATE CONTACT ---------- */

void createContact(AddressBook *addressBook)
{
    Contact *contact =
        &addressBook->contacts[addressBook->contactCount];

    /* NAME */

    while (1)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]", contact->name);

        if (validateName(contact->name))
            break;

        printf("Invalid name. Please re-enter.\n");
    }


    /* PHONE */

    while (1)
    {
        printf("Enter the phone number: ");
        scanf("%19s", contact->phone);

        if (validatePhone(contact->phone))
            break;

        printf("Invalid phone number. Please re-enter.\n");
    }


    /* EMAIL */

    while (1)
    {
        printf("Enter the email: ");
        scanf("%49s", contact->email);

        if (validateEmail(contact->email))
            break;

        printf("Invalid email. Please re-enter.\n");
    }


    addressBook->contactCount++;

    printf("\nContact added successfully!\n");
}


/* ---------- LOWERCASE ---------- */

char toLower(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return ch + 32;

    return ch;
}


/* ---------- SUBSTRING SEARCH ---------- */

int substring(char str[], char sub[])
{
    int i, j;

    for (i = 0; str[i] != '\0'; i++)
    {
        for (j = 0; sub[j] != '\0'; j++)
        {
            if (str[i + j] == '\0')
                break;

            if (toLower(str[i + j]) != toLower(sub[j]))
                break;
        }

        if (sub[j] == '\0')
            return 1;
    }

    return 0;
}


/* ---------- SEARCH CONTACT ---------- */

void searchContact(AddressBook *addressBook)
{
    char search[50];
    int i;
    int found = 0;

    printf("Enter name to search: ");
    scanf(" %[^\n]", search);

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (substring(addressBook->contacts[i].name, search))
        {
            printf("\nName  : %s",
                   addressBook->contacts[i].name);

            printf("\nPhone : %s",
                   addressBook->contacts[i].phone);

            printf("\nEmail : %s\n",
                   addressBook->contacts[i].email);

            found = 1;
        }
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }
}


/* ---------- LIST / SORT CONTACTS ---------- */

void listContacts(AddressBook *addressBook, int sortCriteria)
{
    int i, j;
    Contact temp;

    /* Sorting */

    for (i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (j = i + 1;
             j < addressBook->contactCount;
             j++)
        {
            /* Sort by NAME */

            if (sortCriteria == 1)
            {
                if (strcmp(addressBook->contacts[i].name,
                           addressBook->contacts[j].name) > 0)
                {
                    temp = addressBook->contacts[i];

                    addressBook->contacts[i] =
                        addressBook->contacts[j];

                    addressBook->contacts[j] = temp;
                }
            }


            /* Sort by PHONE */

            else if (sortCriteria == 2)
            {
                if (strcmp(addressBook->contacts[i].phone,
                           addressBook->contacts[j].phone) > 0)
                {
                    temp = addressBook->contacts[i];

                    addressBook->contacts[i] =
                        addressBook->contacts[j];

                    addressBook->contacts[j] = temp;
                }
            }


            /* Sort by EMAIL */

            else if (sortCriteria == 3)
            {
                if (strcmp(addressBook->contacts[i].email,
                           addressBook->contacts[j].email) > 0)
                {
                    temp = addressBook->contacts[i];

                    addressBook->contacts[i] =
                        addressBook->contacts[j];

                    addressBook->contacts[j] = temp;
                }
            }
        }
    }


    /* Display contacts */

    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("\nName  : %s",
               addressBook->contacts[i].name);

        printf("\nPhone : %s",
               addressBook->contacts[i].phone);

        printf("\nEmail : %s\n",
               addressBook->contacts[i].email);
    }
}


/* ---------- INITIALIZE ---------- */

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file during initialization
    // loadContactsFromFile(addressBook);
}


/* ---------- SAVE AND EXIT ---------- */

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);

    exit(EXIT_SUCCESS);
}


/* ---------- EDIT CONTACT ---------- */

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
}


/* ---------- DELETE CONTACT ---------- */

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
}
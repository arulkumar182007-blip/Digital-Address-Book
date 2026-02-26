#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Contact {
    char name[50];
    char phone[15];
    char email[50];
    char address[100];
};

struct Contact contacts[MAX];
int count = 0;

// Function to load contacts from file
void loadFromFile() {
    FILE *fp = fopen("addressbook.txt", "r");
    if (fp == NULL) return;

    while (fread(&contacts[count], sizeof(struct Contact), 1, fp)) {
        count++;
    }
    fclose(fp);
}

// Function to save contacts to file
void saveToFile() {
    FILE *fp = fopen("addressbook.txt", "w");
    if (fp == NULL) {
        printf("Error saving file!\n");
        return;
    }

    fwrite(contacts, sizeof(struct Contact), count, fp);
    fclose(fp);
}

// Add new contact
void addContact() {
    if (count >= MAX) {
        printf("Address book is full!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", contacts[count].name);

    printf("Enter Phone: ");
    scanf(" %[^\n]", contacts[count].phone);

    printf("Enter Email: ");
    scanf(" %[^\n]", contacts[count].email);

    printf("Enter Address: ");
    scanf(" %[^\n]", contacts[count].address);

    count++;
    saveToFile();
    printf("Contact added successfully!\n");
}

// View all contacts
void viewContacts() {
    if (count == 0) {
        printf("No contacts found!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("\nContact %d\n", i + 1);
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
        printf("Address: %s\n", contacts[i].address);
    }
}

// Search contact by name
void searchContact() {
    char searchName[50];
    int found = 0;

    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, searchName) == 0) {
            printf("\nContact Found:\n");
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Email: %s\n", contacts[i].email);
            printf("Address: %s\n", contacts[i].address);
            found = 1;
        }
    }

    if (!found)
        printf("Contact not found!\n");
}

// Delete contact
void deleteContact() {
    char deleteName[50];
    int found = 0;

    printf("Enter name to delete: ");
    scanf(" %[^\n]", deleteName);

    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, deleteName) == 0) {
            for (int j = i; j < count - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            count--;
            saveToFile();
            printf("Contact deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Contact not found!\n");
}

// Main function
int main() {
    int choice;

    loadFromFile();

    do {
        printf("\n==== Digital Address Book ====\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
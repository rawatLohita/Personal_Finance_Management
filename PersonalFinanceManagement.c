#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_RECORDS 100
#define MAX_DESC 50
#define USERNAME "user"
#define PASSWORD "pass"

int income = 0;
int balance = 0;
int record_count = 0;

int authenticate();

typedef struct {
    char description[MAX_DESC];
    float amount;
    char date[11]; // Format: YYYY-MM-DD
} Record;

Record records[MAX_RECORDS];

void add_income(){
    printf("Enter monthly income: ");
    scanf("%d", &income);
    balance = income;  // Set balance equal to income when adding it
}

void add_transaction(){
    if (record_count >= MAX_RECORDS) {
        printf("Record limit reached.\n");
        return;
    }

    printf("Enter description: ");
    getchar();  // to consume the newline from previous input
    fgets(records[record_count].description, MAX_DESC, stdin);  // to allow spaces in the description
    records[record_count].description[strcspn(records[record_count].description, "\n")] = 0;  // Remove the newline

    printf("Enter amount: ");
    scanf("%f", &records[record_count].amount);

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", records[record_count].date);

    record_count++;
    printf("Transaction added successfully\n");
}

void view_transaction(){
    if (record_count == 0) {
        printf("No records to display.\n");
        return;
    }
    printf("\nFinancial Records:\n");
    for (int i = 0; i < record_count; i++) {
        printf("Record %d: %s, Amount: %.2f, Date: %s\n",
               i + 1, records[i].description, records[i].amount, records[i].date);
    }
}
void total_balance(){
    float total_balance = income;  // Start with income

    // Subtract all transactions from the balance
    for (int i = 0; i < record_count; i++) {
        total_balance -= records[i].amount;
    }

    printf("Total balance: %.2f\n", total_balance);
}



void delete_records(){
    if (record_count == 0) {
        printf("No records to delete.\n");
        return;
    }

    int index;
    printf("Enter record number to delete: ");
    scanf("%d", &index);
    if (index < 1 || index > record_count) {
        printf("Invalid record number.\n");
        return;
    }

    for (int i = index - 1; i < record_count - 1; i++) {
        records[i] = records[i + 1];
    }
    record_count--;
    printf("Record deleted successfully\n");
}

void save_records(){
    FILE *fptr;
    fptr = fopen("records.txt", "w");
    if (fptr == NULL) {
        printf("Error saving records\n");
        return;
    }

    for (int i = 0; i < record_count; i++) {
        fprintf(fptr, "%s %.2f %s\n", records[i].description, records[i].amount, records[i].date);
    }

    fclose(fptr);
    printf("Records saved successfully\n");
}

void load_records(){
    FILE *fptr;
    fptr = fopen("records.txt", "r");
    if (fptr == NULL) {
        printf("Error loading records.\n");
        return;
    }

    while (fscanf(fptr, " %[^\n]s %f %s",
                   records[record_count].description,
                   &records[record_count].amount,
                   records[record_count].date) != EOF) {
        record_count++;
    }

    fclose(fptr);
    printf("Records loaded successfully\n");
}

void showmenu(){
    printf("\nPersonal Finance Management System\n");
    printf("1. Add Income\n");
    printf("2. Add Transaction\n");
    printf("3. View Transaction\n");
    printf("4. View Total Balance\n");
    printf("5. Delete Records\n");
    printf("6. Save Records To File\n");
    printf("7. Load Records From File\n");
    printf("8. Exit\n");
}

int authenticate(){
    char username[50];
    char password[50];

    // Prompt for username
    printf("Enter username: ");
    scanf("%s", username);

    // Prompt for password
    printf("Enter password: ");
    scanf("%s", password);

    // Check username and password
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main(){
    if (!authenticate()) {
        printf("Authentication failed\n");
        return 1;
    }

    load_records();  // Load records at the start

    int choice = 0;
    while (choice != 8) {
        showmenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_income();
                break;
            case 2:
                add_transaction();
                break;
            case 3:
                view_transaction();
                break;
            case 4:
                total_balance();
                break;
            case 5:
                delete_records();
                break;
            case 6:
                save_records();
                break;
            case 7:
                load_records();
                break;
            case 8:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
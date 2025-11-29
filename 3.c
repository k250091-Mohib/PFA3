#include<stdio.h>
#include<string.h>
struct Employee
{
    int id;
    char name[20];
    char designation[20];
    float salary;
};

void displayEmployees(int n, struct Employee employees[]);
void searchemployee(int n, struct Employee employees[]);
void findHighestSalary(int n, struct Employee employees[]);
void bonus(int n, struct Employee employees[]);

int main() {
    printf("Enter the number of employees: ");
    int n;
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid Number of Employees\n");
        return 0;
    }  
    struct Employee employees[n];
    
    for (int i = 0; i < n; i++) {
        printf("Employee %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Name: ");
        getchar();
        fgets(employees[i].name, 20, stdin);
        employees[i].name[strcspn(employees[i].name, "\n")] = 0;
        printf("Designation: ");
        fgets(employees[i].designation, 20, stdin);
        employees[i].designation[strcspn(employees[i].designation, "\n")] = 0;
        printf("Salary: ");
        scanf("%f", &employees[i].salary);
    }
    
    while (1) {
        int choice;
        printf("\nMenu\n");
        printf("1. Display Employees\n");
        printf("2. Search for a Employee\n");
        printf("3. Find Highest Salary\n");
        printf("4. Give Bonus\n");
        printf("5. Exit\n");
        printf("Enter a choice from the menu: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: displayEmployees(n, employees); break;
            case 2: searchemployee(n, employees); break;
            case 3: findHighestSalary(n, employees); break;
            case 4: bonus(n, employees); break;
            case 5: printf("Exiting.....\n"); return 0;
            default: printf("Invalid Input.\n"); break;
        }
    }
}

void displayEmployees(int n, struct Employee employees[]) {
    printf("\nEmployee Records:\n");
    printf("ID\tName\t\tDesignation\tSalary\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%-10s\t%-10s\t%.2f\n",employees[i].id,employees[i].name,employees[i].designation,employees[i].salary);
    }
}

void searchemployee(int n, struct Employee employees[]) {
    char choice;
    int found = 0;
    printf("Do you want to search for an employee by ID or Name?\n");
    printf("Enter 'I' for ID 'N' for Name: ");
    getchar();
    scanf("%c", &choice);
    if (choice == 'I' || choice == 'i') {
        int id;
        printf("Enter ID to search for: ");
        scanf("%d", &id);
        for (int i = 0; i < n; i++) {
            if (id == employees[i].id) {
                found = 1;
                printf("Found: ID: %d, Name: %s, Designation: %s, Salary: %.2f\n",employees[i].id,employees[i].name,employees[i].designation,employees[i].salary);
                break;
            }
        }
        if (!found) {
            printf("Employee with ID %d not found.\n", id);
        }
    }
    else if (choice == 'N' || choice == 'n') {
        char name[20];
        printf("Enter the name of the employee you want to search for: ");
        getchar();
        fgets(name, 20, stdin);
        name[strcspn(name, "\n")] = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(name, employees[i].name) == 0) {
                found = 1;
                printf("Found: ID: %d, Name: %s, Designation: %s, Salary: %.2f\n",employees[i].id,employees[i].name,employees[i].designation,employees[i].salary);
                break;
            }
        }
        if (!found) {
            printf("Employee with name '%s' not found.\n", name);
        }
    }
    else {
        printf("Invalid Input.\n");
    }
}

void findHighestSalary(int n, struct Employee employees[]) {
    if (n == 0) {
        printf("No employees found.\n");
        return;
    }
    
    int maxIndex = 0;
    float highest = employees[0].salary;
    for (int i = 1; i < n; i++) {
        if (employees[i].salary > highest) {
            highest = employees[i].salary;
            maxIndex = i;
        }
    }
    printf("Employee with the highest Salary:\n");
    printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n",employees[maxIndex].id,employees[maxIndex].name,employees[maxIndex].designation,employees[maxIndex].salary);
}

void bonus(int n, struct Employee employees[]) {
    int threshold = 50000,count=0;    
    for (int i = 0; i < n; i++) {
        if (employees[i].salary < threshold) {
            employees[i].salary = employees[i].salary + (employees[i].salary * 0.1);
            count++;
        }
    }
    printf("Bonuses Awarded Successfully to %d employees!\n", count);
}
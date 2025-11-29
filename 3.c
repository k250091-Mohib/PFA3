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
    printf("ABC Technologies Employee Management System\n");
    printf("Enter the number of employees: ");
    int n;
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid Number of Employees\n");
        return 0;
    }  
    struct Employee employees[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d:\n", i + 1);
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
        printf("\nMAIN MENU\n");
        printf("1. Display All Employees\n");
        printf("2. Search Employee\n");
        printf("3. Find Highest Salary\n");
        printf("4. Give Bonus to Low-Salary Employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: displayEmployees(n, employees); break;
            case 2: searchemployee(n, employees); break;
            case 3: findHighestSalary(n, employees); break;
            case 4: bonus(n, employees); break;
            case 5: printf("Exiting... Thank you!\n"); return 0;
            default: printf("Invalid choice. Please try again.\n"); break;
        }
    }
}

void displayEmployees(int n, struct Employee employees[]) {
    printf("\nEMPLOYEE RECORDS\n");
    printf("ID\tName\t\tDesignation\tSalary\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%-12s\t%-12s\tRs.%.2f\n",employees[i].id,employees[i].name,employees[i].designation,employees[i].salary);
    }
}

void searchemployee(int n, struct Employee employees[]) {
    char choice;
    int found = 0;
    
    printf("\nSearch by:\n");
    printf("I - ID\n");
    printf("N - Name\n");
    printf("Enter your choice: ");
    getchar();
    scanf("%c", &choice);
    
    if (choice == 'I' || choice == 'i') {
        int id;
        printf("Enter Employee ID: ");
        scanf("%d", &id);
        
        for (int i = 0; i < n; i++) {
            if (id == employees[i].id) {
                found = 1;
                printf("\nEmployee Found:\n");
                printf("ID: %d\n", employees[i].id);
                printf("Name: %s\n", employees[i].name);
                printf("Designation: %s\n", employees[i].designation);
                printf("Salary: Rs.%.2f\n", employees[i].salary);
                break;
            }
        }
        if (!found) {
            printf("Employee with ID %d not found.\n", id);
        }
    }
    else if (choice == 'N' || choice == 'n') {
        char name[20];
        printf("Enter Employee Name: ");
        getchar();
        fgets(name, 20, stdin);
        name[strcspn(name, "\n")] = 0;
        
        for (int i = 0; i < n; i++) {
            if (strcmp(name, employees[i].name) == 0) {
                found = 1;
                printf("\nEmployee Found:\n");
                printf("ID: %d\n", employees[i].id);
                printf("Name: %s\n", employees[i].name);
                printf("Designation: %s\n", employees[i].designation);
                printf("Salary: Rs.%.2f\n", employees[i].salary);
                break;
            }
        }
        if (!found) {
            printf("Employee with name '%s' not found.\n", name);
        }
    }
    else {
        printf("Invalid choice.\n");
    }
}

void findHighestSalary(int n, struct Employee employees[]) {
    if (n == 0) {
        printf("No employees found.\n");
        return;
    }
    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (employees[i].salary > employees[maxIndex].salary) {
            maxIndex = i;
        }
    }
    printf("\nHIGHEST SALARY EMPLOYEE\n");
    printf("ID: %d\n", employees[maxIndex].id);
    printf("Name: %s\n", employees[maxIndex].name);
    printf("Designation: %s\n", employees[maxIndex].designation);
    printf("Salary: Rs.%.2f\n", employees[maxIndex].salary);
}

void bonus(int n, struct Employee employees[]) {
    float threshold;
    printf("Enter salary threshold for bonus (employees below this get 10%% bonus): ");
    scanf("%f", &threshold);
    int count = 0;
    printf("\nApplying 10%% bonus to employees with salary below Rs.%.2f...\n", threshold);
    for (int i = 0; i < n; i++) {
        if (employees[i].salary < threshold) {
            float oldSalary = employees[i].salary;
            employees[i].salary *= 1.10;
            printf("  %s: Rs.%.2f -> Rs.%.2f\n", employees[i].name, oldSalary, employees[i].salary);
            count++;
        }
    }
    printf("Bonus applied successfully to %d employees!\n", count);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME 100
#define MAX_BATCH 20
#define FILENAME "members.dat"
typedef struct {
    int studentID;
    char fullName[MAX_NAME];
    char batch[MAX_BATCH];
    char membershipType[10];
    char registrationDate[11];
    char dateOfBirth[11];
    char interest[10];
} Student;

Student *students = NULL;
int studentCount = 0;
int capacity = 0;

void loadDatabase(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("No existing database found. Starting fresh.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    studentCount = fileSize / sizeof(Student);
    capacity = studentCount + 10;
    students = malloc(capacity * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return;
    }
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf("Loaded %d student records.\n", studentCount);
}

void saveDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Cannot save database!\n");
        return;
    }
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf("Saved %d student records.\n", studentCount);
}

int isDuplicateID(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            return 1;
        }
    }
    return 0;
}

void addStudent(Student s, const char *filename) {
    if (isDuplicateID(s.studentID)) {
        printf("Error: Student ID %d already exists!\n", s.studentID);
        return;
    }
    if (studentCount >= capacity) {
        capacity += 10;
        students = realloc(students, capacity * sizeof(Student));
        if (!students) {
            printf("Memory allocation failed!\n");
            return;
        }
    }
    students[studentCount++] = s;
    saveDatabase(filename);
    printf("Student added successfully!\n");
}

void updateStudent(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            printf("Updating student %d:\n", studentID);
            printf("Enter new batch (CS/SE/Cyber Security/AI): ");
            scanf("%s", students[i].batch);
            printf("Enter new membership type (IEEE/ACM): ");
            scanf("%s", students[i].membershipType);
            printf("Enter new interest (IEEE/ACM/Both): ");
            scanf("%s", students[i].interest);
            
            saveDatabase(FILENAME);
            printf("Student updated successfully!\n");
            return;
        }
    }
    printf("Error: Student ID %d not found!\n", studentID);
}

void deleteStudent(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            saveDatabase(FILENAME);
            printf("Student deleted successfully!\n");
            return;
        }
    }
    printf("Error: Student ID %d not found!\n", studentID);
}

void displayAllStudents() {
    if (studentCount == 0) {
        printf("No students registered.\n");
        return;
    }
    printf("\n%-10s %-20s %-15s %-10s %-12s %-12s %s\n",  "ID", "Name", "Batch", "Member", "Reg Date", "DOB", "Interest");
    for (int i = 0; i < studentCount; i++) {
        printf("%-10d %-20s %-15s %-10s %-12s %-12s %s\n",students[i].studentID,students[i].fullName,students[i].batch,students[i].membershipType,students[i].registrationDate,students[i].dateOfBirth,students[i].interest);
    }
}

void generateBatchReport(const char *batch) {
    printf("\nBatch Report for %s:\n", batch);
    printf("%-10s %-20s %-10s %s\n", "ID", "Name", "Member", "Interest");
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            printf("%-10d %-20s %-10s %s\n",students[i].studentID,students[i].fullName,students[i].membershipType,students[i].interest);
            found = 1;
        }
    }
    if (!found) {
        printf("No students found in batch %s.\n", batch);
    }
}

void registerNewStudent() {
    Student s;
    printf("Enter Student ID: ");
    scanf("%d", &s.studentID);
    getchar();
    if (isDuplicateID(s.studentID)) {
        printf("Error: Student ID already exists!\n");
        return;
    }
    printf("Enter Full Name: ");
    fgets(s.fullName, MAX_NAME, stdin);
    s.fullName[strcspn(s.fullName, "\n")] = '\0';
    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    scanf("%s", s.batch);
    printf("Enter Membership Type (IEEE/ACM): ");
    scanf("%s", s.membershipType);
    printf("Enter Registration Date (YYYY-MM-DD): ");
    scanf("%s", s.registrationDate);
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf("%s", s.dateOfBirth);
    printf("Enter Interest (IEEE/ACM/Both): ");
    scanf("%s", s.interest);
    addStudent(s, FILENAME);
}

void freeMemory() {
    free(students);
    students = NULL;
    studentCount = 0;
    capacity = 0;
}

int main() {
    int choice, studentID;
    char batch[20];
    printf("IEEE/ACM Membership Registration Manager\n");
    loadDatabase(FILENAME);
    while (1) {
        printf("\n1. Register New Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Registrations\n");
        printf("5. Generate Batch Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:registerNewStudent();break; 
            case 2:
                printf("Enter Student ID to update: ");
                scanf("%d", &studentID);
                updateStudent(studentID);
                break;
                
            case 3:
                printf("Enter Student ID to delete: ");
                scanf("%d", &studentID);
                deleteStudent(studentID);
                break;
                
            case 4:displayAllStudents();break;
            case 5:
                printf("Enter batch (CS/SE/Cyber Security/AI): ");
                scanf("%s", batch);
                generateBatchReport(batch);
                break;   
            case 6:
                saveDatabase(FILENAME);
                freeMemory();
                printf("Database saved. Exiting...\n");
                return 0;    
            default:printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
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

int isValidBatch(const char *batch) {
    const char *validBatches[] = {"CS", "SE", "Cyber Security", "AI"};
    for (int i = 0; i < 4; i++) {
        if (strcmp(batch, validBatches[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isValidMembership(const char *membership) {
    return (strcmp(membership, "IEEE") == 0 || strcmp(membership, "ACM") == 0);
}

int isValidInterest(const char *interest) {
    return (strcmp(interest, "IEEE") == 0 || strcmp(interest, "ACM") == 0 || strcmp(interest, "Both") == 0);
}

int isValidDate(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return 0;
    }
    return 1;
}

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
    if (fileSize % sizeof(Student) != 0) {
        printf("Warning: Database file may be corrupted!\n");
        fclose(file);
        return;
    }
    capacity = studentCount + 10;
    students = malloc(capacity * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed!\n");
        fclose(file);
        return;
    }
    size_t readCount = fread(students, sizeof(Student), studentCount, file);
    if (readCount != studentCount) {
        printf("Error reading database file!\n");
        free(students);
        students = NULL;
        studentCount = 0;
        capacity = 0;
    } else {
        printf("Loaded %d student records.\n", studentCount);
    }
    fclose(file);
}

void saveDatabase(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Cannot save database! Check file permissions.\n");
        return;
    }
    size_t written = fwrite(students, sizeof(Student), studentCount, file);
    if (written != studentCount) {
        printf("Error writing to database file!\n");
    } else {
        printf("Saved %d student records to %s.\n", studentCount, filename);
    }
    
    fclose(file);
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
        Student *temp = realloc(students, capacity * sizeof(Student));
        if (!temp) {
            printf("Memory allocation failed! Cannot add student.\n");
            return;
        }
        students = temp;
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
            while (!isValidBatch(students[i].batch)) {
                printf("Invalid batch! Enter valid batch (CS/SE/Cyber Security/AI): ");
                scanf("%s", students[i].batch);
            }
            printf("Enter new membership type (IEEE/ACM): ");
            scanf("%s", students[i].membershipType);
            while (!isValidMembership(students[i].membershipType)) {
                printf("Invalid membership! Enter IEEE or ACM: ");
                scanf("%s", students[i].membershipType);
            }
            printf("Enter new interest (IEEE/ACM/Both): ");
            scanf("%s", students[i].interest);
            while (!isValidInterest(students[i].interest)) {
                printf("Invalid interest! Enter IEEE/ACM/Both: ");
                scanf("%s", students[i].interest);
            }
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
    printf("\n%-10s %-20s %-15s %-10s %-12s %-12s %s\n", "ID", "Name", "Batch", "Member", "Reg Date", "DOB", "Interest");
    for (int i = 0; i < studentCount; i++) {
        printf("%-10d %-20s %-15s %-10s %-12s %-12s %s\n",students[i].studentID,students[i].fullName,students[i].batch,students[i].membershipType,students[i].registrationDate,students[i].dateOfBirth,students[i].interest);
    }
    printf("Total students: %d\n", studentCount);
}

void generateBatchReport(const char *batch) {
    if (!isValidBatch(batch)) {
        printf("Error: Invalid batch '%s'! Use CS/SE/Cyber Security/AI\n", batch);
        return;
    }
    
    printf("\nBatch Report for %s:\n", batch);
    printf("%-10s %-20s %-10s %s\n", "ID", "Name", "Member", "Interest");
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, batch) == 0) {
            printf("%-10d %-20s %-10s %s\n",
                   students[i].studentID,
                   students[i].fullName,
                   students[i].membershipType,
                   students[i].interest);
            found = 1;
        }
    }
    
    if (!found) {
        printf("No students found in batch %s.\n", batch);
    } else {
        printf("End of report for batch %s\n", batch);
    }
}

void registerNewStudent() {
    Student s;
    printf("Enter Student ID: ");
    if (scanf("%d", &s.studentID) != 1) {
        printf("Error: Invalid Student ID!\n");
        while (getchar() != '\n');
        return;
    }
    if (isDuplicateID(s.studentID)) {
        printf("Error: Student ID %d already exists!\n", s.studentID);
        return;
    }
    getchar();
    printf("Enter Full Name: ");
    fgets(s.fullName, MAX_NAME, stdin);
    s.fullName[strcspn(s.fullName, "\n")] = '\0';
    printf("Enter Batch (CS/SE/Cyber Security/AI): ");
    scanf("%s", s.batch);
    while (!isValidBatch(s.batch)) {
        printf("Invalid batch! Enter valid batch (CS/SE/Cyber Security/AI): ");
        scanf("%s", s.batch);
    }
    printf("Enter Membership Type (IEEE/ACM): ");
    scanf("%s", s.membershipType);
    while (!isValidMembership(s.membershipType)) {
        printf("Invalid membership! Enter IEEE or ACM: ");
        scanf("%s", s.membershipType);
    }
    printf("Enter Registration Date (YYYY-MM-DD): ");
    scanf("%s", s.registrationDate);
    while (!isValidDate(s.registrationDate)) {
        printf("Invalid date format! Use YYYY-MM-DD: ");
        scanf("%s", s.registrationDate);
    }
    
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf("%s", s.dateOfBirth);
    while (!isValidDate(s.dateOfBirth)) {
        printf("Invalid date format! Use YYYY-MM-DD: ");
        scanf("%s", s.dateOfBirth);
    }
    
    printf("Enter Interest (IEEE/ACM/Both): ");
    scanf("%s", s.interest);
    while (!isValidInterest(s.interest)) {
        printf("Invalid interest! Enter IEEE/ACM/Both: ");
        scanf("%s", s.interest);
    }
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
        printf("\nMain Menu\n");
        printf("1. Register New Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Registrations\n");
        printf("5. Generate Batch Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        
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
                printf("Database saved. Memory freed. Exiting...\n");
                return 0;
            default:printf("Invalid choice! Please enter 1-6.\n");
        }
    }   
    return 0;
}

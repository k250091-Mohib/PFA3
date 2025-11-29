#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#define INITIAL_CAPACITY 2
char **lines = NULL;
int lineCount = 0;
int capacity = 0;

void insertLine(int index, const char *text) {
    if (index < 0 || index > lineCount) {
        printf("Invalid index!\n");
        return;
    }
    if (lineCount >= capacity) {
        capacity = capacity ? capacity * 2 : INITIAL_CAPACITY;
        lines = realloc(lines, capacity * sizeof(char*));
        if (!lines) {
            perror("Memory allocation failed");
            exit(1);
        }
    }
    memmove(&lines[index + 1], &lines[index], (lineCount - index) * sizeof(char*));
    lines[index] = malloc(strlen(text) + 1);
    if (!lines[index]) {
        perror("Memory allocation failed");
        exit(1);
    }
    strcpy(lines[index], text);
    lineCount++;
}

void deleteLine(int index) {
    if (index < 0 || index >= lineCount) {
        printf("Invalid index!\n");
        return;
    }
    free(lines[index]);
    memmove(&lines[index], &lines[index + 1], (lineCount - index - 1) * sizeof(char*));
    lineCount--;
}

void printAllLines() {
    for (int i = 0; i < lineCount; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
}

void shrinkToFit() {
    if (lineCount < capacity) {
        capacity = lineCount;
        lines = realloc(lines, capacity * sizeof(char*));
        if (!lines && capacity > 0) {
            perror("Memory reallocation failed");
            exit(1);
        }
    }
}

void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < lineCount; i++) {
        fprintf(file, "%s\n", lines[i]);
    }
    fclose(file);
    printf("Saved %d lines to %s\n", lineCount, filename);
}

void loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < lineCount; i++) {
        free(lines[i]);
    }
    free(lines);
    lines = NULL;
    lineCount = 0;
    capacity = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insertLine(lineCount, buffer);
    }
    fclose(file);
    printf("Loaded %d lines from %s\n", lineCount, filename);
}

void freeAll() {
    for (int i = 0; i < lineCount; i++) {
        free(lines[i]);
    }
    free(lines);
    lines = NULL;
    lineCount = 0;
    capacity = 0;
}

int main() {
    int choice, index;
    char text[1024];
    char filename[100]; 
    printf("Minimal Text Editor\n");
    while (1) {
        printf("Menu\n");
        printf("1. Insert Line.\n");
        printf("2. Delete Line\n");
        printf("3. Print all\n");
        printf("4. Save to file\n");
        printf("5. Load from file\n");
        printf("6. Shrink to fit\n");
        printf("7. Exit\n");
        printf("Choice: ");
        printf("5. Load from file\n6. Shrink to fit\n7. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                printf("Enter index and text: ");
                scanf("%d", &index);
                getchar();
                fgets(text, sizeof(text), stdin);
                text[strcspn(text, "\n")] = '\0';
                insertLine(index, text);
                break;
                
            case 2:
                printf("Enter index to delete: ");
                scanf("%d", &index);
                deleteLine(index);
                break;
                
            case 3:
                printAllLines();
                break;
                
            case 4:
                printf("Enter filename: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                saveToFile(filename);
                break;
            case 5:
                printf("Enter filename: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                loadFromFile(filename);
                break;
            case 6:
                shrinkToFit();
                printf("Memory optimized. Capacity: %d\n", capacity);
                break;
            case 7:
                freeAll();
                printf("Exiting. Memory freed.\n");
                return 0;
            default:printf("Invalid choice!\n");
        }
    }
}
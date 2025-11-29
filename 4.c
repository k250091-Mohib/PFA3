#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 1000

typedef struct {
    int id;
    int score;
    int access_time;
} book;

book shelf[MAX_BOOKS];
int book_count = 0;
int max_capacity;
int global_time = 0;

int find_book_index(int id) {
    for (int i = 0; i < book_count; i++) {
        if (shelf[i].id == id) {
            return i;
        }
    }
    return -1;
}

int find_oldest_book() {
    int min_time = shelf[0].access_time;
    int min_index = 0;
    for (int i = 1; i < book_count; i++) {
        if (shelf[i].access_time < min_time) {
            min_time = shelf[i].access_time;
            min_index = i;
        }
    }
    return min_index;
}

void add_book(int id, int score) {
    int index = find_book_index(id);
    if (index != -1) {
        shelf[index].score = score;
        shelf[index].access_time = global_time++;
        printf("Book %d updated with popularity score %d\n", id, score);
        return;
    }

    if (book_count < max_capacity) {
        shelf[book_count].id = id;
        shelf[book_count].score = score;
        shelf[book_count].access_time = global_time++;
        book_count++;
        printf("Book %d added with popularity score %d\n", id, score);
    } else {
        int old_index = find_oldest_book();
        int old_id = shelf[old_index].id;
        shelf[old_index].id = id;
        shelf[old_index].score = score;
        shelf[old_index].access_time = global_time++;
        printf("Book %d removed. Book %d added with popularity score %d\n", old_id, id, score);
    }
}

void access_book(int id) {
    int index = find_book_index(id);
    if (index == -1) {
        printf("Book %d not found. Result: -1\n", id);
        return;
    }
    shelf[index].access_time = global_time++;
    printf("Book %d accessed. Popularity score: %d\n", id, shelf[index].score);
}

void display_all_books() {
    printf("\nCurrent books on shelf:\n");
    if (book_count == 0) {
        printf("Shelf is empty\n");
        return;
    }
    for (int i = 0; i < book_count; i++) {
        printf("Book ID: %d, Popularity: %d, Last Access Time: %d\n", 
               shelf[i].id, shelf[i].score, shelf[i].access_time);
    }
}

int main() {
    printf("Enter shelf capacity: ");
    scanf("%d", &max_capacity);
    printf("Shelf capacity set to %d books\n", max_capacity);
    
    int choice;
    
    while (1) {
        printf("\n--- Library Shelf System ---\n");
        printf("1. ADD book\n");
        printf("2. ACCESS book\n");
        printf("3. Display all books\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                int id, score;
                printf("Enter book ID: ");
                scanf("%d", &id);
                printf("Enter popularity score: ");
                scanf("%d", &score);
                add_book(id, score);
                break;
            }
            case 2: {
                int id;
                printf("Enter book ID to access: ");
                scanf("%d", &id);
                access_book(id);
                break;
            }
            case 3:
                display_all_books();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

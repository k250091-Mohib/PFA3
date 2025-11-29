#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 1000
struct book{
    int id;
    int score;
    int access_time;
};
struct book shelf[MAX_BOOKS];
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
        return;
    }

    if (book_count < max_capacity) {
        shelf[book_count].id = id;
        shelf[book_count].score = score;
        shelf[book_count].access_time = global_time++;
        book_count++;
    } else {
        int old_index = find_oldest_book();
        shelf[old_index].id = id;
        shelf[old_index].score = score;
        shelf[old_index].access_time = global_time++;
    }
}

int access_book(int id) {
    int index = find_book_index(id);
    if (index == -1) {
        return -1;
    }
    shelf[index].access_time = global_time++;
    return shelf[index].score;
}

int main() {
    printf("Enter capacity and number of operations: ");
    scanf("%d %d", &max_capacity, &book_count);
    int q = book_count;
    book_count = 0;
    
    for (int i = 0; i < q; i++) {
        char operation[10];
        printf("Enter operation (ADD or ACCESS): ");
        scanf("%s", operation);   
        if (strcmp(operation, "ADD") == 0) {
            int id, score;
            printf("Enter book ID and popularity score: ");
            scanf("%d %d", &id, &score);
            add_book(id, score);
        } else if (strcmp(operation, "ACCESS") == 0) {
            int id;
            printf("Enter book ID to access: ");
            scanf("%d", &id);
            int result = access_book(id);
            printf("Result: %d\n", result);
        }
    }   
    return 0;
}
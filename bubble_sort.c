#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10

int array[SIZE];
int sorted_array[SIZE];

typedef struct {
    int start;
    int end;
} Range;

void bubble_sort(int start, int end) {
    int i, j, temp;
    for (i = start; i < end; i++) {
        for (j = start; j < end - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void merge(int start1, int end1, int start2, int end2) {
    int i = start1, j = start2, k = 0;
    
    while (i < end1 && j < end2) {
        if (array[i] <= array[j]) {
            sorted_array[k++] = array[i++];
        } else {
            sorted_array[k++] = array[j++];
        }
    }
    
    while (i < end1) {
        sorted_array[k++] = array[i++];
    }
    
    while (j < end2) {
        sorted_array[k++] = array[j++];
    }
}

void *sort_thread(void *arg) {
    Range *range = (Range *)arg;
    bubble_sort(range->start, range->end);
    pthread_exit(NULL);
}

void *merge_thread(void *arg) {
    merge(0, SIZE/2, SIZE/2, SIZE);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2, tid3;
    Range range1, range2;
    int i;
    
    printf("Enter %d integers: ", SIZE);
    for (i = 0; i < SIZE; i++) {
        scanf("%d", &array[i]);
    }
    
    range1.start = 0;
    range1.end = SIZE/2;
    range2.start = SIZE/2;
    range2.end = SIZE;
    
    pthread_create(&tid1, NULL, sort_thread, &range1);
    pthread_create(&tid2, NULL, sort_thread, &range2);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    pthread_create(&tid3, NULL, merge_thread, NULL);
    pthread_join(tid3, NULL);
    
    printf("Sorted array: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");
    
    return 0;
}
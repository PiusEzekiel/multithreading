#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_numbers(void *arg) {
    long start = (long)arg;
    long end = start + 100000; // Each thread prints 100,000 numbers

    for (long i = start; i < end; i++) {
        printf("%ld\n", i);
    }

    pthread_exit(NULL);
}

int main() {
    long n;
    printf("Enter a large number: ");
    scanf("%ld", &n);

    pthread_t threads[10];
    for (int i = 0; i < 10; i++) {
        long start = i * 100000; 
        if (pthread_create(&threads[i], NULL, print_numbers, (void *)start) != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    for (int i = 0; i < 10; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            exit(1);
        }
    }

    printf("All threads completed.\n");
    return 0;
}

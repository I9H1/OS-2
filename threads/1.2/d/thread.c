#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function() {
    printf("Поток %lu\n", pthread_self());
    return NULL;
}

int main() {
    printf("(%d)\n", getpid());
    int counter = 0;
    while(1) {
        pthread_t thread;
        int result = pthread_create(&thread, NULL, thread_function, NULL);
        if (result != 0) {
            printf("Ошибка создания потока, код %d\n", result);
            break;
        }
        printf("Создано потоков: %d\n", counter);
        ++counter;
    }
    
    return 0;
}

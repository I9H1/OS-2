#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* thread_function() {
    pthread_detach(pthread_self());
    printf("Поток %lu\n", pthread_self());
    return NULL;
}

int main() {
    int counter = 0;
    while(1) {
        pthread_t thread;
        int result = pthread_create(&thread, NULL, thread_function, NULL);
        if (result != 0) {
            printf("Ошибка создания потока, код %d\n", result);
            break;
        }
        
        ++counter;
        printf("Создано потоков: %d\n", counter);
    }
    
    return 0;
}

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

    pthread_attr_t attr;
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    while(1) {
        pthread_t thread;
        int result = pthread_create(&thread, &attr, thread_function, NULL);
        if (result != 0) {
            printf("Ошибка создания потока, код %d\n", result);
            break;
        }
        
        ++counter;
        printf("Создано потоков: %d\n", counter);
    }
    
    pthread_attr_destroy(&attr);

    return 0;
}

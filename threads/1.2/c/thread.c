#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void* mythread() {
    char* result = "Hello world";
    return (void*)result;
}

int main() {
    pthread_t thread;
    char* thread_result;
    
    pthread_create(&thread, NULL, mythread, NULL);
    pthread_join(thread, (void**)&thread_result);
    
    printf("Поток вернул: %s\n", thread_result);
    
    return 0;
}
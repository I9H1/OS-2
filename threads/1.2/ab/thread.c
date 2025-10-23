#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void* mythread() {
    int* result = malloc(sizeof(int));
    *result = 42;
    return (void*)result;
}

int main() {
    pthread_t thread;
    int* thread_result;
    
    pthread_create(&thread, NULL, mythread, NULL);
    
    pthread_join(thread, (void**)&thread_result);
    
    printf("Поток вернул: %d\n", *thread_result);

    free(thread_result);
    return 0;
}

#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define THREADS_COUNT 5

int global_variable;

void *mythread(void* arg) {
	int local_variable; 
	static int local_static;
	const int local_const;

	printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());

	// ID потока
	int thread_num = *(int*)arg;
	printf("mythread %d: pthread_self() = %ld, gettid() = %d\n",
           thread_num, pthread_self(), gettid());

	// Адреса переменных
    printf("Address of local_var = %p\n", (void *)&local_variable);
    printf("Address of local_static = %p\n", (void *)&local_static);
    printf("Address of local_const = %p\n", (void *)&local_const);
    printf("Address of global_var = %p\n\n", (void *)&global_variable);

	return NULL;
}

int main() {
	pthread_t threads[THREADS_COUNT];
	int thread_nums[THREADS_COUNT];

	printf("main [%d %d %d]: Hello from main!\n", getpid(), getppid(), gettid());

	int err;
	int threads_created_count = 0;
	for (int i = 0; i < THREADS_COUNT; ++i) {
		thread_nums[i] = i + 1;
		err = pthread_create(&threads[i], NULL, mythread, &thread_nums[i]);
		printf("from main: thread_num %d, create returned %ld\n", i + 1, threads[i]);
		if (err) {
	    	printf("main: pthread_create() failed: %s\n", strerror(err));
			break;
		}
		++threads_created_count;
	}

	for (int i = 0; i < threads_created_count; ++i) {
		err = pthread_join(threads[i], NULL);
    	if (err) {
        	printf("main: pthread_join() failed: %s\n", strerror(err));
        	return -1;
    	}
	}

	return 0;
}

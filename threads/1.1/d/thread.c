#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#define THREADS_COUNT 5

int global_variable = 1;

void *mythread(void* arg) {
	int local_variable = 2; 
	static int local_static = 3;
	const int local_const = 4;

	printf("mythread [%d %d %d]: Hello from mythread!\n", getpid(), getppid(), gettid());

	// ID потока
	int thread_num = *(int*)arg;
	printf("mythread %d: pthread_self() = %ld, gettid() = %d\n",
           thread_num, pthread_self(), gettid());
		
	// Изменяем значения переменных
	if (thread_num == 1) {
		global_variable = -1;
		local_variable = -2;
		local_static = -3;
	}

	// Значения и адреса переменных
    printf("Local_var = %d, address = %p\n", local_variable, (void *)&local_variable);
    printf("Local_static = %d, address = %p\n", local_static, (void *)&local_static);
    printf("Local_const = %d, address = %p\n", local_const, (void *)&local_const);
    printf("Global_var = %d, address = %p\n\n", global_variable, (void *)&global_variable);
	sleep(10);
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

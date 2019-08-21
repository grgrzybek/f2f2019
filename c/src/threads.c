/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/syscall.h>

void *task(void *);

int
main(int argc, char** argv) {

	// http://man7.org/linux/man-pages/man7/pthreads.7.html
	// http://man7.org/linux/man-pages/man7/nptl.7.html
    // https://en.wikipedia.org/wiki/Native_POSIX_Thread_Library

	printf("My PID: %d\n", getpid());

	int tids[5];
	pthread_t pthreads[5];
	pthread_attr_t attrs[5];

	for (int i=1; i<=5; i++) {
		pthread_attr_init(&attrs[i-1]);
		tids[i-1] = pthread_create(&pthreads[i-1], &attrs[i-1], task, NULL);
		pthread_attr_destroy(&attrs[i-1]);
	}

	fgetc(stdin);

	for (int i=1; i<=5; i++) {
		pthread_cancel(pthreads[i-1]);
		pthread_join(pthreads[i-1], NULL);
	}

	return 0;
}

void *
task(void *p) {
	pthread_t tid = pthread_self();
	pthread_attr_t attr;
	pthread_getattr_np(tid, &attr);
	void *stack_address;
	size_t stack_size;

	pthread_attr_getstack(&attr, &stack_address, &stack_size);
	printf("ptid: %d, pid: %d, tid: %d, stack: %p, stack size: %d\n", tid, getpid(), syscall(SYS_gettid), stack_address, stack_size);
	while (1) {
		sleep(5);
	}
	return NULL;
}

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

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/auxv.h>
#include <sys/syscall.h>

#include "grgr_f2f2019_n_NativeBridge.h"

const char *ORG_SLF4J_LOGGER_SIG = "Lorg/slf4j/Logger;";

void *task1(void *);
void *task2(void *);
void log_info(JNIEnv *, jclass, jobject, const char *);

typedef struct task_info {
	JavaVM *vm;
	jobject this;
	jclass logger_class;
} task_info;

JNIEXPORT void JNICALL Java_grgr_f2f2019_n_NativeBridge_helloNative (JNIEnv *env, jobject this, jstring name) {
	printf("My PID: %d\n", getpid());

	const char *s = (*env)->GetStringUTFChars(env, name, NULL);
	printf("Hello %s from native code!\n", s);
	fflush(stdout);
	(*env)->ReleaseStringUTFChars(env, name, s);

	log_info(env, (*env)->FindClass(env, "Lorg/slf4j/Logger;"), this, "Calling logger from native code");
}

JNIEXPORT void JNICALL Java_grgr_f2f2019_n_NativeBridge_processInformation (JNIEnv *env, jobject this) {
	printf("My PID: %d\n", getpid());

	printf("-----------------\n");
	printf("AT_BASE: %016p\n", getauxval(AT_BASE));
	printf("AT_ENTRY: %016p\n", getauxval(AT_ENTRY));
	printf("AT_EXECFN: %016p\n", getauxval(AT_EXECFN));
	printf("AT_EXECFN (string): %s\n", getauxval(AT_EXECFN));
	printf("AT_PHDR: %016p\n", getauxval(AT_PHDR));
	printf("AT_PHENT: %d\n", getauxval(AT_PHENT));
	printf("AT_PHNUM: %d\n", getauxval(AT_PHNUM));
	printf("AT_PLATFORM: %016p\n", getauxval(AT_PLATFORM));
	printf("AT_PLATFORM (string): %s\n", getauxval(AT_PLATFORM));
	printf("AT_BASE_PLATFORM: %016p\n", getauxval(AT_BASE_PLATFORM));
	printf("AT_BASE_PLATFORM (string): %s\n", getauxval(AT_BASE_PLATFORM));
	printf("AT_UID: %d\n", getauxval(AT_UID));
	printf("AT_SYSINFO_EHDR: %016p\n", getauxval(AT_SYSINFO_EHDR));
}

/*
 * This method will create threads that won't be attached to VM
 */
JNIEXPORT void JNICALL Java_grgr_f2f2019_n_NativeBridge_pthreads(JNIEnv *env, jobject this) {
	int tids[5];
	pthread_t pthreads[5];
	pthread_attr_t attrs[5];

	task_info param;
	(*env)->GetJavaVM(env, &param.vm);
	param.this = this;
	param.logger_class = (*env)->FindClass(env, "Lorg/slf4j/Logger;");

	for (int i=1; i<=5; i++) {
		pthread_attr_init(&attrs[i-1]);
		tids[i-1] = pthread_create(&pthreads[i-1], &attrs[i-1], task1, &param);
		pthread_attr_destroy(&attrs[i-1]);
	}

	fgetc(stdin);

	for (int i=1; i<=5; i++) {
		pthread_cancel(pthreads[i-1]);
		pthread_join(pthreads[i-1], NULL);
	}
}

/*
 * This method will create threads that will be attached to VM
 */
JNIEXPORT void JNICALL Java_grgr_f2f2019_n_NativeBridge_pthreadsAttached (JNIEnv *env, jobject this) {
	int tids[5];
	pthread_t pthreads[5];
	pthread_attr_t attrs[5];

	task_info param;
	(*env)->GetJavaVM(env, &param.vm);
	param.this = this;
	param.logger_class = (*env)->FindClass(env, "Lorg/slf4j/Logger;");

	for (int i=1; i<=5; i++) {
		pthread_attr_init(&attrs[i-1]);
		tids[i-1] = pthread_create(&pthreads[i-1], &attrs[i-1], task2, &param);
		pthread_attr_destroy(&attrs[i-1]);
	}

	jclass system_class = (*env)->FindClass(env, "Ljava/lang/System;");
	jclass is_class = (*env)->FindClass(env, "Ljava/io/InputStream;");
	jfieldID in_fid = (*env)->GetStaticFieldID(env, system_class, "in", "Ljava/io/InputStream;");
	jobject in = (*env)->GetStaticObjectField(env, system_class, in_fid);

	jmethodID read_mid = (*env)->GetMethodID(env, is_class, "read", "()I");
	(*env)->CallIntMethod(env, in, read_mid);

	for (int i=1; i<=5; i++) {
		pthread_cancel(pthreads[i-1]);
		pthread_join(pthreads[i-1], NULL);
	}
}

/*
 * This method will create both kind of threads (3 of each)
 */
JNIEXPORT void JNICALL Java_grgr_f2f2019_n_NativeBridge_pthreadsAll (JNIEnv *env, jobject this) {
	int tids[6];
	pthread_t pthreads[6];
	pthread_attr_t attrs[6];

	task_info param;
	(*env)->GetJavaVM(env, &param.vm);
	param.this = this;
	param.logger_class = (*env)->FindClass(env, "Lorg/slf4j/Logger;");

	for (int i=1; i<=3; i++) {
		pthread_attr_init(&attrs[i-1]);
		tids[i-1] = pthread_create(&pthreads[i-1], &attrs[i-1], task1, &param);
		pthread_attr_destroy(&attrs[i-1]);
	}
	for (int i=4; i<=6; i++) {
		pthread_attr_init(&attrs[i-1]);
		tids[i-1] = pthread_create(&pthreads[i-1], &attrs[i-1], task2, &param);
		pthread_attr_destroy(&attrs[i-1]);
	}

	jclass system_class = (*env)->FindClass(env, "Ljava/lang/System;");
	jclass is_class = (*env)->FindClass(env, "Ljava/io/InputStream;");
	jfieldID in_fid = (*env)->GetStaticFieldID(env, system_class, "in", "Ljava/io/InputStream;");
	jobject in = (*env)->GetStaticObjectField(env, system_class, in_fid);

	jmethodID read_mid = (*env)->GetMethodID(env, is_class, "read", "()I");
	(*env)->CallIntMethod(env, in, read_mid);

	for (int i=1; i<=3; i++) {
		pthread_cancel(pthreads[i-1]);
		pthread_join(pthreads[i-1], NULL);
	}
	for (int i=4; i<=6; i++) {
		pthread_cancel(pthreads[i-1]);
		pthread_join(pthreads[i-1], NULL);
	}
}

/**
 * A task to be called from a thread that's not going to be _attached_ to VM and will call printf()
 */
void *
task1(void *p) {
	task_info *eao = (task_info *)p;
	JavaVM *vm = eao->vm;
	jobject this = eao->this;

	pthread_t tid = pthread_self();
	pthread_attr_t attr;
	pthread_getattr_np(tid, &attr);
	void *stack_address;
	size_t stack_size;

	pthread_attr_getstack(&attr, &stack_address, &stack_size);

	char *cmsg = calloc(1024, sizeof(char));
	printf("ptid: %d, pid: %d, tid: %d, stack: %p, stack size: %d\n", tid, getpid(), syscall(SYS_gettid), stack_address, stack_size);
	free(cmsg);
	while (1) {
		sleep(5);
	}
	return NULL;
}

/**
 * A task to be called from a thread that's going to be _attached_ to VM (because it needs access to JNIEnv*)
 *
 * https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/invocation.html#attaching_to_the_vm
 * The JNI interface pointer (JNIEnv) is valid only in the current thread. Should another thread need to
 * access the Java VM, it must first call AttachCurrentThread() to attach itself to the VM and obtain a JNI
 * interface pointer
 */
void *
task2(void *p) {
	task_info *ti = (task_info *)p;
	JavaVM *vm = ti->vm;
	jobject this = ti->this;
	jclass logger_class = ti->logger_class;

	pthread_t tid = pthread_self();
	pthread_attr_t attr;
	pthread_getattr_np(tid, &attr);
	void *stack_address;
	size_t stack_size;

	void *penv;
	(*vm)->AttachCurrentThread(vm, &penv, NULL);
	JNIEnv *env = (JNIEnv *)penv;

	pthread_attr_getstack(&attr, &stack_address, &stack_size);

	char *cmsg = calloc(1024, sizeof(char));
	snprintf(cmsg, 1024, "ptid: %d, pid: %d, tid: %d, stack: %p, stack size: %d\n", tid, getpid(), syscall(SYS_gettid), stack_address, stack_size);
	log_info(env, logger_class, this, cmsg);
	free(cmsg);
	while (1) {
		sleep(5);
	}

	(*vm)->DetachCurrentThread(vm);

	return NULL;
}

/*
 * This method calls back to invoking class and invokes org.slf4j.Logger.info() on its static member
 */
void
log_info(JNIEnv *env, jclass logger_class, jobject this, const char *msg) {
	jclass class = (*env)->GetObjectClass(env, this);
	jfieldID log_fid = (*env)->GetStaticFieldID(env, class, "LOG", ORG_SLF4J_LOGGER_SIG);
	jobject log = (*env)->GetStaticObjectField(env, class, log_fid);

	jclass system_class = (*env)->FindClass(env, "Ljava/lang/System;");
	jclass ps_class = (*env)->FindClass(env, "Ljava/io/PrintStream;");
	jfieldID out_fid = (*env)->GetStaticFieldID(env, system_class, "out", "Ljava/io/PrintStream;");
	jobject out = (*env)->GetStaticObjectField(env, system_class, out_fid);

	jmethodID println_mid = (*env)->GetMethodID(env, ps_class, "println", "(Ljava/lang/String;)V");
	jmethodID flush_mid = (*env)->GetMethodID(env, ps_class, "flush", "()V");

	jmethodID info_mid = (*env)->GetMethodID(env, logger_class, "info", "(Ljava/lang/String;)V");
	char *cmsg = calloc(1024, sizeof(char));
	strcpy(cmsg, "Calling logger from native code");
	jstring jmsg = (*env)->NewStringUTF(env, msg);
	(*env)->CallVoidMethod(env, log, info_mid, jmsg);
	free(cmsg);
}

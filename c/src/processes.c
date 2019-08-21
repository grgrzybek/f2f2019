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

#include <sys/auxv.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>

#include "config.h"

static long long_in_initialized_data_section __attribute__ ((unused)) = 42L;
static long long_in_uninitialized_data_section __attribute__ ((unused));

char *pchar_in_initialized_data_section = "Grzegorz (char * initialized)";
static char *static_pchar_in_initialized_data_section = "Grzegorz (static char * initialized)";

int
main(int argc, char** argv) {

	static int local_static_int_in_initialized_data_section __attribute__ ((unused)) = 43;
	static int local_static_int_in_uninitialized_data_section __attribute__ ((unused));

	// 26.3 Process Identification
	printf("-----------------\n");
	pid_t pid = getpid();
	printf("My PID: %d\n", pid);

	// man 3 getauxval
	// 25.5 Auxiliary Vector
	// When a program is executed, it receives information from the operating system about the environment
	// in which it is operating. The form of this information is a table of key-value pairs, where the keys are from
	// the set of ‘AT_’ values in elf.h. Some of the data is provided by the kernel for libc consumption, and may be
	// obtained by ordinary interfaces, such as sysconf. However, on a platform-by-platform basis there may be information
	// that is not available any other way.
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

	printf("-----------------\n");
	printf("sbrk(0): %p\n", sbrk(0));

	int32_t *sarray = malloc(sizeof(int32_t) * (4096+1024));
	sarray[0] = 0x01234567;
	int32_t *larray = malloc(sizeof(int32_t) * (4096*1024));
	larray[0] = 0x89abcdef;

	printf("small array: %p\n", sarray);
	printf("large array: %p\n", larray);
	printf("current sbrk(0): %p\n", sbrk(0));

	printf("-----------------\n");
	int32_t auto_int = 0x1f;
	printf("&auto_int: %p\n", &auto_int);
	printf("main: %p\n", main);

	printf("-----------------\n");
	printf("in_the_initialized_data_section: %p\n", &long_in_initialized_data_section);
	printf("in_the_uninitialized_data_section: %p\n", &long_in_uninitialized_data_section);
	printf("local_static_initialized_variable1: %p\n", &local_static_int_in_initialized_data_section);
	printf("local_static_uninitialized_variable2: %p\n", &local_static_int_in_uninitialized_data_section);

	printf("-----------------\n");
	char *home = secure_getenv("HOME");
	printf("home: %s\n", home);
	printf("&home: %p\n", home);

	printf("-----------------\n");
	printf("pchar_in_initialized_data_section (string): %s\n", pchar_in_initialized_data_section);
	printf("pchar_in_initialized_data_section (pointer): %p\n", pchar_in_initialized_data_section);
	printf("&pchar_in_initialized_data_section: %p\n", &pchar_in_initialized_data_section);
	printf("static_pchar_in_initialized_data_section (string): %s\n", static_pchar_in_initialized_data_section);
	printf("static_pchar_in_initialized_data_section (pointer): %p\n", static_pchar_in_initialized_data_section);
	printf("&static_pchar_in_initialized_data_section: %p\n", &static_pchar_in_initialized_data_section);
	char *my_name3 = "Grzegorz (local char * initialized)";
	printf("my_name3: %s\n", my_name3);
	printf("&my_name3: %p\n", my_name3);
	printf("&&my_name3: %p\n", &my_name3);

	// 22.4.2 How to get information about the memory subsystem?
	printf("-----------------\n");
	printf("page size: %d\n", getpagesize());
	printf("page size: %d\n", sysconf(_SC_PAGESIZE));
	printf("number of pages of physical memory: %d (%.02fk)\n", sysconf(_SC_PHYS_PAGES), sysconf(_SC_PHYS_PAGES)/1024.0);
	printf("number of currently available pages of physical memory: %d (%.02fk)\n", sysconf(_SC_AVPHYS_PAGES), sysconf(_SC_AVPHYS_PAGES)/1024.0);

	// 22.1 Resource Usage
	printf("-----------------\n");
	struct rusage *rusage = malloc(sizeof(struct rusage));
	if (!getrusage(RUSAGE_SELF, rusage)) {
		printf("maximum resident set size used, in kilobytes: %d\n", rusage->ru_maxrss);
		printf("the amount of unshared memory used for data: %d\n", rusage->ru_idrss);
		printf("the amount of unshared memory used for stack space: %d\n", rusage->ru_isrss);
		free(rusage);
	}

	printf("-----------------\n");
	fgetc(stdin);

	free(sarray);
	free(larray);

	return 0;
}


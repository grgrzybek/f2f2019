#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.
#

cmake_minimum_required(VERSION 3.14)

# https://cmake.org/cmake/help/v3.14/command/project.html
project(f2f2019 VERSION 0.1.0
                DESCRIPTION "F2F 2019 presentation about low level foundation of Java, Go and C processes"
                HOMEPAGE_URL "https://github.com/grgrzybek/f2f2019")

# https://cmake.org/cmake/help/v3.14/command/set.html
set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/_install")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -g")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

# https://cmake.org/cmake/help/v3.14/module/FindThreads.html
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# https://cmake.org/cmake/help/v3.14/command/configure_file.html
configure_file(config.h.in "${CMAKE_INSTALL_PREFIX}/include/config.h")
include_directories("${CMAKE_INSTALL_PREFIX}/include" "${PROJECT_SOURCE_DIR}/include")

add_executable(cversion)
target_sources(cversion PUBLIC src/cversion.c)
#add_executable(threads)
#target_sources(threads PUBLIC src/threads.c)
#target_link_libraries(threads Threads::Threads)

# https://cmake.org/cmake/help/v3.14/module/FindJNI.html
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
add_library(nbridge SHARED src/nbridge.c)

# https://cmake.org/cmake/help/v3.14/command/install.html
install(TARGETS cversion RUNTIME DESTINATION bin)


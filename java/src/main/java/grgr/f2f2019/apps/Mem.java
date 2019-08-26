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
package grgr.f2f2019.apps;

import java.lang.management.ManagementFactory;
import javax.management.ObjectName;

public class Mem {

    public static void main(String[] args) throws Exception {
//        new ServerSocket().bind(new InetSocketAddress("localhost", 4242));
        Object name = ManagementFactory.getPlatformMBeanServer().getAttribute(new ObjectName("java.lang:type=Runtime"), "Name");
        System.out.println("PID: " + ((String)name).split("@")[0]);
        Runtime r = Runtime.getRuntime();
        long fm = r.freeMemory();
        long mm = r.maxMemory();
        long tm = r.totalMemory();
        System.out.println("Runtime.freeMemory(): " + fm + "b, " + fm / 1024 + "k, " + fm / (1024 * 1024) + "m");
        System.out.println("Runtime.maxMemory(): " + mm + "b, " + mm / 1024 + "k, " + mm / (1024 * 1024) + "m");
        System.out.println("Runtime.totalMemory(): " + tm + "b, " + tm / 1024 + "k, " + tm / (1024 * 1024) + "m");
        System.out.println("Hit <enter> to allocate quite big array");
        System.in.read();

        int[] array = new int[10 * 1024 * 1024];
        fm = r.freeMemory();
        mm = r.maxMemory();
        tm = r.totalMemory();
        System.out.println("Runtime.freeMemory(): " + fm + "b, " + fm / 1024 + "k, " + fm / (1024 * 1024) + "m");
        System.out.println("Runtime.maxMemory(): " + mm + "b, " + mm / 1024 + "k, " + mm / (1024 * 1024) + "m");
        System.out.println("Runtime.totalMemory(): " + tm + "b, " + tm / 1024 + "k, " + tm / (1024 * 1024) + "m");
        System.out.println("Hit <enter> to quit");
        System.in.read();


    }

}

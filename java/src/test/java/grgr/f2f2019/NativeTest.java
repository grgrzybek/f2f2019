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
package grgr.f2f2019;

import java.io.IOException;

import grgr.f2f2019.n.NativeBridge;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

public class NativeTest {

    private static NativeBridge NB;

    @BeforeAll
    public static void init() {
        NB = new NativeBridge();
    }

    @Test
    public void invokeJavaMethods() {
        NB.helloJava("Grzegorz");
    }

    @Test
    public void invokeNativeMethods() {
        NB.helloNative("Grzegorz");
    }

    @Test
    public void nativeProcessInformation() throws IOException {
        NB.processInformation();
        System.in.read();
    }

}

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
package grgr.f2f2019.n;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class NativeBridge {

    public static Logger LOG = LoggerFactory.getLogger(NativeBridge.class);

    static {
        System.load("/home/ggrzybek/sources/github.com/grgrzybek/f2f2019/c/build/Debug/libnbridge.so");
    }

    public native void helloNative(String name);

    public native void processInformation();

    public native void pthreads();

    public native void pthreadsAttached();

    public native void pthreadsAll();

    public void helloJava(String name) {
        LOG.info("Hello {}!", name);
    }

}

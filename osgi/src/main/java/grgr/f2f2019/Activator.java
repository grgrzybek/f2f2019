/*
 * Copyright 2005-2020 Red Hat, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package grgr.f2f2019;

import com.rh.example.NativeBridgeCallback;
import grgr.f2f2019.n.NativeBridge;
import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class Activator implements BundleActivator {

    private NativeBridge nb;

    @Override
    public void start(BundleContext context) throws Exception {
        System.loadLibrary("nbridge");
        nb = new NativeBridge();
        nb.helloJava("Hello Java");
        nb.helloNative("Hello Native");

        nb.helloNativeWithCallback("Hello Native", NativeBridgeCallback.class.getClassLoader());
    }

    @Override
    public void stop(BundleContext context) throws Exception {
        nb.helloNative("Goodbye Native");
        nb.helloJava("Goodbye Java");
    }

}

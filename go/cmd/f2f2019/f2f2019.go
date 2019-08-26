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
package main

import (
	"bufio"
	"fmt"
	"github.com/grgrzybek/f2f2019/pkg/f2f"
	"github.com/spf13/cobra"
	"os"
	"runtime"
)

func init() {
	var memCmd = &cobra.Command{
		Use:   "mem",
		Short: "Memory details",
		Run:   run,
	}
	f2f.RootCmd.AddCommand(memCmd)
}

func run(_ *cobra.Command, _ []string) {
	var m runtime.MemStats
	runtime.ReadMemStats(&m)
	fmt.Printf("Free memory (HeapAlloc): %d\n", m.HeapAlloc)

	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Hit <enter> to quit")
	_, _ = reader.ReadString('\n')
}

func main() {
	f2f.Execute()
}

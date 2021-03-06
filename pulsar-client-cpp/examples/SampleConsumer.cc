/**
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
#include <iostream>

#include <pulsar/Client.h>
#include <pulsar/Logger.h>

// #include <lib/LogUtils.h>

// DECLARE_LOG_OBJECT()

using namespace pulsar;

int main() {

    Client client("pulsar://localhost:6650");

    Consumer consumer;
    Result result = client.subscribe("persistent://prop/r1/ns1/my-topic", "consumer-1", consumer);
    if (result != ResultOk) {
        // LOG_ERROR("Failed to subscribe: " << result);
        std::cerr << "Failed to subscribe: " << result << std::endl;
        return -1;
    }

    Message msg;

    while (true) {
        consumer.receive(msg);
        // LOG_INFO("Received: " << msg << "  with payload '" << msg.getDataAsString() << "'");
        std::cout << "Received: " << msg << "  with payload '" << msg.getDataAsString() << "'" << std::endl;

        consumer.acknowledge(msg);
    }

    client.close();
}

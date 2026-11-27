//
// Created by User on 27/11/2026.
//

#include "NetClient.h"

#include <iostream>
#include <string>

int main() {
    NetClient client;
    if (!client.connect("172.25.107.126", 9000)) {
        return 1;
    }

    client.send_message("Hello from Alon!");

    // Keep client alive and poll for ~2 seconds so you see the server's reply
    for (int i = 0; i < 120 && client.is_connected(); ++i) {
        client.poll(16);
    }

    return 0;
}
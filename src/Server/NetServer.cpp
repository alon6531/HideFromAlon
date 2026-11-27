//
// Created by User on 27/11/2026.
//

#include "NetServer.h"

#include <iostream>
#include <ostream>

NetServer::~NetServer() {
    if (server) {
        enet_host_destroy(server);
        server = nullptr;
    }
    enet_deinitialize();
}

bool NetServer::initialize(enet_uint16 port, size_t max_peers, size_t channel_limit) {
    if (enet_initialize() != 0) {
        std::cerr << "Failed to initialize ENet\n";
        return false;
    }

    address.host = ENET_HOST_ANY;
    address.port = port;


    server = enet_host_create(&address, max_peers, channel_limit, 0, 0);
    if (server == nullptr) {
        std::cerr << "Failed to bind port " << port << "\n";
        return false;
    }

    std::cout << "Server listening on IP: " << address.host << "UDP port " << port << "\n" << std::endl;
    return true;

}

void NetServer::run() {
    running = true;
    ENetEvent event{};

    while (running)
    {
        while (enet_host_service(server, &event, 33) > 0)
        {
            switch (event.type) {

                case ENET_EVENT_TYPE_CONNECT: {
                    char ip[64]{};
                    enet_address_get_host_ip(&event.peer->address, ip, sizeof(ip));
                    std::cout << "Client connected from " << ip << ":" << event.peer->address.port << std::endl;
                    break;
                }
                case ENET_EVENT_TYPE_RECEIVE:
                    handle_receive_event(event);
                    break;

                case ENET_EVENT_TYPE_DISCONNECT: {
                    char ip[64]{};
                    enet_address_get_host_ip(&event.peer->address, ip, sizeof(ip));
                    std::cout << "client %x:%u disconnected \n" << ip << ":" << event.peer->address.port << std::endl;
                    break;
                }
                default:
                    break;

            }
        }
    }
}

void NetServer::handle_receive_event(const ENetEvent &event) {
    std::string msg(reinterpret_cast<char*>(event.packet->data), event.packet->dataLength);
    char ip[64]{};
    enet_address_get_host_ip(&event.peer->address, ip, sizeof(ip));
    std::cout << "Received: " << msg << " from " << ip << ":" << event.peer->address.port << "\n";


}


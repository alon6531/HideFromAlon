//
// Created by User on 27/11/2026.
//

#include "NetClient.h"

#include <iostream>

NetClient::~NetClient() {
    disconnect();
    if (client) {
        enet_host_destroy(client);
        client = nullptr;
    }
    enet_deinitialize();
}

bool NetClient::connect(const std::string& host, enet_uint16 port, size_t channels) {
    if (enet_initialize() != 0) {
        std::cerr << "Failed to initialize ENet\n";
        return false;
    }

    client = enet_host_create(nullptr, 1, channels, 0, 0);
    if (!client) {
        std::cerr << "Failed to create ENet client host\n";
        return false;
    }


    enet_address_set_host(&address, host.c_str());
    address.port = port;

    peer = enet_host_connect(client, &address, channels, 0);
    if (!peer) {
        std::cerr << "No available peers for initiating connection\n";
        return false;
    }

    ENetEvent event{};
    if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
        std::cout << "Connected to " << host << ":" << port << "\n";
        return true;
    }

    enet_peer_reset(peer);
    peer = nullptr;
    std::cerr << "Connection to " << host << ":" << port << " timed out\n";
    return false;
}

void NetClient::send_message(const std::string& msg) const {
    if (!peer) return;
    ENetPacket* pkt = enet_packet_create(msg.data(), msg.size(), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, pkt);
}

void NetClient::poll(enet_uint32 timeout_ms) {
    if (!client) return;

    ENetEvent event{};
    while (enet_host_service(client, &event, timeout_ms) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE: {
                std::string reply(reinterpret_cast<char*>(event.packet->data), event.packet->dataLength);
                std::cout << "[Server]: " << reply << "\n";
                enet_packet_destroy(event.packet);
                break;
            }
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected from server\n";
                peer = nullptr;
                break;
            default:
                break;
        }
    }
}

void NetClient::disconnect() {
    if (!peer || !client) return;

    enet_peer_disconnect(peer, 0);
    ENetEvent event{};
    while (enet_host_service(client, &event, 1000) > 0) {
        if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            enet_packet_destroy(event.packet);
        } else if (event.type == ENET_EVENT_TYPE_DISCONNECT) {
            break;
        }
    }
    peer = nullptr;
}
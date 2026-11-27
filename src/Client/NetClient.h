//
// Created by User on 27/11/2026.
//

#ifndef HIDEFROMALON_NETCLIENT_H
#define HIDEFROMALON_NETCLIENT_H
#include <string>
#include "enet/enet.h"


class NetClient {
public:
    NetClient() = default;
    ~NetClient();

    bool connect(const std::string& host, enet_uint16 port, size_t channels = 2);
    void send_message(const std::string& msg) const;
    void poll(enet_uint32 timeout_ms = 16);
    void disconnect();

    [[nodiscard]] bool is_connected() const { return peer != nullptr; }

private:
    ENetAddress address;
    ENetHost* client = nullptr;
    ENetPeer* peer = nullptr;
};

#endif //HIDEFROMALON_NETCLIENT_H
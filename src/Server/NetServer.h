//
// Created by User on 27/11/2026.
//

#ifndef HIDEFROMALON_NETSERVER_H
#define HIDEFROMALON_NETSERVER_H

#include <enet/enet.h>

class NetServer {
public:
    NetServer() = default;
    ~NetServer();

    bool initialize(enet_uint16 port, size_t max_peers, size_t channel_limit);
    void run();

private:
    ENetAddress address{};
    ENetHost* server = nullptr;
    bool running = false;

    void handle_receive_event(const ENetEvent &event);

};


#endif //HIDEFROMALON_NETSERVER_H
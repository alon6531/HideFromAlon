#include <iostream>

#include "NetServer.h"
#include "Config.h"

int main() {
    const ServerConfig cfg = ServerConfig::from_env();

    NetServer server;
    if (!server.initialize(cfg.port, cfg.max_peers, cfg.channel_limit)) {
        return 1;
    }

    server.run();
    return 0;
}
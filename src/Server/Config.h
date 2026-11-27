//
// Created by User on 27/11/2026.
//

#ifndef HIDEFROMALON_CONFIG_H
#define HIDEFROMALON_CONFIG_H
#include <enet/enet.h>
#include <cstdint>
#include <string>

struct ServerConfig {
    uint16_t port = 9000;
    size_t max_peers = 10;
    size_t channel_limit = 2;
    int tick_rate = 30;
    int seeker_count = 2;
    float vision_radius = 140.0f;

    static ServerConfig from_env() {
        ServerConfig cfg;
        cfg.port          = static_cast<enet_uint16>(read_int("SERVER_PORT", cfg.port));
        cfg.max_peers     = static_cast<size_t>(read_int("MAX_PEERS", static_cast<int>(cfg.max_peers)));
        cfg.channel_limit = static_cast<size_t>(read_int("CHANNEL_LIMIT", static_cast<int>(cfg.channel_limit)));
        cfg.tick_rate     = read_int("TICK_RATE", cfg.tick_rate);
        cfg.seeker_count  = read_int("SEEKER_COUNT", cfg.seeker_count);
        cfg.vision_radius = read_float("VISION_RADIUS", cfg.vision_radius);
        return cfg;
    }

private:
    static int read_int(const char* key, int fallback) {
        if (const char* v = std::getenv(key); v && *v) {
            try { return std::stoi(v); } catch (...) {}
        }
        return fallback;
    }

    static float read_float(const char* key, float fallback) {
        if (const char* v = std::getenv(key); v && *v) {
            try { return std::stof(v); } catch (...) {}
        }
        return fallback;
    }
};

#endif //HIDEFROMALON_CONFIG_H
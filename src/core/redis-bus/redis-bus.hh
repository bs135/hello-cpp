#pragma once

#ifndef CORE_REDIS_BUS_H
#define CORE_REDIS_BUS_H

#include <string>
#include <sw/redis++/redis++.h>
// #include <sw/redis++/async_redis++.h>

#define REDIS_HOST_DEFAULT "127.0.0.1"
#define REDIS_PORT_DEFAULT 6379
#define REDIS_DB_DEFAULT 0
#define REDIS_PASS_DEFAULT ""

class RedisBus
{
private:
    std::string _host;
    int _port;
    int _db;
    std::string _pass;

public:
    RedisBus();
    RedisBus(std::string host, int port, int db, std::string pass);
    // RedisBus(const RedisBus &rd);
    // RedisBus &operator=(const RedisBus &rhs)
    ~RedisBus();

    void Connect();
    void Loop();
};

#endif
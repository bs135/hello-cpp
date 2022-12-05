#pragma once

#ifndef CORE_REDIS_BUS_H
#define CORE_REDIS_BUS_H

#include <iostream>
#include <string>
#include <sw/redis++/redis++.h>
// #include <sw/redis++/async_redis++.h>

using namespace sw::redis;
using namespace std;

#define REDIS_HOST_DEFAULT "127.0.0.1" // localhost
#define REDIS_PORT_DEFAULT 6379
#define REDIS_DB_DEFAULT 0
#define REDIS_PASS_DEFAULT ""

class RedisBus
{
private:
    ConnectionOptions _opts;
    Redis *_redis_client;

public:
    RedisBus();
    RedisBus(string host, int port, int db, string pass);
    //  RedisBus(const RedisBus &rd);
    //  RedisBus &operator=(const RedisBus &rhs)
    ~RedisBus();

    using MsgHandler = std::function<void(std::string, std::string)>;

    void Connect();
    void Publish(string topic, string message);
    void Subscribe(string topic, MsgHandler handler);
    void Loop();
    void Stop();
};

#endif
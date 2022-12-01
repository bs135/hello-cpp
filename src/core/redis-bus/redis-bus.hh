#pragma once

#ifndef CORE_REDIS_BUS_H
#define CORE_REDIS_BUS_H

#include <iostream>
#include <string>
#include <sw/redis++/redis++.h>
// #include <sw/redis++/async_redis++.h>

using namespace sw::redis;
using namespace std;

#define REDIS_HOST_TEST "192.168.1.24"
#define REDIS_HOST_DEFAULT "120.0.0.1"
#define REDIS_PORT_DEFAULT 6379
#define REDIS_DB_DEFAULT 0
#define REDIS_PASS_DEFAULT ""

class RedisBus
{
private:
    ConnectionOptions _opts;
    Redis *_redis_client;

public:
    RedisBus() : RedisBus(REDIS_HOST_TEST, REDIS_PORT_DEFAULT, REDIS_DB_DEFAULT, REDIS_PASS_DEFAULT) {}
    RedisBus(string host, int port, int db, string pass);
    //  RedisBus(const RedisBus &rd);
    //  RedisBus &operator=(const RedisBus &rhs)
    ~RedisBus();

    void Connect();
    void Publish(string topic, string message);
    // template <typename MsgCb>
    void Subscribe(string topic);
    void Loop();
    void Stop();
};

#endif
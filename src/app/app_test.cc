/**
 * @file app.hh
 * @author bs
 * @brief
 * @version 0.1
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <climits>
#include <string>
#include "log.h"
#include "app_test.hh"

void test_handler1(string topic, string msg)
{
    log_debug("message [{}]: {}", topic, msg);
}

void test_handler2(string topic, string msg)
{
    log_debug("message [{}]: {}", topic, msg);
}

void test_wildcard_handler(string topic, string msg)
{
    log_debug("message [{}]: {}", topic, msg);
}

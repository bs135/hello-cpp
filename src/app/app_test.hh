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

#pragma once

#ifndef APP_TEST_H
#define APP_TEST_H

#include <string>

using namespace std;

void test_handler1(string topic, string msg);
void test_handler2(string topic, string msg);
void test_wildcard_handler(string topic, string msg);

#endif
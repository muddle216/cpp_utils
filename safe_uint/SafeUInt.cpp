//
// Created by LC on 2022/4/18.
//

#include "Log.h"

using namespace ZEngine;

void SafeUIntLogger::log(const char *func, uint64_t a, uint64_t b, uint64_t result, uint64_t operatorResult) {
    if (operatorResult != result) {
        LOG_ERROR("SafeUIntTpl overflow|%s(%llu, %llu) = %llu|operatorResult = %llu", func, a, b, result, operatorResult);
    } else {
        LOG_DEBUG("SafeUIntTpl|%s(%llu, %llu) = %llu", func, a, b, result);
    }
}
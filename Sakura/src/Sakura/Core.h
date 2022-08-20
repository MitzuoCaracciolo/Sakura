#pragma once

#include <utility>
#include <stdint.h>

#include "Sakura/Log.h"

using byte = uint8_t;

using int32 = int32_t;
using int16 = int16_t;
using int8 = int8_t;

using uint32 = uint32_t;
using uint16 = uint16_t;
using uint8 = uint8_t;

#define SAKURA_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
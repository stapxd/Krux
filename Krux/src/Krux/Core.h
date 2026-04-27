#pragma once

#include "Log.h"

#define KRX_ENABLE_ASSERT 1

#if KRX_ENABLE_ASSERT
	#define KRX_CORE_ASSERT(x, ...) { if(!(x)) { KRX_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define KRX_ASSERT(x, ...)      { if(!(x)) { KRX_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define KRX_CORE_ASSERT(x, ...)
	#define KRX_ASSERT(x, ...)
#endif

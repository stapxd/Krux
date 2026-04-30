#pragma once

#include "Log.h"

#ifndef KRX_SYS_WINDOWS
	#error "Krux supports only windows!"
#endif

// Macros
#define BIND_EVENT_FUNC(name) [this](auto& event) { return name(event); }
#define BIT(x) (1 << x)

#define KRX_ENABLE_ASSERT 1

#if KRX_ENABLE_ASSERT
	#define KRX_INTERNAL_ASSERT_MSG(type, x, ...) { if(!(x)) { KRX##type##ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define KRX_INTERNAL_ASSERT_NO_MSG(type, x)   { if(!(x)) { KRX##type##ERROR("Assertion failed at {0}:{1}", __FILE__, __LINE__); __debugbreak(); } }

	#define KRX_GET_ASSERT_MACRO(_1, _2, NAME, ...) NAME

	#define KRX_EXPAND_MACRO(x) x
	#define KRX_ASSERT_DISPATCH(type, ...) \
		KRX_EXPAND_MACRO(KRX_GET_ASSERT_MACRO(__VA_ARGS__, KRX_INTERNAL_ASSERT_MSG, KRX_INTERNAL_ASSERT_NO_MSG)(type, __VA_ARGS__))

	#define KRX_CORE_ASSERT(...) KRX_ASSERT_DISPATCH(_CORE_, __VA_ARGS__)
	#define KRX_ASSERT(...)      KRX_ASSERT_DISPATCH(_, __VA_ARGS__)
#else
	#define KRX_CORE_ASSERT(...)
	#define KRX_ASSERT(...)
#endif

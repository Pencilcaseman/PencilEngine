#pragma once

#include <pcpch.h>

#ifdef PC_PLATFORM_WINDOWS
#ifdef PC_BUILD_DLL
#define PENCIL_API __declspec(dllexport)
#else
#define PENCIL_API __declspec(dllimport)
#endif
#else
#error PencilEngine only supports Windows
#endif

#ifdef PC_ENABLE_ASSERT
#define PC_ASSERT(cond, msg, ...) if (!cond) { PC_FATAL(msg, __VA_ARGS__); __debugbreak(); }
#define PC_CORE_ASSERT(cond, msg, ...) if (!cond) { PC_CORE_FATAL(msg, __VA_ARGS__); __debugbreak(); }
#else
#define PC_ASSERT(cond, msg, ...)
#define PC_CORE_ASSERT(cond, msg, ...)
#endif

#define BIT(n) (1 << n)

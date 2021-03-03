#pragma once

#ifdef PC_PLATFORM_WINDOWS
#ifdef PC_BUILD_DLL
#define PENCIL_API __declspec(dllexport)
#else
#define PENCIL_API __declspec(dllimport)
#endif
#else
#error PencilEngine only supports Windows
#endif

#pragma once

#ifdef SAKURA_PLATFORM_WINDOWS
	#ifdef SAKURA_BUILD_DLL
		#define SAKURA_API __declspec(dllexport)
	#else
		#define SAKURA_API __declspec(dllimport)
	#endif
#else 
    #error Sakura only supports Windows
#endif
// dllmain.cpp : Defines the entry point for the DLL application.

#include <Windows.h>

#include "DLL.hpp"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DLL::init();
        break;
    case DLL_PROCESS_DETACH:
        DLL::quit();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}


#include "includes.h"

DWORD WINAPI Main(HMODULE hModule) {
    void* p_endScene = hook::GetPointerEndScene();
    hook::InstallHook(p_endScene);
    return 0; 
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, hModule, 0, nullptr));
    }
    return TRUE;
}


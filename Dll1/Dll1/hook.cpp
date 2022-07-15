#include "includes.h"

LPVOID p_mem;

_declspec(naked) void hook::Pit()
{
    static volatile LPDIRECT3DDEVICE9 pDevise = nullptr;

    __asm {
        pushad
        pushfd
        mov esi, [esp + 0x28]
        mov pDevise, esi
    }

    draftsman::Paint(pDevise);

    __asm {
        popfd
        popad
        jmp[p_mem]
    }
}

void* hook::GetPointerEndScene()
{
    IDirect3DDevice9* fakeDevise;
    IDirect3D9* p_vmt = Direct3DCreate9(D3D_SDK_VERSION);
    D3DPRESENT_PARAMETERS d3dParams;
    ZeroMemory(&d3dParams, sizeof(d3dParams));
    d3dParams.Windowed = true;
    d3dParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dParams.hDeviceWindow = GetForegroundWindow();
    p_vmt->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dParams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dParams, &fakeDevise);
    void* p_endScene = *(*(void***)fakeDevise + 0x2A);
    fakeDevise->Release();
    p_vmt->Release();
    return p_endScene;
}

void hook::InstallHook(void* p_endScene)
{
    DWORD oldProtect;
    uintptr_t src;
    uintptr_t dst;
    p_mem = VirtualAlloc(NULL, 12, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(p_mem, p_endScene, 7);
    dst = (uintptr_t)p_endScene + 7;
    src = (uintptr_t)p_mem + 7;
    *(byte*)src = 0xE9;
    *(uintptr_t*)(src + 1) = dst - src - 5;
    VirtualProtect(p_endScene, 10, PAGE_EXECUTE_READWRITE, &oldProtect);
    *(byte*)p_endScene = 0xE9;
    src = (uintptr_t)p_endScene;
    dst = (uintptr_t)Pit;
    *(uintptr_t*)(src + 1) = dst - src - 5;
    VirtualProtect(p_endScene, 10, oldProtect, &oldProtect);
}

#include <windows.h>
#include "../offsets.h"

namespace viewmodel_fov{
    extern bool isInit = false;
    static float oldFov;

    static void Viewmodel_init(){
        if (isInit) return;

        oldFov = *(float*)(сlient_t + 0x1A762AC);

        DWORD oldProtect;
    
        BYTE* opcodes[5] = {
            (BYTE*)(сlient_t + 0x804E16),
            (BYTE*)(сlient_t + 0x804E2A),
            (BYTE*)(сlient_t + 0x7FA14B),
            (BYTE*)(сlient_t + 0x7FA15A),
            (BYTE*)(сlient_t + 0x7FA2CB)
        };
    
        const BYTE nops[8] = { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
    
        for(size_t i = 0; i < 5; i++)
            VirtualProtect(opcodes[i], 1, PAGE_EXECUTE_READWRITE, &oldProtect);
    
        for(size_t i = 0; i < 5; i++)
            memcpy(opcodes[i], nops, 8);
    
        for(size_t i = 0; i < 5; i++)
            VirtualProtect(opcodes[i], 1, oldProtect, &oldProtect);
        
        isInit = !isInit;
    }
}
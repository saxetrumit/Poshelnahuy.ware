#define _CRT_SECURE_NO_WARNINGS
#include "windows.h"
#include <stdio.h>
#include "menu.h"

void WINAPI INIT() {

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    printf(R"EOF(
            _......._
       .-'.'.'.'.'.'.`-.
     .'.'.'.'.'.'.'.'.'.`.
    /.'.'               '.\
    |.'    _.--...--._     |
    \    `._.-.....-._.'   /                   - make your decisions right nigga
    |     _..- .-. -.._   |
 .-.'    `.   ((@))  .'   '.-.
( ^ \      `--.   .-'     / ^ )
 \  /         .   .       \  /
 /          .'     '.  .-    \
( _.\    \ (_`-._.-'_)    /._\)
 `-' \   ' .--.          / `-'
     |  / /|_| `-._.'\   |
     |   |       |_| |   /-.._
 _..-\   `.--.______.'  |
      \       .....     |
       `.  .'      `.  /
         \           .'
          `-..___..-`
          
    )EOF");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)INIT, NULL, 0, NULL);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)OVERLAY_THREAD, NULL, 0, NULL);
    }
    return TRUE;
}


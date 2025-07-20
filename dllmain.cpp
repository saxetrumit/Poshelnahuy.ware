#define _CRT_SECURE_NO_WARNINGS
#include "windows.h"
#include <stdio.h>

void WINAPI INIT() {
    HANDLE hRead, hWrite;

    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };

    AllocConsole();
    freopen("CONOUT$", "w", stdout);


    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) return;

    if (!SetStdHandle(STD_OUTPUT_HANDLE, hWrite) || !SetStdHandle(STD_ERROR_HANDLE, hWrite)) return;

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

    printf("\n");

    DWORD bytesRead;
    char buffer[256];
    while (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved){
    if (ul_reason_for_call) {
        HANDLE hMainThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)INIT, NULL, 0, NULL);
    }
    return TRUE;
}


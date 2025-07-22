#include <Windows.h>
#include <stdio.h>
#include <d3d11.h>
#include <dxgi.h>
#include "kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

typedef struct SDL_Window SDL_Window;

typedef SDL_Window** (__stdcall* SDL_GetWindows)(int * count);
typedef bool (__stdcall* SDL_SetWindowRelativeMouseMode)(SDL_Window* window, bool enabled);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

HMODULE hSDL3 = GetModuleHandleA("SDL3.dll");

SDL_SetWindowRelativeMouseMode pSDL_SetWindowRelativeMouseMode;
SDL_GetWindows pSDL_GetWindows;

bool MENU_ACTIVE = false;
bool MOUSE_CAPTURE_STATE = false;
int windows = 0;

void InitImGui()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (MENU_ACTIVE){
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) 
            return false;
        if (uMsg) return true;
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    if (!init) {
        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
            pDevice->GetImmediateContext(&pContext);
            DXGI_SWAP_CHAIN_DESC sd;
            pSwapChain->GetDesc(&sd);
            window = sd.OutputWindow;
            ID3D11Texture2D* pBackBuffer;
            pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
            pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
            pBackBuffer->Release();
            oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
            InitImGui();
            init = true;

			pSDL_SetWindowRelativeMouseMode = (SDL_SetWindowRelativeMouseMode)GetProcAddress(hSDL3, "SDL_SetWindowRelativeMouseMode");
            pSDL_GetWindows = (SDL_GetWindows)GetProcAddress(hSDL3, "SDL_GetWindows");
        }
        else
            return oPresent(pSwapChain, SyncInterval, Flags);
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

	if ((GetAsyncKeyState(VK_INSERT) & 0x01)){
		MENU_ACTIVE = !MENU_ACTIVE;
        pSDL_SetWindowRelativeMouseMode(pSDL_GetWindows(&windows)[0], MOUSE_CAPTURE_STATE);
        MOUSE_CAPTURE_STATE = !MOUSE_CAPTURE_STATE;
	}

    ImGui::GetIO().MouseDrawCursor = MENU_ACTIVE;

    ImGui::NewFrame();
	if (MENU_ACTIVE){
		ImGui::Begin("Poshelnahuy.ware");
		ImGui::End();
	}

    ImGui::Render();
    pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI OVERLAY_THREAD(LPVOID lpReserved) {
    bool init_hook = false;
    do {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
            kiero::bind(8, (void**)&oPresent, (void*)hkPresent);
            init_hook = true;
        }
    } while (!init_hook);
    return TRUE;
}
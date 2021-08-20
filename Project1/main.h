#pragma once
#include <iostream>
#include <windows.h>
#include <thread>
bool loader_active = true;
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")
IDirect3DTexture9* masterlogo;

#include "others/ImGui/imgui.h"
#include "others/ImGui/imgui_impl_dx9.h"
#include "others/ImGui/imgui_impl_win32.h"
//
#include "auth/auth.h"
#include "auth/hwid.h"
#include "termcolor.hpp"
#include "remember.h"
#include "xorstr.h"
#include "xorstring.h"
#include "cheat/functions.h"
//

static int width = 440;
static int height = 380;
static int mastergui = 0;
HWND main_hwnd = nullptr;

LPDIRECT3DDEVICE9        g_pd3dDevice;
D3DPRESENT_PARAMETERS    g_d3dpp;
LPDIRECT3D9              g_pD3D;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return false;

	// Create the D3DDevice
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;
	return true;
}

void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

static std::string random_string(int length)
{
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	std::random_device rd;
	std::mt19937 generator(rd());
	std::shuffle(str.begin(), str.end(), generator);
	return str.substr(0, length);    // assumes 32 < number of characters in str         
}
static DWORDLONG random_number(DWORDLONG min, DWORDLONG max)
{
	srand(time(0));
	DWORDLONG out = min + rand() % (max - min + 1);
	return out;
}
static std::string randomclassname = random_string(random_number(4, 16));

int APIENTRY WindownsMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, randomclassname.c_str(), NULL };
	RegisterClassEx(&wc);
	main_hwnd = CreateWindow(wc.lpszClassName, randomclassname.c_str(), WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);

	if (!CreateDeviceD3D(main_hwnd)) {
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}
	ShowWindow(main_hwnd, SW_HIDE);
	UpdateWindow(main_hwnd);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
	{
		return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
	};

	auto& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	const ImVec4 bgColor = ColorFromBytes(37, 37, 38);
	const ImVec4 lightBgColor = ColorFromBytes(82, 82, 85);
	const ImVec4 veryLightBgColor = ColorFromBytes(90, 90, 95);

	const ImVec4 panelColor = ColorFromBytes(51, 51, 55);
	const ImVec4 panelHoverColor = ColorFromBytes(29, 151, 236);
	const ImVec4 panelActiveColor = ColorFromBytes(0, 224, 255);

	const ImVec4 textColor = ColorFromBytes(255, 255, 255);
	const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
	const ImVec4 borderColor = ColorFromBytes(78, 78, 78);

	colors[ImGuiCol_Text] = textColor;
	colors[ImGuiCol_TextDisabled] = textDisabledColor;
	colors[ImGuiCol_TextSelectedBg] = panelActiveColor;
	colors[ImGuiCol_WindowBg] = bgColor;
	colors[ImGuiCol_ChildBg] = ColorFromBytes(121, 121, 121);;
	colors[ImGuiCol_PopupBg] = bgColor;
	colors[ImGuiCol_Border] = borderColor;
	colors[ImGuiCol_BorderShadow] = borderColor;
	colors[ImGuiCol_FrameBg] = panelColor;
	colors[ImGuiCol_FrameBgHovered] = panelHoverColor;
	colors[ImGuiCol_FrameBgActive] = panelActiveColor;
	colors[ImGuiCol_TitleBg] = bgColor;
	colors[ImGuiCol_TitleBgActive] = bgColor;
	colors[ImGuiCol_TitleBgCollapsed] = bgColor;
	colors[ImGuiCol_MenuBarBg] = panelColor;
	colors[ImGuiCol_ScrollbarBg] = panelColor;
	colors[ImGuiCol_ScrollbarGrab] = lightBgColor;
	colors[ImGuiCol_ScrollbarGrabHovered] = veryLightBgColor;
	colors[ImGuiCol_ScrollbarGrabActive] = veryLightBgColor;
	colors[ImGuiCol_CheckMark] = panelActiveColor;
	colors[ImGuiCol_SliderGrab] = panelHoverColor;
	colors[ImGuiCol_SliderGrabActive] = panelActiveColor;
	colors[ImGuiCol_Button] = panelColor;
	colors[ImGuiCol_ButtonHovered] = panelHoverColor;
	colors[ImGuiCol_ButtonActive] = panelHoverColor;
	colors[ImGuiCol_Header] = panelColor;
	colors[ImGuiCol_HeaderHovered] = panelHoverColor;
	colors[ImGuiCol_HeaderActive] = panelActiveColor;
	colors[ImGuiCol_Separator] = borderColor;
	colors[ImGuiCol_SeparatorHovered] = borderColor;
	colors[ImGuiCol_SeparatorActive] = borderColor;
	colors[ImGuiCol_ResizeGrip] = bgColor;
	colors[ImGuiCol_ResizeGripHovered] = panelColor;
	colors[ImGuiCol_ResizeGripActive] = lightBgColor;
	colors[ImGuiCol_PlotLines] = panelActiveColor;
	colors[ImGuiCol_PlotLinesHovered] = panelHoverColor;
	colors[ImGuiCol_PlotHistogram] = panelActiveColor;
	colors[ImGuiCol_PlotHistogramHovered] = panelHoverColor;
	colors[ImGuiCol_DragDropTarget] = bgColor;
	colors[ImGuiCol_NavHighlight] = bgColor;
	colors[ImGuiCol_DockingPreview] = panelActiveColor;
	colors[ImGuiCol_Tab] = bgColor;
	colors[ImGuiCol_TabActive] = panelActiveColor;
	colors[ImGuiCol_TabUnfocused] = bgColor;
	colors[ImGuiCol_TabUnfocusedActive] = panelActiveColor;
	colors[ImGuiCol_TabHovered] = panelHoverColor;

	style.WindowRounding = 0.0f;
	style.ChildRounding = 0.0f;
	style.FrameRounding = 0.0f;
	style.GrabRounding = 0.0f;
	style.PopupRounding = 0.0f;
	style.ScrollbarRounding = 0.0f;
	style.TabRounding = 0.0f;

	ImGui_ImplWin32_Init(main_hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	DWORD window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar;
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	auto x = float(screen_rect.right - width) / 2.f;
	auto y = float(screen_rect.bottom - height) / 2.f;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(width, height));
			ImGui::SetNextWindowBgAlpha(1.0f);

			ImGui::Begin(randomclassname.c_str(), &loader_active, window_flags);
			{
				if (mastergui == 1) {
					ImGui::Spacing();
					ImGui::Text("");
					ImGui::SameLine(15);
					ImGui::BeginChild("too big", ImVec2(200.0f, 250.0f));
					ImGui::Spacing();
					ImGui::Text("");
					ImGui::SameLine(60);
					ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "Features");
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Admin Flag").c_str(), &admin_flag_checkboxx);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Spiderman").c_str(), &spiderman_checkboxx);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Fov Changer").c_str(), &fov_changer_checbox);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Gravity").c_str(), &gravity_checkboxx);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Jump Shot").c_str(), &jumpshot_checkbox);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Fast Eoka").c_str(), &super_eoka_checkbox);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Fast Bow").c_str(), &fast_bow_checkbox);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Time Changer").c_str(), &change_time_checkbox);
					ImGui::EndChild();
					ImGui::SameLine();
					ImGui::BeginChild("too big2", ImVec2(200.0f, 250.0f));
					ImGui::Spacing();
					ImGui::Text("");
					ImGui::SameLine(70);
					ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "Weapons");
					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("No Recoil ").c_str(), &no_recoil_checkbox);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("No Spread").c_str(), &nospread_checkbox);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Force Full Automatic").c_str(), &full_automatic_checkbox);
					ImGui::Spacing();
					ImGui::SameLine(10);
					ImGui::Checkbox(_xor_("Fat Bullet (Risky)").c_str(), &fat_bullet_checkbox);

					if (fov_changer_checbox == TRUE) {
						ImGui::Spacing();
						ImGui::Text("");
						ImGui::SameLine(65);
						ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "FOV Value");
						ImGui::Text("");
						ImGui::SameLine(10);
						ImGui::PushItemWidth(180);
						ImGui::SliderFloat(_xor_("##Fov Value").c_str(), &fov_valuee, 70, 150, "% .0f");
					}
					if (gravity_checkboxx == TRUE) {
						ImGui::Spacing();
						ImGui::Text("");
						ImGui::SameLine(50);
						ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "Gravity Value");
						ImGui::Text("");
						ImGui::SameLine(10);
						ImGui::PushItemWidth(180);
						ImGui::SliderFloat(_xor_("##Gravity Value").c_str(), &gravity_distancee, 1, 10, "% .1f");
					}
					if (change_time_checkbox == TRUE) {
						ImGui::Spacing();
						ImGui::Text("");
						ImGui::SameLine(65);
						ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "Day Time");
						ImGui::Text("");
						ImGui::SameLine(10);
						ImGui::PushItemWidth(180);
						ImGui::SliderInt(_xor_("##Time Value").c_str(), &time_ammout, 1, 24);
					}
					ImGui::EndChild();
				}
			}
			ImGui::End();
		}
		ImGui::EndFrame();

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ResetDevice();
		}
		if (!loader_active) {
			msg.message = WM_QUIT;
		}
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	CleanupDeviceD3D();
	DestroyWindow(main_hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;
	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
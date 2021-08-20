#include <iostream>
#include <random>
#include <Windows.h>
#include <memory>
#include <TlHelp32.h>
#include <mutex>
#include <urlmon.h>
#pragma comment (lib, "urlmon.lib")
//
#include "main.h"
//

using namespace std;

std::string response;
void login()
{
	get_calc_hwid();

	response = Login(license, md5(hwid_data));

	if (response == " true") {
		mastergui = 1;
	}
	else if (response == " new") {
		MessageBoxA(0, XorStr("Try login again"), XorStr("New License"), MB_OK | MB_ICONINFORMATION);
		exit(1);
	}
	else if (response == " false") {
		MessageBoxA(0, XorStr("Wrong HWID or user"), XorStr("Error"), MB_OK | MB_ICONERROR);
		exit(1);
	}
	else {
		MessageBoxA(0, XorStr("Unknown error"), XorStr("Error"), MB_OK | MB_ICONERROR);
		exit(1);
	}
}
void all_features() {
	admin_flag();
	SleepEx(2, true);

	spiderman();
	gravity();
	change_fov();
	change_time();
	jump_shot();
	no_recoil();
	FatBullet();
}
void InitLockalPlayer()
{
	process_id = get_process_id("RustClient.exe");
	game_assembly_base_adress = get_module_base_address("GameAssembly.dll");
	unity_player_base_adress = get_module_base_address("UnityPlayer.dll");

	std::cout << termcolor::bright_blue << " [+] " << termcolor::white << "Process ID: " << termcolor::bright_blue << process_id << std::endl;
	std::cout << termcolor::bright_blue << " [+] " << termcolor::white << "Base Adress: " << termcolor::bright_blue << game_assembly_base_adress << std::endl;
	std::cout << termcolor::bright_blue << " [+] " << termcolor::white << "Unity Player: " << termcolor::bright_blue << unity_player_base_adress << std::endl;

	long long i = 0;
	UINT64  ObjMgr = safe_read(unity_player_base_adress + 0x17C1F18, UINT64);
	UINT64  Obj = safe_read(ObjMgr + 0x8, UINT64);

	bool LP_isValid = false;

	for (UINT64 Obj = safe_read(ObjMgr + 0x8, UINT64); (Obj && (Obj != safe_read(ObjMgr, UINT64))); Obj = safe_read(Obj + 0x8, UINT64))
	{
		UINT64 GameObject = safe_read(Obj + 0x10, UINT64);
		WORD Tag = safe_read(GameObject + 0x54, WORD);

		if (Tag == 6 || Tag == 5 || Tag == 20011)
		{
			UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
			UINT64 Entity = safe_read(ObjClass + 0x18, UINT64);
			if (Tag == 6)
			{
				Player2 = safe_read(Entity + 0x28, UINT64);
				if (safe_read(safe_read(GameObject + 0x60, UINT64), UINT64) == 0x616C506C61636F4C)
				{
					LP_isValid = true;
					Player2;
					while (true) {
						all_features();
					}
					SleepEx(2, true);
				}
			}
			else if (Tag == 5)
			{
				UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
				UINT64 Entity = safe_read(ObjClass + 0x18, UINT64);
			}
			else if (Tag == 20011)
			{
				UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
				UINT64    Entity = safe_read(ObjClass + 0x18, UINT64);
				UINT64 Dome = safe_read(Entity + 0x28, UINT64);
				TodCycle = safe_read(Dome + 0x38, UINT64);
			}
		}
	}
	SleepEx(2, true);
}
void loadcheat() {
	std::thread(&InitLockalPlayer).detach();
}
int main() {
	//
	read_username();
	config_create_control_2();
	klasor_kontrol();

	if (mastergui == 0) {
		write_username();
		login();
	}
	if (mastergui == 1) {
		system("cls");
		std::cout << termcolor::yellow << " [+] Open Rust, Join Server and Press Enter.";
		std::cout << "" << std::endl;
		cin.get();
		loadcheat();
		WindownsMain(0,0,0,0);
	}
}
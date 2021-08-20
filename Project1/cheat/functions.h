#include "../cheat/cheat.h"
#include "../offsets.h"
#include "../settings.h"

//
#define safe_read(Addr, Type) Read<Type>(Addr)
#define safe_write(Addr, Data, Type) write<Type>(Addr, Data)

std::mutex mtx;

UINT64 GetHeldItem(UINT64 LocalPlayer)
{
	const auto base_player = LocalPlayer;
	const auto active_item_id = safe_read(base_player + oActiveUID, UINT64);
	const auto player_inventory = safe_read(base_player + oPlayerInventory, UINT64);
	const auto inventory_belt = safe_read(player_inventory + oContainerBelt, UINT64);
	const auto belt_contents_list = safe_read(inventory_belt + oBeltContentList, UINT64);
	const auto belt_contents_sz = safe_read(belt_contents_list + 0x14, uint32_t);
	const auto belt_contents = safe_read(belt_contents_list + 0x10, UINT64);

	for (auto i = 0u; i <= 6; i++)
	{
		if (belt_contents != 0)
		{
			const auto current_item = safe_read(belt_contents + (0x20 + (i * 8)), UINT64);
			if (!current_item) continue;
			if (active_item_id == safe_read(current_item + 0x28, uint32_t)) return current_item;
		}
	}
}
int get_item_id(uintptr_t item)
{
	return safe_read(item + 0x18, UINT64);
}
std::wstring get_item_name(uintptr_t item)
{
	auto unk = safe_read(item + 0x20, UINT64);
	unk = safe_read(unk + 0x20, UINT64);
	return read_wstring(unk + 0x14, 14);
}
bool is_weapon(uintptr_t helditem)
{
	auto ItemName = get_item_name(helditem);
	if (ItemName.find(L"rifle") != std::string::npos) return true;
	if (ItemName.find(L"pistol") != std::string::npos) return true;
	if (ItemName.find(L"bow") != std::string::npos) return true;
	if (ItemName.find(L"lmg") != std::string::npos) return true;
	if (ItemName.find(L"shotgun") != std::string::npos) return true;
	if (ItemName.find(L"smg") != std::string::npos) return true;
	else return false;
}

bool admin_flag() {

	mtx.lock();
	auto _local_player = Player2;
	mtx.unlock();

	if (!_local_player) {
		return false;
	}
	auto player_flags = safe_read(_local_player + oPlayerFlags, uintptr_t);
	if (!player_flags) {
		return false;
	}
	if (admin_flag_checkboxx == true) {
		player_flags |= 4;
		safe_write(_local_player + oPlayerFlags, player_flags, uintptr_t);
		return true;
	}
}
bool spiderman() {
	auto _local_player = Player2;
	if (spiderman_checkboxx) {
		auto base_movement = safe_read(Player2 + oPlayerMovement, uintptr_t);
		if (!base_movement) {
			return false;
		}
		safe_write(base_movement + oGroundAngle, 0.f, float);
		safe_write(base_movement + oGroundAngleNew, 0.f, float);
		return true;
	}
}
bool gravity() {
	auto _local_player = Player2;
	if (gravity_checkboxx == true) {
		auto base_movement = safe_read(Player2 + oPlayerMovement, uintptr_t);
		if (!base_movement) {
			return false;
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			safe_write(base_movement + oGravityMultiplier, gravity_distancee / 2, float);
		}
		else
		{
			safe_write(base_movement + oGravityMultiplier, 2.f, float);
		}
	}
}
bool change_fov() {
	if (fov_changer_checbox == TRUE) {
		constexpr auto m_ConVarGraphics2 = oFovConVarGraphics;                    // "Signature": "ConVar_Graphics_c*"
		const auto klass3 = safe_read(game_assembly_base_adress + m_ConVarGraphics2, uint64_t);
		const auto static_fields = safe_read(klass3 + 0xB8, uint64_t);

		safe_write(static_fields + 0x18, fov_valuee, float);
		return true;
	}
}
bool change_time() {
	if (change_time_checkbox == TRUE) {
		if (!TodCycle) {
			return false;
		}
		safe_write(TodCycle + 0x10, time_ammout, float);
	}
}
bool jump_shot() {
	if (jumpshot_checkbox == TRUE) {
		auto base_movement3 = safe_read(Player2 + oPlayerMovement, uintptr_t);
		if (!base_movement3) {
			return false;
		}
		auto mov_flag = safe_read(base_movement3 + oModelState, uintptr_t);
		if (!mov_flag) {
			return false;
		}
		safe_write(mov_flag, oFlagOnGround, uintptr_t);
		safe_write(base_movement3 + oGroundAngle, 1.f, float);
		safe_write(base_movement3 + oGroundAngleNew, 1.f, float);
	}
}

bool no_recoil() {

	const auto current_item = GetHeldItem(Player2);
	bool isWeapon = is_weapon(current_item);

	if (isWeapon) {
		auto base_projectile = safe_read(current_item + oHeld, uintptr_t);
		auto recoil_prop = safe_read(base_projectile + oRecoilProperties, uintptr_t);

		if (no_recoil_checkbox) {
			if (!std::count(Recoil::Automatics.begin(), Recoil::Automatics.end(), current_item)) {
				Recoil::Automatics.push_back(current_item);
				safe_write(recoil_prop + oRecoilYawMin, 0, float);
				safe_write(recoil_prop + oRecoilYawMax, 0, float);
				safe_write(recoil_prop + oRecoilPitchMin, 0, float);
				safe_write(recoil_prop + oRecoilPitchMax, 0, float);
			}
		}
		if (full_automatic_checkbox) {
			if (!std::count(Recoil::Weapons.begin(), Recoil::Weapons.end(), current_item)) {
				Recoil::Weapons.push_back(current_item);
				return safe_write(base_projectile + oAutomatic, full_automatic_checkbox, bool);
			}
		}
		if (nospread_checkbox) {
			if (!std::count(Recoil::Spreads.begin(), Recoil::Spreads.end(), current_item)) {
				Recoil::Spreads.push_back(current_item);
				safe_write(base_projectile + 0x31C, 0.f, float);
				safe_write(base_projectile + 0x320, 0.f, float);
				safe_write(base_projectile + 0x2EC, 0.f, float);
				safe_write(base_projectile + 0x2E8, 0.f, float);
				safe_write(base_projectile + 0x2F0, 0.f, float);
			}
		}
		if (super_eoka_checkbox) {
			safe_write(base_projectile + oEokaSuccessFraction, 1.f, float);
		}
	}
}
void FatBullet() {
	if (fat_bullet_checkbox) {
		const auto current_item = GetHeldItem(Player2);
		DWORD64 Held = safe_read(current_item + oHeld, DWORD64);
		DWORD64 List = safe_read(Held + 0x358, DWORD64);
		int size = safe_read(List + 0x18, DWORD64);
		List = safe_read(List + 0x10, DWORD64);
		{
			for (int i = 0; i < size; ++i)
			{
				UINT64 Item = safe_read(List + 0x20 + (i * 0x8), UINT64);
				safe_write(Item + 0x2C, 1.0f, float);
			}
		}
	}
}
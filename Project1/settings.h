inline bool no_recoil_checkbox = false;
inline float no_recoil_x_val = 0.f;
inline float no_recoil_y_val = 0.f;
inline bool fat_bullet_checkbox = false;

inline bool fast_bow_checkbox = false;
inline bool nospread_checkbox = false;
inline bool full_automatic_checkbox = false;
inline bool super_eoka_checkbox = false;
inline bool spiderman_checkboxx = false;
inline bool gravity_checkboxx = false;
inline float gravity_distancee = 2;
inline bool admin_flag_checkboxx = false;
inline bool walk_on_water_checkbox = false;
inline bool walk_on_water_boost_checkbox = false;
inline bool longneck_checkbox = false;
inline bool debug_camera_bypass_checkbox = false;
inline bool frooze_player_checkbox = false;
inline bool inf_jump_checkbox = false;
inline bool jumpshot_checkbox = false;
inline bool fov_changer_checbox = false;
inline float fov_valuee = 90.f;
inline bool change_time_checkbox = false;
inline int time_ammout = 12;

namespace Recoil {
	std::vector<uintptr_t> Weapons{};
	std::vector<uintptr_t> Automatics{};
	std::vector<uintptr_t> Spreads{};
}
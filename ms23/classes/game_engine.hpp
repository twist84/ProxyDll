#pragma once
#include <Utils.hpp>

struct c_game_engine
{
	int (*_get_index)();
	void *_vftable1;
	void *_vftable2;
	void *_get_score;
	void *_vftable4;
	signed int (*_vftable5)(int player_index, int team_index);
	void *_vftable6;
	void *_vftable7;
	void *_vftable8;
	void *_vftable9;
	void *_vftable10;
	void *_vftable11;
	void *_vftable12;
	void *_vftable13;
	void *_vftable14;
	void *_vftable15;
	void *_vftable16;
	void *_vftable17;
	void *_vftable18;
	void *_vftable19;
	void *_vftable20;
	void *_vftable21;
	void *_vftable22;
	void *_vftable23;
	void *_vftable24;
	void *_vftable25;
	void *_vftable26;
	void *_vftable27;
	void *_vftable28;
	void *_vftable29;
	void *_vftable30;
	void *_vftable31;
	void *_vftable32;
	void *_vftable33;
	void *_vftable34;
	void *_vftable35;
	void *_vftable36;
	void *_vftable37;
	void *_vftable38;
	void *_vftable39;
	void *_vftable40;
	void *_vftable41;
	void *_vftable42;
	void *_vftable43;
	void *_vftable44;
	void *_vftable45;
	void *_vftable46;
	void *_vftable47;
	void *_vftable48;
	void *_vftable49;
	void *_vftable50;
	void *_vftable51;
	void *_vftable52;
	void *_vftable53;
	void *_vftable54;
	void *_vftable55;
	void *_vftable56;
	void *_vftable57;
	void *_vftable58;
	void *_vftable59;
	void *_vftable60;
	void *_vftable61;
	void *_vftable62;
	void *_vftable63;
	void *_vftable64;
	void *_vftable65;
	void *_vftable66;
	void *_vftable67;
	void *_vftable68;
	void *_vftable69;
	void *_vftable70;
	void *_vftable71;
	void *_vftable72;
	void *_vftable73;
	void *_vftable74;
	void *_vftable75;
	void *_vftable76;
	void *_vftable77;
	void *_event_game_start;
};
struct c_ctf_engine : c_game_engine
{
	void *_vftable79;
	void *_vftable80;
	void *_vftable81;
	void *_vftable82;
	void *_vftable83;
	void *_vftable84;
	void *_vftable85;
	void *_vftable86;
	void *_vftable87;
	void *_vftable88;
	void *_vftable89;
};
struct c_slayer_engine : c_game_engine
{
};
struct c_oddball_engine : c_game_engine
{
};
struct c_king_engine : c_game_engine
{
};
struct c_sandbox_engine : c_game_engine
{
};
struct c_vip_engine : c_game_engine
{
};
struct c_juggernaut_engine : c_game_engine
{
};
struct c_territories_engine : c_game_engine
{
};
struct c_assault_engine : c_ctf_engine
{
};
struct c_infection_engine : c_game_engine
{
};

void SetupEngines()
{
	c_ctf_engine c_ctf_engine;
	c_slayer_engine c_slayer_engine;
	c_oddball_engine c_oddball_engine;
	c_king_engine c_king_engine;
	c_sandbox_engine c_sandbox_engine;
	c_vip_engine c_vip_engine;
	c_juggernaut_engine c_juggernaut_engine;
	c_territories_engine c_territories_engine;
	c_assault_engine c_assault_engine;
	c_infection_engine c_infection_engine;

	c_ctf_engine._get_index = []() { return 1; };
	c_slayer_engine._get_index = []() { return 2; };
	c_oddball_engine._get_index = []() { return 3; };
	c_king_engine._get_index = []() { return 4; };
	c_sandbox_engine._get_index = []() { return 5; };
	c_vip_engine._get_index = []() { return 6; };
	c_juggernaut_engine._get_index = []() { return 7; };
	c_territories_engine._get_index = []() { return 8; };
	c_assault_engine._get_index = []() { return 9; };
	c_infection_engine._get_index = []() { return 10; };
}

// TODO: Write these out and actually make them functional

// https://gist.github.com/theTwist84/9ff80d8a53c6e9cae361f6bb37126969
struct c_gui_selected_item
{
	// 0x680C50, c_gui_selected_item::vftable00
	// 0x680BD0, c_gui_selected_item::vftable01
	// 0x680BA0, c_gui_selected_item::vftable02::get_file_path_hook
	// 0x680C40, c_gui_selected_item::vftable03
	// 0x680B00, c_gui_selected_item::vftable04
	// 0x680B20, c_gui_selected_item::vftable05
	// 0xAC35C0, c_gui_selected_item::vftable06
	// 0x680B30, c_gui_selected_item::vftable07
	// 0x680AC0, c_gui_selected_item::vftable08
	// 0x680BC0, c_gui_selected_item::vftable09
};
struct c_gui_saved_screenshot_selected_item : c_gui_selected_item
{
	// 0x680B80, c_gui_saved_screenshot_selected_item::vftable10
};
struct c_gui_map_selected_item : c_gui_selected_item
{
	// 0xAD97B0, c_gui_map_selected_item::vftable10
};
struct c_gui_difficulty_selected_item : c_gui_selected_item
{
	// same as c_gui_selected_item
};
struct c_gui_game_variant_selected_item : c_gui_selected_item
{
	// 0xADB4B0, c_gui_game_variant_selected_item::vftable10
};
struct c_gui_saved_film_selected_item : c_gui_selected_item
{
	// 0xADCAE0, c_gui_saved_film_selected_item::vftable10
};
struct c_gui_level_selected_item : c_gui_selected_item
{
	// same as c_gui_selected_item
};
struct c_gui_network_mode_selected_item : c_gui_selected_item
{
	// same as c_gui_selected_item
};
struct c_gui_hopper_selected_item : c_gui_selected_item
{
	// same as c_gui_selected_item
};

struct c_gui_widget
{
	// 0xAB8720, c_gui_widget::vftable00
	// 0xAB63A0, c_gui_widget::vftable01
	// 0xAB9BD0, c_gui_widget::vftable02
	// 0xAB9DD0, c_gui_widget::vftable03
	// 0xAB8620, c_gui_widget::vftable04
	// 0xAB94B0, c_gui_widget::vftable05
	// 0xAB8F30, c_gui_widget::vftable06
	// 0xAB8D10, c_gui_widget::vftable07
	// 0xAB8F70, c_gui_widget::vftable08
	// 0xABA2D0, c_gui_widget::vftable09
	// 0xAB8CE0, c_gui_widget::vftable11
	// 0xAB8BC0, c_gui_widget::vftable12
	// 0xABA850, c_gui_widget::vftable13
	// 0xAB8CB0, c_gui_widget::vftable14
	// 0xAB7930, c_gui_widget::vftable15
	// 0xABB300, c_gui_widget::vftable16
	// 0xAB83E0, c_gui_widget::vftable17
	// 0xAB81A0, c_gui_widget::vftable18
	// 0xAB8260, c_gui_widget::vftable19
	// 0xAB8200, c_gui_widget::vftable20
	// 0xAB8320, c_gui_widget::vftable21
	// 0xAB82C0, c_gui_widget::vftable22
	// 0xAB8380, c_gui_widget::vftable23
	// 0xABB070, c_gui_widget::vftable24
	// 0xABB1A0, c_gui_widget::vftable25
	// 0xAB9FD0, c_gui_widget::vftable26
	// 0xABAC60, c_gui_widget::vftable27
	// 0xABACB0, c_gui_widget::vftable28
	// 0xAB7330, c_gui_widget::vftable29
	// 0xAB9BA0, c_gui_widget::vftable30
	// 0xAB9BB0, c_gui_widget::vftable31
	// 0xAB9B40, c_gui_widget::vftable32
	// 0xAB9980, c_gui_widget::vftable33
	// 0xAB99E0, c_gui_widget::vftable34
	// 0xAB9A40, c_gui_widget::vftable35
	// 0xAB9700, c_gui_widget::vftable36
};
struct c_gui_screen_widget : c_gui_widget
{
	// 0xAB06A0, c_gui_screen_widget::vftable01
	// 0xAB14D0, c_gui_screen_widget::vftable02
	// 0xAB18E0, c_gui_screen_widget::vftable03
	// 0xAB0980, c_gui_screen_widget::vftable04
	// 0xAB0DA0, c_gui_screen_widget::vftable10
	// 0xAB2940, c_gui_screen_widget::vftable24
	// 0xAB1270, c_gui_screen_widget::vftable35
	// 0xAB1000, c_gui_screen_widget::vftable36
	// 0xAAB260, c_gui_screen_widget::vftable37
	// 0xAAB1D0, c_gui_screen_widget::vftable38
	// 0xAB1C10, c_gui_screen_widget::vftable39
	// 0xAB1650, c_gui_screen_widget::vftable40
	// 0xAB1CE0, c_gui_screen_widget::vftable41
	// 0xAB1DF0, c_gui_screen_widget::vftable42
	// 0xAB1AE0, c_gui_screen_widget::vftable43
	// 0xAB1B80, c_gui_screen_widget::vftable44
	// 0xAB0840, c_gui_screen_widget::vftable45
	// 0xAB29A0, c_gui_screen_widget::vftable46
	// 0xAB1BA0, c_gui_screen_widget::vftable47
	// 0xAB1420, c_gui_screen_widget::vftable48
	// 0xAB14C0, c_gui_screen_widget::vftable49
	// 0xAB13F0, c_gui_screen_widget::vftable50
	// 0xAB2510, c_gui_screen_widget::vftable51
	// 0xAB2850, c_gui_screen_widget::vftable52
	// 0xAB1760, c_gui_screen_widget::vftable53
	// 0xAB2930, c_gui_screen_widget::vftable54
};
struct c_gui_screen_codeless_widget : c_gui_screen_widget
{
	// 0xAB0670, c_gui_screen_codeless_widget::vftable01
	// 0xAB1560, c_gui_screen_codeless_widget::vftable40
};
struct c_gui_screen_terminal : c_gui_screen_widget
{
	// 0xAA8D60, c_gui_screen_terminal::vftable01
	// 0xB12080, c_gui_screen_terminal::vftable18
	// 0xB12960, c_gui_screen_terminal::vftable24
	// 0xB122B0, c_gui_screen_terminal::vftable35
};
struct c_gui_screen_scoreboard : c_gui_screen_widget
{
	// 0xAB2BD0, c_gui_screen_scoreboard::vftable01
	// 0xAB3810, c_gui_screen_scoreboard::vftable03
	// 0xAB3E10, c_gui_screen_scoreboard::vftable24
	// 0xAB3230, c_gui_screen_scoreboard::vftable35
	// 0xAB30E0, c_gui_screen_scoreboard::vftable37
	// 0xAB3590, c_gui_screen_scoreboard::vftable40
	// 0xAB3470, c_gui_screen_scoreboard::vftable49
};
struct c_gui_screen_boot_betrayer : c_gui_screen_widget
{
	// 0xAB54D0, c_gui_screen_boot_betrayer::vftable01
	// 0xAB57A0, c_gui_screen_boot_betrayer::vftable02
	// 0xAB5660, c_gui_screen_boot_betrayer::vftable04
	// 0xAB56A0, c_gui_screen_boot_betrayer::vftable35
	// 0xAB5760, c_gui_screen_boot_betrayer::vftable50
};
struct c_gui_screen_in_progress : c_gui_screen_widget
{
	// 0xAFBC80, c_gui_screen_in_progress::vftable01
	// 0xAFBCB0, c_gui_screen_in_progress::vftable24
	// 0xAC00B0, c_gui_screen_in_progress::vftable37
};
struct c_gui_screen_carnage_report : c_gui_screen_widget
{
	// 0xABFC40, c_gui_screen_carnage_report::vftable01
	// 0xAC09E0, c_gui_screen_carnage_report::vftable02
	// 0xABFE10, c_gui_screen_carnage_report::vftable04
	// 0xABFD90, c_gui_screen_carnage_report::vftable18
	// 0xAC25B0, c_gui_screen_carnage_report::vftable24
	// 0xAC2990, c_gui_screen_carnage_report::vftable25
	// 0xAC0310, c_gui_screen_carnage_report::vftable35
	// 0xAC00A0, c_gui_screen_carnage_report::vftable37
	// 0xAC1160, c_gui_screen_carnage_report::vftable40
	// 0xAC2190, c_gui_screen_carnage_report::vftable43
	// 0xAC0680, c_gui_screen_carnage_report::vftable49
	// 0xAC0660, c_gui_screen_carnage_report::vftable50
};
struct c_gui_screen_alpha_motd : c_gui_screen_widget
{
	// 0xAE6F60, c_gui_screen_alpha_motd::vftable01
	// 0xAE7040, c_gui_screen_alpha_motd::vftable03
	// 0xAE7010, c_gui_screen_alpha_motd::vftable35
};
struct c_gui_screen_maximum_party_size : c_gui_screen_widget
{
	// 0xB0A810, c_gui_screen_maximum_party_size::vftable01
	// 0xB0A930, c_gui_screen_maximum_party_size::vftable02
	// 0xB0A9C0, c_gui_screen_maximum_party_size::vftable03
	// 0xB0AA70, c_gui_screen_maximum_party_size::vftable24
	// 0xB0A840, c_gui_screen_maximum_party_size::vftable35
};
struct c_gui_screen_game_options : c_gui_screen_widget
{
	// 0xB0B370, c_gui_screen_game_options::vftable01
	// 0xB0CA70, c_gui_screen_game_options::vftable02
	// 0xB0CEE0, c_gui_screen_game_options::vftable03
	// 0xB0D410, c_gui_screen_game_options::vftable24
	// 0xB0C0B0, c_gui_screen_game_options::vftable35
	// 0xB0CB20, c_gui_screen_game_options::vftable40
	// 0xB0C470, c_gui_screen_game_options::vftable49
	// 0xB0C200, c_gui_screen_game_options::vftable50
};
struct c_gui_screen_alpha_legal : c_gui_screen_widget
{
	// 0xB0E050, c_gui_screen_alpha_legal::vftable01
	// 0xB0E0E0, c_gui_screen_alpha_legal::vftable03
	// 0xB0E120, c_gui_screen_alpha_legal::vftable24
	// 0xB0E080, c_gui_screen_alpha_legal::vftable35
};
struct c_gui_screen_alpha_locked_down : c_gui_screen_widget
{
	// 0xB0E230, c_gui_screen_alpha_locked_down::vftable01
	// 0xB0E290, c_gui_screen_alpha_locked_down::vftable03
	// 0xB0E260, c_gui_screen_alpha_locked_down::vftable35
};
struct c_gui_screen_forge_legal : c_gui_screen_widget
{
	// 0xB0E2E0, c_gui_screen_forge_legal::vftable01
	// 0xB0E390, c_gui_screen_forge_legal::vftable03
	// 0xB0E310, c_gui_screen_forge_legal::vftable35
};

struct c_gui_screen_campaign_select_difficulty : c_gui_screen_widget
{
	// 0xAFC320, c_gui_screen_campaign_select_difficulty::vftable01
	// 0xAFC770, c_gui_screen_campaign_select_difficulty::vftable02
	// 0xAFC860, c_gui_screen_campaign_select_difficulty::vftable24
	// 0xAFC790, c_gui_screen_campaign_select_difficulty::vftable40
	// 0xAFC620, c_gui_screen_campaign_select_difficulty::vftable49
	// 0xAFC5A0, c_gui_screen_campaign_select_difficulty::vftable50
};
struct c_gui_screen_campaign_select_level : c_gui_screen_widget
{
	// 0xAFCBA0, c_gui_screen_campaign_select_level::vftable01
	// 0xAFD180, c_gui_screen_campaign_select_level::vftable02
	// 0xAFD9B0, c_gui_screen_campaign_select_level::vftable03
	// 0xAFCC00, c_gui_screen_campaign_select_level::vftable18
	// 0xAFDC50, c_gui_screen_campaign_select_level::vftable24
	// 0xAFCE00, c_gui_screen_campaign_select_level::vftable35
	// 0xAFD600, c_gui_screen_campaign_select_level::vftable40
	// 0xAFCF90, c_gui_screen_campaign_select_level::vftable49
	// 0xAFCF20, c_gui_screen_campaign_select_level::vftable50
};
struct c_gui_screen_campaign_settings : c_gui_screen_widget
{
	// 0xB20FA0, c_gui_screen_campaign_settings::vftable01
	// 0xB20FD0, c_gui_screen_campaign_settings::vftable50
};
struct c_gui_screen_campaign_select_scoring : c_gui_screen_campaign_settings
{
	// 0xAFE2B0, c_gui_screen_campaign_select_scoring::vftable01
	// 0xAFE400, c_gui_screen_campaign_select_scoring::vftable02
	// 0xAFE330, c_gui_screen_campaign_select_scoring::vftable49
	// 0xAFE2E0, c_gui_screen_campaign_select_scoring::vftable50
};
struct c_gui_screen_campaign_select_skulls : c_gui_screen_campaign_settings
{
	// 0xAFE5C0, c_gui_screen_campaign_select_skulls::vftable01
	// 0xAFEF60, c_gui_screen_campaign_select_skulls::vftable02
	// 0xAFF460, c_gui_screen_campaign_select_skulls::vftable24
	// 0xAFE960, c_gui_screen_campaign_select_skulls::vftable35
	// 0xAFEF90, c_gui_screen_campaign_select_skulls::vftable40
	// 0xAFEE20, c_gui_screen_campaign_select_skulls::vftable49
	// 0xAFEE11, c_gui_screen_campaign_select_skulls::vftable50
};

struct c_gui_screen_pregame_switch_lobby : c_gui_screen_widget
{
	// 0xB02E20, c_gui_screen_pregame_switch_lobby::vftable01
	// 0xB02F60, c_gui_screen_pregame_switch_lobby::vftable03
};
struct c_gui_screen_pregame_selection : c_gui_screen_widget
{
	// 0xB03220, c_gui_screen_pregame_selection::vftable01
	// 0xB044B0, c_gui_screen_pregame_selection::vftable02
	// 0xB04B30, c_gui_screen_pregame_selection::vftable03
	// 0xB03810, c_gui_screen_pregame_selection::vftable04
	// 0xB03790, c_gui_screen_pregame_selection::vftable18
	// 0xB051D0, c_gui_screen_pregame_selection::vftable24
	// 0xB03950, c_gui_screen_pregame_selection::vftable35
	// 0xB04BB0, c_gui_screen_pregame_selection::vftable39
	// 0xB045A0, c_gui_screen_pregame_selection::vftable40
	// 0xB03EE0, c_gui_screen_pregame_selection::vftable49
	// 0xB03D90, c_gui_screen_pregame_selection::vftable50
};
struct c_gui_screen_pregame_lobby : c_gui_screen_widget
{
	// 0xB21230, c_gui_screen_pregame_lobby::vftable01
	// 0xB22140, c_gui_screen_pregame_lobby::vftable02
	// 0xB22AF0, c_gui_screen_pregame_lobby::vftable03
	// 0xB21400, c_gui_screen_pregame_lobby::vftable04
	// 0xB212F0, c_gui_screen_pregame_lobby::vftable18
	// 0xB21370, c_gui_screen_pregame_lobby::vftable21
	// 0xB22DE0, c_gui_screen_pregame_lobby::vftable24
	// 0xB21A20, c_gui_screen_pregame_lobby::vftable35
	// 0xAFFA10, c_gui_screen_pregame_lobby::vftable37
	// 0xAFF9E0, c_gui_screen_pregame_lobby::vftable38
	// 0xB224D0, c_gui_screen_pregame_lobby::vftable40
	// 0xB21EA0, c_gui_screen_pregame_lobby::vftable49
	// 0xB21E20, c_gui_screen_pregame_lobby::vftable50
	// 0xB22DD0, c_gui_screen_pregame_lobby::vftable55
	// 0xB22130, c_gui_screen_pregame_lobby::vftable56
	// 0xB22DB0, c_gui_screen_pregame_lobby::vftable61
	// 0xB22DC0, c_gui_screen_pregame_lobby::vftable62
};

struct c_gui_screen_pregame_lobby_campaign : c_gui_screen_pregame_lobby
{
	// 0xAFF900, c_gui_screen_pregame_lobby_campaign::vftable01
	// 0xAFFDA0, c_gui_screen_pregame_lobby_campaign::vftable02
	// 0xB00230, c_gui_screen_pregame_lobby_campaign::vftable24
	// 0xAFFA90, c_gui_screen_pregame_lobby_campaign::vftable35
	// 0xAFFAE0, c_gui_screen_pregame_lobby_campaign::vftable49
	// 0xAFFD80, c_gui_screen_pregame_lobby_campaign::vftable56
	// 0xAFF9F0, c_gui_screen_pregame_lobby_campaign::header_string_id
	// 0xAFFA20, c_gui_screen_pregame_lobby_campaign::start_string_id
	// 0xAFFA00, c_gui_screen_pregame_lobby_campaign::title_string_id
	// 0xAFF9D0, c_gui_screen_pregame_lobby_campaign::ui_game_mode
};
struct c_gui_screen_pregame_lobby_survival : c_gui_screen_pregame_lobby
{
	// 0xB00930, c_gui_screen_pregame_lobby_survival::vftable01
	// 0xB00CB0, c_gui_screen_pregame_lobby_survival::vftable02
	// 0xB00DF0, c_gui_screen_pregame_lobby_survival::vftable24
	// 0xB009F0, c_gui_screen_pregame_lobby_survival::vftable35
	// 0xB00A40, c_gui_screen_pregame_lobby_survival::vftable49
	// 0xB00C90, c_gui_screen_pregame_lobby_survival::vftable56
	// 0xB009B0, c_gui_screen_pregame_lobby_survival::header_string_id
	// 0xB009D0, c_gui_screen_pregame_lobby_survival::start_string_id
	// 0xB009C0, c_gui_screen_pregame_lobby_survival::title_string_id
	// 0xB009A0, c_gui_screen_pregame_lobby_survival::ui_game_mode
};
struct c_gui_screen_pregame_lobby_multiplayer : c_gui_screen_pregame_lobby
{
	// 0xB011A0, c_gui_screen_pregame_lobby_multiplayer::vftable01
	// 0xB013B0, c_gui_screen_pregame_lobby_multiplayer::vftable02
	// 0xB014B0, c_gui_screen_pregame_lobby_multiplayer::vftable22
	// 0xB01250, c_gui_screen_pregame_lobby_multiplayer::vftable49
	// 0xB01220, c_gui_screen_pregame_lobby_multiplayer::header_string_id
	// 0xB01240, c_gui_screen_pregame_lobby_multiplayer::start_string_id
	// 0xB01230, c_gui_screen_pregame_lobby_multiplayer::title_string_id
	// 0xB01210, c_gui_screen_pregame_lobby_multiplayer::ui_game_mode
};
struct c_gui_screen_pregame_lobby_matchmaking : c_gui_screen_pregame_lobby
{
	// 0xB01760, c_gui_screen_pregame_lobby_matchmaking::vftable01
	// 0xB01B10, c_gui_screen_pregame_lobby_matchmaking::vftable02
	// 0xB017F0, c_gui_screen_pregame_lobby_matchmaking::vftable18
	// 0xB01E40, c_gui_screen_pregame_lobby_matchmaking::vftable24
	// 0xB01920, c_gui_screen_pregame_lobby_matchmaking::vftable49
	// 0xB018E0, c_gui_screen_pregame_lobby_matchmaking::vftable50
	// 0xB01E20, c_gui_screen_pregame_lobby_matchmaking::vftable61
	// 0xB01E30, c_gui_screen_pregame_lobby_matchmaking::vftable62
	// 0xB018B0, c_gui_screen_pregame_lobby_matchmaking::header_string_id
	// 0xB018D0, c_gui_screen_pregame_lobby_matchmaking::start_string_id
	// 0xB018C0, c_gui_screen_pregame_lobby_matchmaking::title_string_id
	// 0xB01870, c_gui_screen_pregame_lobby_matchmaking::ui_game_mode
};
struct c_gui_screen_pregame_lobby_mapeditor : c_gui_screen_pregame_lobby
{
	// 0xB021D0, c_gui_screen_pregame_lobby_mapeditor::vftable01
	// 0xB023C0, c_gui_screen_pregame_lobby_mapeditor::vftable02
	// 0xB02470, c_gui_screen_pregame_lobby_mapeditor::vftable03
	// 0xB02560, c_gui_screen_pregame_lobby_mapeditor::vftable24
	// 0xB02280, c_gui_screen_pregame_lobby_mapeditor::vftable49
	// 0xB02250, c_gui_screen_pregame_lobby_mapeditor::header_string_id
	// 0xB02270, c_gui_screen_pregame_lobby_mapeditor::start_string_id
	// 0xB02260, c_gui_screen_pregame_lobby_mapeditor::title_string_id
	// 0xB02240, c_gui_screen_pregame_lobby_mapeditor::ui_game_mode
};
struct c_gui_screen_pregame_lobby_theater : c_gui_screen_pregame_lobby
{
	// 0xB025F0, c_gui_screen_pregame_lobby_theater::vftable01
	// 0xB02790, c_gui_screen_pregame_lobby_theater::vftable02
	// 0xB02B70, c_gui_screen_pregame_lobby_theater::vftable24
	// 0xB02910, c_gui_screen_pregame_lobby_theater::vftable40
	// 0xB026A0, c_gui_screen_pregame_lobby_theater::vftable49
	// 0xB02B60, c_gui_screen_pregame_lobby_theater::vftable55
	// 0xB02670, c_gui_screen_pregame_lobby_theater::header_string_id
	// 0xB02690, c_gui_screen_pregame_lobby_theater::start_string_id
	// 0xB02680, c_gui_screen_pregame_lobby_theater::title_string_id
	// 0xB02660, c_gui_screen_pregame_lobby_theater::ui_game_mode
};

struct c_gui_screen_postgame_lobby : c_gui_screen_widget
{
	// 0xB06960, c_gui_screen_postgame_lobby::vftable01
	// 0xB06F00, c_gui_screen_postgame_lobby::vftable02
	// 0xB07240, c_gui_screen_postgame_lobby::vftable03
	// 0xB069D0, c_gui_screen_postgame_lobby::vftable21
	// 0xB07270, c_gui_screen_postgame_lobby::vftable24
	// 0xB06B10, c_gui_screen_postgame_lobby::vftable35
	// 0xB06B00, c_gui_screen_postgame_lobby::vftable37
	// 0xB06A60, c_gui_screen_postgame_lobby::vftable38
	// 0xB07030, c_gui_screen_postgame_lobby::vftable40
	// 0xB06DB0, c_gui_screen_postgame_lobby::vftable49
	// 0xB06D60, c_gui_screen_postgame_lobby::vftable50
};

struct c_gui_screen_matchmaking_advanced_options : c_gui_screen_widget
{
	// 0xB05F00, c_gui_screen_matchmaking_advanced_options::vftable01
	// 0xB060E0, c_gui_screen_matchmaking_advanced_options::vftable02
	// 0xB06430, c_gui_screen_matchmaking_advanced_options::vftable03
	// 0xB05FF0, c_gui_screen_matchmaking_advanced_options::vftable04
	// 0xB05F70, c_gui_screen_matchmaking_advanced_options::vftable18
	// 0xB06510, c_gui_screen_matchmaking_advanced_options::vftable24
	// 0xB06030, c_gui_screen_matchmaking_advanced_options::vftable49
};
struct c_gui_screen_matchmaking_searching : c_gui_screen_widget
{
	// 0xB0E550, c_gui_screen_matchmaking_searching::vftable01
	// 0xB0EAE0, c_gui_screen_matchmaking_searching::vftable02
	// 0xB0FC40, c_gui_screen_matchmaking_searching::vftable03
	// 0xB0E650, c_gui_screen_matchmaking_searching::vftable04
	// 0xB0E5C0, c_gui_screen_matchmaking_searching::vftable21
	// 0xB0FC80, c_gui_screen_matchmaking_searching::vftable24
	// 0xB0E7A0, c_gui_screen_matchmaking_searching::vftable35
	// 0xB0E790, c_gui_screen_matchmaking_searching::vftable37
	// 0xB0E750, c_gui_screen_matchmaking_searching::vftable38
	// 0xB0EEE0, c_gui_screen_matchmaking_searching::vftable40
	// 0xB0E9A0, c_gui_screen_matchmaking_searching::vftable49
	// 0xB0E950, c_gui_screen_matchmaking_searching::vftable50
};
struct c_gui_screen_matchmaking_match_found : c_gui_screen_widget
{
	// 0xB10510, c_gui_screen_matchmaking_match_found::vftable01
	// 0xB107E0, c_gui_screen_matchmaking_match_found::vftable02
	// 0xB11470, c_gui_screen_matchmaking_match_found::vftable03
	// 0xB10540, c_gui_screen_matchmaking_match_found::vftable18
	// 0xB105C0, c_gui_screen_matchmaking_match_found::vftable21
	// 0xB114A0, c_gui_screen_matchmaking_match_found::vftable24
	// 0xB10680, c_gui_screen_matchmaking_match_found::vftable35
	// 0xB10670, c_gui_screen_matchmaking_match_found::vftable37
	// 0xB10660, c_gui_screen_matchmaking_match_found::vftable38
	// 0xB10AB0, c_gui_screen_matchmaking_match_found::vftable40
	// 0xB11490, c_gui_screen_matchmaking_match_found::vftable47
	// 0xB10690, c_gui_screen_matchmaking_match_found::vftable49
};

struct c_gui_data
{
	// 0xAD46A0, c_gui_data::vftable00
	// 0xAD52F0, c_gui_data::player_select_actions
	// 0xAD4950, c_gui_data::vftable02
	// 0xAD54E0, c_gui_data::vftable03
	// 0xAD53B0, c_gui_data::vftable04
	// 0xAD4CE0, c_gui_data::vftable10
	// 0xAD4E80, c_gui_data::vftable11
	// 0xAD5220, c_gui_data::vftable12
	// 0xAD5180, c_gui_data::vftable13
	// 0xAD5160, c_gui_data::vftable14
	// 0xAD5170, c_gui_data::vftable15
	// 0xAD5080, c_gui_data::vftable16
	// 0xAD4E70, c_gui_data::vftable17
	// 0xAD4F90, c_gui_data::vftable18
	// 0xAD4810, c_gui_data::vftable19
	// 0xAD48A0, c_gui_data::vftable20
	// 0xAD5480, c_gui_data::vftable21
	// 0xAD4F40, c_gui_data::vftable22
	// 0xAD4830, c_gui_data::vftable23
	// 0xAD5430, c_gui_data::vftable24
	// 0xAD48D0, c_gui_data::vftable25
	// 0xAD4960, c_gui_data::vftable26
};
struct c_gui_data_array : c_gui_data
{
	// 0xAD46D0, c_gui_data_array::vftable00
	// 0xAD5300, c_gui_data_array::vftable01
	// 0xAD4BD0, c_gui_data_array::vftable05
	// 0xAD4DB0, c_gui_data_array::vftable06
	// 0xAD4FB0, c_gui_data_array::vftable07
	// 0xAD5090, c_gui_data_array::vftable08
	// 0xAD4CF0, c_gui_data_array::vftable10
	// 0xAD4FA0, c_gui_data_array::vftable18
	// 0xAD4820, c_gui_data_array::vftable19
	// 0xAD48B0, c_gui_data_array::vftable20
	// 0xAD5490, c_gui_data_array::vftable21
};
struct c_gui_data_array_test : c_gui_data
{
	// 0xAD4740, c_gui_data_array_test::vftable00
	// 0xAD5330, c_gui_data_array_test::vftable01
	// 0xAD4A50, c_gui_data_array_test::vftable09
	// 0xAD4E90, c_gui_data_array_test::vftable11
	// 0xAD5230, c_gui_data_array_test::vftable12
	// 0xAD5190, c_gui_data_array_test::vftable13
};
struct c_gui_data_proxy : c_gui_data
{
	// 0xAE19E0, c_gui_data_proxy::vftable00
	// 0xAE1D90, c_gui_data_proxy::vftable05
	// 0xAE1E30, c_gui_data_proxy::vftable06
	// 0xAE1F20, c_gui_data_proxy::vftable07
	// 0xAE1F70, c_gui_data_proxy::vftable08
	// 0xAE1D50, c_gui_data_proxy::vftable09
	// 0xAE1DE0, c_gui_data_proxy::vftable10
	// 0xAE1E80, c_gui_data_proxy::vftable11
	// 0xAE2000, c_gui_data_proxy::vftable12
	// 0xAE1F80, c_gui_data_proxy::vftable13
	// 0xAE1F10, c_gui_data_proxy::vftable18
	// 0xAE1B60, c_gui_data_proxy::vftable19
	// 0xAE1D00, c_gui_data_proxy::vftable20
	// 0xAE31E0, c_gui_data_proxy::vftable21
	// 0xAD5370, c_gui_data_proxy::vftable27
};

struct c_gui_ordered_data : c_gui_data
{
	// 0xAD47B0, c_gui_ordered_data::vftable00
	// 0xAD4BE0, c_gui_ordered_data::vftable05
	// 0xAD4DD0, c_gui_ordered_data::vftable06
	// 0xAD4FE0, c_gui_ordered_data::vftable07
	// 0xAD50C0, c_gui_ordered_data::vftable08
	// 0xAD4840, c_gui_ordered_data::vftable23
	// 0xAD5440, c_gui_ordered_data::vftable24
	// 0xAD48E0, c_gui_ordered_data::vftable25
	// 0xAD4970, c_gui_ordered_data::vftable26
};
struct c_player_screenshots_datasource : c_gui_ordered_data
{
	// 0xAF36C0, c_player_screenshots_datasource::vftable00
	// 0xAF40A0, c_player_screenshots_datasource::player_select_actions
	// 0xAF3910, c_player_screenshots_datasource::vftable02
	// 0xAF3940, c_player_screenshots_datasource::vftable09
	// 0xAF3A20, c_player_screenshots_datasource::vftable11
	// 0xAF3AC0, c_player_screenshots_datasource::vftable12
	// 0xAF39F0, c_player_screenshots_datasource::vftable17
	// 0xAF39A0, c_player_screenshots_datasource::vftable27
};
struct c_player_select_actions_datasource : c_gui_ordered_data
{
	// 0xB07B50, c_player_select_actions_datasource::vftable00
	// 0xB07D50, c_player_select_actions_datasource::vftable09
	// 0xB07E50, c_player_select_actions_datasource::vftable13
	// 0xB07DB0, c_player_select_actions_datasource::vftable27
};
struct c_player_select_medals_datasource : c_gui_ordered_data
{
	// 0xB07B80, c_player_select_medals_datasource::vftable00
	// 0xB07D70, c_player_select_medals_datasource::vftable09
	// 0xB07DF0, c_player_select_medals_datasource::vftable11
	// 0xB07E90, c_player_select_medals_datasource::vftable13
	// 0xB07DC0, c_player_select_medals_datasource::vftable27
};

struct c_gui_hopper_category_datasource : c_gui_ordered_data
{
	// 0xB24110, c_gui_hopper_category_datasource::vftable09
	// 0xB241D0, c_gui_hopper_category_datasource::vftable11
	// 0xB242D0, c_gui_hopper_category_datasource::vftable12
	// 0xB24290, c_gui_hopper_category_datasource::vftable13
	// 0xB24180, c_gui_hopper_category_datasource::vftable27
};
struct c_gui_hopper_subitem_selectable_item_datasource : c_gui_ordered_data
{
	// 0xB240E0, c_gui_hopper_subitem_selectable_item_datasource::vftable00
	// 0xB24150, c_gui_hopper_subitem_selectable_item_datasource::vftable09
	// 0xB24240, c_gui_hopper_subitem_selectable_item_datasource::vftable11
	// 0xB24330, c_gui_hopper_subitem_selectable_item_datasource::vftable12
	// 0xB242B0, c_gui_hopper_subitem_selectable_item_datasource::vftable13
	// 0xB241A0, c_gui_hopper_subitem_selectable_item_datasource::vftable17
	// 0xB24190, c_gui_hopper_subitem_selectable_item_datasource::vftable27
	// 0xB244E0, c_gui_hopper_subitem_selectable_item_datasource::vftable28::player_actions
};
struct c_gui_network_mode_category_datasource : c_gui_ordered_data
{
	// 0xB23810, c_gui_network_mode_category_datasource::vftable00
	// 0xB23A80, c_gui_network_mode_category_datasource::vftable09
	// 0xB23B80, c_gui_network_mode_category_datasource::vftable11
	// 0xB23C70, c_gui_network_mode_category_datasource::vftable12
	// 0xB23C30, c_gui_network_mode_category_datasource::vftable13
	// 0xB23B20, c_gui_network_mode_category_datasource::vftable17
	// 0xB23B00, c_gui_network_mode_category_datasource::vftable27
};
struct c_gui_network_mode_subitem_selectable_item_datasource : c_gui_ordered_data
{
	// 0xB23840, c_gui_network_mode_subitem_selectable_item_datasource::vftable00
	// 0xB23AC0, c_gui_network_mode_subitem_selectable_item_datasource::vftable09
	// 0xB23BD0, c_gui_network_mode_subitem_selectable_item_datasource::vftable11
	// 0xB23CF0, c_gui_network_mode_subitem_selectable_item_datasource::vftable12
	// 0xB23C50, c_gui_network_mode_subitem_selectable_item_datasource::vftable13
	// 0xB23B50, c_gui_network_mode_subitem_selectable_item_datasource::vftable17
	// 0xB23B10, c_gui_network_mode_subitem_selectable_item_datasource::vftable27
	// 0xB23DE0, c_gui_network_mode_subitem_selectable_item_datasource::vftable28::player_actions
};

struct c_gui_roster_data : c_gui_ordered_data
{
	// 0xB248C0, c_gui_roster_data::vftable00
	// 0xB24BC0, c_gui_roster_data::vftable09
	// 0xB24CA0, c_gui_roster_data::vftable11
	// 0xB24FE0, c_gui_roster_data::vftable12
	// 0xB24EA0, c_gui_roster_data::vftable16
	// 0xB24C90, c_gui_roster_data::vftable27
	// 0xB24F90, c_gui_roster_data::vftable28
	// 0xB24F40, c_gui_roster_data::vftable29
};
struct c_gui_active_roster_data : c_gui_roster_data
{
	// 0xB24890, c_gui_active_roster_data::vftable00
	// 0xB25430, c_gui_active_roster_data::vftable03
};
struct c_gui_static_roster_data : c_gui_roster_data
{
	// 0xB248F0, c_gui_static_roster_data::vftable00
};

struct c_message
{
	// 0xA92C20, c_message::vftable00
	// 0xA930F0, c_message::vftable01
	// 0xA932B0, c_message::vftable02
};
struct c_load_screen_message : c_message
{
	// 0xA92B90, c_load_screen_message::vftable00
	// 0xA92DA0, c_load_screen_message::vftable03
};
struct c_load_terminal_screen_message : c_load_screen_message
{
	// 0xBB6360, c_load_terminal_screen_message::vftable00
	// 0xBB6390, c_load_terminal_screen_message::vftable03
};

struct c_view
{
	// __purecall
	// __purecall
	// __purecall
	// __purecall
};
struct c_world_view : c_view
{
	// __purecall
	// __purecall
	// __purecall
	// __purecall
};
struct c_ui_view : c_view
{
	// 0xA290A0, c_ui_view::vftable00
	// 0x604E40, c_ui_view::vftable01
	// 0x604190, c_ui_view::vftable02
	// 0x604E60, c_ui_view::vftable03
};
struct c_fullscreen_view : c_view
{
	// 0xA29050, c_fullscreen_view::vftable00
	// 0xA29250, c_fullscreen_view::vftable01
	// 0x604180, c_fullscreen_view::vftable02
	// 0x604E50, c_fullscreen_view::vftable03
};
struct c_lights_view : c_world_view
{
	// 0x60FEB0, c_lights_view::vftable00
	// 0xA67170, c_lights_view::vftable01
	// 0x60EF60, c_lights_view::vftable02
	// 0xA671B0, c_lights_view::vftable03
};
struct c_lightmap_shadows_view : c_world_view
{
	// 0x60FEA0, c_lightmap_shadows_view::vftable00
	// 0x610090, c_lightmap_shadows_view::vftable01
	// 0x60EF50, c_lightmap_shadows_view::vftable02
	// 0xA6B340, c_lightmap_shadows_view::vftable03
};
struct c_occlusion_view : c_lightmap_shadows_view
{
	// 0x6100A0, c_occlusion_view::vftable01
	// 0xA6D7F0, c_occlusion_view::vftable04
	// 0xA6D740, c_occlusion_view::vftable05
};
struct c_reflection_view : c_view
{
	// 0x60FEC0, c_reflection_view::vftable00
	// 0x6100B0, c_reflection_view::vftable01
	// 0x60EF70, c_reflection_view::vftable02
	// 0x610130, c_reflection_view::vftable03
};
struct c_first_person_view : c_view
{
	// 0x60FE90, c_first_person_view::vftable00
	// 0xA29240, c_first_person_view::vftable01
	// 0x60EF40, c_first_person_view::vftable02
	// 0x610120, c_first_person_view::vftable03
};
struct c_player_view : c_world_view
{
	// 0xA39960, c_player_view::vftable00
	// 0xA3A850, c_player_view::vftable01
	// 0xA38D10, c_player_view::vftable02
	// 0xA3AAA0, c_player_view::vftable03
};
struct c_hud_camera_view : c_player_view
{
	// 0xA2EB50, c_hud_camera_view::vftable01	
};
struct c_texture_camera_view : c_player_view
{
	// 0xA70950, c_texture_camera_view::vftable00
	// 0xA71350, c_texture_camera_view::vftable01
	// 0xA71420, c_texture_camera_view::vftable03
	// 0xA70700, c_texture_camera_view::vftable04
};

struct s_simulation_globals_type_collection
{
	uint32_t simulation_global_and_entity_count;
	void *simulation_global_and_entity_vftable_array[32];
	uint32_t simulation_event_count;
	void *simulation_event_vftable_array[64];

	int set_global_and_entity(int index, void *simulation_entity_definition)
	{
		this->simulation_global_and_entity_vftable_array[index] = simulation_entity_definition;

		return index;
	}
	int set_event_data(int index, void *simulation_event_definition)
	{
		this->simulation_event_vftable_array[index] = simulation_event_definition;

		return index;
	}
};

struct c_simulation_entity_definition
{
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
};
struct c_simulation_game_engine_globals_definition : c_simulation_entity_definition
{
	// 0x4B6080, c_simulation_game_engine_globals_definition::vftable03
	// 0x4B6110, c_simulation_game_engine_globals_definition::vftable06
	// 0x4B6120, c_simulation_game_engine_globals_definition::vftable07
	// 0x4B6850, c_simulation_game_engine_globals_definition::vftable08
	// 0x4B60D0, c_simulation_game_engine_globals_definition::vftable09
	// 0x4B6090, c_simulation_game_engine_globals_definition::vftable10
	// 0x4B7280, c_simulation_game_engine_globals_definition::vftable11
	// 0x4B60F0, c_simulation_game_engine_globals_definition::vftable13
	// 0x4B60E0, c_simulation_game_engine_globals_definition::vftable14
	// 0x4B6100, c_simulation_game_engine_globals_definition::vftable18
	// 0x4B5F70, c_simulation_game_engine_globals_definition::vftable19
	// 0x4B5F30, c_simulation_game_engine_globals_definition::vftable20
	// 0x4B5F80, c_simulation_game_engine_globals_definition::vftable21
	// 0x4B7220, c_simulation_game_engine_globals_definition::vftable22
	// 0x4B7170, c_simulation_game_engine_globals_definition::vftable23
	// 0x4B71A0, c_simulation_game_engine_globals_definition::vftable24
	// 0x4B6030, c_simulation_game_engine_globals_definition::vftable25
	// 0x4B7230, c_simulation_game_engine_globals_definition::vftable26
	// 0x4B60A0, c_simulation_game_engine_globals_definition::vftable27
	// 0x4B71B0, c_simulation_game_engine_globals_definition::vftable28
};
struct c_simulation_slayer_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C2CA0, c_simulation_slayer_engine_globals_definition::vftable00::get_index
	// 0x4C2CB0, c_simulation_slayer_engine_globals_definition::vftable01::get_name
	// 0x4C2D60, c_simulation_slayer_engine_globals_definition::vftable02::get_size
	// 0x4C2D70, c_simulation_slayer_engine_globals_definition::vftable04
	// 0x4C2D40, c_simulation_slayer_engine_globals_definition::vftable05
	// 0x4C2D80, c_simulation_slayer_engine_globals_definition::vftable12
	// 0x4C2D20, c_simulation_slayer_engine_globals_definition::vftable15
	// 0x4C2CC0, c_simulation_slayer_engine_globals_definition::vftable16
	// 0x4C2C80, c_simulation_slayer_engine_globals_definition::vftable17
	// 0x4C2DA0, c_simulation_slayer_engine_globals_definition::vftable29::update
};
struct c_simulation_ctf_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C2E60, c_simulation_ctf_engine_globals_definition::vftable00::get_index
	// 0x4C2E70, c_simulation_ctf_engine_globals_definition::vftable01::get_name
	// 0x4C3460, c_simulation_ctf_engine_globals_definition::vftable02::get_size
	// 0x4C3470, c_simulation_ctf_engine_globals_definition::vftable04
	// 0x4C3440, c_simulation_ctf_engine_globals_definition::vftable05
	// 0x4C3480, c_simulation_ctf_engine_globals_definition::vftable12
	// 0x4C3060, c_simulation_ctf_engine_globals_definition::vftable15
	// 0x4C2E80, c_simulation_ctf_engine_globals_definition::vftable16
	// 0x4C2E40, c_simulation_ctf_engine_globals_definition::vftable17
	// 0x4C3540, c_simulation_ctf_engine_globals_definition::vftable29::update
};
struct c_simulation_assault_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C3600, c_simulation_assault_engine_globals_definition::vftable00::get_index
	// 0x4C3610, c_simulation_assault_engine_globals_definition::vftable01::get_name
	// 0x4C3C40, c_simulation_assault_engine_globals_definition::vftable02::get_size
	// 0x4C3C50, c_simulation_assault_engine_globals_definition::vftable04
	// 0x4C3C20, c_simulation_assault_engine_globals_definition::vftable05
	// 0x4C3C60, c_simulation_assault_engine_globals_definition::vftable12
	// 0x4C3800, c_simulation_assault_engine_globals_definition::vftable15
	// 0x4C3620, c_simulation_assault_engine_globals_definition::vftable16
	// 0x4C35E0, c_simulation_assault_engine_globals_definition::vftable17
	// 0x4C3D20, c_simulation_assault_engine_globals_definition::vftable29::update
};
struct c_simulation_oddball_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C3EC0, c_simulation_oddball_engine_globals_definition::vftable00::get_index
	// 0x4C3ED0, c_simulation_oddball_engine_globals_definition::vftable01::get_name
	// 0x4C44E0, c_simulation_oddball_engine_globals_definition::vftable02::get_size
	// 0x4C44F0, c_simulation_oddball_engine_globals_definition::vftable04
	// 0x4C44C0, c_simulation_oddball_engine_globals_definition::vftable05
	// 0x4C4500, c_simulation_oddball_engine_globals_definition::vftable12
	// 0x4C4070, c_simulation_oddball_engine_globals_definition::vftable15
	// 0x4C3EE0, c_simulation_oddball_engine_globals_definition::vftable16
	// 0x4C3E40, c_simulation_oddball_engine_globals_definition::vftable17
	// 0x4C4590, c_simulation_oddball_engine_globals_definition::vftable29::update
};
struct c_simulation_king_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C4650, c_simulation_king_engine_globals_definition::vftable00::get_index
	// 0x4C4660, c_simulation_king_engine_globals_definition::vftable01::get_name
	// 0x4C4850, c_simulation_king_engine_globals_definition::vftable02::get_size
	// 0x4C4860, c_simulation_king_engine_globals_definition::vftable04
	// 0x4C4830, c_simulation_king_engine_globals_definition::vftable05
	// 0x4C4870, c_simulation_king_engine_globals_definition::vftable12
	// 0x4C4720, c_simulation_king_engine_globals_definition::vftable15
	// 0x4C4670, c_simulation_king_engine_globals_definition::vftable16
	// 0x4C4630, c_simulation_king_engine_globals_definition::vftable17
	// 0x4C48D0, c_simulation_king_engine_globals_definition::vftable29::update
};
struct c_simulation_territories_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C4A10, c_simulation_territories_engine_globals_definition::vftable00::get_index
	// 0x4C4A20, c_simulation_territories_engine_globals_definition::vftable01::get_name
	// 0x4C4ED0, c_simulation_territories_engine_globals_definition::vftable02::get_size
	// 0x4C4EE0, c_simulation_territories_engine_globals_definition::vftable04
	// 0x4C4EB0, c_simulation_territories_engine_globals_definition::vftable05
	// 0x4C4EF0, c_simulation_territories_engine_globals_definition::vftable12
	// 0x4C4BC0, c_simulation_territories_engine_globals_definition::vftable15
	// 0x4C4A30, c_simulation_territories_engine_globals_definition::vftable16
	// 0x4C49F0, c_simulation_territories_engine_globals_definition::vftable17
	// 0x4C5010, c_simulation_territories_engine_globals_definition::vftable29::update
};
struct c_simulation_juggernaut_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C50D0, c_simulation_juggernaut_engine_globals_definition::vftable00::get_index
	// 0x4C50E0, c_simulation_juggernaut_engine_globals_definition::vftable01::get_name
	// 0x4C5340, c_simulation_juggernaut_engine_globals_definition::vftable02::get_size
	// 0x4C5350, c_simulation_juggernaut_engine_globals_definition::vftable04
	// 0x4C5320, c_simulation_juggernaut_engine_globals_definition::vftable05
	// 0x4C5360, c_simulation_juggernaut_engine_globals_definition::vftable12
	// 0x4C51E0, c_simulation_juggernaut_engine_globals_definition::vftable15
	// 0x4C50F0, c_simulation_juggernaut_engine_globals_definition::vftable16
	// 0x4C50B0, c_simulation_juggernaut_engine_globals_definition::vftable17
	// 0x4C53E0, c_simulation_juggernaut_engine_globals_definition::vftable29::update
};
struct c_simulation_sandbox_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4B7350, c_simulation_sandbox_engine_globals_definition::vftable00::get_index
	// 0x4B7360, c_simulation_sandbox_engine_globals_definition::vftable01::get_name
	// 0x4B77B0, c_simulation_sandbox_engine_globals_definition::vftable02::get_size
	// 0x4B77C0, c_simulation_sandbox_engine_globals_definition::vftable04
	// 0x4B7790, c_simulation_sandbox_engine_globals_definition::vftable05
	// 0x4B7320, c_simulation_sandbox_engine_globals_definition::vftable09
	// 0x4B77D0, c_simulation_sandbox_engine_globals_definition::vftable12
	// 0x4B74C0, c_simulation_sandbox_engine_globals_definition::vftable15
	// 0x4B7370, c_simulation_sandbox_engine_globals_definition::vftable16
	// 0x4B7330, c_simulation_sandbox_engine_globals_definition::vftable17
	// 0x4B7870, c_simulation_sandbox_engine_globals_definition::vftable29::update
};
struct c_simulation_infection_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C5490, c_simulation_infection_engine_globals_definition::vftable00::get_index
	// 0x4C54A0, c_simulation_infection_engine_globals_definition::vftable01::get_name
	// 0x4C5790, c_simulation_infection_engine_globals_definition::vftable02::get_size
	// 0x4C57A0, c_simulation_infection_engine_globals_definition::vftable04
	// 0x4C5770, c_simulation_infection_engine_globals_definition::vftable05
	// 0x4C57B0, c_simulation_infection_engine_globals_definition::vftable12
	// 0x4C55D0, c_simulation_infection_engine_globals_definition::vftable15
	// 0x4C54B0, c_simulation_infection_engine_globals_definition::vftable16
	// 0x4C5470, c_simulation_infection_engine_globals_definition::vftable17
	// 0x4C5850, c_simulation_infection_engine_globals_definition::vftable29::update
};
struct c_simulation_vip_engine_globals_definition : c_simulation_game_engine_globals_definition
{
	// 0x4C5960, c_simulation_vip_engine_globals_definition::vftable00::get_index
	// 0x4C5970, c_simulation_vip_engine_globals_definition::vftable01::get_name
	// 0x4C5CF0, c_simulation_vip_engine_globals_definition::vftable02::get_size
	// 0x4C5D00, c_simulation_vip_engine_globals_definition::vftable04
	// 0x4C5CD0, c_simulation_vip_engine_globals_definition::vftable05
	// 0x4C5D10, c_simulation_vip_engine_globals_definition::vftable12
	// 0x4C5AD0, c_simulation_vip_engine_globals_definition::vftable15
	// 0x4C5980, c_simulation_vip_engine_globals_definition::vftable16
	// 0x4C5940, c_simulation_vip_engine_globals_definition::vftable17
	// 0x4C5E50, c_simulation_vip_engine_globals_definition::vftable29::update
};
struct c_simulation_game_engine_player_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_game_statborg_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_breakable_surface_group_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_map_variant_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_unit_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_item_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_generic_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_generic_garbage_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_vehicle_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_projectile_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_weapon_entity_definition : c_simulation_game_engine_globals_definition
{
};
struct c_simulation_device_entity_definition : c_simulation_game_engine_globals_definition
{
};

struct c_simulation_event_definition // TODO: add all the inherited `classes` for this `class`
{
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// __purecall
	// c_simulation_event_definition__vftable12
	// __purecall
};


auto g_simulation_globals_type_collection = GetStructure<s_simulation_globals_type_collection>(0x19A9FBC);

auto simulation_slayer_engine_globals_definition = GetStructure<c_simulation_slayer_engine_globals_definition>(0x161FFF4);
auto simulation_ctf_engine_globals_definition = GetStructure<c_simulation_ctf_engine_globals_definition>(0x1641B94);
auto simulation_assault_engine_globals_definition = GetStructure<c_simulation_assault_engine_globals_definition>(0x1641D2C);
auto simulation_oddball_engine_globals_definition = GetStructure<c_simulation_oddball_engine_globals_definition>(0x1641E84);
auto simulation_king_engine_globals_definition = GetStructure<c_simulation_king_engine_globals_definition>(0x1641FD4);
auto simulation_territories_engine_globals_definition = GetStructure<c_simulation_territories_engine_globals_definition>(0x164210C);
auto simulation_juggernaut_engine_globals_definition = GetStructure<c_simulation_juggernaut_engine_globals_definition>(0x16422BC);
auto simulation_sandbox_engine_globals_definition = GetStructure<c_simulation_sandbox_engine_globals_definition>(0x1620074);
auto simulation_infection_engine_globals_definition = GetStructure<c_simulation_infection_engine_globals_definition>(0x164244C);
auto simulation_vip_engine_globals_definition = GetStructure<c_simulation_vip_engine_globals_definition>(0x1642654);
auto simulation_game_engine_player_entity_definition = GetStructure<c_simulation_game_engine_player_entity_definition>(0x1640624);
auto simulation_game_statborg_entity_definition = GetStructure<c_simulation_game_statborg_entity_definition>(0x164278C);
auto simulation_breakable_surface_group_entity_definition = GetStructure<c_simulation_breakable_surface_group_entity_definition>(0x1642AE4);
auto simulation_map_variant_entity_definition = GetStructure<c_simulation_map_variant_entity_definition>(0x1643A54);
auto simulation_unit_entity_definition = GetStructure<c_simulation_unit_entity_definition>(0x1640F34);
auto simulation_item_entity_definition = GetStructure<c_simulation_item_entity_definition>(0x1642D9C);
auto simulation_generic_entity_definition = GetStructure<c_simulation_generic_entity_definition>(0x1642F24);
auto simulation_generic_garbage_entity_definition = GetStructure<c_simulation_generic_garbage_entity_definition>(0x1642F24);
auto simulation_vehicle_entity_definition = GetStructure<c_simulation_vehicle_entity_definition>(0x164311C);
auto simulation_projectile_entity_definition = GetStructure<c_simulation_projectile_entity_definition>(0x1640204);
auto simulation_weapon_entity_definition = GetStructure<c_simulation_weapon_entity_definition>(0x1643384);
auto simulation_device_entity_definition = GetStructure<c_simulation_device_entity_definition>(0x164385C);

auto simulation_damage_aftermath_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_damage_aftermath_event_definition*/>(0x16429A0);
auto simulation_damage_section_response_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_damage_section_response_event_definition*/>(0x16429F0);
auto simulation_breakable_surface_damage_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_breakable_surface_damage_event_definition*/>(0x1642A44);
auto simulation_projectile_attached_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_projectile_attached_event_definition*/>(0x164029C);
auto simulation_projectile_detonate_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_projectile_detonate_event_definition*/>(0x16402EC);
auto simulation_projectile_impact_effect_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_projectile_impact_effect_event_definition*/>(0x164033C);
auto simulation_projectile_object_impact_effect_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_projectile_object_impact_effect_event_definition*/>(0x1640394);
auto simulation_effect_on_pos_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_effect_on_pos_event_definition*/>(0x163F824);
auto simulation_game_engine_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_game_engine_event_definition*/>(0x163FE20);
auto simulation_unit_board_vehicle_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_board_vehicle_event_definition*/>(0x16410BC);
auto simulation_unit_pickup_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_pickup_event_definition*/>(0x1641334);
auto simulation_weapon_effect_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_weapon_effect_event_definition*/>(0x1643590);
auto simulation_weapon_empty_click_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_weapon_empty_click_event_definition*/>(0x16435DC);
auto simulation_hit_marker_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_hit_marker_event_definition*/>(0x1642A9C);
auto simulation_unit_exit_vehicle_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_exit_vehicle_event_definition*/>(0x164101C);
auto simulation_unit_assassinate_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_assassinate_event_definition*/>(0x164106C);
auto simulation_player_taunt_request_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_player_taunt_request_event_definition*/>(0x164074C);
auto simulation_weapon_fire_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_weapon_fire_event_definition*/>(0x164341C);
auto simulation_weapon_reload_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_weapon_reload_event_definition*/>(0x1643464);
auto simulation_unit_throw_initiate_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_throw_initiate_event_definition*/>(0x164110C);
auto simulation_unit_melee_initiate_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_melee_initiate_event_definition*/>(0x16411AC);
auto simulation_weapon_pickup_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_weapon_pickup_event_definition*/>(0x16434B0);
auto simulation_weapon_put_away_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_weapon_put_away_event_definition*/>(0x16434FC);
auto simulation_weapon_drop_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_weapon_drop_event_definition*/>(0x1643548);
auto simulation_vehicle_flip_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_vehicle_flip_event_definition*/>(0x164129C);
auto simulation_vehicle_trick_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_vehicle_trick_event_definition*/>(0x16412E8);
auto simulation_device_touch_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_device_touch_event_definition*/>(0x16438F4);
auto simulation_unit_throw_release_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_throw_release_event_definition*/>(0x164115C);
auto simulation_unit_melee_damage_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_melee_damage_event_definition*/>(0x16411FC);
auto simulation_unit_melee_clang_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_melee_clang_event_definition*/>(0x164124C);
auto simulation_unit_enter_vehicle_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_enter_vehicle_event_definition*/>(0x1640FCC);
auto simulation_game_engine_request_boot_player_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_game_engine_request_boot_player_event_definition*/>(0x163FE68);
auto simulation_unit_equipment_use_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_equipment_use_event_definition*/>(0x1640EE4);
auto simulation_unit_equipment_pickup_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_unit_equipment_pickup_event_definition*/>(0x164137C);
auto simulation_player_respawn_request_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_player_respawn_request_event_definition*/>(0x16406A0);
auto simulation_player_force_base_respawn_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_player_force_base_respawn_event_definition*/>(0x16406F4);
auto simulation_player_editor_request_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_player_editor_request_event_definition*/>(0x16407A0);
auto simulation_projectile_supercombine_request_event_definition = GetStructure<c_simulation_event_definition/*c_simulation_projectile_supercombine_request_event_definition*/>(0x16403F0);
auto simulation_object_refresh_event_definitionftable = GetStructure<c_simulation_event_definition/*c_simulation_object_refresh_event_definition*/>(0x163F7D8);

int *simulation_definitions_table_initialize_hook(s_simulation_globals_type_collection *a1, int *simulation_global_and_entity_count, int *simulation_event_count)
{
	a1->set_global_and_entity(0, simulation_slayer_engine_globals_definition);
	a1->set_global_and_entity(1, simulation_ctf_engine_globals_definition);
	a1->set_global_and_entity(2, simulation_assault_engine_globals_definition);
	a1->set_global_and_entity(3, simulation_oddball_engine_globals_definition);
	a1->set_global_and_entity(4, simulation_king_engine_globals_definition);
	a1->set_global_and_entity(5, simulation_territories_engine_globals_definition);
	a1->set_global_and_entity(6, simulation_juggernaut_engine_globals_definition);
	a1->set_global_and_entity(7, simulation_sandbox_engine_globals_definition);
	a1->set_global_and_entity(8, simulation_infection_engine_globals_definition);
	a1->set_global_and_entity(9, simulation_vip_engine_globals_definition);
	a1->set_global_and_entity(10, simulation_game_engine_player_entity_definition);
	a1->set_global_and_entity(11, simulation_game_statborg_entity_definition);
	a1->set_global_and_entity(12, simulation_breakable_surface_group_entity_definition);
	a1->set_global_and_entity(13, simulation_map_variant_entity_definition);
	a1->set_global_and_entity(14, simulation_unit_entity_definition);
	a1->set_global_and_entity(15, simulation_item_entity_definition);
	a1->set_global_and_entity(16, simulation_generic_entity_definition);
	a1->set_global_and_entity(17, simulation_generic_garbage_entity_definition);
	a1->set_global_and_entity(18, simulation_vehicle_entity_definition);
	a1->set_global_and_entity(19, simulation_projectile_entity_definition);
	a1->set_global_and_entity(20, simulation_weapon_entity_definition);
	a1->set_global_and_entity(21, simulation_device_entity_definition);


	a1->set_event_data(0, simulation_damage_aftermath_event_definition);
	a1->set_event_data(1, simulation_damage_section_response_event_definition);
	a1->set_event_data(2, simulation_breakable_surface_damage_event_definition);
	a1->set_event_data(3, simulation_projectile_attached_event_definition);
	a1->set_event_data(4, simulation_projectile_detonate_event_definition);
	a1->set_event_data(5, simulation_projectile_impact_effect_event_definition);
	a1->set_event_data(6, simulation_projectile_object_impact_effect_event_definition);
	a1->set_event_data(7, simulation_effect_on_pos_event_definition);
	a1->set_event_data(8, simulation_game_engine_event_definition);
	a1->set_event_data(9, simulation_unit_board_vehicle_event_definition);
	a1->set_event_data(10, simulation_unit_pickup_event_definition);
	a1->set_event_data(11, simulation_weapon_effect_event_definition);
	a1->set_event_data(12, simulation_weapon_empty_click_event_definition);
	a1->set_event_data(13, simulation_hit_marker_event_definition);
	a1->set_event_data(14, simulation_unit_exit_vehicle_event_definition);
	a1->set_event_data(15, simulation_unit_assassinate_event_definition);
	a1->set_event_data(16, simulation_player_taunt_request_event_definition);
	a1->set_event_data(17, simulation_weapon_fire_event_definition);
	a1->set_event_data(18, simulation_unit_equipment_use_event_definition);
	a1->set_event_data(19, simulation_weapon_reload_event_definition);
	a1->set_event_data(20, simulation_unit_throw_initiate_event_definition);
	a1->set_event_data(21, simulation_unit_melee_initiate_event_definition);
	a1->set_event_data(22, simulation_weapon_pickup_event_definition);
	a1->set_event_data(23, simulation_weapon_put_away_event_definition);
	a1->set_event_data(24, simulation_weapon_drop_event_definition);
	a1->set_event_data(25, simulation_vehicle_flip_event_definition);
	a1->set_event_data(26, simulation_vehicle_trick_event_definition);
	a1->set_event_data(27, simulation_device_touch_event_definition);
	a1->set_event_data(28, simulation_unit_throw_release_event_definition);
	a1->set_event_data(29, simulation_unit_melee_damage_event_definition);
	a1->set_event_data(30, simulation_unit_melee_clang_event_definition);
	a1->set_event_data(31, simulation_unit_enter_vehicle_event_definition);
	a1->set_event_data(32, simulation_game_engine_request_boot_player_event_definition);
	a1->set_event_data(33, simulation_player_respawn_request_event_definition);
	a1->set_event_data(34, simulation_player_force_base_respawn_event_definition);
	a1->set_event_data(35, simulation_unit_equipment_pickup_event_definition);
	a1->set_event_data(36, simulation_projectile_supercombine_request_event_definition);
	a1->set_event_data(37, simulation_object_refresh_event_definitionftable);
	a1->set_event_data(38, simulation_player_editor_request_event_definition);

	*simulation_global_and_entity_count = 22;
	*simulation_event_count = 39;
	return simulation_event_count;
}

s_simulation_globals_type_collection *__cdecl simulation_globals_type_collection_get()
{
	return g_simulation_globals_type_collection;
}

inline void SubmitGameEngineHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//HookManager.Submit({ 0x715D0 }, &simulation_definitions_table_initialize_hook, "simulation_definitions_table_initialize"); // I don't feel comfortable testing this until all the `classes` above are mapped
	}
}

inline void SubmitGameEnginePatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}
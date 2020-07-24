#pragma once
#include <iostream>

#include <Utils.hpp>

#include "../memory/local_types.hpp"


char* XnkIdToStringHook(XnkAddr* a1)
{
	return a1->String();
}

char* XnkAddrToStringHook(XnkAddr* a1)
{
	return a1->String();
}

unsigned int __cdecl managed_session_game_end_hook(int session)
{
	auto& managed_session = reference_get<c_managed_session>(0x2247450, session);
	unsigned int result = managed_session.ShortFlagsE >> 10;
	if (result & 1)
	{
		printf_s("MP/NET/STUB_LOG_PATH,STUB_LOG_FILTER: managed_session_game_end: [0x%08X] calling game end before the game start processed, canceling both\n", session);
		managed_session.ShortFlagsE &= (unsigned)-0x401;
		printf_s("MP/NET/STUB_LOG_PATH,STUB_LOG_FILTER: managed_session_successful_game_start_complete: session 0x%8X, game start completed successfully\n", session);
		managed_session.LongFlags8 |= (unsigned)0x2000;
		result = printf_s("MP/NET/STUB_LOG_PATH,STUB_LOG_FILTER: managed_session_successful_game_end_complete: session 0x%8X, game end completed successfully\n", session);
		managed_session.LongFlags8 |= (unsigned)0x8000;
	}
	else
	{
		managed_session.ShortFlagsE = managed_session.ShortFlagsE | 0x200;
		managed_session.LongFlags8 &= (unsigned)-0x18001;
	}
	managed_session.LongFlags8 &= (unsigned)-5;
	managed_session.UnknownTimeValue = 0;
	return result;
}

// ManagedSession == 0 = Offline, ManagedSession == 1 = Local, ManagedSession == 2 = ???

char ManagedSession_XSession_GetHandle_hook(int ManagedSessionIndex, uint32_t* a2)
{
	if (ManagedSessionIndex == -1)
		return false;
	uint32_t* Handle = reference_get<c_managed_session>(0x2247450, ManagedSessionIndex).LiveSession.Handle;
	if (!Handle || Handle == (uint32_t*)-1)
		return false;
	*a2 = *Handle;
	//printf_s("ManagedSession[%d].LiveSession.Handle: 0x%d\n", ManagedSessionIndex, Handle);
	return true;
}

const char* ManagedSession_XSession_GetAddress_hook(int ManagedSessionIndex)
{
	if (ManagedSessionIndex != -1)
		return "00:00:00:00:00:00:00:00";

	//printf_s("ManagedSession[%d].LiveSession.XnkAddr: %s\n", ManagedSessionIndex, XnkAddr);
	return XnkAddrToStringHook(reference_get<c_managed_session>(0x2247450, ManagedSessionIndex).LiveSession.XnkAddr);
}

void __cdecl ManagedSession_DeleteSession_hook(int ManagedSessionIndex)
{
	static auto sub_5A8F50 = (char(__cdecl*)(uint32_t*))(0x5A8F50);
	auto& managed_session = reference_get<c_managed_session>(0x2247450, ManagedSessionIndex);
	managed_session.LiveSession.Handle = 0;
	managed_session.LongFlags8 &= -0x31;
	if ((managed_session.ShortFlagsE >> 1) & 1)
	{
		managed_session.ShortFlagsE = managed_session.ShortFlagsE & -3;
		if (HIWORD(managed_session.OverlappedTask.type) == e_session_overlapped_task_type::_modify)
			sub_5A8F50((uint32_t*)&managed_session.OverlappedTask);
		managed_session.LongFlags8 &= -2;
	}
	else
	{
		memset(managed_session.XnkAddr, 0, 0x30);
		memset(&managed_session.LiveSession, 0, 0x150);
		memset(&managed_session.LocalSession, 0, 0x150);
	}
}

char network_is_connected_to_live_hook()
{
	return IsConnectedToLive() == 0;
}

bool transport_available()
{
	return Transport()[0] && Transport()[1];
}

bool __fastcall network_session_parameter_countdown_timer_request_change_hook(void* thisPtr, void* unused, int state, int value)
{
	if (state == 2) // start
		value = 0;

	static auto network_session_parameter_countdown_timer_request_change = (bool(__thiscall*)(void* thisPtr, int state, int newValue))(0x453740);
	return network_session_parameter_countdown_timer_request_change(thisPtr, state, value);
}

char __cdecl change_network_privacy_hook(e_privacy_mode a1)
{
	printf_s("Changing network privacy to %s", a1.GetName());
	return ((char(__cdecl*)(e_privacy_mode))0xA7F950)(a1);
}

const char* __cdecl session_composition_get_string_hook(e_session_composition session_composition)
{
	printf_s("session composition: %s", session_composition.GetName());
	return session_composition.GetName();
}

// this is the function the game ui uses to connect the hosts | a3, a4, a5 are all the hosts XnkAddr
char __cdecl game_browser_join_host_hook(char a1, int a2, XnkAddr* a3, XnkAddr* a4, XnkAddr* a5)
{
	return s_join_data(a1, a2, a3, a4, a5)./*Print()->*/Join();
}

// this could probably use some error checking
char __cdecl network_join_to_remote_squad(char not_leader, char a2, char should_squad_join, int session_class, s_transport_secure_identifier* session_id, long(*key)[4], s_transport_secure_address* host_address)
{
	s_network_session_remote_session_join_data* remote_session_join_data = nullptr;

	// c_managed_sessions::squad_in_session
	// get_session_array
	if (!((void* (__thiscall*)(void*, s_transport_secure_identifier*))0x45F0E0)(((void* (__cdecl*)())0x49E1A0)(), session_id))
	{
		// network_squad_session_player_is_leader
		if (should_squad_join && ((bool(__cdecl*)())0x455320)())
		{
			if (&g_network_squad_session)
			{
				memset(remote_session_join_data, 0, sizeof(s_network_session_remote_session_join_data));
				remote_session_join_data = new s_network_session_remote_session_join_data(a2, session_class, session_id, host_address);

				// c_network_session_parameter_requested_remote_join_data::request_change
				((char(__thiscall*)(void*, s_network_session_remote_session_join_data*))0x4595B0)(g_network_squad_session.session_parameters_get()->requested_remote_join_data_get(), remote_session_join_data);

				g_remote_session_join_data = *remote_session_join_data;

				return true;
			}
		}
	}

	return false;
}

inline void SubmitNetworkingHooks(const char* name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		HookManager.Submit({ 0x00430C50 }, &XnkIdToStringHook, "XnkId::ToString");
		HookManager.Submit({ 0x00430ED0 }, &XnkAddrToStringHook, "XnkAddr::ToString");

		HookManager.Submit({ 0x00481E10 }, &managed_session_game_end_hook, "managed_session_game_end");

		HookManager.Submit({ 0x00482000 }, &ManagedSession_XSession_GetHandle_hook, "ManagedSession::XSession::GetHandle");
		HookManager.Submit({ 0x004820A0 }, &ManagedSession_XSession_GetAddress_hook, "ManagedSession::XSession::GetAddress");
		HookManager.Submit({ 0x004831F0 }, &ManagedSession_DeleteSession_hook, "ManagedSession::DeleteSession");

		HookManager.Submit({ 0x00442A90 }, &network_is_connected_to_live_hook, "network_is_connected_to_live");

		HookManager.Submit({ 0x00A83D45 }, &network_session_parameter_countdown_timer_request_change_hook, "network_session_parameter_countdown_timer_request_change", HookFlags::IsCall);

		//HookManager.Submit({ 0x69D631, 0xA7E2F2, 0xA7ED2B, 0xAA6C2D, 0xAA70E3, 0xAE888E, 0xAE88A4, 0xAE88B7, 0xAE9247, 0xAE925F, 0xAE9274, 0xAEA6D3, 0xAEA6EB, 0xAEA700, 0xAEBC0D, 0xAEBC23, 0xAEBC36, 0xB018FB }, &change_network_privacy_hook, "change_network_privacy", HookFlags::IsCall);

		HookManager.Submit({ 0x004D34E0 }, &session_composition_get_string_hook, "session_composition_get_string");

		HookManager.Submit({ 0x00ADE26D }, &game_browser_join_host_hook, "game_browser::join_host", HookFlags::IsCall);
	}
}

inline void SubmitNetworkingPatches(const char* name)
{
	if (ConfigManager.GetBool("Patches", name))
	{

	}
}
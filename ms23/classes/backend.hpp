#pragma once
#include <unordered_map>

#include "../utils/Utils.hpp"

#include "../memory/local_types.hpp"

std::unordered_map<const char *, const char *> BackendHashMap
{
	{ "f96526423b3c473eb3350716b74634b1", "FriendsService" },
	{ "7804a9f0c48f4e68bc3b16e9933e58e4", "SubscriptionAdd" },
	{ "dec87cc927e7495582b7adc34f0860d8", "SubscriptionRemove" },
	{ "0c9bf0e3062445a0a73330230e85c0ac", "GetSubscriptions" },

	{ "a74f776492be448295798ba5c74ab4eb", "GameStatisticsService" },
	{ "80d708a9f90345ec97f50bb4d7bbdc57", "GetChallengeSlots" },
	{ "975c93760e80490dab77353e475fbf1a", "RerollSlot" },
	{ "e116f6a8e3f34405803cb440562fab9c", "GetChallengeSlotInstances" },
	{ "3c214f66f0d446948981f6cf264236d5", "GetChallengeInstances" },
	{ "5c84448cf8374e60afef20c28252dc66", "GetChallengeDefinitions" },
	{ "697218622fb0441293559baddd764c2e", "ActivateChallenges" },
	{ "3f721e32ed8940bf8a63a59bfc451781", "DeactivateChallenges" },

	{ "e4b95cd8156947828b12000f80474850", "HeartbeatService" },
	{ "461d92357a0d43628f01ddd7e075e6ea", "GetServicesStatus" },
	{ "f152c44779c9442b841ed401c012a35a", "GetHeartbeatStatus" },
	{ "852b0ea5ac8444fca71bb4d86f96a20d", "GetDate" },

	{ "8a30791a119a4a2cb6db7f496132dff3", "MessagingService" },
	{ "27d1f8c2eb7b4d2fb67562e20cda99d4", "JoinChannels" },
	{ "c62ab4fd430642688323647ff442fc26", "LeaveChannels" },
	{ "a244b7f4b0cd49259e931dd28be75c90", "Send" },
	{ "2d3844a2559b4268a984f96fc5d8014e", "SendServiceMessage" },
	{ "a48546b55a1446c7acce1061545ed196", "Receive" },

	{ "9c1aaae299da4b9db7e9583dc8b0b2f2", "VivoxService" },
	{ "9c1aaae299da4b9db7e9583dc8b0b2f2", "Login" },

	{ "caa11c5e19dc42c38b67cf4acda5db44", "PresenceService" },
	{ "d3116e1e6b2b4157b21dd98582ee85db", "PresenceDisconnect" },
	{ "be1c65d830d445ba93f33dfeca6419ed", "PresenceConnect" },
	{ "4a2ae7db19f94cbc82af96f0c35bf95c", "PresenceGetUsersPresence" },
	{ "05c8d2d966dd4948b438066de594ccf7", "PartyJoin" },
	{ "9d17002ac24b4cecb1ac321dcdf7c495", "PartyLeave" },
	{ "21ceed397c454e38bb19526b7751bf83", "PartyKick" },
	{ "3f70ac03ffc24443bf229eab2d16a6c1", "PartySetGameData" },
	{ "5e7d3efa99c147d7a05dbea0d4629c63", "PartyGetStatus" },
	{ "d592dc7d4cf64ee8a398dbf08f210b52", "PartyGetStatusVersion" },
	{ "c0858270a5ad414ca7ff5075adcb2c6d", "CustomGameStart" },
	{ "553c7026b6c3445f9305690f347bb90c", "CustomGameStop" },
	{ "2313549188154d409cc401cb8cc6eee6", "MatchmakeStart" },
	{ "90439d26ddbe46bfb6ef8827441c24c5", "MatchmakeStop" },
	{ "8acbd061727e421bba5bef015c18e2e2", "MatchmakeGetStatus" },
	{ "724a87acdaa9410e9702ec220a8f0680", "ReportOnlineStats" },
	{ "7f1c2580473f4a17951e8129dca74adf", "GetPlaylistStat" },
	{ "ab323f1083ad4caa8658bda7912fc4a6", "GetPlaylistStatVersion" },

	{ "b4d15f136196431a998e01903c605367", "SessionControlService" },
	{ "cc6882b588d94b7a843de5289f05355b", "ClientGetStatus" },
	{ "a743cb48398e43dc8edbcc465ea52673", "GetSessionBasicData" },
	{ "0a490cb9c5e145be9a7ceb7c098caf9a", "GetSessionChain" },

	{ "ee3aec5524854d6e918307d24a14623d", "TitleResourceService" },
	{ "c3bf25f34b72499ca307c6e4431c79c1", "GetTitleConfiguration" },
	{ "8daf1363deae4319a8beecda0490b9f9", "GetTitleConfigRaw" },
	{ "a37bdcfd61fe48efaab11586255fdd54", "GetTitleTagsPatchConfiguration" },

	{ "d7e31cf042024b22ac09d2a42c0403cb", "UserStorageService" },
	{ "1275b0dfa4ed4d9bacd8bb37bdc9fac4", "SetPrivateData" },
	{ "ab52a321ea8d4a78a61f10620d74e2d1", "GetPrivateData" },
	{ "69d967acb77e455987e230d6e8b5b1c0", "SetPublicData" },
	{ "dbcbbedf8eb748b19766e1f7e25e6e46", "GetPublicData" },

	{ "416c82d428394df6a1bb9897f7d248b2", "UserService" },
	{ "aebaa08921984fe19ce6562850b34281", "SignOut" },
	{ "28635cd91941462aac4d0c36497e00f1", "GetUsersByNickname" },
	{ "fd9a7e1d508242be9effaf969860fba8", "NicknameChange" },
	{ "fba12d422e6b447ea7f3d9a19a6964bb", "GetUsersBaseData" },
	{ "f6cf5fa595f2496290875288874a3396", "GetUsersPrimaryStates" },
	{ "9e18f0339c27412c89551072bfb60fb6", "GetUserStates" },
	{ "f4278d2a42314dfbaa5f0e3d3e196dfa", "GetTransactionHistory" },
	{ "751112d775824326b45cdf038296df88", "ApplyExternalOffer" },
	{ "a9681a7e8685475599c406b8747739ee", "ApplyOfferAndGetTransactionHistory" },
	{ "c5f3082e2d584d53abcb0ff0a9ad81cf", "ApplyOfferListAndGetTransactionHistory" },
	{ "85aa11207964476da0eeee10c54bbed4", "ApplyOffer" },
	{ "ff7dfbec3141480783455955980d8084", "ApplyOfferList" },
	{ "7f561c33e3bb492693f8c6c8ede19bb4", "GetItemOffers" },
	{ "872c55a7fb1d4c848e14d96f7e78fc03", "GetShop" },

	{ "89dffc06f9fc43eba2bd9271d22a609b", "ClanService" },
	{ "a2e33ce546ed4cefaf71533fc5fd07c4", "ClanCreate" },
	{ "20baf94d9482443cb75876344d492369", "ClanGetBaseData" },
	{ "611f172a9eca4816905ebbdd7d8e55d0", "ClanGetMembership" },
	{ "a1a2b7c387a0488fa6f72847959a4ba6", "ClanJoin" },
	{ "24223c8811154233ba26ac82dc01f0c4", "ClanKick" },
	{ "f1a64d6e121543eca2b4b3ae7ed9fdeb", "ClanLeave" },
	{ "044d42867b7e431e85ae58e868e1cf96", "ClanGetByName" },

	{ "ca7ce17947c14aaa9adff2cabd8e8fdc", "ArbitraryStorageService" },
	{ "0cfbb05ba5fa4ac3a2d8760b59c78276", "WriteDiagnosticsData" },
	{ "920e14f21b584d7280f18c8fe4a90257", "WriteADFPack" }
};

//.text:0094D480; const char *__cdecl BackEnd::IUserService()
const char *__cdecl BackEnd__IUserService()
{
	return BackendHashMap.at("416c82d428394df6a1bb9897f7d248b2");
}

inline void AddBackendHooks(const char *name)
{
	if (ConfigManager.GetBool("Hooks", name))
	{
		//if (!ms23)
		//{
			//	AddHook({ 0x53BD40 }, &BackEnd__IAuthorizationService__RefreshTokens, "BackEnd::IAuthorizationService::RefreshTokens");
			//	AddHook({ 0x53BD50 }, &BackEnd__IAuthorizationService, "BackEnd::IAuthorizationService");
			//	AddHook({ 0x53C8C0 }, &BackEnd__IAuthorizationService__Enqueue, "BackEnd::IAuthorizationService::Enqueue");
			//	AddHook({ 0x53CFA0 }, &BackEnd__IAuthorizationService__Upqueue, "BackEnd::IAuthorizationService::Upqueue");
			//	AddHook({ 0x53D550 }, &BackEnd__IAuthorizationService__CheckBan, "BackEnd::IAuthorizationService::CheckBan");
			//	AddHook({ 0x53DA40 }, &BackEnd__IAuthorizationService__Dequeue, "BackEnd::IAuthorizationService::Dequeue");
			//	AddHook({ 0x53DEE0 }, &BackEnd__IEndpointsDispatcherService__GetAuthorizationEndpoints__GetEndPoints,, "BackEnd::IEndpointsDispatcherService::GetAuthorizationEndpoints");
			//	AddHook({ 0x53E590 }, &BackEnd__IEndpointsDispatcherService__GetAuthorizationEndpointsAndDate__GetEndPoints,, "BackEnd::IEndpointsDispatcherService::GetAuthorizationEndpointsAndDate");
			//	AddHook({ 0x53EC50 }, &BackEnd__IFriendsService__SubscriptionAdd, "BackEnd::IFriendsService::SubscriptionAdd");
			//	AddHook({ 0x53EC60 }, &BackEnd__IFriendsService, "BackEnd::IFriendsService");
			//	AddHook({ 0x53F250 }, &BackEnd__IFriendsService__SubscriptionRemove, "BackEnd::IFriendsService::SubscriptionRemove");
			//	AddHook({ 0x53F6A0 }, &BackEnd__IFriendsService__GetSubscriptions, "BackEnd::IFriendsService::GetSubscriptions");
			//	AddHook({ 0x53FBB0 }, &BackEnd__IGameStatisticsService__GetChallengeSlots, "BackEnd::IGameStatisticsService::GetChallengeSlots");
			//	AddHook({ 0x53FBC0 }, &BackEnd__IGameStatisticsService, "BackEnd::IGameStatisticsService");
			//	AddHook({ 0x540150 }, &BackEnd__IGameStatisticsService__RerollSlot, "BackEnd::IGameStatisticsService::RerollSlot");
			//	AddHook({ 0x540650 }, &BackEnd__IGameStatisticsService__GetChallengeSlotInstances, "BackEnd::IGameStatisticsService::GetChallengeSlotInstances");
			//	AddHook({ 0x540D20 }, &BackEnd__IGameStatisticsService__GetChallengeInstances, "BackEnd::IGameStatisticsService::GetChallengeInstances");
			//	AddHook({ 0x5413F0 }, &BackEnd__IGameStatisticsService__GetChallengeDefinitions, "BackEnd::IGameStatisticsService::GetChallengeDefinitions");
			//	AddHook({ 0x541A20 }, &BackEnd__IGameStatisticsService__ActivateChallenges, "BackEnd::IGameStatisticsService::ActivateChallenges");
			//	AddHook({ 0x542080 }, &BackEnd__IGameStatisticsService__DeactivateChallenges, "BackEnd::IGameStatisticsService::DeactivateChallenges");
			//	AddHook({ 0x5425E0 }, &BackEnd__IHeartbeatService__GetServicesStatus__GetEndPoints,, "BackEnd::IHeartbeatService::GetServicesStatus");
			//	AddHook({ 0x5425F0 }, &BackEnd__IHeartbeatService__GetEndPoints,, "BackEnd::IHeartbeatService");
			//	AddHook({ 0x542BF0 }, &BackEnd__IHeartbeatService__GetHeartbeatStatus__GetEndPoints,, "BackEnd::IHeartbeatService::GetHeartbeatStatus");
			//	AddHook({ 0x543180 }, &BackEnd__IHeartbeatService__GetDate__GetEndPoints,, "BackEnd::IHeartbeatService::GetDate");
			//	AddHook({ 0x543610 }, &BackEnd__IMessagingService__JoinChannels, "BackEnd::IMessagingService::JoinChannels");
			//	AddHook({ 0x543620 }, &BackEnd__IMessagingService, "BackEnd::IMessagingService");
			//	AddHook({ 0x543C20 }, &BackEnd__IMessagingService__LeaveChannels, "BackEnd::IMessagingService::LeaveChannels");
			//	AddHook({ 0x544150 }, &BackEnd__IMessagingService__Send, "BackEnd::IMessagingService::Send");
			//	AddHook({ 0x544740 }, &BackEnd__IMessagingService__SendServiceMessage, "BackEnd::IMessagingService::SendServiceMessage");
			//	AddHook({ 0x544B90 }, &BackEnd__IMessagingService__Receive, "BackEnd::IMessagingService::Receive");
			//	AddHook({ 0x545070 }, &BackEnd__IVivoxService__Login__GetEndPoints,, "BackEnd::IVivoxService::Login");
			//	AddHook({ 0x545080 }, &BackEnd__IVivoxService__GetEndPoints,, "BackEnd::IVivoxService");
			//	AddHook({ 0x545530 }, &BackEnd__IPresenceService__PresenceDisconnect, "BackEnd::IPresenceService::PresenceDisconnect");
			//	AddHook({ 0x545540 }, &BackEnd__IPresenceService, "BackEnd::IPresenceService");
			//	AddHook({ 0x5458F0 }, &BackEnd__IPresenceService__PresenceConnect, "BackEnd::IPresenceService::PresenceConnect");
			//	AddHook({ 0x545D90 }, &BackEnd__IPresenceService__PresenceGetUsersPresence, "BackEnd::IPresenceService::PresenceGetUsersPresence");
			//	AddHook({ 0x5463C0 }, &BackEnd__IPresenceService__PartyJoin, "BackEnd::IPresenceService::PartyJoin");
			//	AddHook({ 0x546920 }, &BackEnd__IPresenceService__PartyLeave, "BackEnd::IPresenceService::PartyLeave");
			//	AddHook({ 0x546C70 }, &BackEnd__IPresenceService__PartyKick, "BackEnd::IPresenceService::PartyKick");
			//	AddHook({ 0x547030 }, &BackEnd__IPresenceService__PartySetGameData, "BackEnd::IPresenceService::PartySetGameData");
			//	AddHook({ 0x547390 }, &BackEnd__IPresenceService__PartyGetStatus, "BackEnd::IPresenceService::PartyGetStatus");
			//	AddHook({ 0x5477C0 }, &BackEnd__IPresenceService__PartyGetStatusVersion, "BackEnd::IPresenceService::PartyGetStatusVersion");
			//	AddHook({ 0x547B70 }, &BackEnd__IPresenceService__CustomGameStart, "BackEnd::IPresenceService::CustomGameStart");
			//	AddHook({ 0x548120 }, &BackEnd__IPresenceService__CustomGameStop, "BackEnd::IPresenceService::CustomGameStop");
			//	AddHook({ 0x5484D0 }, &BackEnd__IPresenceService__MatchmakeStart, "BackEnd::IPresenceService::MatchmakeStart");
			//	AddHook({ 0x548830 }, &BackEnd__IPresenceService__MatchmakeStop, "BackEnd::IPresenceService::MatchmakeStop");
			//	AddHook({ 0x548B90 }, &BackEnd__IPresenceService__MatchmakeGetStatus, "BackEnd::IPresenceService::MatchmakeGetStatus");
			//	AddHook({ 0x548FE0 }, &BackEnd__IPresenceService__ReportOnlineStats, "BackEnd::IPresenceService::ReportOnlineStats");
			//	AddHook({ 0x549450 }, &BackEnd__IPresenceService__GetPlaylistStat, "BackEnd::IPresenceService::GetPlaylistStat");
			//	AddHook({ 0x549A50 }, &BackEnd__IPresenceService__GetPlaylistStatVersion, "BackEnd::IPresenceService::GetPlaylistStatVersion");
			//	AddHook({ 0x54A020 }, &BackEnd__ISessionControlService__ClientGetStatus, "BackEnd::ISessionControlService::ClientGetStatus");
			//	AddHook({ 0x54A030 }, &BackEnd__ISessionControlService, "BackEnd::ISessionControlService");
			//	AddHook({ 0x54A640 }, &BackEnd__ISessionControlService__GetSessionBasicData, "BackEnd::ISessionControlService::GetSessionBasicData");
			//	AddHook({ 0x54AC70 }, &BackEnd__ISessionControlService__GetSessionChain, "BackEnd::ISessionControlService::GetSessionChain");
			//	AddHook({ 0x54B340 }, &BackEnd__ITitleResourceService__GetTitleConfiguration, "BackEnd::ITitleResourceService::GetTitleConfiguration");
			//	AddHook({ 0x54B350 }, &BackEnd__ITitleResourceService, "BackEnd::ITitleResourceService");
			//	AddHook({ 0x54B770 }, &BackEnd__ITitleResourceService__GetTitleConfigRaw, "BackEnd::ITitleResourceService::GetTitleConfigRaw");
			//	AddHook({ 0x54BB90 }, &BackEnd__ITitleResourceService__GetTitleTagsPatchConfiguration, "BackEnd::ITitleResourceService::GetTitleTagsPatchConfiguration");
			//	AddHook({ 0x54C080 }, &BackEnd__IUserStorageService__SetPrivateData, "BackEnd::IUserStorageService::SetPrivateData");
			//	AddHook({ 0x54C090 }, &BackEnd__IUserStorageService, "BackEnd::IUserStorageService");
			//	AddHook({ 0x54C680 }, &BackEnd__IUserStorageService__GetPrivateData, "BackEnd::IUserStorageService::GetPrivateData");
			//	AddHook({ 0x54CAA0 }, &BackEnd__IUserStorageService__SetPublicData, "BackEnd::IUserStorageService::SetPublicData");
			//	AddHook({ 0x54CE50 }, &BackEnd__IUserStorageService__GetPublicData, "BackEnd::IUserStorageService::GetPublicData");
			//	AddHook({ 0x54D470 }, &BackEnd__IUserService__SignOut, "BackEnd::IUserService::SignOut");
			//	AddHook({ 0x54D480 }, &BackEnd__IUserService, "BackEnd::IUserService");
			//	AddHook({ 0x54D830 }, &BackEnd__IUserService__GetUsersByNickname, "BackEnd::IUserService::GetUsersByNickname");
			//	AddHook({ 0x54DE40 }, &BackEnd__IUserService__NicknameChange, "BackEnd::IUserService::NicknameChange");
			//	AddHook({ 0x54E2C0 }, &BackEnd__IUserService__GetUsersBaseData, "BackEnd::IUserService::GetUsersBaseData");
			//	AddHook({ 0x54E8F0 }, &BackEnd__IUserService__GetUsersPrimaryStates, "BackEnd::IUserService::GetUsersPrimaryStates");
			//	AddHook({ 0x54EED0 }, &BackEnd__IUserService__GetUserStates, "BackEnd::IUserService::GetUserStates");
			//	AddHook({ 0x54F290 }, &BackEnd__IUserService__GetTransactionHistory, "BackEnd::IUserService::GetTransactionHistory");
			//	AddHook({ 0x54F760 }, &BackEnd__IUserService__ApplyExternalOffer, "BackEnd::IUserService::ApplyExternalOffer");
			//	AddHook({ 0x54FB10 }, &BackEnd__IUserService__ApplyOfferAndGetTransactionHistory, "BackEnd::IUserService::ApplyOfferAndGetTransactionHistory");
			//	AddHook({ 0x54FF40 }, &BackEnd__IUserService__ApplyOfferListAndGetTransactionHistory, "BackEnd::IUserService::ApplyOfferListAndGetTransactionHistory");
			//	AddHook({ 0x550470 }, &BackEnd__IUserService__ApplyOffer, "BackEnd::IUserService::ApplyOffer");
			//	AddHook({ 0x550910 }, &BackEnd__IUserService__ApplyOfferList, "BackEnd::IUserService::ApplyOfferList");
			//	AddHook({ 0x550E40 }, &BackEnd__IUserService__GetItemOffers, "BackEnd::IUserService::GetItemOffers");
			//	AddHook({ 0x5513A0 }, &BackEnd__IUserService__GetShop, "BackEnd::IUserService::GetShop");
			//	AddHook({ 0x5517D0 }, &BackEnd__IClanService__ClanCreate, "BackEnd::IClanService::ClanCreate");
			//	AddHook({ 0x5517E0 }, &BackEnd__IClanService, "BackEnd::IClanService");
			//	AddHook({ 0x551EE0 }, &BackEnd__IClanService__ClanGetBaseData, "BackEnd::IClanService::ClanGetBaseData");
			//	AddHook({ 0x552510 }, &BackEnd__IClanService__ClanGetMembership, "BackEnd::IClanService::ClanGetMembership");
			//	AddHook({ 0x552B40 }, &BackEnd__IClanService__ClanJoin, "BackEnd::IClanService::ClanJoin");
			//	AddHook({ 0x553050 }, &BackEnd__IClanService__ClanKick, "BackEnd::IClanService::ClanKick");
			//	AddHook({ 0x553420 }, &BackEnd__IClanService__ClanLeave, "BackEnd::IClanService::ClanLeave");
			//	AddHook({ 0x5537D0 }, &BackEnd__IClanService__ClanGetByName, "BackEnd::IClanService::ClanGetByName");
			//	AddHook({ 0x553F40 }, &BackEnd__IArbitraryStorageService__WriteDiagnosticsData, "BackEnd::IArbitraryStorageService::WriteDiagnosticsData");
			//	AddHook({ 0x553F50 }, &BackEnd__IArbitraryStorageService, "BackEnd::IArbitraryStorageService");
			//	AddHook({ 0x5544A0 }, &BackEnd__IArbitraryStorageService__WriteADFPack, "BackEnd::IArbitraryStorageService::WriteADFPack");
		//}
	}
}

//TODO: get this working
void ReplaceStringPtr(const char *string, std::vector<size_t> next_op_offsets)
{
	for (auto next_op_offset : next_op_offsets)
		SetMemoryAtOffset<const char *>(next_op_offset - 4, string);
}

void FriendsService()
{
	ReplaceStringPtr(BackendHashMap.at("f96526423b3c473eb3350716b74634b1"), { 0x711AF4, 0x7C5903, 0x7C5B23, 0x93EC60, 0x93EDBD, 0x93F2AD, 0x93F81D, 0x982DB1, 0x988FEA, 0x107BC74, 0x12FF654, 0x12FF6C0, 0x12FF6C8, 0x12FF784 });
	ReplaceStringPtr(BackendHashMap.at("7804a9f0c48f4e68bc3b16e9933e58e4"), { 0x7C58FE, 0x93EC55, 0x93EDC7, 0x12FF6C8 });
	ReplaceStringPtr(BackendHashMap.at("dec87cc927e7495582b7adc34f0860d8"), { 0x7C5B1E, 0x93F255, 0x93F2B7, 0x12FF6C4 });
	ReplaceStringPtr(BackendHashMap.at("0c9bf0e3062445a0a73330230e85c0ac"), { 0x711AEF, 0x93F6A5, 0x93F827, 0x988FE5, 0x12FF66C });
}

inline void AddBackendPatches(const char *name)
{
	if (ConfigManager.GetBool("Patches", name))
	{
		//if (!ms23)
		//{
			//AddPatch(&FriendsService, "FriendsService");
		//}
	}
}
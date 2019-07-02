#pragma once

auto DLL_NAME = "haloreach";

#pragma comment(linker, "/export:SetLibrarySettings=haloreach_org.SetLibrarySettings")
#pragma comment(linker, "/export:CreateGameEngine=haloreach_org.CreateGameEngine")
#pragma comment(linker, "/export:CreateDataAccess=haloreach_org.CreateDataAccess")
#pragma comment(linker, "/export:CreateDedicatedServerInfo=haloreach_org.CreateDedicatedServerInfo")

#pragma endregion

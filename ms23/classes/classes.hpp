#pragma once


#include "camera.hpp"
#include "cinematic.hpp"
#include "filo.hpp"
#include "game_engine.hpp"
#include "game_globals.hpp"
#include "game_state.hpp"
#include "game_systems.hpp"
#include "level.hpp"
#include "map.hpp"
#include "misc.hpp"
#include "networking.hpp"
#include "physics.hpp"
#include "player_profile.hpp"
#include "players.hpp"
#include "preferences.hpp"
#include "print.hpp"
#include "simulation.hpp"
#include "tags.hpp"
#include "ui.hpp"
#include "unit.hpp"

void AddHooks()
{
	AddCameraHooks("Camera");
	AddFiloHooks("Filo");
	AddGameEngineHooks("GameEngine");
	AddGameGlobalsHooks("GameGlobals");
	AddGameStateHooks("GameState");
	AddGameSystemsHooks("GameSystems");
	AddLevelHooks("Level");
	AddMapHooks("Map");
	AddMiscHooks("Misc");
	AddNetworkingHooks("Networking");
	AddPhysicsHooks("Physics");
	AddPlayerProfileHooks("PlayerProfile");
	AddPlayersHooks("Players");
	AddPreferencesHooks("Preferences");
	AddPrintHooks("Print");
	AddRendererHooks("Renderer");
	AddSimulationHooks("Simulation");
	AddTagsHooks("Tags");
	AddUiHooks("Ui");
	AddUnitHooks("Unit");
}

void AddPatches()
{
	AddCameraPatches("Camera");
	AddFiloPatches("Filo");
	AddGameEnginePatches("GameEngine");
	AddGameGlobalsPatches("GameGlobals");
	AddGameStatePatches("GameState");
	AddGameSystemsPatches("GameSystems");
	AddLevelPatches("Level");
	AddMapPatches("Map");
	AddMiscPatches("Misc");
	AddNetworkingPatches("Networking");
	AddPhysicsPatches("Physics");
	AddPlayerProfilePatches("PlayerProfile");
	AddPlayersPatches("Players");
	AddPreferencesPatches("Preferences");
	AddPrintPatches("Print");
	AddRendererPatches("Renderer");
	AddSimulationPatches("Simulation");
	AddTagsPatches("Tags");
	AddUiPatches("Ui");
	AddUnitPatches("Unit");
}
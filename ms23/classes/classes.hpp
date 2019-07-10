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

void SubmitHooks()
{
	SubmitCameraHooks("Camera");
	SubmitFiloHooks("Filo");
	SubmitGameEngineHooks("GameEngine");
	SubmitGameGlobalsHooks("GameGlobals");
	SubmitGameStateHooks("GameState");
	SubmitGameSystemsHooks("GameSystems");
	SubmitLevelHooks("Level");
	SubmitMapHooks("Map");
	SubmitMiscHooks("Misc");
	SubmitNetworkingHooks("Networking");
	SubmitPhysicsHooks("Physics");
	SubmitPlayerProfileHooks("PlayerProfile");
	SubmitPlayersHooks("Players");
	SubmitPreferencesHooks("Preferences");
	SubmitPrintHooks("Print");
	SubmitRendererHooks("Renderer");
	SubmitSimulationHooks("Simulation");
	SubmitTagsHooks("Tags");
	SubmitUiHooks("Ui");
	SubmitUnitHooks("Unit");
}

void SubmitPatches()
{
	SubmitCameraPatches("Camera");
	SubmitFiloPatches("Filo");
	SubmitGameEnginePatches("GameEngine");
	SubmitGameGlobalsPatches("GameGlobals");
	SubmitGameStatePatches("GameState");
	SubmitGameSystemsPatches("GameSystems");
	SubmitLevelPatches("Level");
	SubmitMapPatches("Map");
	SubmitMiscPatches("Misc");
	SubmitNetworkingPatches("Networking");
	SubmitPhysicsPatches("Physics");
	SubmitPlayerProfilePatches("PlayerProfile");
	SubmitPlayersPatches("Players");
	SubmitPreferencesPatches("Preferences");
	SubmitPrintPatches("Print");
	SubmitRendererPatches("Renderer");
	SubmitSimulationPatches("Simulation");
	SubmitTagsPatches("Tags");
	SubmitUiPatches("Ui");
	SubmitUnitPatches("Unit");
}
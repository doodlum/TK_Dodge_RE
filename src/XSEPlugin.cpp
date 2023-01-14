#include "Hooks.h"
#include "InputEvents.h"
#include "TKRE.h"
#include "AnimationEvents.h"

void MessageHandler(SKSE::MessagingInterface::Message* a_msg)
{
	switch (a_msg->type) {
		// Skyrim lifecycle events.
	case SKSE::MessagingInterface::kPostLoad:      // Called after all plugins have finished running SKSEPlugin_Load.
												   // It is now safe to do multithreaded operations, or operations against other plugins.
	case SKSE::MessagingInterface::kPostPostLoad:  // Called after all kPostLoad message handlers have run.
	case SKSE::MessagingInterface::kInputLoaded:   // Called when all game data has been found.
		break;
	case SKSE::MessagingInterface::kDataLoaded:  // All ESM/ESL/ESP plugins have loaded, main menu is now active.
		// It is now safe to access form data.
		Settings::readSettings();
		InputEventHandler::Register();
		animEventHandler::RegisterForPlayer();
		Hooks::install();
		break;

		// Skyrim game events.
	case SKSE::MessagingInterface::kNewGame:       // Player starts a new game from main menu.
	case SKSE::MessagingInterface::kPreLoadGame:   // Player selected a game to load, but it hasn't loaded yet.
												   // Data will be the name of the loaded save.
	case SKSE::MessagingInterface::kPostLoadGame:  // Player's selected save game has finished loading.
												   // Data will be a boolean indicating whether the load was successful.
	case SKSE::MessagingInterface::kSaveGame:      // The player has saved a game.
												   // Data will be the save name.
	case SKSE::MessagingInterface::kDeleteGame:    // The player deleted a saved game from within the load menu.
		break;
	}
}

void Load()
{
	auto messaging = SKSE::GetMessagingInterface();
	messaging->RegisterListener("SKSE", MessageHandler);
}

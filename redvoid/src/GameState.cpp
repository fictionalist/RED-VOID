#include "GameState.hpp"

/* GameState namespace:
	* defines the RoundState struct, which holds game data information at a certain point in time, such as players' positioning, hit points and meter; and round and match data, such as round time remaining, and number of matches elapsed;
	* provides a way to save and load game states.
*/

#include <Windows.h>
#include <Definitions.hpp>

#include "Memory.hpp"
#include "Logger.hpp"

struct PlayerState {
	unsigned int HP;
	unsigned int Meter;
	struct _GRD {
		unsigned int Blocks;
		unsigned int IncompleteBlock;
	} GRD;
	struct _Position {
		unsigned int X;
		unsigned int Y;
	} Position;
};

struct RoundState {
	PlayerState P1;
	PlayerState P2;
	unsigned int TSTimer;
	unsigned int RoundTimer;
} *savedState = nullptr;

bool GameState::init() {
	return true;
}

bool GameState::save() {
	if (VALUE_OF(UNICLR_CURRENT_SCENE) != (unsigned long)GameScenes::InGame) {
		return false;
	}
	savedState = new RoundState;

	savedState->RoundTimer = VALUE_OF(UNICLR_INGAME_ROUND_TIMER);
	savedState->TSTimer = VALUE_OF(UNICLR_INGAME_TS_TIMER);

	savedState->P1.HP = VALUE_OF(UNICLR_INGAME_P1_HP);
	savedState->P1.Meter = VALUE_OF(UNICLR_INGAME_P1_METER);
	savedState->P1.GRD.Blocks = VALUE_OF(UNICLR_INGAME_P1_GRID_BLOCKS);
	savedState->P1.GRD.IncompleteBlock = VALUE_OF(UNICLR_INGAME_P1_GRID_INCOMPLETE_BLOCK_PROGRESS);
	savedState->P1.Position.X = VALUE_OF(UNICLR_INGAME_P1_X);
	savedState->P1.Position.Y = VALUE_OF(UNICLR_INGAME_P1_Y);

	savedState->P2.HP = VALUE_OF(UNICLR_INGAME_P2_HP);
	savedState->P2.Meter = VALUE_OF(UNICLR_INGAME_P2_METER);
	savedState->P2.GRD.Blocks = VALUE_OF(UNICLR_INGAME_P2_GRID_BLOCKS);
	savedState->P2.GRD.IncompleteBlock = VALUE_OF(UNICLR_INGAME_P2_GRID_INCOMPLETE_BLOCK_PROGRESS);
	savedState->P2.Position.X = VALUE_OF(UNICLR_INGAME_P2_X);
	savedState->P2.Position.Y = VALUE_OF(UNICLR_INGAME_P2_Y);

	Logger::log("Saved game state.");
	return true;
}

bool GameState::load() {
	if (VALUE_OF(UNICLR_CURRENT_SCENE) != (unsigned long)GameScenes::InGame) {
		return false;
	}
	if (savedState == nullptr) {
		return false;
	}

	VALUE_OF(UNICLR_INGAME_ROUND_TIMER) = savedState->RoundTimer;
	VALUE_OF(UNICLR_INGAME_TS_TIMER) = savedState->TSTimer;

	VALUE_OF(UNICLR_INGAME_P1_HP) = savedState->P1.HP;
	VALUE_OF(UNICLR_INGAME_P1_METER) = savedState->P1.Meter;
	VALUE_OF(UNICLR_INGAME_P1_GRID_BLOCKS) = savedState->P1.GRD.Blocks;
	VALUE_OF(UNICLR_INGAME_P1_GRID_INCOMPLETE_BLOCK_PROGRESS) = savedState->P1.GRD.IncompleteBlock;
	VALUE_OF(UNICLR_INGAME_P1_X) = savedState->P1.Position.X;
	VALUE_OF(UNICLR_INGAME_P1_Y) = savedState->P1.Position.Y;

	VALUE_OF(UNICLR_INGAME_P2_HP) = savedState->P2.HP;
	VALUE_OF(UNICLR_INGAME_P2_METER) = savedState->P2.Meter;
	VALUE_OF(UNICLR_INGAME_P2_GRID_BLOCKS) = savedState->P2.GRD.Blocks;
	VALUE_OF(UNICLR_INGAME_P2_GRID_INCOMPLETE_BLOCK_PROGRESS) = savedState->P2.GRD.IncompleteBlock;
	VALUE_OF(UNICLR_INGAME_P2_X) = savedState->P2.Position.X;
	VALUE_OF(UNICLR_INGAME_P2_Y) = savedState->P2.Position.Y;

	Logger::log("Loaded game state.");
	return true;
}
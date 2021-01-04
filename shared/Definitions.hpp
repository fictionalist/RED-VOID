#pragma once

/*	Definitions.hpp:
	* shared list of mostly macros used throughout the entire project.
	* defines macros for game memory addresses for easier management.
*/

#define RED_VOID_MAJOR_VERSION 0
#define RED_VOID_MINOR_VERSION 1

#define WINDOW_NAME "UNDER NIGHT IN-BIRTH Exe:Late[cl-r]"

#ifdef _DEBUG
#define DLLName "redvoid_d.dll"
#else
#define DLLName "redvoid.dll"
#endif

/* Global variables */

#define UNICLR_CURRENT_SCENE							( (unsigned long) 0x2EA1C0 )

// Important game scenes
enum class GameScenes {
	TitleScreen			= 3,	// Title screen
	MainMenu			= 5,	// CS main menu
	CharacterSelect		= 22,	// Character select screen
	ImmortalizeScreen	= 13,	// Screen showing both players' character choices
	PreInGame			= 15,	// Black screen that shows very briefly after picking retry
	InGame				= 1,	// Battle screen
	Results				= 12	// Results screen
};

#define UNICLR_P1_SIDE_PLAYER							( (unsigned long) 0x953CF4 )
#define UNICLR_P2_SIDE_PLAYER							( (unsigned long) 0x953CF8 )

/* Character Select variables */

#define UNICLR_CHARACTERSELECT_P1_CHARACTER				( (unsigned long) 0x44B360 )
#define UNICLR_CHARACTERSELECT_P1_COLOR					( (unsigned long) 0x44B360 )
#define UNICLR_CHARACTERSELECT_P2_CHARACTER				( (unsigned long) 0x44B39C )
#define UNICLR_CHARACTERSELECT_P2_COLOR					( (unsigned long) 0x44B3A0 )

/* In-game variables */

#define UNICLR_PAUSE_FLAG								( (unsigned long) 0x4AAC64 )
#define UNICLR_INGAME_ROUND_TIMER						( (unsigned long) 0x4AC570 )
#define UNICLR_INGAME_TS_TIMER							( (unsigned long) 0x4AB078 )
#define UNICLR_INGAME_

#define UNICLR_INGAME_P1_INGAME_CHARACTER				( (unsigned long) 0x436C78 )
#define UNICLR_INGAME_P1_CHARACTER_COLOR				( (unsigned long) 0x436C74 )
#define UNICLR_INGAME_P1_HP								( (unsigned long) 0x7D4A04 )
#define UNICLR_INGAME_P1_METER							( (unsigned long) 0x7D4A24 )
#define UNICLR_INGAME_P1_GRID_BLOCKS					( (unsigned long) 0x4AAEA8 )
#define UNICLR_INGAME_P1_GRID_INCOMPLETE_BLOCK_PROGRESS ( (unsigned long) 0x4AAEAC )
#define UNICLR_INGAME_P1_X								( (unsigned long) 0x7D49DC )
#define UNICLR_INGAME_P1_Y								( (unsigned long) 0x7D49E0 )

#define UNICLR_INGAME_P2_CHARACTER						( (unsigned long) 0x436C8C )
#define UNICLR_INGAME_P2_CHARACTER_COLOR				( (unsigned long) 0x436C88 )
#define UNICLR_INGAME_P2_HP								( (unsigned long) 0x7D53E4 )
#define UNICLR_INGAME_P2_METER							( (unsigned long) 0x7D5404 )
#define UNICLR_INGAME_P2_GRID_BLOCKS					( (unsigned long) 0x4AAFE8 )
#define UNICLR_INGAME_P2_GRID_INCOMPLETE_BLOCK_PROGRESS ( (unsigned long) 0x4AAFEC )
#define UNICLR_INGAME_P2_X								( (unsigned long) 0x7D53BC )
#define UNICLR_INGAME_P2_Y								( (unsigned long) 0x7D53C0 )

/* Game routines */

#define UNICLR_START_VERSUS								( (unsigned long) 0xED220 )

/* Routine patches */

//
#define UNICLR_MAINMENU_DECISION_NETWORK_DETOUR			( (unsigned long) 0x119C28 )
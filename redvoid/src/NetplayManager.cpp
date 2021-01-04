#include "NetplayManager.hpp"

/* NetplayManager namespace:
	* provides the framework for interacting between two game clients.
	* might be replaced by the GGPO framework.
*/

#include <Definitions.hpp>
#include "Logger.hpp"

// MAX_DELAY_FRAMES: maximum number of frames to delay inputs
#define MAX_DELAY_FRAMES ( 15 )

// MAX_ROLLBACK_FRAMES: maximum number of frames to rollback
#define MAX_ROLLBACK_FRAMES ( 15 )

unsigned int FrameDelay = 0;
unsigned int FrameRollback = 0;

bool NetplayManager::init(int delay, int rollback) {
	FrameDelay = delay;
	FrameRollback = rollback;
	return true;
}

void NetplayManager::onFrame() {

}
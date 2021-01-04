#pragma once

namespace NetplayManager {
	enum class NetplayState {
		Initialized,
		CharacterSelect,
		PlayerIntro,
		InGame,
		Results
	};

	bool init(int delay, int rollback);
	void onFrame();
}
#pragma once
#include "Common.h"

namespace Title {

	void Init();
	void Update();
	void Draw();
	void Terminate();
	bool IsScreenChangeOK();
	GameScreen CreateScreen();
}

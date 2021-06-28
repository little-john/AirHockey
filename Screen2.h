#pragma once
#include "Common.h"

namespace Screen2
{
	void Init();
	void Update();
	void Draw();
	void Terminate();
	bool IsScreenChangeOK();
	GameScreen CreateScreen();
}
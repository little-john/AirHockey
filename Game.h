#pragma once
#include "Common.h"

namespace Game 
{
	void Init();
	
	void Update();

	void Draw();

	// ‰æ–Ê‘JˆÚ‚³‚¹‚éˆ—
	// ˆø”‚É‚Í‘JˆÚ‚µ‚½‚¢‰æ–Ê‚ğ“n‚·
	void ChangeScreen(Screen screenName);

	// 1‚Â‘O‚Ì‰æ–Ê‚Ö–ß‚éˆ—
	bool BackToPreviousScreen();
	
	GlobalData* GetGlobalData();

	EnemyData* GetEnemyData(GameDifficulty difficulty);
}
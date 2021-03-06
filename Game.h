#pragma once
#include "Common.h"

namespace Game 
{
	void Init();
	
	void Update();

	void Draw();

	// 画面遷移させる処理
	// 引数には遷移したい画面を渡す
	void ChangeScreen(Screen screenName);

	// 1つ前の画面へ戻る処理
	bool BackToPreviousScreen();
	
	GlobalData* GetGlobalData();

	EnemyData* GetEnemyData(GameDifficulty difficulty);
}
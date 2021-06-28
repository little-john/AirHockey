#pragma once
#include "Common.h"

namespace Game 
{
	void Init();
	
	void Update();

	void Draw();

	// ��ʑJ�ڂ����鏈��
	// �����ɂ͑J�ڂ�������ʂ�n��
	void ChangeScreen(Screen screenName);

	// 1�O�̉�ʂ֖߂鏈��
	bool BackToPreviousScreen();
	
	GlobalData* GetGlobalData();

	EnemyData* GetEnemyData(GameDifficulty difficulty);
}
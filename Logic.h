#pragma once
#include "Common.h"
#include "Player.h"
#include "Game.h"

namespace Logic 
{
	// ゲームの終了判定させるための、各プレイヤーのスコアの差分
	// 差分がこの値より大きくなったらゲームを終了にする
	const int SCORE_DIFF_FOR_END = 5;

	// スコアーの差分を判定したいため、各プレイヤーを引数で引き受ける
	bool ValidateGameFinish(Player::Player& p1, Player::Player& p2);
}
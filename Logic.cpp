#include "Logic.h"

namespace Logic
{
	bool ValidateGameFinish(Player::Player& p1, Player::Player& p2) 
	{
		bool isGameEnd = false;

		if (Math::Abs(p1.score - p2.score) > SCORE_DIFF_FOR_END)
		{
			GlobalData* globalData = Game::GetGlobalData();

			if (p1.score > p2.score)
			{
				globalData->result = GameResult::WIN;
			}
			else
			{
				globalData->result = GameResult::LOSE;
			}

			isGameEnd = true;
		}

		return isGameEnd;
	}

}

// -> (アロー演算子)
// * => ポインター（実習）
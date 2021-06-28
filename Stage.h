#pragma once
#include "Common.h"
#include "Player.h"

// ゲームステージ
// 例えば、壁とゴールの位置を変えたり
// 動的にゴールの位置を動かしたりすることで
// ゲームの難易度を変更できたりします。

namespace Stage 
{
	// ステージ内のボールが当たるオブジェクトのタイプ
	enum HitObject {
		None,	// あたらない
		WallLR,	// 左右の壁
		WallUD,	// 上下の壁
		UpGoal,	// 上側のゴール
		DownGoal// 下側のゴール
	};

	// 壁のサイズ
	const int WALL_SIZE = 25;

	void Init();

	// スコアーを更新させるためプレイヤーへの参照を引数として引き受ける
	// p1 => 下のゴール用
	// p2 => 上のゴール用
	void Update(Player::Player& p1, Player::Player& p2);

	void Draw();

	void Terminate();

	// 引数でわたってきた円が壁やゴールとあたるか判定用処理
	HitObject GetHitObject(Circle ballCollision);

}

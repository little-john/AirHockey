#pragma once
#include "Common.h"
#include "Paddle.h"

namespace Player 
{
	// ユーザーなのかCPU（AI)なのかの定義
	enum Type {
		User,
		CPU
	};

	// プレイヤーの要素（持物）
	struct Player {
		Type playerType;
		Paddle::Paddle paddle;
		int score;
	};

	// プレイヤー構造体の作成
	Player CreatePlayer(Type t);

	void Init(Player& p);
	void Update(Player& p);
	void Draw(Player& p);
	void Terminate(Player& p);
}

// 実習:C言語値渡しと参照渡し
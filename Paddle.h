#pragma once
#include "Common.h"

namespace Paddle 
{
	// パドルの半径
	const int PADDLE_SIZE = 50;
	
	// パドルを動かす速度(1秒:60フレーム)
	const int PADDLE_SPEED = 500;

	// Paddleの構造体定義
	struct Paddle {
		Circle circle;
		Vec2 moveDirection;
	};

	void Init(Paddle& p);
	
	// tはプレイヤータイプ
	void Update(Paddle& p,int t);
	
	void Draw(Paddle& p);
	
	void Terminate(Paddle& p);
	
	// Paddle構造体の変数を作成
	Paddle CreatePaddle(Vec2 pos);
	
	// ボールとパドルが当たったか判定用
	bool IsHit(Paddle& p, Circle ballCollision);
}
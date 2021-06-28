#pragma once
#include "Common.h"

namespace Ball 
{
	// ボールの半径のサイズ
	const int BALL_SIZE = 10;
	
	// 1秒間(60フレーム)でボールを動かす速度
	const float BALL_SPEED = 600;

	// 引数のposを生成位置として初期化する
	void Init(Vec2 pos);

	void Update();

	void Draw();

	void Terminate();

	// X軸の移動の向きを反転
	void FlipVelocityDirectionX();
	
	// Y軸の移動の向きを反転
	void FlipVelocityDirectionY();
	
	// 移動する加速度の変更
	void ChangeVelocity(Vec2 v);

	// ボールの当たり判定(円)を返す
	Circle GetCollision();
	
	// ボールの加速度を返す
	Vec2 GetVelocity();
}

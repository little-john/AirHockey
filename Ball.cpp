#include "Ball.h"

namespace Ball 
{
	// ボールの円
	Circle ball;
	
	// 加速度
	Vec2 ballVelocity;

	void Init(Vec2 pos) {
		
		ball = Circle(pos, BALL_SIZE);

		// ランダムでボールの移動向きを決める
		// 三項演算子
		float startXDirection = (Random(-1.0f, 1.0f) <= 0.0f) ? -1 : 1;
		float startYDirection = (Random(-1.0f, 1.0f) <= 0.0f) ? -1 : 1;
		ballVelocity = Vec2(BALL_SPEED * startXDirection, BALL_SPEED * startYDirection);
	}

	void Update() 
	{
		ball.moveBy(ballVelocity * Scene::DeltaTime());
	}
	
	void Draw() 
	{
		ball.draw(Palette::Orange);
	}

	void Terminate() 
	{
	
	}
	
	void FlipVelocityDirectionX() 
	{
		/*playOneShot()が前回再生してから再生中であっても上書き再生する
		*play()は再生して再生が終わるまで待つので、重ねて呼んでもすぐは再生されない
		*SEはplayOneShot()で鳴らしてください。
		*/
		AudioAsset(U"HitSE").playOneShot();
		ballVelocity.x *= -1;
	}

	void FlipVelocityDirectionY() 
	{
		AudioAsset(U"HitSE").playOneShot();
		ballVelocity.y *= -1;
	}

	void ChangeVelocity(Vec2 v) 
	{
		AudioAsset(U"HitSE").playOneShot();
		ballVelocity = v;
	}
	
	Circle GetCollision() {
		return ball;
	}

	Vec2 GetVelocity() 
	{
		return ballVelocity;
	}
}
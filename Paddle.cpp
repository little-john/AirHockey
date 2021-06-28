#include "Paddle.h"
#include "Stage.h"
#include "Ball.h"
#include "Player.h"

namespace Paddle 
{
	Paddle CreatePaddle(Vec2 pos) 
	{
		Paddle p;
		p.circle = Circle(pos, PADDLE_SIZE);
		p.moveDirection = Vec2(0, 0);
		return p;
	}

	void Init(Paddle& p) 
	{
				
	}
	
	void Update(Paddle& p, int t)
	{
		// パドルを動かす
		p.circle.moveBy(p.moveDirection * PADDLE_SPEED * Scene::DeltaTime());

		// ステージの壁からでていかないように制御
		double radius = p.circle.lineDiameter().length() * 0.5f;

		if (p.circle.x - radius <= Stage::WALL_SIZE) {
			p.circle.x = Stage::WALL_SIZE + radius ;
		}

		if (p.circle.x + radius >= Scene::Width() - Stage::WALL_SIZE) {
			p.circle.x = Scene::Width() - (Stage::WALL_SIZE + radius );
		}

		if (p.circle.y - radius <= Stage::WALL_SIZE) {
			p.circle.y = Stage::WALL_SIZE + radius;
		}

		if (p.circle.y + radius >= Scene::Height() - Stage::WALL_SIZE) {
			p.circle.y = Scene::Height() - (Stage::WALL_SIZE + radius);
		}

		// ボールと当たったらボールを反転させる
		Vec2 ballVelocity = Ball::GetVelocity();
		if (t == Player::Type::User && ballVelocity.y > 0) 
		{
			// プレイヤーのゴールが下にあるため
			// ballVelocity.yが0以上（下にボールが動いてる場合のみ）
			// ボールが上に向かって移動中はこの処理が呼ばれません

			if (IsHit(p, Ball::GetCollision()))
			{
				double vx = (Ball::GetCollision().x - p.circle.x) * 10;
				double vy = -ballVelocity.y;
				ballVelocity = Vec2(vx, vy).setLength(Ball::BALL_SPEED);
				Ball::ChangeVelocity(ballVelocity);
			}		
		}
		else if (t == Player::Type::CPU && ballVelocity.y < 0)
		{
			// CPUのゴールが上にあるため
			// ballVelocity.yが0以下（上にボールが動いてる場合のみ）
			// ボールが下に向かって移動中はこの処理が呼ばれません

			if (IsHit(p, Ball::GetCollision()))
			{
				double vx = (Ball::GetCollision().x - p.circle.x) * 10;
				double vy = -ballVelocity.y;
				ballVelocity = Vec2(vx, vy).setLength(Ball::BALL_SPEED);
				Ball::ChangeVelocity(ballVelocity);
			}
		}
	}

	void Draw(Paddle& p) {
		p.circle.draw(Palette::Black);
		p.circle.drawFrame(5, Palette::White);
	}

	void Terminate(Paddle& p) 
	{
		
	}

	bool IsHit(Paddle& p, Circle ballCollision)
	{
		return (p.circle.intersects(ballCollision));
	}

}

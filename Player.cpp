#include "Player.h"
#include "Ball.h"
#include "Game.h"

namespace Player 
{
	Player CreatePlayer(Type t) 
	{
		// 構造体の変数宣言
		Player p;
		
		p.playerType = t;
		
		p.score = 0;

		// プレイヤータイプによってパドルの生成位置を変更
		if (t == CPU)
			p.paddle = Paddle::CreatePaddle(Scene::Center().moveBy(0, -200));
		else
			p.paddle = Paddle::CreatePaddle(Scene::Center().moveBy(0, 200));

		return p;
	}

	void Init(Player& p) 
	{
		Paddle::Init(p.paddle);
	}

	void Update(Player& p)
	{
		int dx = 0;
		int dy = 0;

		if (p.playerType == User) 
		{	
			if (KeyLeft.pressed() || KeyLeft.down()) {
				dx = -1;
			}
			else if (KeyRight.pressed() || KeyRight.down()) {
				dx = 1;
			}

			if (KeyUp.pressed() || KeyUp.down()) {
				dy = -1;
			}
			else if (KeyDown.pressed() || KeyDown.down()) {
				dy = 1;
			}
		}
		else // AIを搭載する時はここを変える
		{
			/*if (KeyA.pressed() || KeyA.down()) {
				dx = -1;
			}
			else if (KeyD.pressed() || KeyD.down()) {
				dx = 1;
			}

			if (KeyW.pressed() || KeyW.down()) {
				dy = -1;
			}
			else if (KeyS.pressed() || KeyS.down()) {
				dy = 1;
			}*/

			// ボールの座標
			Vec2 ballPos = Ball::GetCollision().center;

			// パドルの座標
			Vec2 paddlePos = p.paddle.circle.center;

			// x軸の距離
			double xDistance = ballPos.x - paddlePos.x;

			// y軸の距離
			double yDistance = ballPos.y - paddlePos.y;

			// 移動する向き
			int xDir = (xDistance > 0) ? 1 : -1;
			int yDir = (yDistance > 0) ? 1 : -1;

			EnemyData enemyData = *Game::GetEnemyData(Game::GetGlobalData()->difficulty);

			// 抽選して結果が〇〇の確率だったら動かす
			if ( Random(1,10) <= enemyData.MovePossibility )
			{
				dx = xDir;

				// パドルの位置（座標+半径）が画面の中央をこえなければ
				if ( paddlePos.y + Paddle::PADDLE_SIZE < Scene::Center().y )
				{
					// x軸の距離が min以上でmax以下だったら
					double absXDistance = Math::Abs(xDistance);
					if (absXDistance > enemyData.YMoveByXMin && absXDistance < enemyData.YMoveByXMax)
					{
						dy = yDir * Random(-1, 1);
					}
				}
				else // ずっと中央にいるので上に戻す
				{
					dy = -1;
				}
			}
		}

		p.paddle.moveDirection = Vec2(dx, dy);
		Paddle::Update(p.paddle, p.playerType);
	}
	
	void Draw(Player& p) 
	{
		Paddle::Draw(p.paddle);

		int scorePos = (p.playerType == CPU) ? -100 : 100;
		FontAsset(U"Score")(p.score).drawAt(Scene::Center().moveBy(0, scorePos));
	}
	
	void Terminate(Player& p) 
	{
		Paddle::Terminate(p.paddle);
	}
}
#include "Player.h"
#include "Ball.h"
#include "Game.h"

namespace Player 
{
	Player CreatePlayer(Type t) 
	{
		// �\���̂̕ϐ��錾
		Player p;
		
		p.playerType = t;
		
		p.score = 0;

		// �v���C���[�^�C�v�ɂ���ăp�h���̐����ʒu��ύX
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
		else // AI�𓋍ڂ��鎞�͂�����ς���
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

			// �{�[���̍��W
			Vec2 ballPos = Ball::GetCollision().center;

			// �p�h���̍��W
			Vec2 paddlePos = p.paddle.circle.center;

			// x���̋���
			double xDistance = ballPos.x - paddlePos.x;

			// y���̋���
			double yDistance = ballPos.y - paddlePos.y;

			// �ړ��������
			int xDir = (xDistance > 0) ? 1 : -1;
			int yDir = (yDistance > 0) ? 1 : -1;

			EnemyData enemyData = *Game::GetEnemyData(Game::GetGlobalData()->difficulty);

			// ���I���Č��ʂ��Z�Z�̊m���������瓮����
			if ( Random(1,10) <= enemyData.MovePossibility )
			{
				dx = xDir;

				// �p�h���̈ʒu�i���W+���a�j����ʂ̒����������Ȃ����
				if ( paddlePos.y + Paddle::PADDLE_SIZE < Scene::Center().y )
				{
					// x���̋����� min�ȏ��max�ȉ���������
					double absXDistance = Math::Abs(xDistance);
					if (absXDistance > enemyData.YMoveByXMin && absXDistance < enemyData.YMoveByXMax)
					{
						dy = yDir * Random(-1, 1);
					}
				}
				else // �����ƒ����ɂ���̂ŏ�ɖ߂�
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
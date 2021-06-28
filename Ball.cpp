#include "Ball.h"

namespace Ball 
{
	// �{�[���̉~
	Circle ball;
	
	// �����x
	Vec2 ballVelocity;

	void Init(Vec2 pos) {
		
		ball = Circle(pos, BALL_SIZE);

		// �����_���Ń{�[���̈ړ����������߂�
		// �O�����Z�q
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
		/*playOneShot()���O��Đ����Ă���Đ����ł����Ă��㏑���Đ�����
		*play()�͍Đ����čĐ����I���܂ő҂̂ŁA�d�˂ČĂ�ł������͍Đ�����Ȃ�
		*SE��playOneShot()�Ŗ炵�Ă��������B
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
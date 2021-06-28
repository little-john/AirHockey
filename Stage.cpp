#include "Stage.h"
#include "Ball.h"

namespace Stage
{
	/*
	* ���E�̕�
	*/
	Rect leftWall;
	Rect rightWall;
	
	/*
	* ����̕ǁA��̃S�[���A�E��̕�
	*/
	Rect upWallLeft;
	Rect upGoal;
	Rect upWallRight;
	
	/*
	* �����̕ǁA���̃S�[���A�E���̕�
	*/
	Rect downWallLeft;
	Rect downGoal;
	Rect downWallRight;

	void Init()
	{
		leftWall = Rect(0, 0, WALL_SIZE, Scene::Height());
		rightWall = Rect(Scene::Width() - WALL_SIZE, 0, WALL_SIZE, Scene::Height());

		float wallWidth = Scene::Width() * 0.35f;
		upWallLeft = Rect(0, 0, wallWidth, WALL_SIZE);
		upGoal = Rect(wallWidth, -(WALL_SIZE - 5), wallWidth, WALL_SIZE);
		upWallRight = Rect(wallWidth * 2, 0, wallWidth, WALL_SIZE);

		downWallLeft = Rect(0, Scene::Height() - WALL_SIZE, wallWidth, WALL_SIZE);
		downGoal = Rect(wallWidth, Scene::Height() - 5, wallWidth, WALL_SIZE);
		downWallRight = Rect(wallWidth * 2, Scene::Height() - WALL_SIZE, wallWidth, WALL_SIZE);
	}

	/*
	* �X�e�[�W����OBJ�Ƃ̓����炢���茋�ʂɂ��
	* �{�[���̔��]������A�v���C���[�̃X�R�A�[�X�V���s��
	*/
	void Update(Player::Player& p1, Player::Player& p2)
	{
		HitObject hitObject = GetHitObject(Ball::GetCollision());
		switch (hitObject)
		{
		case Stage::HitObject::WallLR:
			Ball::FlipVelocityDirectionX();
			break;
		case Stage::HitObject::WallUD:
			Ball::FlipVelocityDirectionY();
			break;
		case Stage::HitObject::UpGoal:
			// SE�̖炵�ƃX�R�A�[�X�V�ƃ{�[���̃��Z�b�g
			AudioAsset(U"GoalSE").playOneShot();
			p1.score += 1;
			Ball::Init(Scene::Center());
			break;
		case Stage::HitObject::DownGoal:
			// SE�̖炵�ƃX�R�A�[�X�V�ƃ{�[���̃��Z�b�g
			AudioAsset(U"GoalSE").playOneShot();
			p2.score += 1;
			Ball::Init(Scene::Center());
			break;
		}
	}

	HitObject GetHitObject(Circle ballCollision) 
	{
		HitObject result = None;
		if (leftWall.intersects(ballCollision) ||
			rightWall.intersects(ballCollision)){
			result = WallLR;
		}
		else if(
			upWallLeft.intersects(ballCollision) ||
			upWallRight.intersects(ballCollision) ||
			downWallLeft.intersects(ballCollision) ||
			downWallRight.intersects(ballCollision)) 
		{
			result = WallUD;
		}
		else if (upGoal.intersects(ballCollision)) {
			result = UpGoal;
		}
		else if (downGoal.intersects(ballCollision)) {
			result = DownGoal;
		}

		return result;
	}

	void Draw() 
	{
		leftWall.draw(Palette::Red);
		rightWall.draw(Palette::Red);

		upWallLeft.draw(Palette::Blue);
		upGoal.drawFrame();
		upWallRight.draw(Palette::Blue);

		downWallLeft.draw(Palette::Green);
		downGoal.drawFrame();
		downWallRight.draw(Palette::Green);
	}

	void Terminate() 
	{
		
	}
}
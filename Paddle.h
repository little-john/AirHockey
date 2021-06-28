#pragma once
#include "Common.h"

namespace Paddle 
{
	// �p�h���̔��a
	const int PADDLE_SIZE = 50;
	
	// �p�h���𓮂������x(1�b:60�t���[��)
	const int PADDLE_SPEED = 500;

	// Paddle�̍\���̒�`
	struct Paddle {
		Circle circle;
		Vec2 moveDirection;
	};

	void Init(Paddle& p);
	
	// t�̓v���C���[�^�C�v
	void Update(Paddle& p,int t);
	
	void Draw(Paddle& p);
	
	void Terminate(Paddle& p);
	
	// Paddle�\���̂̕ϐ����쐬
	Paddle CreatePaddle(Vec2 pos);
	
	// �{�[���ƃp�h������������������p
	bool IsHit(Paddle& p, Circle ballCollision);
}
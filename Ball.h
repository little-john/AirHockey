#pragma once
#include "Common.h"

namespace Ball 
{
	// �{�[���̔��a�̃T�C�Y
	const int BALL_SIZE = 10;
	
	// 1�b��(60�t���[��)�Ń{�[���𓮂������x
	const float BALL_SPEED = 600;

	// ������pos�𐶐��ʒu�Ƃ��ď���������
	void Init(Vec2 pos);

	void Update();

	void Draw();

	void Terminate();

	// X���̈ړ��̌����𔽓]
	void FlipVelocityDirectionX();
	
	// Y���̈ړ��̌����𔽓]
	void FlipVelocityDirectionY();
	
	// �ړ���������x�̕ύX
	void ChangeVelocity(Vec2 v);

	// �{�[���̓����蔻��(�~)��Ԃ�
	Circle GetCollision();
	
	// �{�[���̉����x��Ԃ�
	Vec2 GetVelocity();
}

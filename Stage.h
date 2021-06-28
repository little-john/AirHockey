#pragma once
#include "Common.h"
#include "Player.h"

// �Q�[���X�e�[�W
// �Ⴆ�΁A�ǂƃS�[���̈ʒu��ς�����
// ���I�ɃS�[���̈ʒu�𓮂������肷�邱�Ƃ�
// �Q�[���̓�Փx��ύX�ł����肵�܂��B

namespace Stage 
{
	// �X�e�[�W���̃{�[����������I�u�W�F�N�g�̃^�C�v
	enum HitObject {
		None,	// ������Ȃ�
		WallLR,	// ���E�̕�
		WallUD,	// �㉺�̕�
		UpGoal,	// �㑤�̃S�[��
		DownGoal// �����̃S�[��
	};

	// �ǂ̃T�C�Y
	const int WALL_SIZE = 25;

	void Init();

	// �X�R�A�[���X�V�����邽�߃v���C���[�ւ̎Q�Ƃ������Ƃ��Ĉ����󂯂�
	// p1 => ���̃S�[���p
	// p2 => ��̃S�[���p
	void Update(Player::Player& p1, Player::Player& p2);

	void Draw();

	void Terminate();

	// �����ł킽���Ă����~���ǂ�S�[���Ƃ����邩����p����
	HitObject GetHitObject(Circle ballCollision);

}

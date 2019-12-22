//MSG.hpp
//���b�Z�[�W�N���X

#pragma once

//################ �w�b�_�t�@�C���ǂݍ��� ##################
#include "DxLib.h"
#include "main.hpp"
#include "UI.hpp"
#include "PLAYER.hpp"
#include "ENEMY.hpp"

//################ �}�N����` ####################
#define MSG_DRAW_X 0		//���b�Z�[�W�̕`��ʒu(X)
#define MSG_DRAW_Y 400		//���b�Z�[�W�̕`��ʒu(Y)

//################ �N���X��` ####################
class MESSAGE
{
private:

	int X;		//X�`��ʒu
	int Y;		//Y�`��ʒu

public:

	MESSAGE();		//�R���X�g���N�^

	~MESSAGE();		//�f�X�g���N�^

	void DrawBattleMsg(int,int,int,PLAYER *,ENEMY *);		//�퓬��ʂł̃��b�Z�[�W�`��

	void DrawDamage(int,int);			//�_���[�W�`��

	void DrawName(const char *);		//���O�`��

};

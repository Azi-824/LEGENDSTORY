//MSG.cpp
//���b�Z�[�W�N���X

//################# �w�b�_�t�@�C���ǂݍ��� ######################
#include "MSG.hpp"

//################# �N���X��` ############################

//�R���X�g���N�^
MESSAGE::MESSAGE()
{
	this->X = MSG_DRAW_X;	//�`��ʒu(X)
	this->Y = MSG_DRAW_Y;	//�`��ʒu(Y)

	return;
}

//�f�X�g���N�^
MESSAGE::~MESSAGE()
{
	return;
}

//�퓬��ʂ̃��b�Z�[�W�`��
/*
�����Fint�F���݂̃o�g�����
�����Fint�F���݂̃^�[��
�����Fint�F�I�񂾃R�}���h
*/
void MESSAGE::DrawBattleMsg(int battlestage,int turn,int command,PLAYER *player,ENEMY *enemy)
{
	switch (battlestage)	//�o�g����Ԃɂ���ĕ\�����镶�����ς���
	{

	case (int)ACT_MSG:		//�s�����b�Z�[�W�\����Ԃ�������

		if (turn == (int)MY_TURN)	//�����̃^�[����������
		{
			if (command == (int)ESCAPE)	//�I�񂾃R�}���h�������邾������
			{
				DrawString(this->X, this->Y, "��肭�����؂ꂽ�I", GetColor(255, 255, 255));	//�����`��
			}
			else
			{
				this->DrawName(player->GetName());		//���O�`��
			}
		}
		else if (turn == (int)ENEMY_TURN)	//�G�̃^�[���̎�
		{
			this->DrawName(enemy->GetName());		//���O�`��
		}

		break;			//�s�����b�Z�[�W�\����Ԃ̏�����������

	case(int)DRAW_DAMEGE:			//�_���[�W�`���Ԃ�������

		if (turn == (int)MY_TURN)		//�����̃^�[����������
		{
			this->DrawDamage(turn,player->GetSendDamege());		//�^�����_���[�W�\��
		}
		else if (turn = (int)ENEMY_TURN)	//�G�̃^�[����������
		{
			this->DrawDamage(turn,player->GetRecvDamege());		//�󂯂����b�Z�[�W�\��
		}

		break;				//�_���[�W�`���Ԃ̏��������܂�

	default:
		break;
	}

	return;
}

//�_���[�W�`��
void MESSAGE::DrawDamage(int turn, int damege)
{
	if (turn == (int)MY_TURN)		//�����̃^�[���̎�
	{
		DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%d�̃_���[�W����������", damege);	//�_���[�W�e�L�X�g�`��
	}
	else if (turn == (int)ENEMY_TURN)	//�G�̃^�[���̎�
	{
		DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%d�̃_���[�W���󂯂�", damege);	//�_���[�W�e�L�X�g�`��
	}
	return;
}

//���O�`��
void MESSAGE::DrawName(const char *name)
{
	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%s�̂��������I", name);	//�G�̖��O�`��
}

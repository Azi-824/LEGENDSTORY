//MSG.cpp
//���b�Z�[�W�N���X

//################# �w�b�_�t�@�C���ǂݍ��� ######################
#include "MSG.hpp"

//################# �N���X��` ############################

//�R���X�g���N�^
MESSAGE::MESSAGE()
{
	//����������
	this->X = BT_MSG_DRAW_X;	//�`��ʒu(X)
	this->Y = BT_MSG_DRAW_Y;	//�`��ʒu(Y)
	this->IsResultMsgEnd = false;	//���U���g���b�Z�[�W�\���I�����Ă��Ȃ�
	this->ResultMsgStep = (int)WIN_MSG;	//�\���i�K�͍ŏ�
	this->IsDrawMsg = false;		//���b�Z�[�W�`�撆�ł͂Ȃ�

	return;
}

//�f�X�g���N�^
MESSAGE::~MESSAGE()
{

	std::vector<std::string> v;			//���vector���쐬����
	this->Msg.swap(v);					//��ƒ��g�����ւ���

	return;
}

//�퓬��ʂ̃��b�Z�[�W�`��
/*
�����Fint�F���݂̃o�g�����
�����Fint�F���݂̃^�[��
�����Fint�F�I�񂾃R�}���h
*/
void MESSAGE::DrawBattleMsg(int battlestage,int turn,int command,PLAYER *player,ENEMY *enemy,bool push_enter)
{
	switch (battlestage)	//�o�g����Ԃɂ���ĕ\�����镶�����ς���
	{

	case (int)ACT_MSG:		//�s�����b�Z�[�W�\����Ԃ�������

		if (turn == (int)MY_TURN)	//�����̃^�[����������
		{
			if (command == (int)COMMANDE_ESCAPE)	//�I�񂾃R�}���h�������邾������
			{
				DrawString(this->X, this->Y, "��肭�����؂ꂽ�I", GetColor(255, 255, 255));	//�����`��
			}
			else if (command == (int)COMMANDE_DEFENSE)	//�h���I�񂾎���
			{
				DrawString(this->X, this->Y, "�h�䂵�Ă���I", GetColor(255, 255, 255));		//�����`��
			}
			else								//����ȊO�̎���
			{
				this->DrawName(player->GetName());		//���O�`��
			}
		}
		else if (turn == (int)ENEMY_TURN)	//�G�̃^�[���̎�
		{
			this->DrawName(enemy->GetName());		//���O�`��
		}

		this->IsDrawMsg = true;	//���b�Z�[�W�`�撆

		break;			//�s�����b�Z�[�W�\����Ԃ̏�����������

	case(int)DRAW_DAMEGE:			//�_���[�W�`���Ԃ�������

		if (turn == (int)MY_TURN)		//�����̃^�[����������
		{
			if (command == (int)COMMANDE_DEFENSE)	//�h���I�񂾎���
			{
				DrawString(this->X, this->Y, "�h�䂵�Ă���I",GetColor(255, 255, 255));		//�����`��
			}
			else						//����ȊO�̎���
			{
				this->DrawDamage(turn, player->GetSendDamege());		//�^�����_���[�W�\��
			}
		}
		else if (turn == (int)ENEMY_TURN)	//�G�̃^�[����������
		{
			this->DrawDamage(turn,player->GetRecvDamege());		//�󂯂��_���[�W�\��
		}

		this->IsDrawMsg = true;	//���b�Z�[�W�`�撆

		break;				//�_���[�W�`���Ԃ̏��������܂�

	case(int)RESULT_MSG:			//���U���g���b�Z�[�W�\����Ԃ�������

		if (player->GetIsBattleWin())			//�퓬�ɏ������Ă�����
		{
			switch (this->ResultMsgStep)		//���U���g���b�Z�[�W�̕\���i�K�ɍ��킹�ĕ\�����镶����ς���
			{

			case (int)WIN_MSG:		//�퓬�ɏ����������b�Z�[�W

				DrawString(this->X, this->Y, "�����X�^�[����������I", GetColor(255, 255, 255));	//�����`��

				break;

			case (int)EXP_MSG:		//�o���l�̃��b�Z�[�W

				DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%d�̌o���l���Q�b�g�����I", enemy->GetEXP());	//�擾�o���l�̕\��

				break;

			case(int)LEVELUP_MSG:	//���x���A�b�v�̃��b�Z�[�W

				DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "���x�����オ�����I\n���x��%d�ɂȂ����I", player->GetLevel());

				break;

			default:
				break;
			}
			if (push_enter)		//�G���^�[�L�[�������ꂽ��
			{
				if (player->GetLevUpMsgStartFlg())	//���x���A�b�v�����Ƃ���
				{
					if (this->ResultMsgStep < (int)LEVELUP_MSG)	//���x���A�b�v���b�Z�[�W�܂�
					{
						this->ResultMsgStep++;	//���U���g���b�Z�[�W�̕\���i�K������
					}
					else										//����ȊO�Ȃ�
					{
						this->IsResultMsgEnd = true;			//���b�Z�[�W�\���I��
						player->SetLevUpMsgStartFlg(false);		//���x���A�b�v���b�Z�[�W�I��
					}
				}
				else			//���x���A�b�v���ĂȂ��Ƃ���
				{
					if (this->ResultMsgStep < (int)EXP_MSG)	//�o���l���b�Z�[�W�܂�
					{
						this->ResultMsgStep++;	//���U���g���b�Z�[�W�̕\���i�K������
					}
					else										//����ȊO�Ȃ�
					{
						this->IsResultMsgEnd = true;			//���b�Z�[�W�\���I��
					}
				}
			}
		}
		else if (player->GetIsBattleWin() == false)	//�퓬�ɔs�k���Ă�����
		{
			DrawString(this->X, this->Y, "�S�ł��Ă��܂����E�E�E", GetColor(255, 255, 255));	//�����`��
			if (push_enter)	//�G���^�[�L�[�������ꂽ��
			{
				this->IsResultMsgEnd = true;			//���b�Z�[�W�\���I��
			}
		}

		this->IsDrawMsg = true;	//���b�Z�[�W�`�撆

		break;

	default:

		this->IsDrawMsg = false;	//���b�Z�[�W�`�撆�ł͂Ȃ�

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

//���U���g���b�Z�[�W�̕\�����I���������ݒ�
void MESSAGE::SetIsResultMsgEnd(bool isend)
{
	this->IsResultMsgEnd = isend;
	return;
}

//���U���g���b�Z�[�W�֌W�̃����o�[�����Z�b�g
void MESSAGE::ResetResultMsg(void)
{
	this->IsResultMsgEnd = false;	//���U���g���b�Z�[�W�\���I�����Ă��Ȃ�
	this->ResultMsgStep = (int)WIN_MSG;	//�\���i�K�͍ŏ�

	return;
}

//���b�Z�[�W�`�撆���ݒ�
void MESSAGE::SetIsDrawMsg(bool isdrawmsg)
{
	this->IsDrawMsg = isdrawmsg;
	return;
}


//���U���g���b�Z�[�W�̕\�����I���������擾
bool MESSAGE::GetIsResultMsgEnd(void)
{
	return this->IsResultMsgEnd;
}

//�ǂ̃��b�Z�[�W��`�悵�Ă����Ԃ��擾
int MESSAGE::GetDrawMsgKind(void)
{
	return this->ResultMsgStep;
}

//���b�Z�[�W�`�撆���擾
bool MESSAGE::GetIsDrawMsg(void)
{
	return this->IsDrawMsg;
}

//�������ݒ�
void MESSAGE::SetMsg(const char *msg)
{
	this->Msg.push_back(msg);		//�󂯎�����������ǉ�
	this->Msg_itr = this->Msg.begin();	//�擪�v�f�̃A�h���X���擾
	return;
}

//���̃��b�Z�[�W�ֈړ�����
void MESSAGE::NextMsg(void)
{
	if (*this->Msg_itr != this->Msg.back())			//�Ō�̃��b�Z�[�W�łȂ����
	{
		++this->Msg_itr;	//���̃��b�Z�[�W��
	}
	return;
}

//�O�̃��b�Z�[�W�ֈړ�����
void MESSAGE::BackMsg(void)
{
	if (*this->Msg_itr != this->Msg.front())		//�ŏ��̃��b�Z�[�W����Ȃ����
	{
		--this->Msg_itr;	//�O�̃��b�Z�[�W��
	}
}

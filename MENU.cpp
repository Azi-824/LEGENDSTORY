//MENU.cpp
//���j���[�E�B���h�E�p�̃N���X

//############ �w�b�_�t�@�C���ǂݍ��� ##################
#include "MENU.hpp"

//########### �N���X��` ###################

//�R���X�g���N�^
MENU::MENU()
{
	this->X = 0;		
	this->Y = 0;		

	this->Width = 0;	
	this->Height = 0;	

	this->StrHeight = GetFontSize();	//�������擾

	this->IsChoise = false;		//�I������Ă��Ȃ�

	return;

}

//�f�X�g���N�^
MENU::~MENU()
{
	return;
}


//�I�񂾓��e���Ƃ̕`��
void MENU::DrawChoise(int choise,PLAYER *player,ITEM *item[])
{

	switch (choise)			//�I�񂾓��e���Ƃɏ����𕪂���
	{

	case (int)MENU_STATUS:	//�X�e�[�^�X��I�񂾎��̏�����������

		//�X�e�[�^�X�`�揈��
		//DrawString(400, 300, "�X�e�[�^�X�`��", GetColor(255, 255, 255));	//�����`��

		//�X�e�[�^�X�`��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%s\nHP %d/%d\nMP %d/%d\nATK %d\nDEF %d\nSPD %d",
			player->GetName(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetATK(), player->GetDEF(), player->GetSPD());

		break;				//�X�e�[�^�X��I�񂾎��̏��������܂�

	case (int)MENU_ITEM:	//�A�C�e����I�񂾎��̏�����������

		//�A�C�e���`�揈��
		//DrawString(400, 300, "�A�C�e���`��", GetColor(255, 255, 255));	//�����`��

		for (int cnt = 0; cnt < ITEM_KIND; ++cnt)
		{
			DrawFormatString(0, cnt * MENU_SPACE, GetColor(255, 255, 255), "%s %s\n", item[cnt]->GetName(), item[cnt]->GetDescription());
		}

		break;				//�A�C�e����I�񂾂Ƃ��̏��������܂�

	case (int)MENU_SOUBI:	//������I�񂾎��̏�����������

		//�����`�揈��
		DrawString(400, 300, "�����`��", GetColor(255, 255, 255));	//�����`��

		break;				//������I�񂾎��̏��������܂�

	case (int)MENU_SAVE:	//�Z�[�u��I�񂾎��̏�����������

		//�Z�[�u���̕`�揈��
		DrawString(400, 300, "�Z�[�u���ł��B", GetColor(255, 255, 255));	//�����`��

		break;				//�Z�[�u��I�񂾎��̏��������܂�

	default:
		break;
	}

	return;
}

//�I��v�f�����Z�b�g
void MENU::Reset()
{
	//this->Menu_itr = this->Menu.begin();
	this->IsChoise = false;
	return;
}
//�I������Ă��邩�ݒ�
void MENU::SetIsChoise(bool Ischoise)
{
	this->IsChoise = Ischoise;
	return;
}

//�I������Ă��邩�擾
bool MENU::GetIsChoise(void)
{
	return this->IsChoise;
}

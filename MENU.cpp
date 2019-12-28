//MENU.cpp
//���j���[�E�B���h�E�p�̃N���X

//############ �w�b�_�t�@�C���ǂݍ��� ##################
#include "MENU.hpp"

//########### �N���X��` ###################

//�R���X�g���N�^
MENU::MENU()
{
	this->Menu = { "�X�e�[�^�X","�A�C�e��","����","�Z�[�u" };	//���j���[�E�B���h�E�̕������ݒ�
	this->Menu_itr = this->Menu.begin();	//�擪�̃A�h���X������

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
	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->Menu.swap(v);					//��ƒ��g�����ւ���

	return;

}

//�`��
void MENU::Draw(int x,int y)
{

	//�`��ʒu�ݒ�
	this->X = x;
	this->Y = y;

	int cnt = 0;	//�`��ʒu�p
	
	auto w_itr = this->Menu_itr;	//�ޔ�p

	for (this->Menu_itr=this->Menu.begin();this->Menu_itr!=this->Menu.end();++this->Menu_itr)
	{
		if (w_itr == this->Menu_itr)			//�I�𒆂̗v�f��������
		{
			DrawFormatString(this->X + 10, this->Y + cnt * MENU_SPACE, GetColor(255, 255, 255), "%s\n", this->Menu_itr->c_str());	//�E�ɂ��炵�ĕ`��
		}
		else
		{
			DrawFormatString(this->X, this->Y + cnt * MENU_SPACE, GetColor(255, 255, 255), "%s\n", this->Menu_itr->c_str());	//�����`��
		}
		cnt++;
	}

	this->Menu_itr = w_itr;		//�I��v�f�����ɖ߂�

	return;

}

//�I�񂾓��e���Ƃ̕`��
void MENU::DrawChoise(int choise,PLAYER *player)
{

	switch (choise)			//�I�񂾓��e���Ƃɏ����𕪂���
	{

	case (int)MENU_STATUS:	//�X�e�[�^�X��I�񂾎��̏�����������

		//�X�e�[�^�X�`�揈��
		DrawString(400, 300, "�X�e�[�^�X�`��", GetColor(255, 255, 255));	//�����`��

		DrawFormatString(0, 50, GetColor(255, 255, 255), "%s\nHP %d/%d\nMP %d/%d\nATK %d\nDEF %d\nSPD %d",
			player->GetName(), player->GetHP(), player->GetMaxHP(), player->GetMP(), player->GetMaxMP(), player->GetATK(), player->GetDEF(), player->GetSPD());

		break;				//�X�e�[�^�X��I�񂾎��̏��������܂�

	case (int)MENU_ITEM:	//�A�C�e����I�񂾎��̏�����������

		//�A�C�e���`�揈��
		DrawString(400, 300, "�A�C�e���`��", GetColor(255, 255, 255));	//�����`��

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

//�I��v�f�����ֈړ�
void MENU::Next()
{
	if (this->Menu_itr != this->Menu.end() - 1)	//�Ō�̗v�f�Ŗ������
	{
		this->Menu_itr++;	//���̗v�f��
	}
	return;
}

//�I��v�f��O�ֈړ�
void MENU::Back()
{
	if (this->Menu_itr != this->Menu.begin())	//�ŏ��̗v�f�łȂ����
	{
		this->Menu_itr--;	//�O�̗v�f��
	}
	return;
}

//�I��v�f�����Z�b�g
void MENU::Reset()
{
	this->Menu_itr = this->Menu.begin();
	this->IsChoise = false;
	return;
}

//�I���������ڂ��擾
std::vector<std::string>::iterator MENU::GetChoiseMenu()
{
	return this->Menu_itr;
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

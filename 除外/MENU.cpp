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

//�I��v�f�����Z�b�g
void MENU::Reset()
{
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

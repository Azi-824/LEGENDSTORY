//BATTLE.cpp
//�o�g���̗�����Ǘ�����N���X

//#################### �w�b�_�t�@�C���ǂݍ��� ########################
#include "BATTLE.hpp"

//#################### �N���X��` #########################

//�R���X�g���N�^
BATTLE::BATTLE()
{
	this->IsActMsg = false;		//�s�����b�Z�[�W��\��
	this->IsDamegeCalc = false;	//�_���[�W�v�Z������Ȃ�
	return;
}

//�f�X�g���N�^
BATTLE::~BATTLE()
{
	return;
}

//�s�����b�Z�[�W�\�������擾
bool BATTLE::GetIsActMsg()
{
	return this->IsActMsg;
}

//�_���[�W�v�Z�����擾
bool BATTLE::GetIsDamegeCalc()
{
	return this->IsDamegeCalc;
}

//�s�����b�Z�[�W�\�������ݒ�
void BATTLE::SetIsActMsg(bool Isactmsg)
{
	this->IsActMsg = Isactmsg;
	return;
}

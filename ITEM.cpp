//ITEM.cpp
//�A�C�e���N���X

//##################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "ITEM.hpp"

//##################### �N���X��` ###########################

//�R���X�g���N�^
ITEM::ITEM()
{
	return;
}

//�f�X�g���N�^
ITEM::~ITEM()
{
	return;
}

//���O�ݒ�
void ITEM::SetName(const char *name)
{
	this->Name = name;
	return;
}

//�������ݒ�
void ITEM::SetDescription(const char *desc)
{
	this->Description = desc;
	return;
}

//���O�擾
const char * ITEM::GetName(void)
{
	return this->Name.c_str();
}

//�������擾
const char * ITEM::GetDescription(void)
{
	return this->Description.c_str();
}

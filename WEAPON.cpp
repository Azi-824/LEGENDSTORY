//WEAPON.cpp
//����N���X

//################## �w�b�_�t�@�C���ǂݍ��� ####################
#include "WEAPON.hpp"

//################## �N���X��` ########################

//�R���X�g���N�^
WEAPON::WEAPON()
{
	return;
}

//�f�X�g���N�^
WEAPON::~WEAPON()
{
	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Atk.swap(v);			//��ƒ��g�����ւ���

	return;
}

//�U���͂�ݒ�
void WEAPON::SetAtk(int atk)
{
	this->Atk.push_back(atk);	//�U���͒ǉ�
	return;
}

//�U���͎擾
int WEAPON::GetAtk(int kind)
{
	return this->Atk[kind];		//�U���͎擾
}

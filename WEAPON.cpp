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
//�����Fint�F����R�[�h
int WEAPON::GetAtk(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Atk[i];		//�U���͎擾
		}
	}

}

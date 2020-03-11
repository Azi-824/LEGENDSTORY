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

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Code.swap(v);			//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<int> v2;		//���vector���쐬����
	this->Possession.swap(v2);	//��ƒ��g�����ւ���


	//vector�̃�����������s��
	std::vector<int> v3;			//���vector���쐬����
	this->Recovery.swap(v3);		//��ƒ��g�����ւ���

	return;
}

//�A�C�e���R�[�h�ݒ�
void ITEM::SetCode(int code)
{
	this->Code.push_back(code);
	this->Possession.push_back(1);	//�������������l�Őݒ�
	return;
}

//����������
void ITEM::IncreasePossession(int kind)
{
	this->Possession[kind]++;
	return;
}

//����������
void ITEM::DecreasePossession(int kind)
{
	this->Possession[kind]--;
	return;
}

//�񕜗ʐݒ�
void ITEM::SetRecovery(int recovery)
{
	this->Recovery.push_back(recovery);
	return;
}

//�ǉ��������ݒ�
void ITEM::SetAddFlg(bool add_flg)
{
	this->Add_flg = add_flg;
	return;
}

//�A�C�e���R�[�h�擾
int ITEM::GetCode(int kind)
{
	return this->Code[kind];
}

//�������擾
int ITEM::GetPossession(int code)
{
	return this->Possession[code];
}

//�񕜗ʎ擾
int ITEM::GetRecovery(int code)
{
	return this->Recovery[code];
}

//�v�f�����擾
int ITEM::GetSize(void)
{
	return this->Code.size();
}

//�ǉ��������擾
bool ITEM::GetAddFlg(void)
{
	return this->Add_flg;
}

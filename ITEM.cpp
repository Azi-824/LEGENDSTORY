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

	//vector�̃�����������s��
	std::vector<bool> v4;			//���vector���쐬����
	this->IsDraw.swap(v4);			//��ƒ��g�����ւ���

	return;
}

//�A�C�e���R�[�h�ݒ�
void ITEM::SetCode(int code)
{
	
	this->Code.push_back(code);
	this->Possession.push_back(1);	//�������������l�Őݒ�
	this->IsDraw.push_back(true);	//�`�悵�Ă悢���ݒ�i�`�悵�Ă悢�j
	return;
}

//����������
void ITEM::IncreasePossession(int kind)
{
	this->Possession[kind]++;	//�������𑝂₷
	this->Chenge_flg = true;	//�ύX����
	return;
}

//����������
void ITEM::DecreasePossession(int kind)
{
	this->Possession[kind]--;			//�����������炷
	if (this->Possession[kind] <= 0)	//��������0�ȉ��ɂȂ�����
	{
		this->IsDraw[kind] = false;		//�`�悵�Ă͂����Ȃ�
		this->Possession[kind] = 0;		//0��菭�Ȃ����Ȃ�
	}

	this->Chenge_flg = true;			//�ύX����
	return;
}

//�񕜗ʐݒ�
void ITEM::SetRecovery(int recovery)
{
	this->Recovery.push_back(recovery);
	return;
}

//�ǉ��������ݒ�
void ITEM::SetChengeFlg(bool add_flg)
{
	this->Chenge_flg = add_flg;
	return;
}

//�`�悵�Ă悢���ݒ�
//void ITEM::SetIsDraw(int kind, bool Isdraw)
//{
//	this->IsDraw[kind] = Isdraw;
//	return;
//}

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
bool ITEM::GetChengeFlg(void)
{
	return this->Chenge_flg;
}

//�������擾
std::vector<int> ITEM::GetPossession(void)
{
	return this->Possession;
}

//�`�悵�Ă悢���擾
bool ITEM::GetIsDraw(int kind)
{
	return this->IsDraw[kind];
}

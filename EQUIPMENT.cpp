//EQUIPMENT.cpp
//�����֌W�̃N���X�̌��ɂȂ�N���X

//####################### �w�b�_�t�@�C���ǂݍ��� #########################
#include "EQUIPMENT.hpp"

//####################### �N���X��` ##########################

//�R���X�g���N�^
EQUIPMENT::EQUIPMENT()
{
	return;
}

//�f�X�g���N�^
EQUIPMENT::~EQUIPMENT()
{
	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->CodeNum.swap(v);		//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<int> v2;			//���vector���쐬����
	this->PossessionNum.swap(v2);	//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<bool> v3;			//���vector���쐬����
	this->EquipFlg.swap(v3);		//��ƒ��g�����ւ���

	return;

}

//�����������ݒ�
void EQUIPMENT::SetPossessionNum(int kind, int possesionnum)
{
	this->PossessionNum[kind] = possesionnum;	//�������ݒ�
	return;
}

//�����t���O�ݒ�
void EQUIPMENT::SetEquipFlg(int kind, bool equipflg)
{
	this->EquipFlg[kind] = equipflg;	//�����t���O�ݒ�
	return;
}

//�v�f���ݒ�
void EQUIPMENT::SetSize()
{
	this->Size = this->CodeNum.size();	//�T�C�Y�ݒ�
	return;
}

//�����ǉ��������ݒ�
void EQUIPMENT::SetAddFlg(bool addflg)
{
	this->AddFlg = addflg;
	return;
}

//�R�[�h�ԍ��擾
int EQUIPMENT::GetCodeNum(int kind)
{
	return this->CodeNum[kind];
}

//�����������擾
int EQUIPMENT::GetPossessionNum(int kind)
{
	return this->PossessionNum[kind];
}

//�����t���O�擾
bool EQUIPMENT::GetEquipFlg(int kind)
{
	return this->EquipFlg[kind];
}

//�v�f���擾
int EQUIPMENT::GetSize()
{
	return this->Size;
}

//������ǉ��������ǂ����擾
bool EQUIPMENT::GetAddFlg(void)
{
	return this->AddFlg;
}

//�����ǉ�
void EQUIPMENT::Add(int codenum)
{
	this->CodeNum.push_back(codenum);		//�R�[�h�ԍ��ǉ�

	//�v�f0�ɃR�[�h�ԍ�0�����邽�߂�+1���Ă���
	if (this->PossessionNum.size() < codenum + 1)	//�R�[�h�ԍ����v�f����菭�Ȃ��ꍇ
	{
		this->PossessionNum.resize(codenum + 1);	//�v�f�T�C�Y��ύX
		this->EquipFlg.resize(codenum + 1);			//�v�f�T�C�Y��ύX
	}

	//�v�f���ɃR�[�h�ԍ����w�肵�ēo�^
	this->PossessionNum[codenum] = 1;		//������������ǉ�
	this->EquipFlg[codenum] = false;		//�ǉ����������̑�����Ԃ�ݒ�

	this->Size = this->CodeNum.size();		//�T�C�Y�ݒ�

	this->AddFlg = true;					//�����ǉ��t���O
	
	return;
}

//������������������
void EQUIPMENT::AddPossession(int kind)
{
	this->PossessionNum[kind]++;	//����
	return;
}

//EQUIPMENT.cpp
//�����֌W�̃N���X�̌��ɂȂ�N���X

//####################### �w�b�_�t�@�C���ǂݍ��� #########################
#include "EQUIPMENT.h"

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

//�����ǉ�
void EQUIPMENT::Add(int codenum)
{
	this->CodeNum.push_back(codenum);		//�R�[�h�ԍ��ǉ�
	this->PossessionNum.push_back(1);		//������������ǉ�
	this->EquipFlg.push_back(false);		//�ǉ����������̑�����Ԃ�ݒ�
	
	return;
}

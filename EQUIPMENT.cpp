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
	
	//vector�̃�����������s��
	std::vector<bool> v4;			//���vector���쐬����
	this->IsDraw.swap(v4);			//��ƒ��g�����ւ���


	return;

}

//�����������ݒ�
//void EQUIPMENT::SetPossessionNum(int kind, int possesionnum)
//{
//	this->PossessionNum[kind] = possesionnum;	//�������ݒ�
//	return;
//}

//����������
void EQUIPMENT::IncreasePossession(int kind)
{
	this->PossessionNum[kind]++;
	return;
}

//����������
void EQUIPMENT::DecreasePossession(int kind)
{
	this->PossessionNum[kind]--;
	if (this->PossessionNum[kind] <= 0)	//��������0�ȉ��ɂȂ�����
	{
		this->IsDraw[kind] = false;		//�`�悵�Ă͂����Ȃ�
	}
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

//������ύX�������ݒ�
void EQUIPMENT::SetChengeFlg(bool addflg)
{
	this->Chenge_flg = addflg;
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

//�����������擾
std::vector<int> EQUIPMENT::GetPossessionNum(void)
{
	return this->PossessionNum;	
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
bool EQUIPMENT::GetChengeFlg(void)
{
	return this->Chenge_flg;
}

//�����ǉ�
void EQUIPMENT::Add(int codenum)
{
	//�w�肳�ꂽ�R�[�h�����ɓo�^����Ă��邩����
	for (int i = 0; i < this->CodeNum.size(); ++i)	//�R�[�h�ԍ��̐����J��Ԃ�
	{
		if (this->CodeNum[i] == codenum)	//�ǉ����ꂽ�R�[�h�����łɓo�^����Ă���ꍇ
		{
			this->PossessionNum[i]++;		//�������𑝉�
			this->IsDraw[i] = true;			//�`�悵�Ă悢
			this->Chenge_flg = true;		//�����ύX�t���O
			return;							//�ǉ������I��
		}
	}

	//�R�[�h���o�^����Ă��Ȃ������ꍇ
	this->CodeNum.push_back(codenum);	//�R�[�h�ԍ��ǉ�
	this->PossessionNum.push_back(1);	//��������ǉ��i�ŏ���1�j
	this->EquipFlg.push_back(false);	//������Ԑݒ�i�ŏ��͑������Ă��Ȃ���ԁj
	this->Size = this->CodeNum.size();	//�v�f���ݒ�
	this->IsDraw.push_back(true);		//�`�悵�Ă悢
	this->Chenge_flg = true;			//�����ύX�t���O

	return;
}

//������������������
//void EQUIPMENT::AddPossession(int kind)
//{
//	this->PossessionNum[kind]++;	//����
//	return;
//}

//�`�悵�Ă悢���擾
bool EQUIPMENT::GetIsDraw(int kind)
{
	return this->IsDraw[kind];
}

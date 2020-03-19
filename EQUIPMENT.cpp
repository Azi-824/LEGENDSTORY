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
	this->Code.swap(v);		//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<int> v2;			//���vector���쐬����
	this->Possession.swap(v2);	//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<bool> v3;			//���vector���쐬����
	this->EquipFlg.swap(v3);		//��ƒ��g�����ւ���
	
	//vector�̃�����������s��
	std::vector<bool> v4;			//���vector���쐬����
	this->IsDraw.swap(v4);			//��ƒ��g�����ւ���


	return;

}

//����������
void EQUIPMENT::IncreasePossession(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			this->Possession[i]++;
			this->Chenge_flg = true;	//�ύX����
		}
	}


	return;
}

//����������
void EQUIPMENT::DecreasePossession(int code)
{
	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			this->Possession[i]--;

			if (this->Possession[i] <= 0)	//��������0�ȉ��ɂȂ�����
			{
				this->IsDraw[i] = false;	//�`�悵�Ă͂����Ȃ�
			}

			this->Chenge_flg = true;		//�ύX����

		}
	}


	return;
}

//�����t���O�ݒ�
void EQUIPMENT::SetEquipFlg(int code, bool equipflg)
{

	for (int i = 0; i < this->EquipFlg.size(); ++i)	//���������J��Ԃ�
	{
		this->EquipFlg[i] = false; //������Ԃ����ׂă��Z�b�g
	}

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			this->EquipFlg[i] = equipflg;	//�����t���O�ݒ�
		}
	}

	return;
}

//�v�f���ݒ�
void EQUIPMENT::SetSize()
{
	this->Size = this->Code.size();	//�T�C�Y�ݒ�
	return;
}

//������ύX�������ݒ�
void EQUIPMENT::SetChengeFlg(bool addflg)
{
	this->Chenge_flg = addflg;
	return;
}

//�R�[�h�ԍ��擾
int EQUIPMENT::GetCode(int kind)
{
	return this->Code[kind];
}

//�����������擾
int EQUIPMENT::GetPossession(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Possession[i];
		}
	}


}

//�����������擾
std::vector<int> EQUIPMENT::GetPossession(void)
{
	return this->Possession;	
}

//�����t���O�擾
bool EQUIPMENT::GetEquipFlg(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->EquipFlg[i];
		}
	}


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
/*
�߂�l�Ftrue�F���������o�^�������ꍇ
�߂�l�Ffalse�F�������o�^�ς݂������ꍇ
*/
bool EQUIPMENT::Add(int code)
{
	//�w�肳�ꂽ�R�[�h�����ɓo�^����Ă��邩����
	for (int i = 0; i < this->Code.size(); ++i)	//�R�[�h�ԍ��̐����J��Ԃ�
	{
		if (this->Code[i] == code)	//�ǉ����ꂽ�R�[�h�����łɓo�^����Ă���ꍇ
		{
			this->Possession[i]++;		//�������𑝉�
			this->IsDraw[i] = true;			//�`�悵�Ă悢
			this->Chenge_flg = true;		//�����ύX�t���O
			return false;					//�ǉ������I��(���ɓo�^�ς�)
		}
	}

	//�R�[�h���o�^����Ă��Ȃ������ꍇ
	this->Code.push_back(code);		//�R�[�h�ԍ��ǉ�
	this->Possession.push_back(1);	//��������ǉ��i�ŏ���1�j
	this->EquipFlg.push_back(false);	//������Ԑݒ�i�ŏ��͑������Ă��Ȃ���ԁj
	this->Size = this->Code.size();	//�v�f���ݒ�
	this->IsDraw.push_back(true);		//�`�悵�Ă悢
	this->Chenge_flg = true;			//�����ύX�t���O

	return true;	//�ǉ������I���i���o�^�j
}

//��������ǂݍ���
void EQUIPMENT::LoadData(int code, int posse)
{
	this->Code.push_back(code);			//�R�[�h�ԍ��ǉ�
	this->Possession.push_back(posse);	//�������ǉ�

	if (posse == 0)	//������0��������
	{
		this->IsDraw.push_back(false);	//�`�悵�Ă͂����Ȃ�
	}
	else			//0����Ȃ����
	{
		this->IsDraw.push_back(true);	//�`�悵�Ă悢
	}

	this->EquipFlg.push_back(false);	//�������Ă��Ȃ�
	this->Size = this->Code.size();	//�v�f���ݒ�
	this->Chenge_flg = true;	//�ύX����

	return;

}

//�`�悵�Ă悢���擾
bool EQUIPMENT::GetIsDraw(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->IsDraw[i];
		}
	}

}

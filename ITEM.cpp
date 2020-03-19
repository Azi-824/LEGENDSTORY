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
	std::vector<char> v4;			//���vector���쐬����
	this->ItemType.swap(v4);		//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<bool> v5;			//���vector���쐬����
	this->IsDraw.swap(v5);			//��ƒ��g�����ւ���

	return;
}

//����������
void ITEM::IncreasePossession(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			this->Possession[i]++;	//�������𑝂₷
			this->Chenge_flg = true;	//�ύX����
		}
	}


	return;
}

//����������
void ITEM::DecreasePossession(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			this->Possession[i]--;		//�����������炷
			if (this->Possession[i] <= 0)	//��������0�ȉ��ɂȂ�����
			{
				this->IsDraw[i] = false;		//�`�悵�Ă͂����Ȃ�
				this->Possession[i] = 0;		//0��菭�Ȃ����Ȃ�
			}

			this->Chenge_flg = true;	//�ύX����
		}
	}
	return;
}

//�񕜗ʐݒ�
void ITEM::SetRecovery(int recovery,char type)
{
	this->Recovery.push_back(recovery);	//�񕜗�
	this->ItemType.push_back(type);		//�A�C�e���^�C�v
	return;
}

//�ǉ��������ݒ�
void ITEM::SetChengeFlg(bool add_flg)
{
	this->Chenge_flg = add_flg;
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

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Possession[i];
		}
	}

}

//�񕜗ʎ擾
int ITEM::GetRecovery(int code)
{

	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Recovery[i];
		}
	}

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
bool ITEM::GetIsDraw(int code)
{
	for (int i = 0; i < this->GetSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->IsDraw[i];
		}
	}

}

//�A�C�e����ǉ�
void ITEM::AddItem(int code,int recovery,char itemtype)
{

	//�w�肳�ꂽ�R�[�h�����ɓo�^����Ă��邩����
	for (int i = 0; i < this->Code.size(); ++i)	//�R�[�h�ԍ��̐����J��Ԃ�
	{
		if (this->Code[i] == code)	//�ǉ����ꂽ�R�[�h�����łɓo�^����Ă���ꍇ
		{
			this->Possession[i]++;			//�������𑝉�
			this->IsDraw[i] = true;			//�`�悵�Ă悢
			this->Chenge_flg = true;		//�����ύX�t���O
			return;							//�ǉ������I��
		}
	}

	//�R�[�h���o�^����Ă��Ȃ������ꍇ
	this->Code.push_back(code);			//�R�[�h�ǉ�
	this->Possession.push_back(1);		//�������ǉ�
	this->Recovery.push_back(recovery);	//�񕜗ʒǉ�
	this->ItemType.push_back(itemtype);	//�A�C�e���̃^�C�v��ǉ�
	this->IsDraw.push_back(true);		//�`�悵�Ă悢
	this->Chenge_flg = true;			//�ύX����

	return;

}

//�Z�[�u�f�[�^��ǂݍ���
void ITEM::LoadData(int code, int possession)
{
	this->Code.push_back(code);					//�R�[�h�ǉ�
	this->Possession.push_back(possession);		//�������ǉ�

	if (possession == 0)	//��������0��������
	{
		this->IsDraw.push_back(false);	//�`�悵�Ă͂����Ȃ�
	}
	else					//0����Ȃ����
	{
		this->IsDraw.push_back(true);	//�`�悵�Ă悢
	}

	this->Chenge_flg = true;	//�ύX����

}

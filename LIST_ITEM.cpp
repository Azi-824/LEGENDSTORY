//LIST_ITEM.cpp�N���X
//LIST�N���X�̔h��
//�A�C�e���̈ꗗ���Ǘ�����N���X

//################# �w�b�_�t�@�C���ǂݍ��� ##############
#include "LIST_ITEM.hpp"

//################# �N���X��` ######################

//�R���X�g���N�^
/*
�����Fconst char *�F�ǂݍ��ރf�[�^�̃f�B���N�g��
�����Fconst char *�F�ǂݍ��ރf�[�^�̖��O
*/
LIST_ITEM::LIST_ITEM(const char *dir, const char *name)
{
	std::string LoadFile;
	LoadFile += dir;
	LoadFile += name;

	std::ifstream ifs(LoadFile.c_str());	//�t�@�C���ǂݎ��

	if (!ifs)		//�t�@�C���I�[�v�����s��
	{
		std::string ErrorMsg(LIST_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErrorMsg += TEXT('\n');						//���s
		ErrorMsg += LoadFile;					//�摜�̃p�X

		MessageBox(
			NULL,
			ErrorMsg.c_str(),	//char * ��Ԃ�
			TEXT(LIST_ERROR_TTILE),
			MB_OK);

		this->SetIsLoad(false);	//�ǂݍ��ݎ��s

		return;	//�ǂݍ��ݎ��s

	}


	std::string buf;		//�t�@�C���ǂݍ��ݗp

	//1�s�ڂ�ǂݍ���Ŕ�΂�
	std::getline(ifs, buf);	//1�s�ǂݍ���

	int cnt = 0;	//���[�v���J�E���g�p
	int type_key_pos = 0;	//�A�C�e���^�C�v�̃L�[�ƂȂ�ꏊ�̈ʒu������ϐ�

	while (!ifs.eof())		//�t�@�C���I�[�܂œǂݍ���
	{

		std::getline(ifs, buf, ',');				//�J���}�܂œǂݍ���
		this->SetCode(atoi(buf.c_str()));		//�R�[�h�ԍ��ǂݍ���

		std::getline(ifs, buf, ',');				//�J���}�܂œǂݍ���
		this->SetName(buf.c_str());					//���O�ǂݍ���

		std::getline(ifs, buf, ',');					//�J���}�܂œǂݍ���
		this->Recovery.push_back(atoi(buf.c_str()));	//�񕜗ʓǂݍ���

		std::getline(ifs, buf, '\n');				//���s�܂œǂݍ���
		this->Description.push_back(buf.c_str());	//�������ǂݍ���

		type_key_pos = this->Description[cnt].find("HP");	//HP�Ƃ����P���T���A�擪�̈ʒu���擾����
		if (type_key_pos == -1)	//HP�Ƃ����P�ꂪ������Ȃ�������
		{
			type_key_pos = this->Description[cnt].find("MP");	//MP�Ƃ����P���T���A�擪�̈ʒu���擾����
		}

		this->Type.push_back(this->Description[cnt][type_key_pos]);	//�P��̐擪�������A�A�C�e���^�C�v�Ƃ��Ċi�[����

		++cnt;	//�J�E���g�A�b�v

	}

	this->SetSize();		//���X�g�̗v�f���ݒ�

	this->SetIsLoad(true);	//�ǂݍ��ݐ���

	return;

}

//�f�X�g���N�^
LIST_ITEM::~LIST_ITEM()
{
	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Recovery.swap(v);		//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<std::string> v2;	//���vector���쐬����
	this->Description.swap(v2);		//��ƒ��g�����ւ���

	return;

}

//�񕜗ʎ擾
int LIST_ITEM::GetRecovery(int code)
{
	for (int i = 0; i < this->GetListSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Recovery[i];
		}
	}
}

//�������擾
const char * LIST_ITEM::GetDescription(int code)
{

	for (int i = 0; i < this->GetListSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Description[i].c_str();
		}
	}

}

//�A�C�e���̃^�C�v���擾
char LIST_ITEM::GetItemType(int code)
{
	for (int i = 0; i < this->GetListSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Type[i];
		}
	}

}

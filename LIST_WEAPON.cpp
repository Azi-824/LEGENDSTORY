//LIST_WEAPON.cpp
//����̈ꗗ���Ǘ�����N���X

//################# �w�b�_�t�@�C���ǂݍ��� ################
#include "LIST_WEAPON.hpp"

//################# �N���X��` #####################

//�R���X�g���N�^
/*
�����Fconst char *�F�ǂݍ��ރf�[�^�̃f�B���N�g��
�����Fconst char *�F�ǂݍ��ރf�[�^�̖��O
*/
LIST_WEAPON::LIST_WEAPON(const char *dir, const char *name)
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

	while (!ifs.eof())		//�t�@�C���I�[�܂œǂݍ���
	{

		std::getline(ifs, buf, ',');				//�J���}�܂œǂݍ���
		this->SetCode(atoi(buf.c_str()));		//�R�[�h�ԍ��ǂݍ���

		std::getline(ifs, buf, ',');				//�J���}�܂œǂݍ���
		this->SetName(buf.c_str());					//���O�ǂݍ���

		std::getline(ifs, buf, '\n');				//���s�܂œǂݍ���
		this->Power.push_back(atoi(buf.c_str()));	//�U���͓ǂݍ���

	}

	this->SetSize();		//���X�g�̗v�f���ݒ�

	this->SetIsLoad(true);	//�ǂݍ��ݐ���

	return;

}

//�f�X�g���N�^
LIST_WEAPON::~LIST_WEAPON()
{
	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Power.swap(v);		//��ƒ��g�����ւ���

}

//�U���͎擾
int LIST_WEAPON::GetPower(int code)
{
	for (int i = 0; i < this->GetListSize(); ++i)	//���X�g�̃T�C�Y�����J��Ԃ�
	{
		if (this->GetCode(i) == code)	//�w�肳�ꂽ�R�[�h�ƈ�v������
		{
			return this->Power[i];		//�U���͎擾
		}
	}
}

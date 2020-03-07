//LIST_ARMOR.cpp
//LIST�N���X����̔h��
//�h��ꗗ���Ǘ�����N���X

//################ �w�b�_�t�@�C���ǂݍ��� ##################
#include "LIST_ARMOR.hpp"

//############### �N���X��` ######################

//�R���X�g���N�^
/*
�����Fconst char *�F�ǂݍ��ރf�[�^�̃f�B���N�g��
�����Fconst char *�F�ǂݍ��ރf�[�^�̖��O
*/
LIST_ARMOR::LIST_ARMOR(const char *dir, const char *name)
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
		this->SetCodeNum(atoi(buf.c_str()));		//�R�[�h�ԍ��ǂݍ���

		std::getline(ifs, buf, ',');				//�J���}�܂œǂݍ���
		this->SetName(buf.c_str());					//���O�ǂݍ���

		std::getline(ifs, buf, '\n');				//���s�܂œǂݍ���
		this->Defense.push_back(atoi(buf.c_str()));	//�h��͓ǂݍ���

	}

	this->SetSize();		//���X�g�̗v�f���ݒ�

	this->SetIsLoad(true);	//�ǂݍ��ݐ���

	return;

}

//�f�X�g���N�^
LIST_ARMOR::~LIST_ARMOR()
{
	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Defense.swap(v);		//��ƒ��g�����ւ���

}

//�h��͎擾
int LIST_ARMOR::GetDefense(int kind)
{
	return this->Defense[kind];	//�h��͎擾
}


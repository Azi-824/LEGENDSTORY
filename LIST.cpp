//LIST.cpp
//���@��X�L���̈ꗗ���Ǘ�����N���X

//################### �w�b�_�t�@�C���ǂݍ��� ###########################
#include "LIST.hpp"

//################### �N���X��` ############################

//�R���X�g���N�^
/*
�����Fconst char *�F���X�g�̃t�@�C����
�����Fconst char *�F���X�g�̖��O
*/
LIST::LIST(const char *dir, const char *name)
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

		this->IsLoad = false;	//�ǂݍ��ݎ��s

		return;	//�ǂݍ��ݎ��s

	}


	std::string buf;
	//1�s�ڂ�ǂݍ���Ŕ�΂�
	std::getline(ifs, buf);	//1�s�ǂݍ���

	while (!ifs.eof())		//�t�@�C���I�[�܂œǂݍ���
	{
		std::getline(ifs, buf, ',');		//�J���}�܂œǂݍ���
		this->Name.push_back(buf.c_str());		//�Z���ǂݍ���
		
		std::getline(ifs, buf,'\n');		//���s�܂œǂݍ���
		this->Cost.push_back(atoi(buf.c_str()));//����MP�ǂݍ���

	}

	this->IsLoad = true;	//�ǂݍ��ݐ���

	return;

}

//�f�X�g���N�^
LIST::~LIST()
{
	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Cost.swap(v);			//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<std::string> v2;			//���vector���쐬����
	this->Name.swap(v2);					//��ƒ��g�����ւ���

	return;
}

//���O�擾
const char * LIST::GetName(int kind)
{
	return this->Name[kind].c_str();
}

//����MP�擾
int LIST::GetCost(int kind)
{
	return this->Cost[kind];
}

//�ǂݍ��߂����擾
bool LIST::GetIsLoad(void)
{
	return this->IsLoad;
}

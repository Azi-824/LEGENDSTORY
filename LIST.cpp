//LIST.cpp
//���@��X�L���̈ꗗ���Ǘ�����N���X

//################### �w�b�_�t�@�C���ǂݍ��� ###########################
#include "LIST.hpp"

//################### �N���X��` ############################

//�R���X�g���N�^
LIST::LIST()
{
	return;
}

//�f�X�g���N�^
LIST::~LIST()
{

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Code.swap(v);			//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<std::string> v2;			//���vector���쐬����
	this->Name.swap(v2);					//��ƒ��g�����ւ���

	return;
}

//���O�ݒ�
void LIST::SetName(std::string name)
{
	this->Name.push_back(name.c_str());	//���O�ݒ�
	return;
}

//�R�[�h�ԍ��ݒ�
void LIST::SetCode(int code)
{
	this->Code.push_back(code);	//�R�[�h�ԍ��ݒ�
	return;
}

//���X�g�̗v�f����ݒ�
void LIST::SetSize(void)
{
	this->Size = this->Code.size();	//�T�C�Y�ݒ�
	return;
}

//�ǂݍ��߂����ݒ�
void LIST::SetIsLoad(bool Isload)
{
	this->IsLoad = Isload;	//�ǂݍ��߂����ݒ�
	return;
}

//���O�擾
const char * LIST::GetName(int kind)
{
	return this->Name[kind].c_str();
}

//�ǂݍ��߂����擾
bool LIST::GetIsLoad(void)
{
	return this->IsLoad;
}

//���X�g�̗v�f�����擾
int LIST::GetListSize(void)
{
	return this->Size;
}

//�R�[�h�ԍ��擾
int LIST::GetCode(int kind)
{
	return this->Code[kind];
}

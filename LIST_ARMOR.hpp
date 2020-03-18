//LIST_ARMOR.hpp
//LIST�N���X����h��
//�h��ꗗ���Ǘ�����N���X

#pragma once

//################## �w�b�_�t�@�C���ǂݍ��� ######################
#include "LIST.hpp"

//################## �}�N����` ########################
#define ARMOR_LIST_NAME	R"(armor_list.csv)"		//�h��ꗗ�̃t�@�C����

//################## �N���X��` ########################
class LIST_ARMOR :public LIST
{
private:

	std::vector<int> Defense;		//�h���

public:

	LIST_ARMOR(const char *, const char *);			//�R���X�g���N�^
	~LIST_ARMOR();									//�f�X�g���N�^

	int GetDefense(int);							//�h��͎擾

};

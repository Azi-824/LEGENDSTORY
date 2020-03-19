//LIST_ITEM.hpp
//LIST�N���X����̔h��
//�A�C�e���̈ꗗ���Ǘ�����N���X

#pragma once

//################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "LIST.hpp"

//################### �}�N����` ####################
#define ITEM_LIST_NAME	R"(item_list.csv)"		//�A�C�e���ꗗ�̃t�@�C����

//################### �N���X��` ####################
class LIST_ITEM :public LIST		//LIST�N���X���p��
{
private:

	std::vector<int> Recovery;				//�񕜗�
	std::vector<std::string> Description;	//������
	std::vector<char> Type;					//�A�C�e���̃^�C�v

public:

	LIST_ITEM(const char *, const char *);	//�R���X�g���N�^
	~LIST_ITEM();							//�f�X�g���N�^

	int GetRecovery(int);					//�񕜗ʎ擾
	const char * GetDescription(int);		//�������擾
	char GetItemType(int);					//�A�C�e���̃^�C�v�擾

};

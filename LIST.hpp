//LIST.hpp
//�X�L���▂�@�̈ꗗ���Ǘ�����N���X

#pragma once

//################ �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
#include <vector>
#include <string>
#include <fstream>

//################ �}�N����` #########################
#define LIST_DIR		R"(.\MY_DATA\List\)"			//���X�g�̃f�B���N�g����

#define MGC_LIST_NAME	R"(magic_list.csv)"				//���@�ꗗ��csv�f�[�^�̖��O


//############## �}�N����`�F�G���[���b�Z�[�W ###################
#define LIST_ERROR_TTILE	"LIST_ERROR"						//�G���[�^�C�g��
#define LIST_ERROR_MSG		"���X�g���ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//################ �N���X��` #########################
class LIST
{
private:

	std::vector<int> Cost;				//����MP
	std::vector < std::string> Name;	//�Z��

	bool IsLoad;						//�ǂݍ��߂���

public:	

	LIST(const char *,const char *);	//�R���X�g���N�^
	
	~LIST();							//�f�X�g���N�^

	int GetCost(int);					//����MP�擾
	const char * GetName(int);			//�Z���擾
	bool GetIsLoad(void);				//�ǂݍ��߂���


};

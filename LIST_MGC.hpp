//MGCLIST.hpp
//���@���X�g�̃N���X


#pragma once

//################ �w�b�_�t�@�C���ǂݍ��� ###################
#include "LIST.hpp"

//################ �}�N����` #####################
#define MGC_LIST_NAME	R"(magic_list.csv)"				//���@�ꗗ��csv�f�[�^�̖��O

//################ �N���X��` #####################
class LIST_MGC : public LIST			//���X�g�N���X���p��
{
private:

	std::vector<int> Cost;		//����MP

public:

	LIST_MGC(const char *,const char *);			//�R���X�g���N�^
	~LIST_MGC();									//�f�X�g���N�^

	//�Z�b�^


	//�Q�b�^
	int GetCost(int);			//����MP�擾
};

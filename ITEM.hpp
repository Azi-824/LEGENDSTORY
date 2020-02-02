//ITEM.hpp
//�A�C�e���N���X

#pragma once

//#################### �w�b�_�t�@�C���ǂݍ��� ########################
#include "DxLib.h"
#include <vector>
#include <string>

//#################### �}�N����` ############################
#define ITEM_KIND 2		//�A�C�e���̎��

#define ITME_YAKUSOU_RECOVERY_AMOUNT 30	//�򑐂̉񕜗�

//#################### �N���X��` ############################
class ITEM
{
private:

	std::string Name;				//�A�C�e����

	std::string Description;		//�A�C�e���̐�����

public:

	ITEM();				//�R���X�g���N�^

	~ITEM();			//�f�X�g���N�^

	void SetName(const char *);				//�A�C�e�����ݒ�

	void SetDescription(const char *);		//��������ݒ�

	const char * GetName(void);				//���O�擾

	const char * GetDescription(void);		//�������擾

};

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

	std::vector<int> Code;			//�A�C�e���R�[�h
	std::vector<int> Possession;	//������
	std::vector<int> Recovery;		//�񕜗�

	bool Add_flg;					//�ǉ��������ǂ���

public:

	ITEM();				//�R���X�g���N�^

	~ITEM();			//�f�X�g���N�^

	//�Z�b�^
	void SetCode(int);				//�A�C�e���R�[�h�ݒ�
	void IncreasePossession(int);	//����������
	void DecreasePossession(int);	//����������
	void SetRecovery(int);			//�񕜗ʐݒ�
	void SetAddFlg(bool);			//�ǉ��������ݒ�

	//�Q�b�^
	int GetCode(int);				//�A�C�e���R�[�h�擾
	int GetPossession(int);			//�������擾
	int GetRecovery(int);			//�񕜗ʐݒ�
	int GetSize();					//�v�f�����擾
	bool GetAddFlg(void);			//�ǉ��������擾

};

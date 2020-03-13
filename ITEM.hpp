//ITEM.hpp
//�A�C�e���N���X

#pragma once

//#################### �w�b�_�t�@�C���ǂݍ��� ########################
#include "DxLib.h"
#include <vector>
#include <string>

//#################### �}�N����` ############################
#define ITME_YAKUSOU_RECOVERY_AMOUNT 30	//�򑐂̉񕜗�

//#################### �N���X��` ############################
class ITEM
{
private:

	std::vector<int> Code;			//�A�C�e���R�[�h
	std::vector<int> Possession;	//������
	std::vector<int> Recovery;		//�񕜗�

	std::vector<bool> IsDraw;		//�`�悵�Ă悢��

	bool Chenge_flg;				//�ǉ��������ǂ���

public:

	ITEM();				//�R���X�g���N�^

	~ITEM();			//�f�X�g���N�^

	//�Z�b�^
	void SetCode(int);				//�A�C�e���R�[�h�ݒ�
	void IncreasePossession(int);	//����������
	void DecreasePossession(int);	//����������
	void SetRecovery(int);			//�񕜗ʐݒ�
	void SetChengeFlg(bool);		//�ύX�������ݒ�
	//void SetIsDraw(int, bool);		//�`�悵�Ă悢���ݒ�

	//�Q�b�^
	int GetCode(int);				//�A�C�e���R�[�h�擾
	int GetPossession(int);			//�������擾
	int GetRecovery(int);			//�񕜗ʐݒ�
	int GetSize();					//�v�f�����擾
	bool GetChengeFlg(void);		//�ύX�������擾
	std::vector<int> GetPossession();	//�������擾(�S��)
	bool GetIsDraw(int);			//�`�悵�Ă悢���擾

};

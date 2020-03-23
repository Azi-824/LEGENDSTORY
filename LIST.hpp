//LIST.hpp
//�X�L���▂�@�̈ꗗ���Ǘ�����N���X

/*
�ǉ����@
�E���̃N���X�́A�ꗗ���Ǘ������ɂȂ�N���X�̂��߁A�f�[�^�̓ǂݍ��݂Ȃǂ́A�h���������N���X�ōs��
�@��F����̈ꗗ�f�[�^��ǂݍ��ނ̂́A�h���N���X�ł���ALIST_WEAPON�N���X�ōs���B
�E�h���N���X�ł́A���e�ɂ���ĕK�v�ȗv�f��ǉ�����
�@��F����ꗗ�Ȃ�A�U���́A�h��ꗗ�Ȃ�A�h��͂Ȃ�
*/

#pragma once

//################ �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
#include <vector>
#include <string>
#include <fstream>

//################ �}�N����` #########################
#define LIST_DIR		R"(.\MY_DATA\List\)"			//���X�g�̃f�B���N�g����

//############## �}�N����`�F�G���[���b�Z�[�W ###################
#define LIST_ERROR_TTILE	"LIST_ERROR"						//�G���[�^�C�g��
#define LIST_ERROR_MSG		"���X�g���ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//################ �N���X��` #########################
class LIST
{
private:

	std::vector <std::string> Name;		//���O

	std::vector<int> Code;				//�R�[�h�ԍ�

	int Size;							//���X�g�̗v�f��

	bool IsLoad;						//�ǂݍ��߂���

public:	

	LIST();								//�R���X�g���N�^
	~LIST();							//�f�X�g���N�^

	//�Z�b�^
	void SetName(std::string);			//���O�ݒ�
	void SetCode(int);					//�R�[�h�ԍ��ݒ�
	void SetSize();						//���X�g�̗v�f���ݒ�
	void SetIsLoad(bool);				//�ǂݍ��߂����ݒ�

	//�Q�b�^
	const char * GetName(int);			//�Z���擾
	bool GetIsLoad(void);				//�ǂݍ��߂���
	int GetListSize(void);				//���X�g�̗v�f�����擾
	int GetCode(int);					//�R�[�h�ԍ��擾

};

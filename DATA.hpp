//DATA.hpp
//�f�[�^�N���X
//�e�L�X�g�t�@�C���̕����R�[�h��ANSI�ɂ��ĕۑ�����

#pragma once

//############## �w�b�_�t�@�C���ǂݍ��� #################
#include "DxLib.h"
#include <string>
#include <fstream>


//############## �}�N����`�F�t�@�C�����A�p�X ###################
#define DATA_DIR	R"(.\MY_TEXT\Message\)"		//���b�Z�[�W�e�L�X�g�̃t�@�C����

#define DATA_NAME	R"(msg.txt)"			//���b�Z�[�W�e�L�X�g�̖��O

//############## �}�N����`�F�G���[���b�Z�[�W ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//�G���[�^�C�g��
#define DATA_ERROR_MSG		"�f�[�^���ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//############## �N���X��` #####################
class DATA
{
private:

	std::string Text;		//�����f�[�^

public:

	DATA(const char *, const char *);		//�R���X�g���N�^

	~DATA();								//�f�X�g���N�^

	void Draw(int, int);					//�`��

};

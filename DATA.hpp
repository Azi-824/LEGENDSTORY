//DATA.hpp
//�f�[�^�N���X
//�e�L�X�g�t�@�C���̕����R�[�h��ANSI�ɂ��ĕۑ�����

#pragma once

//############## �w�b�_�t�@�C���ǂݍ��� #################
#include "DxLib.h"
#include <string>
#include <fstream>
#include "PLAYER.hpp"


//############## �}�N����`�F�t�@�C�����A�p�X ###################
#define DATA_DIR	R"(.\MY_TEXT\Message\)"		//���b�Z�[�W�e�L�X�g�̃t�@�C����
#define PLAYER_DATA_DIR	R"(.\MY_DATA\Player\)"	//�v���C���[�̃f�[�^�̃t�@�C����

#define DATA_NAME	R"(msg.txt)"			//���b�Z�[�W�e�L�X�g�̖��O
#define PLAYER_DATA_NAME	R"(player.txt)"	//�v���C���[�̃f�[�^�̖��O

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

	template<typename T>					//�e���v���[�g��
	void Input(T);							//�C���v�b�g
	void Output(PLAYER *,const char *,const char *);//�A�E�g�v�b�g

	void Draw(int, int);					//�`��

};

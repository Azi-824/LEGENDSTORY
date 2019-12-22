//DATA.hpp
//�f�[�^�N���X
//�e�L�X�g�t�@�C���̕����R�[�h��ANSI�ɂ��ĕۑ�����

#pragma once

//############## �w�b�_�t�@�C���ǂݍ��� #################
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include "PLAYER.hpp"
#include "ENEMY.hpp"


//############## �}�N����`�F�t�@�C�����A�p�X ###################
#define DATA_DIR	R"(.\MY_TEXT\Message\)"		//���b�Z�[�W�e�L�X�g�̃t�@�C����
#define PLAYER_DATA_DIR	R"(.\MY_DATA\Player\)"	//�v���C���[�̃f�[�^�̃t�@�C����
#define ENEMY_DATA_DIR	R"(.\MY_DATA\Enemy\)"	//�G�̃f�[�^�̃t�@�C����

#define DATA_NAME	R"(msg.txt)"			//���b�Z�[�W�e�L�X�g�̖��O
#define PLAYER_DATA_NAME	R"(player.txt)"	//�v���C���[�̃f�[�^�̖��O
#define ENEMY_DATA_NAME		R"(Enemy_Data.csv)"	//�G�̃f�[�^�̃t�@�C����

//############## �}�N����`�F�G���[���b�Z�[�W ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//�G���[�^�C�g��
#define DATA_ERROR_MSG		"�f�[�^���ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//############## �N���X��` #####################
class DATA
{
private:

	std::string Text;		//�����f�[�^

	std::vector<int> Data;

public:

	DATA(const char *, const char *);		//�R���X�g���N�^

	~DATA();								//�f�X�g���N�^

	void Input(PLAYER *,const char *, const char *);		//�C���v�b�g�i�����f�[�^�j
	void Input(ENEMY *[],const char *, const char *);			//�C���v�b�g�i�G�f�[�^�j
	void Output(PLAYER *,const char *,const char *);		//�A�E�g�v�b�g

	void Draw(int, int);					//�`��

};

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
#include "ITEM.hpp"


//############## �}�N����`�F�t�@�C�����A�p�X ###################
#define PLAYER_DATA_DIR	R"(.\MY_DATA\Player\)"	//�v���C���[�̃f�[�^�̃t�@�C����
#define ENEMY_DATA_DIR	R"(.\MY_DATA\Enemy\)"	//�G�̃f�[�^�̃t�@�C����
#define ITEM_DATA_DIR	R"(.\MY_DATA\Item\)"	//�A�C�e���̃f�[�^�̃t�@�C����

#define PLAYER_DATA_NAME	R"(Player_Data.csv)"//�v���C���[�̃f�[�^��csv�t�@�C��
#define ENEMY_DATA_NAME		R"(Enemy_Data.csv)"	//�G�̃f�[�^�̖��O
#define ITEM_DATA_NAME		R"(Item_Data.csv)"	//�A�C�e���̃f�[�^�̖��O

//############## �}�N����`�F�G���[���b�Z�[�W ###################
#define DATA_ERROR_TTILE	"DATA_ERROR"						//�G���[�^�C�g��
#define DATA_ERROR_MSG		"�f�[�^���ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//############## �N���X��` #####################
class DATA
{
private:

public:

	DATA();		//�R���X�g���N�^

	~DATA();								//�f�X�g���N�^

	bool LoadPlayer(PLAYER *,const char *, const char *);		//�ǂݍ��݁i�����f�[�^�j
	bool LoadEnemy(ENEMY *[],const char *, const char *);		//�ǂݍ��݁i�G�f�[�^�j
	bool LoadItem(ITEM *[], const char *, const char *);		//�ǂݍ��݁i�A�C�e���f�[�^�j
	bool Save(PLAYER *,const char *,const char *);		//�Z�[�u

};

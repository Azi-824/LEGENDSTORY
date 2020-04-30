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
#include "MSG.hpp"


//############## �}�N����`�F�t�@�C�����A�p�X ###################
#define ENEMY_DATA_DIR	R"(.\MY_DATA\Enemy\)"	//�G�̃f�[�^�̃t�@�C����
#define MSG_DATA_DIR	R"(.\MY_DATA\Msg\)"		//���b�Z�[�W�̃f�[�^�̃t�@�C����
#define MAPPOS_DATA_DIR R"(.\MY_DATA\MapPos)"	//�}�b�v�ʒu�̃f�[�^�̃t�@�C����
#define SAVE_DATA_DIR	R"(C:\LEGENDSTORY_DATA)"//�Z�[�u�f�[�^�̕ۑ��f�B���N�g����

#define ENEMY_DATA_NAME		R"(Enemy_Data.csv)"	//�G�̃f�[�^�̖��O
#define MSG_DATA_NAME		R"(Msg_Data.txt)"	//���b�Z�[�W�f�[�^�̖��O
#define MAPPOS_DATA_NAME	R"(\MapPos_Data.csv)"//�}�b�v�ʒu�̃f�[�^�̖��O
#define MAPPOS_INITDATA_NAME	R"(\MapPos_DataInit.csv)"	//�}�b�v�ʒu�̃f�[�^�̖��O�i�����j

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

	bool LoadEnemy(ENEMY *[],const char *, const char *);		//�ǂݍ��݁i�G�f�[�^�j
	bool LoadMsg(MESSAGE *, const char *, const char *);		//�ǂݍ��݁i���b�Z�[�W�f�[�^�j
	bool LoadNowMap(int *, int *, const char *, const char *);	//�ǂݍ��݁i���݂̃}�b�v�ʒu�j
	bool SaveMap(int, int[],const char *,const char *);			//���݂̃}�b�v�ʒu���Z�[�u

};

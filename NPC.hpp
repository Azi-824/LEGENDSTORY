//NPC.hpp
//NPC���Ǘ�����N���X

#pragma once

//################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include "IMAGE.hpp"
//#include "MSG.hpp"
#include <vector>
#include <string>
#include <fstream>

//#################### �}�N����` ######################
#define NPC_DATA_DIR			R"(.\MY_DATA\NPC\)"		//NPC�f�[�^�̃t�@�C����
#define NPC_IMAGE_DIR			R"(.\MY_IMG\NPC\)"		//NPC�̉摜�f�[�^�̃t�@�C����

#define NPC_DATA_NAME			R"(NPC_Data.csv)"		//NPC�f�[�^�̖��O
#define NPC_IMAGE_DATA_NAME		R"(NPC1.png)"			//NPC�̉摜�̖��O

//############## �}�N����`�F�G���[���b�Z�[�W ###################
#define NPC_DATA_ERROR_TTILE	"NPC_DATA_ERROR"						//�G���[�^�C�g��
#define NPC_DATA_ERROR_MSG		"NPC�f�[�^���ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W


//#################### �N���X��` ######################
class NPC
{
private :

	IMAGE *Image;							//NPC�̉摜
	//MESSAGE *Text;							//NPC�̉�b�e�L�X�g

	std::vector<std::string> Name;			//NPC�̖��O

	std::vector<int>	DrawMapKind;		//NPC��`�悷��}�b�v�̎��
	std::vector<int>	DrawMap_Num;		//NPC�̕`��}�b�v�ԍ�
	std::vector<int>	Draw_X;				//NPC�̕`��X�ʒu
	std::vector<int>	Draw_Y;				//NPC�̕`��Y�ʒu

	bool ImageIsLoad;						//�摜��ǂݍ��߂���

public:	

	NPC(const char *, const char *);		//�R���X�g���N�^
	~NPC();									//�f�X�g���N�^

	bool GetImageIsLoad();					//�摜��ǂݍ��߂����擾

	void DrawNPC(int,int);					//NPC��`�悷��
	//void DrawNPCText(int);					//�w�肳�ꂽNPC�̉�b�e�L�X�g��`�悷��

	bool Load(const char *, const char *);	//NPC�f�[�^��ǂݍ���

};

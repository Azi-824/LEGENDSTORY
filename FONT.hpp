//FONT.hpp
//�t�H���g�N���X

#pragma once

//################# �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
#include <string>


//################ �}�N����` �t�@�C���p�X�Ɩ��O ###############
#define MY_FONT_DIR		R"(.\MY_FONT)"						//�t�H���g�t�@�C���̏ꏊ

#define MY_FONT_NAME	R"(\GD-DOTFONT-DQ-OTF.otf)"			//�t�H���g�̖��O

//############### �}�N����` ##################
#define FONT_NAME		("GD-DOTFONT-DQ-OTF")				//�t�H���g�̐�������
#define DEFAULT_FONTSIZE	32								//�f�t�H���g�̃t�H���g�T�C�Y



//################ �}�N����` �G���[���b�Z�[�W #################
#define FONT_ERROR_TITLE "FONT_ERROR"						//�G���[�^�C�g��
#define FONT_ERROR_MSG	"�t�H���g���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//################ �N���X�̒�` ##################
class FONT {

private:
	std::string FilePath;	//�p�X
	std::string FileName;	//���O

	int Handle;				//�n���h��
	int Width;				//������̉���

	bool Isload;			//�ǂݍ��߂�

public:

	FONT(const char *,const char *,const char *);		//�R���X�g���N�^
	 
	~FONT();								//�f�X�g���N�^

	bool GetIsLoad();						//�ǂݍ��߂���

	void SetSize(int);						//�t�H���g�T�C�Y�ݒ�

	void Draw(int ,int ,const char *);		//�����`��

	int GetWidth(const char *);				//������̉������擾����

};

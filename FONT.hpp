//FONT.hpp
//�t�H���g�N���X

/*
�ǉ����@
�E�t�H���g�̃t�@�C�����ƁA�t�H���g�̖��O���}�N����`����
�E�}�N����`����Ă���t�H���g�̎�ނ𑝂₷
�EAdd�������g�p���āA�Q�[�����Ŏg�p����t�H���g�𑝂₷���Ƃ��ł���
*/

#pragma once

//################# �w�b�_�t�@�C���ǂݍ��� ######################
#include "DxLib.h"
#include <string>
#include <vector>


//################ �}�N����` �t�@�C���p�X�Ɩ��O ###############
#define MY_FONT_DIR		R"(.\MY_FONT)"						//�t�H���g�t�@�C���̏ꏊ

#define MY_FONT_NAME	R"(\PixelMplus10-Regular.ttf)"			//�t�H���g�̖��O

//############### �}�N����` ##################
#define FONT_NAME		("PixelMplus10 Regular")			//�t�H���g2�̐�������
#define DEFAULT_FONTSIZE	20								//�f�t�H���g�̃t�H���g�T�C�Y
#define	MSG_FONTSIZE		40								//���b�Z�[�W�̃t�H���g�T�C�Y
#define BIG_FONTSIZE		64								//�t�H���g�T�C�Y��

#define FONT_KIND			1								//�t�H���g�̎��

//################ �}�N����` �G���[���b�Z�[�W #################
#define FONT_ERROR_TITLE "FONT_ERROR"						//�G���[�^�C�g��
#define FONT_ERROR_MSG	"�t�H���g���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//################ �N���X�̒�` ##################
class FONT {

private:
	std::vector<std::string> FilePath;				//�p�X
	std::vector<std::string>::iterator Path_itr;	//�p�X�̃C�e���[�^
	std::vector<std::string> FileName;				//���O
	std::vector<std::string>::iterator Name_itr;	//���O�̃C�e���[�^

	int LoadFontNow;		//�ǂݍ��񂾃t�H���g�̐�

	bool Isload;			//�ǂݍ��߂�

public:

	FONT(const char *,const char *,const char *);		//�R���X�g���N�^

	FONT();									//�f�t�H���g�R���X�g���N�^
	 
	~FONT();								//�f�X�g���N�^

	bool GetIsLoad();						//�ǂݍ��߂���

	void SetSize(int);						//�t�H���g�T�C�Y�ݒ�

	void AddFont(const char *, const char *, const char *);	//�t�H���g�ǉ�

	void ChengFont(int);					//�t�H���g�ύX

};

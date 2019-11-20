/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				�@ */
/* �摜�N���X 																					�@ */

#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include <string>

//########## �}�N����`�F�摜�̃t�@�C���p�X�Ɩ��O ##########
#define MY_IMG_DIR_TITLE	R"(.\MY_IMG\TITLE)"	//�^�C�g���̉摜�̃t�@�C���̏ꏊ

#define MY_ING_NAME_TITLE	R"(\Title_Logo.png)"			//�^�C�g���摜�̖��O

//########## �}�N����`�F�G���[���b�Z�[�W##########
#define IMAGE_ERROR_TITLE "IMAGE_ERROR"					//�G���[�^�C�g��
#define IMAGE_ERROR_MSG	"�摜���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//########## �N���X�̒�` ##########

class IMAGE
{
private:
	std::string FilePath;	//�p�X
	std::string FileName;	//���O

	int Handle;				//�n���h��

	int Width;				//��
	int Height;				//����

	bool IsLoad;			//�ǂݍ��߂����H

public:
	IMAGE(const char *,const char *);	//�R���X�g���N�^
	virtual ~IMAGE();					//�f�X�g���N�^

	std::string GetFileName(void);	//���O���擾

	int GetWidth(void);				//�����擾
	int GetHeight(void);			//�������擾

	bool GetIsLoad(void);			//�ǂݍ��߂��H

	void Draw(int,int);				//�摜��`��
};


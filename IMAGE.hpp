/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* IMAGE.cpp     																				�@ */
/* �摜�N���X 																					�@ */

#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include <string>
#include <vector>

//########## �}�N����`�F�摜�̃t�@�C���p�X�Ɩ��O ##########
#define MY_IMG_DIR_TITLE	R"(.\MY_IMG\TITLE)"				//�^�C�g���̉摜�̃t�@�C���̏ꏊ
#define MY_IMG_DIR_CHARCTOR	R"(.\MY_IMG\CHARACTOR)"			//�L�����N�^�[�̉摜�̃t�@�C���̏ꏊ
#define MY_IMG_DIR_BACK		R"(.\MY_IMG\BACK)"				//�w�i�摜�̃t�@�C���̏ꏊ

#define MY_ING_NAME_TITLE	R"(\Title_Logo.png)"			//�^�C�g���摜�̖��O
#define MY_IMG_NAME_PLAYER	R"(\yh032.png)"					//��l���̉摜�̖��O
#define MY_IMG_NAME_BACK	R"(\title_back.jpg)"			//�w�i�摜�̖��O

//########## �}�N����`�F�G���[���b�Z�[�W##########
#define IMAGE_ERROR_TITLE "IMAGE_ERROR"					//�G���[�^�C�g��
#define IMAGE_ERROR_MSG	"�摜���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//########## �N���X�̒�` ##########

class IMAGE
{
private:
	std::string FilePath;	//�p�X
	std::string FileName;	//���O

	std::vector<int> Handle;				//�n���h��

	std::vector<int> Width;					//��
	std::vector<int> Height;				//����

	std::vector<int>::iterator Handle_itr;	//�n���h���̃C�e���[�^
	std::vector<int>::iterator Width_itr;	//���̃C�e���[�^
	std::vector<int>::iterator Height_itr;	//�����̃C�e���[�^

	bool IsLoad;			//�ǂݍ��߂����H

public:
	IMAGE(const char *,const char *);	//�R���X�g���N�^
	virtual ~IMAGE();					//�f�X�g���N�^

	std::string GetFileName(void);	//���O���擾

	int GetWidth(int);				//�����擾
	int GetHeight(int);			//�������擾

	bool GetIsLoad(void);			//�ǂݍ��߂��H

	void Draw(int,int,int);				//�摜��`��
};


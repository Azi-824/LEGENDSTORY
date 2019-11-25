//MAP.hpp
//�}�b�v�N���X

#pragma once

//####################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include <string>

//###################### �}�N����`�F�t�@�C���p�X�A���O ##################
#define MY_MAP_DIR		R"(.\MY_MAP\map_csv\)"			//�}�b�vcsv�̃t�@�C���̏ꏊ
#define MY_MAP_IMG_DIR	R"(.\MY_MAP\map_image\)"		//�}�b�v�摜�̃t�@�C���̏ꏊ

#define MY_MAP_1		R"(map_1.csv)"				//�}�b�vcsv�̖��O
#define MY_MAP_IMAGE	R"(pipo-map001.png)"		//�}�b�v�摜�̖��O

//##################### �}�N����`�F�G���[���b�Z�[�W ####################
#define MAP_ERROR_TTILE		"MAP_ERROR"						//�G���[�^�C�g��
#define MAP_ERROR_MSG		"�}�b�v���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//##################### �}�N����` ########################
#define MAP_YOKO		20			//�}�b�v�̐��i���j
#define MAP_TATE		15			//�}�b�v�̐��i�c�j

#define MAP_BUN_YOKO	8			//�}�b�v�̕������i���j
#define MAP_BUN_TATE	11			//�}�b�v�̕������i�c�j

#define MAP_YOKO_SIZE	40			//�}�b�v�̑傫���i���j
#define MAP_TATE_SIZE	40			//�}�b�v�̑傫���i�c�j



//##################### �N���X��` ###################
class MAP
{
private:
	std::string FilePath;				//�p�X
	std::string FileName;				//���O

	int Handle[MAP_BUN_TATE * MAP_BUN_YOKO];		//�n���h��
	int X[MAP_BUN_TATE * MAP_BUN_YOKO];				//X�ʒu
	int Y[MAP_BUN_TATE * MAP_BUN_YOKO];				//Y�ʒu
	int Width[MAP_BUN_TATE * MAP_BUN_YOKO];			//��
	int Height[MAP_BUN_TATE * MAP_BUN_YOKO];		//����

	int MapData[MAP_TATE][MAP_YOKO];		//�}�b�v�f�[�^

	FILE *fp_map_csv;						//�}�b�v�t�@�C���̃|�C���^

public :
	
	MAP();				//�R���X�g���N�^

	~MAP();				//�f�X�g���N�^

	bool LoadCsv(const char *, const char *);	//csv�f�[�^�ǂݍ���

	void Draw();		//�`��

};

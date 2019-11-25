//MAPIMAGE.hpp
//�g�p����}�b�v�`�b�v�̃N���X

#pragma once

//################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "DxLib.h"
#include <string>

//################### �}�N����`�F�t�@�C���p�X�A���O ####################
#define MY_MAP_IMG_DIR	R"(.\MY_MAP\map_image\)"		//�}�b�v�摜�̃t�@�C���̏ꏊ

#define MY_MAP_IMAGE	R"(pipo-map001.png)"			//�}�b�v�摜�̖��O

//##################### �}�N����`�F�G���[���b�Z�[�W ####################
#define MAP_ERROR_TTILE		"MAP_ERROR"						//�G���[�^�C�g��
#define MAP_ERROR_MSG		"�}�b�v���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//##################### �}�N����` ###########################
#define MAP_BUN_YOKO	8			//�}�b�v�̕������i���j
#define MAP_BUN_TATE	11			//�}�b�v�̕������i�c�j

#define MAP_IMAGE_KIND	1			//�g�p����}�b�v�C���[�W�摜�̎��

#define MAP_YOKO_SIZE	40			//�}�b�v�̑傫���i���j
#define MAP_TATE_SIZE	40			//�}�b�v�̑傫���i�c�j

//##################### �񋓌^ ######################
enum MAPIMAGEKIND
{
	FILED		//�t�B�[���h�̃}�b�v�`�b�v�摜
};

//##################### �N���X��` ############################
class MAPIMAGE
{
private:
	
	std::string FilePath;				//�p�X
	std::string FileName;				//���O

	int Handle[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];		//�n���h��
	int X[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];				//X�ʒu
	int Y[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];				//Y�ʒu
	int Width[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];			//��
	int Height[MAP_IMAGE_KIND][MAP_BUN_TATE * MAP_BUN_YOKO];		//����

	bool IsLoad;						//�ǂݍ��߂���

public:

	MAPIMAGE();					//�R���X�g���N�^

	~MAPIMAGE();				//�f�X�g���N�^	

	int * GetHandle(int);		//�w�肵���}�b�v�`�b�v�̃n���h�����擾

	bool GetIsLoad();			//�ǂݍ��߂���

};


//MAP.hpp
//�}�b�v�N���X

#pragma once

//####################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include "MAPIMAGE.hpp"
#include <string>

//###################### �}�N����`�F�t�@�C���p�X�A���O ##################
#define MY_MAP_DIR		R"(.\MY_MAP\map_csv\)"			//�}�b�vcsv�̃t�@�C���̏ꏊ

#define MY_MAP_1		R"(map_1.csv)"				//�}�b�vcsv�̖��O
#define MY_MAP_2		R"(map_1_2.csv)"			//�}�b�vcsv�̖��O

#define MAP_LAYER_KIND	2							//�}�b�v�f�[�^�̃��C���[��
//##################### �}�N����`�F�G���[���b�Z�[�W ####################

//##################### �񋓌^ #########################
enum MAP_LAYER
{
	FIRST_LAYER,		//��w��
	SECOND_LAYER		//��w��
};

//##################### �}�N����` ########################
#define MAP_YOKO		20			//�}�b�v�̐��i���j
#define MAP_TATE		15			//�}�b�v�̐��i�c�j



//##################### �N���X��` ###################
class MAP
{
private:
	std::string FilePath;				//�p�X
	std::string FileName;				//���O

	int MapData[MAP_TATE][MAP_YOKO];		//�}�b�v�f�[�^

	FILE *fp_map_csv;						//�}�b�v�t�@�C���̃|�C���^

public :
	
	MAP();				//�R���X�g���N�^

	~MAP();				//�f�X�g���N�^

	bool LoadCsv(const char *, const char *);	//csv�f�[�^�ǂݍ���

	void Draw(int *);		//�`��

};
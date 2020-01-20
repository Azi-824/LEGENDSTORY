//MAP.hpp
//�}�b�v�N���X

#pragma once

//####################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include "MAPIMAGE.hpp"
#include "PLAYER.hpp"
#include "COLLISION.hpp"
#include <string>

//###################### �}�N����`�F�t�@�C���p�X�A���O ##################
#define MY_MAP_DIR		R"(.\MY_MAP\map_csv\)"			//�}�b�vcsv�̃t�@�C���̏ꏊ

#define MY_MAP_1_1		R"(map_1_1.csv)"			//�}�b�vcsv�̖��O(1�}�b�v�ڃ��C���[1)
#define MY_MAP_1_2		R"(map_1_2.csv)"			//�}�b�vcsv�̖��O(1�}�b�v�ڃ��C���[2)
#define MY_MAP_1_3		R"(map_1_3.csv)"			//�}�b�vcsv�̖��O(1�}�b�v�ڃ��C���[3)
#define MY_MAP_2_1		R"(map_2_1.csv)"			//�}�b�vcsv�̖��O(2�}�b�v�ڃ��C���[1)
#define MY_MAP_2_2		R"(map_2_2.csv)"			//�}�b�vcsv�̖��O(2�}�b�v�ڃ��C���[2)
#define MY_MAP_2_3		R"(map_2_3.csv)"			//�}�b�vcsv�̖��O(2�}�b�v�ڃ��C���[3)
#define MY_MAP_3_1		R"(map_3_1.csv)"			//�}�b�vcsv�̖��O(3�}�b�v�ڃ��C���[1)
#define MY_MAP_3_2		R"(map_3_2.csv)"			//�}�b�vcsv�̖��O(3�}�b�v�ڃ��C���[2)
#define MY_MAP_3_3		R"(map_3_3.csv)"			//�}�b�vcsv�̖��O(3�}�b�v�ڃ��C���[3)
#define MY_MAP_4_1		R"(map_4_1.csv)"			//�}�b�vcsv�̖��O(4�}�b�v�ڃ��C���[1)
#define MY_MAP_4_2		R"(map_4_2.csv)"			//�}�b�vcsv�̖��O(4�}�b�v�ڃ��C���[2)
#define MY_MAP_4_3		R"(map_4_3.csv)"			//�}�b�vcsv�̖��O(4�}�b�v�ڃ��C���[3)

#define MAP_NG_KIND		1	//�ʍs�ł��Ȃ��}�b�v�̎��
#define MAP_OK_KIND		1	//�ʍs�ł���}�b�v�̎��

//##################### �}�N����`�F�G���[���b�Z�[�W ####################

//##################### �񋓌^ #########################
enum MAP_LAYER
{
	FIRST_LAYER,		//��w��
	SECOND_LAYER,		//��w��
	THIRD_LAYER			//�O�w��
};

enum MAP_KIND
{
	MAP_1,				//��}�b�v��
	MAP_2,				//�j�}�b�v��
	MAP_3,				//�O�}�b�v��
	MAP_4				//�l�}�b�v��
};

enum MAP_NG_NUM
{
	MAP_NG_KIND1 =83		//�ʍs�ł��Ȃ��}�b�v�̐���
};

enum MAP_OK_NUM
{
	MAP_OK_KIND1 = 1		//�ʍs�ł���}�b�v�̐���
};

//##################### �}�N����` ########################
#define MAP_YOKO		20			//�}�b�v�̐��i���j
#define MAP_TATE		15			//�}�b�v�̐��i�c�j

#define MAP_LAYER_KIND	3										//�}�b�v�f�[�^�̃��C���[��
#define MAP_DATA_KIND	MAP_DATA_YOKO_KIND * MAP_DATA_TATE_KIND	//�}�b�v�f�[�^�̎�ސ�
#define MAP_DATA_YOKO_KIND	2									//�}�b�v�f�[�^�̉������̎�ސ�
#define MAP_DATA_TATE_KIND	2									//�}�b�v�f�[�^�̏c���̎�ސ�

#define MAPPOS_X	MapNowPos[0]						//�}�b�v��X�ʒu
#define MAPPOS_Y	MapNowPos[1]						//�}�b�v��Y�ʒu

#define POS_X	0									//X���W
#define POS_Y	1									//Y���W

//##################### �N���X��` ###################
class MAP
{
private:
	std::string FilePath;				//�p�X
	std::string FileName;				//���O

	int MapData[MAP_TATE][MAP_YOKO];		//�}�b�v�f�[�^

	COLLISION *RectOK[MAP_TATE][MAP_YOKO];		//�����蔻��(�ʍs�ł���)
	COLLISION *RectNG[MAP_TATE][MAP_YOKO];		//�����蔻��i�ʍs�ł��Ȃ��j

	FILE *fp_map_csv;						//�}�b�v�t�@�C���̃|�C���^

public :
	
	MAP();				//�R���X�g���N�^

	~MAP();				//�f�X�g���N�^

	bool LoadCsv(const char *, const char *);	//csv�f�[�^�ǂݍ���

	void ChengeMap(PLAYER *,int *);				//�}�b�v��؂�ւ���

	void Draw(int *);		//�`��

	void CreateRect(int *,int *);	//�����蔻��̗̈���쐬

	bool CheckDetectionPlayer(COLLISION *player, int *detectionX, int *detectionY);	//�v���C���[�ƃ}�b�v���������Ă��邩�m�F

};

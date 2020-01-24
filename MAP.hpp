//MAP.hpp
//�}�b�v�N���X

#pragma once

//####################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include "COLLISION.hpp"
#include "IMAGE.hpp"
#include <string>

//###################### �}�N����`�F�t�@�C���p�X�A���O ##################
#define MY_MAP_DIR		R"(.\MY_MAP\map_csv\)"		//�}�b�vcsv�̃t�@�C���̏ꏊ
#define IMG_DIR_MAP		R"(.\MY_MAP\map_image\)"	//�}�b�v�̉摜�t�@�C���̏ꏊ

#define IMG_NAME_MAP_SOUGEN	R"(sougen.png)"			//�����̉摜�̖��O
#define MY_MAP_TEST2		R"(forest.png)"			//�X�̉摜�̖��O
#define MY_MAP_TEST3		R"(test_3.png)"			//�e�X�g�p
#define MY_MAP_TEST4		R"(test_4.png)"			//�e�X�g�p

#define MY_MAP_SOUGEN_ATARI	R"(sougen_atari.csv)"	//�����̓����蔻��
#define MY_MAP_TEST2_ATARI	R"(forest_atari.csv)"	//�X�̓����蔻��
#define MY_MAP_TEST3_ATARI	R"(test3_atari.csv)"
#define MY_MAP_TEST4_ATARI	R"(test4_atari.csv)"


#define MAP_NG_KIND		1	//�ʍs�ł��Ȃ��}�b�v�̎��
#define MAP_OK_KIND		1	//�ʍs�ł���}�b�v�̎��

//##################### �}�N����`�F�G���[���b�Z�[�W ####################

//##################### �}�N����` ########################
#define MAP_YOKO		20			//�}�b�v�̐��i���j
#define MAP_TATE		15			//�}�b�v�̐��i�c�j

#define MAP_YOKO_SIZE	40			//�}�b�v�̑傫���i���j
#define MAP_TATE_SIZE	40			//�}�b�v�̑傫���i�c�j

#define MAP_DATA_KIND	MAP_DATA_YOKO_KIND * MAP_DATA_TATE_KIND	//�}�b�v�f�[�^�̎�ސ�
#define MAP_DATA_YOKO_KIND	2									//�}�b�v�f�[�^�̉������̎�ސ�
#define MAP_DATA_TATE_KIND	2									//�}�b�v�f�[�^�̏c���̎�ސ�

#define MAPPOS_X	MapNowPos[0]						//�}�b�v��X�ʒu
#define MAPPOS_Y	MapNowPos[1]						//�}�b�v��Y�ʒu

#define POS_X	0									//X���W
#define POS_Y	1									//Y���W

#define RECT_STAGGER	4	//�̈�����炷��

//##################### �񋓌^ #########################
enum MAP_KIND
{
	MAP_SOUGEN,				//��}�b�v��
	MAP_2,				//�j�}�b�v��
	MAP_3,				//�O�}�b�v��
	MAP_4				//�l�}�b�v��
};

enum MAP_CHENGE_DIST
{
	MAP_CHENGE_UP,		//��̃}�b�v��
	MAP_CHENGE_DOWN,	//���̃}�b�v��
	MAP_CHENGE_LEFT,	//���̃}�b�v��
	MAP_CHENGE_RIGHT,	//�E�̃}�b�v��
	MAP_CHENGE_NONE = -1//�}�b�v�؂�ւ��Ȃ�
};//�ǂ̕����փ}�b�v�؂�ւ��邩

enum MAP_NG_NUM
{
	MAP_NG_KIND1 =83		//�ʍs�ł��Ȃ��}�b�v�̐���
};

enum MAP_OK_NUM
{
	MAP_OK_KIND1 = 1		//�ʍs�ł���}�b�v�̐���
};

//enum MAPIMAGEKIND
//{
//	FILED		//�t�B�[���h�̃}�b�v�`�b�v�摜
//};

//##################### �N���X��` ###################
class MAP
{
private:
	std::string FilePath;				//�p�X
	std::string FileName;				//���O

	int MapData[MAP_TATE][MAP_YOKO];		//�}�b�v�f�[�^

	IMAGE *Map_Image;		//�}�b�v�摜

	COLLISION *RectOK[MAP_TATE][MAP_YOKO];		//�����蔻��(�ʍs�ł���)
	COLLISION *RectNG[MAP_TATE][MAP_YOKO];		//�����蔻��i�ʍs�ł��Ȃ��j

	FILE *fp_map_csv;						//�}�b�v�t�@�C���̃|�C���^

public :
	
	MAP(const char *,const char *);				//�R���X�g���N�^

	~MAP();				//�f�X�g���N�^

	bool LoadCsv(const char *, const char *);	//csv�f�[�^�ǂݍ���

	int ChengeMap(int,int *);			//�}�b�v��؂�ւ���

	void Draw();		//�`��

	void CreateRect(int *,int *);	//�����蔻��̗̈���쐬

	//�ʍs�ł��Ȃ��̈���擾����
	auto GetRectNG(void)
	{
		return this->RectNG;
	}

};

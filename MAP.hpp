//MAP.hpp
//�}�b�v�N���X

#pragma once

//####################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include "COLLISION.hpp"
#include "IMAGE.hpp"
#include <string>

//###################### �}�N����`�F�t�@�C���p�X�A���O ##################
#define MY_MAP_FIELD_CSV_DIR	R"(.\MY_MAP\map_csv\field\)"	//�}�b�vcsv�̃t�@�C���̏ꏊ(�t�B�[���h)
#define MY_MAP_CITY_CSV_DIR		R"(.\MY_MAP\map_csv\city\)"		//�}�b�v��csv�t�@�C���̏ꏊ(�X)

#define IMG_DIR_MAP_FIELD		R"(.\MY_MAP\map_image\field\)"	//�}�b�v�̉摜�t�@�C���̏ꏊ(�t�B�[���h)
#define IMG_DIR_MAP_CITY		R"(.\MY_MAP\map_image\city\)"	//�}�b�v�̉摜�t�@�C���̏ꏊ(�X)

//�t�B�[���h�}�b�v
#define IMG_NAME_MAP_SOUGEN	R"(sougen.png)"			//�����̉摜�̖��O
#define IMG_NAME_MAP_FOREST	R"(forest.png)"			//�X�̉摜�̖��O
#define IMG_NAME_MAP_OCEAN	R"(ocean.png)"			//�C�̉摜�̖��O
#define IMG_NAME_MAP_SPRING	R"(spring.png)"			//�t�̉摜�̖��O
#define IMG_NAME_MAP_AUTUMN	R"(autumn.png)"			//�H�̉摜�̖��O
#define IMG_NAME_MAP_WINTER	R"(winter.png)"			//�~�̉摜�̖��O
#define IMG_NAME_MAP_REMAINS R"(remains.png)"		//��Ղ̉摜�̖��O
#define IMG_NAME_MAP_CASTLE	R"(castle.png)"			//������̉摜�̖��O

//�X�}�b�v
#define IMG_NAME_MAP_CITY_NW R"(city_NW.png)"			//�X�A�k���̉摜�̖��O
#define IMG_NAME_MAP_CITY_W	 R"(city_W.png)"			//�X�A���̉摜�̖��O
#define IMG_NAME_MAP_CITY_SW R"(city_SW.png)"			//�X�A�쐼�̉摜�̖��O
#define IMG_NAME_MAP_CITY_N	 R"(city_N.png)"			//�X�A�k�̉摜�̖��O
#define IMG_NAME_MAP_CITY_CENTER R"(city_center.png)"	//�X�A�����̉摜�̖��O
#define IMG_NAME_MAP_CITY_S	 R"(city_S.png)"			//�X�A��̉摜�̖��O
#define IMG_NAME_MAP_CITY_NE R"(city_NE.png)"			//�X�A�k���̉摜�̖��O
#define IMG_NAME_MAP_CITY_E	 R"(city_E.png)"			//�X�A���̉摜�̖��O
#define IMG_NAME_MAP_CITY_SE R"(city_SE.png)"			//�X�A�쓌�̉摜�̖��O

#define MY_MAP_TEST3		R"(test_3.png)"			//�e�X�g�p
#define MY_MAP_TEST4		R"(test_4.png)"			//�e�X�g�p

//�t�B�[���h�}�b�v
#define MY_MAP_SOUGEN_ATARI	R"(sougen_atari.csv)"	//�����̓����蔻��
#define MY_MAP_FOREST_ATARI	R"(forest_atari.csv)"	//�X�̓����蔻��
#define MY_MAP_OCEAN_ATARI	R"(ocean_atari.csv)"	//�C�̉摜�̓����蔻��
#define MY_MAP_SPRING_ATARI	R"(spring_atari.csv)"	//�t�̉摜�̓����蔻��
#define MY_MAP_AUTUMN_ATARI	R"(autumn_atari.csv)"	//�H�̉摜�̓����蔻��
#define MY_MAP_WINTER_ATARI	R"(winter_atari.csv)"	//�~�̉摜�̓����蔻��
#define MY_MAP_REMAINS_ATARI R"(remains_atari.csv)"	//��Ղ̉摜�̓����蔻��
#define MY_MAP_CASTLE_ATARI	R"(castle_atari.csv)"	//������̉摜�̓����蔻��

//�X�̃}�b�v
#define MY_MAP_CITY_NW_ATARI R"(city_NW_atari.csv)"	//�X�A�k���̓����蔻��
#define MY_MAP_CITY_W_ATARI R"(city_W_atari.csv)"	//�X�A���̓����蔻��
#define MY_MAP_CITY_SW_ATARI R"(city_SW_atari.csv)"	//�X�A�쐼�̓����蔻��
#define MY_MAP_CITY_N_ATARI R"(city_N_atari.csv)"	//�X�A�k�̓����蔻��
#define MY_MAP_CITY_CENTER_ATARI R"(city_center_atari.csv)"	//�X�A�����̓����蔻��
#define MY_MAP_CITY_S_ATARI	 R"(city_S_atari.csv)"	//�X�A��̓����蔻��
#define MY_MAP_CITY_NE_ATARI R"(city_NE_atari.csv)"	//�X�A�k���̓����蔻��
#define MY_MAP_CITY_E_ATARI R"(city_E_atari.csv)"	//�X�A���̓����蔻��
#define MY_MAP_CITY_SE_ATARI R"(city_SE_atari.csv)"	//�X�A�쓌�̓����蔻��

#define MY_MAP_TEST3_ATARI	R"(test3_atari.csv)"
#define MY_MAP_TEST4_ATARI	R"(test4_atari.csv)"


#define MAP_NG_KIND		1	//�ʍs�ł��Ȃ��}�b�v�̎��
#define MAP_OK_KIND		1	//�ʍs�ł���}�b�v�̎��
#define MAP_ENCOUNT_KIND 1	//�G�Ƒ�������}�b�v�̎��

//##################### �}�N����`�F�G���[���b�Z�[�W ####################

//##################### �}�N����` ########################
#define MAP_YOKO		55			//�}�b�v�̐��i���j
#define MAP_TATE		40			//�}�b�v�̐��i�c�j

#define MAP_YOKO_SIZE	16			//�}�b�v�̑傫���i���j
#define MAP_TATE_SIZE	16			//�}�b�v�̑傫���i�c�j

#define MAP_DATA_KIND	MAP_DATA_YOKO_KIND * MAP_DATA_TATE_KIND	//�}�b�v�f�[�^�̎�ސ�
#define MAP_DATA_YOKO_KIND	3									//�}�b�v�f�[�^�̉������̎�ސ�
#define MAP_DATA_TATE_KIND	3									//�}�b�v�f�[�^�̏c���̎�ސ�

#define MAPPOS_X	MapNowPos[0]						//�}�b�v��X�ʒu
#define MAPPOS_Y	MapNowPos[1]						//�}�b�v��Y�ʒu

#define POS_X	0									//X���W
#define POS_Y	1									//Y���W

#define RECT_STAGGER	4	//�̈�����炷��

//##################### �񋓌^ #########################
enum MAP_FIELD_KIND
{
	MAP_SOUGEN,				//��}�b�v��(����)
	MAP_FOREST,				//�j�}�b�v��(�X)
	MAP_OCEAN,				//�O�}�b�v��(�C)
	MAP_AUTUMN,				//�l�}�b�v��(�H)
	MAP_CITY,				//�܃}�b�v��(�X�A��)
	MAP_SPRING,				//�Z�}�b�v��(�t)
	MAP_WINTER,				//���}�b�v��(�~)
	MAP_REMAINS,			//���}�b�v��(���)
	MAP_CASTLE				//��}�b�v��(������)
};//�t�B�[���h�}�b�v�̎��

enum MAP_CITY_KIND
{
	MAP_CITY_NW,			//��}�b�v�ځi�k���j
	MAP_CITY_W,				//��}�b�v�ځi���j
	MAP_CITY_SW,			//�O�}�b�v�ځi�쐼�j
	MAP_CITY_N,				//�l�}�b�v�ځi�k�j
	MAP_CITY_CNETER,		//�܃}�b�v�ځi�����j
	MAP_CITY_S,				//�Z�}�b�v�ځi��j
	MAP_CITY_NE,			//���}�b�v�ځi�k���j
	MAP_CITY_E,				//���}�b�v�ځi���j
	MAP_CITY_SE				//��}�b�v�ځi�쓌)
};//�X�}�b�v�̎��

enum MAP_CHENGE_DIST
{
	MAP_CHENGE_UP,		//��̃}�b�v��
	MAP_CHENGE_DOWN,	//���̃}�b�v��
	MAP_CHENGE_LEFT,	//���̃}�b�v��
	MAP_CHENGE_RIGHT,	//�E�̃}�b�v��
	MAP_CHENGE_NONE = -1//�}�b�v�؂�ւ��Ȃ�
};//�ǂ̕����փ}�b�v�؂�ւ��邩

enum MAP_NUM_KIND
{
	MAP_NG,			//�ʍs�ł��Ȃ�
	MAP_OK,			//�ʍs�ł���
	MAP_ENCOUNT		//�ʍs�ł���(�G�Ƒ�������)
};

enum MAP_NG_NUM
{
	MAP_NG_KIND1 =101		//�ʍs�ł��Ȃ��}�b�v�̐���
};

enum MAP_OK_NUM
{
	MAP_OK_KIND1 = 51			//�ʍs�ł���}�b�v(�G�Ƒ������Ȃ�)
};
enum MAP_ENCOOUNT_NUM
{
	MAP_OK_KIND_ENCOUNT = 151	//�ʍs�ł���}�b�v(�G�Ƒ�������)
};

//enum MAPIMAGEKIND
//{
//	FILED		//�t�B�[���h�̃}�b�v�`�b�v�摜
//};

//##################### �O���[�o���ϐ� #################

//##################### �N���X��` ###################
class MAP
{
private:
	std::string FilePath;				//�p�X
	std::string FileName;				//���O

	int MapData[MAP_TATE][MAP_YOKO];		//�}�b�v�f�[�^

	IMAGE *Map_Image;		//�}�b�v�摜

	COLLISION *RectOK[MAP_TATE][MAP_YOKO];		//�����蔻��(�ʍs�ł���)
	COLLISION *RectEncount[MAP_TATE][MAP_YOKO];	//�����蔻��(�G�Ƒ�������)
	COLLISION *RectNG[MAP_TATE][MAP_YOKO];		//�����蔻��i�ʍs�ł��Ȃ��j

	FILE *fp_map_csv;						//�}�b�v�t�@�C���̃|�C���^

	int MapNGKind[MAP_NG_KIND];				//�ʍs�ł��Ȃ��}�b�v�̎��
	int MapOKKind[MAP_OK_KIND];				//�ʍs�ł���}�b�v�̎��
	int MapEncountKind[MAP_ENCOUNT_KIND];	//�G�Ƒ�������}�b�v�̎��

public :
	
	MAP(const char *,const char *);				//�R���X�g���N�^

	~MAP();				//�f�X�g���N�^

	bool LoadCsv(const char *, const char *);	//csv�f�[�^�ǂݍ���

	int ChengeMap(int,int *);			//�}�b�v��؂�ւ���

	void Draw();		//�`��

	void CreateRect();	//�����蔻��̗̈���쐬

	//�w�肳�ꂽ�̈���擾����
	auto GetRect(int kind)
	{
		switch (kind)
		{

		case (int)MAP_NG:		//�ʍs�ł��Ȃ���
			
			return this->RectNG;

			break;

		case (int)MAP_OK:		//�ʍs�ł���Ƃ�

			return this->RectOK;

			break;

		case (int)MAP_ENCOUNT:	//�G�Ƒ�������Ƃ�

			return this->RectEncount;

			break;

		default:
			break;
		}
	}

};

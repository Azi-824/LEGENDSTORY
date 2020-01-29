//EFFECT.hpp
//�G�t�F�N�g�N���X

#pragma once

//###################### �w�b�_�t�@�C���ǂݍ��� #########################
#include "DxLib.h"
#include <vector>
#include <string>
#include "FPS.hpp"
#include "main.hpp"

//###################### �}�N����`�F�t�@�C���p�X�A���O ######################
#define MY_ANIME_DIR_ATKEFECT	R"(.\MY_ANIME\atack\)"			//�U���G�t�F�N�g�̉摜�t�@�C���̏ꏊ
#define MY_ANIME_DIR_MAGIC		R"(.\MY_ANIME\magic\)"			//���@�G�t�F�N�g�̉摜�t�@�C���̏ꏊ

#define MY_ANIME_NAME_ATKEFECT	R"(atack.png)"					//�U���G�t�F�N�g�̉摜�̖��O
#define MY_ANIME_NAME_MAGIC		R"(magic.png)"					//���@�G�t�F�N�g�̉摜�̖��O
#define MY_ANIME_NAME_MAGIC2	R"(magic2.png)"					//���@�G�t�F�N�g2�̉摜�̖��O

//###################### �}�N����`�F�G���[���b�Z�[�W ########################
#define EFFECT_ERROR_TTILE	"EFFECT_ERROR"						//�G���[�^�C�g��
#define EFFECT_ERROR_MSG	"�G�t�F�N�g���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//###################### �}�N����` #################################
#define ATK_WIDTH		120	//�������镝�̑傫��
#define ATK_HEIGHT		120	//�������鍂���̑傫��
#define MAGIC_WIDTH		880	//�������镝�̑傫��
#define MAGIC_HEIGHT	640	//�������鍂���̑傫��

#define ATK_YOKO_CNT	9
#define ATK_TATE_CNT	1
#define MAGIC_YOKO_CNT	1
#define MAGIC_TATE_CNT	12
#define MAGIC2_YOKO_CNT	5
#define MAGIC2_TATE_CNT	5

#define ATK_ALL_CNT	ATK_YOKO_CNT * ATK_TATE_CNT
#define MAGIC_ALL_CNT MAGIC_YOKO_CNT * MAGIC_TATE_CNT
#define MAGIC2_ALL_CNT	MAGIC2_YOKO_CNT * MAGIC2_TATE_CNT

#define ATK_SPEED		 0.02
#define MAGIC_SPEED		 0.02

#define ATK_DRAW_X		375
#define ATK_DRAW_Y		290

#define MAGIC_EFFECT_KIND		2			//���@�G�t�F�N�g�̎��
#define ATACK_EFFECT_KIND		1			//�U���G�t�F�N�g�̎��

//###################### �񋓌^ ##########################
enum MAGIC_EFFECT_TYPE
{
	MAGIC_1,			//���@�P
	MAGIC_2				//���@�Q
};

enum ATACK_EFFECT_TYPE
{
	NOMAL_ATACK		//�ʏ�U��
};

//###################### �N���X��` ################################
class EFFECT
{
private:

	std::vector<std::vector<int>> Handle;							//�n���h��
	std::vector<int>::iterator Handle_itr;				//�n���h���̃C�e���[�^
	
	std::vector<int> Width;				//��
	std::vector<int> Height;			//����

	double NextChangeSpeed;			//�A�j���[�V������ύX���鑬��(�b)
	int ChangeCnt;					//�A�j���[�V��������t���[���̃J�E���g
	int ChangeMaxCnt;				//�A�j���[�V��������t���[���̍ő�l

	std::vector<bool> IsAnimeLoop;			//�A�j���[�V�����̓��[�v����H
	std::vector<bool> IsAnimeStop;			//�A�j���[�V�����̓X�g�b�v�������H

	bool IsDrawEnd;				//�`��I��������

	bool IsLoad;				//�ǂݍ��߂����H

public:

	EFFECT(const char *, const char *, int, int, int, int, int, double, bool);	//�R���X�g���N�^	

	~EFFECT();					//�f�X�g���N�^

	int GetWidth(int);				//�����擾
	int GetHeight(int);			//�������擾

	bool GetIsLoad(void);			//�ǂݍ��߂��H

	bool GetIsAnimeStop(int);		//�A�j���[�V�����̓X�g�b�v���������擾

	bool GetIsDrawEnd();		//�`��I���������擾

	void SetIsDrawEnd(bool);	//�`��I���������ݒ�

	void ResetIsAnime(int);		//�A�j���[�V�������X�g�b�v�����������Z�b�g

	void Draw(int, int,int);			//�`��

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int);	//�G�t�F�N�g�ǉ�

};

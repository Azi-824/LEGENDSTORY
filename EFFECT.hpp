//EFFECT.hpp
//�G�t�F�N�g�N���X

/*
�G�t�F�N�g�ǉ����@
�E��{�́AANIMATION�N���X�Ɠ���
�E�I�u�W�F�N�g������́AAdd�������g�p���邱�ƂŁA�G�t�F�N�g�̒ǉ������邱�Ƃ��ł���
*/

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
#define MY_ANIME_DIR_ENE_ATK	R"(.\MY_ANIME\enemy_atack\)"	//�G�̍U���G�t�F�N�g�̉摜�̃t�@�C���ꏊ
#define MY_ANIME_DIR_BOSS_ATK	R"(.\MY_ANIME\boss_atack\)"		//�{�X�̍U���G�t�F�N�g�̉摜�̃t�@�C���ꏊ

#define MY_ANIME_NAME_ATKEFECT	R"(atack.png)"					//�U���G�t�F�N�g�̉摜�̖��O
#define MY_ANIME_NAME_MAGIC		R"(magic.png)"					//���@�G�t�F�N�g�̉摜�̖��O
#define MY_ANIME_NAME_MAGIC2	R"(magic2.png)"					//���@�G�t�F�N�g2�̉摜�̖��O

#define MY_ANIME_NAME_ENE_ATK_TUME	R"(tume.png)"				//�G�̍U���i�܁j�̃G�t�F�N�g�摜�̖��O
#define MY_ANIME_NAME_ENE_ATK_KIBA	R"(kiba.png)"				//�G�̍U���i��j�̃G�t�F�N�g�摜�̖��O
#define MY_ANIME_NAME_ENE_ATK_TAIL_BIG	R"(tail_big.png)"		//�G�̍U���i�K����j�̃G�t�F�N�g�摜�̖��O

#define MY_ANIME_NAME_BOSS_ATK_LASER	R"(boss_laser.png)"			//���[�U�[�̃G�t�F�N�g�摜�̖��O
#define MY_ANIME_NAME_BOSS_ATK_TOGE		R"(boss_toge.png)"			//�Ƃ��̃G�t�F�N�g�摜�̖��O

//###################### �}�N����`�F�G���[���b�Z�[�W ########################
#define EFFECT_ERROR_TTILE	"EFFECT_ERROR"						//�G���[�^�C�g��
#define EFFECT_ERROR_MSG	"�G�t�F�N�g���ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//###################### �}�N����` #################################

//********************** �T�C�Y ************************
//�U��
#define ATK_WIDTH		120	//�������镝�̑傫��
#define ATK_HEIGHT		120	//�������鍂���̑傫��
//���@
#define MAGIC_WIDTH		880	//�������镝�̑傫��
#define MAGIC_HEIGHT	640	//�������鍂���̑傫��
//�G�̍U��
#define ENE_ATK_TUME_WIDTH	240	//������
#define ENE_ATK_TUME_HEIGHT	240	//��������
#define ENE_ATK_KIBA_WIDTH	240	//������
#define ENE_ATK_KIBA_HEIGHT	240	//��������
#define ENE_ATK_TAIL_BIG_WIDTH 880	//������
#define ENE_ATK_TAIL_BIG_HEIGHT	640	//��������
//�{�X
#define BOSS_ATK_LEASER_WIDTH	880	//������
#define BOSS_ATK_LEASER_HEIGHT	640	//��������
#define BOSS_ATK_TOGE_WIDTH		880	//������
#define BOSS_ATK_TOGE_HEIGT		640	//��������


//********************** ������ **************************
//�U��
#define ATK_YOKO_CNT	9
#define ATK_TATE_CNT	1
//���@
#define MAGIC_YOKO_CNT	1
#define MAGIC_TATE_CNT	12
#define MAGIC2_YOKO_CNT	5
#define MAGIC2_TATE_CNT	5
//�G�̍U��
#define ENE_ATK_TUME_YOKO_CNT 5	//��������
#define ENE_ATK_TUME_TATE_CNT 2	//�c������
#define ENE_ATK_KIBA_YOKO_CNT 5	//��������
#define ENE_ATK_KIBA_TATE_CNT 2	//�c������
#define ENE_ATK_TAIL_BIG_YOKO_CNT	5	//��������
#define ENE_ATK_TAIL_BIG_TATE_CNT	2	//�c������
//�{�X
#define	BOSS_ATK_LEASER_YOKO_CNT	3	//��������
#define BOSS_ATK_LEASER_TATE_CNT	10	//�c������
#define BOSS_ATK_TOGE_YOKO_CNT		3	//��������
#define BOSS_ATK_TOGE_TATE_CNT		6	//�c������


//************************ �������� **************************
//�U��
#define ATK_ALL_CNT	ATK_YOKO_CNT * ATK_TATE_CNT
//���@
#define MAGIC_ALL_CNT MAGIC_YOKO_CNT * MAGIC_TATE_CNT
#define MAGIC2_ALL_CNT	MAGIC2_YOKO_CNT * MAGIC2_TATE_CNT
//�G�̍U��
#define ENE_ATK_TUME_ALL_CNT 8	//��������
#define ENE_ATK_KIBA_ALL_CNT 8	//��������
#define ENE_ATK_TAIL_BIG_ALL_CNT ENE_ATK_TAIL_BIG_YOKO_CNT * ENE_ATK_TAIL_BIG_TATE_CNT	//��������
//�{�X
#define BOSS_ATK_LEASER_ALL_CNT	BOSS_ATK_LEASER_YOKO_CNT * BOSS_ATK_LEASER_TATE_CNT	//��������
#define BOSS_ATK_TOGE_ALL_CNT	BOSS_ATK_TOGE_YOKO_CNT * BOSS_ATK_TOGE_TATE_CNT		//��������

//************************ �`�摬�x ***************************
//�U��
#define ATK_SPEED		 0.02
//���@
#define MAGIC_SPEED		 0.02
//�G�̍U��
#define ENE_ATK_TUME_SPEED	0.05
#define ENE_ATK_KIBA_SPEED	0.05
#define ENE_ATK_TAIL_BIG_SPEED	0.05
//�{�X
#define BOSS_ATK_LEASER_SPEED	0.02
#define BOSS_ATK_TOGE_SPEED		0.02


#define ATK_DRAW_X		375
#define ATK_DRAW_Y		290

#define MAGIC_EFFECT_KIND		2			//���@�G�t�F�N�g�̎��
#define ATACK_EFFECT_KIND		1			//�U���G�t�F�N�g�̎��
#define ENE_ATK_EFFECT_KIND		3			//�G�U���G�t�F�N�g�̎��
#define BOSS_ATK_EFFECT_KIND	2			//�{�X�̍U���G�t�F�N�g�̎��

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

enum ENEMY_ATACK_EFFECT_TYPE
{
	ENE_ATK_TUME,		//�܍U��
	ENE_ATK_KIBA,		//��U��
	ENE_ATK_TAIL_BIG	//�K���i��j�U��
};
enum BOSS_ATACK_EFFECT_TYPE
{
	BOSS_ATK_LEASER,		//���[�U�[
	BOSS_ATK_TOGE			//�Ƃ��@
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

	EFFECT(const char *, const char *, int, int, int, int, int, double, bool,int);	//�R���X�g���N�^	

	~EFFECT();					//�f�X�g���N�^

	int GetWidth(int);				//�����擾
	int GetHeight(int);			//�������擾

	bool GetIsLoad(void);			//�ǂݍ��߂��H

	bool GetIsAnimeStop(int);		//�A�j���[�V�����̓X�g�b�v���������擾

	bool GetIsDrawEnd();		//�`��I���������擾

	void SetIsDrawEnd(bool);	//�`��I���������ݒ�

	void ResetIsAnime(int);		//�A�j���[�V�������X�g�b�v�����������Z�b�g

	void Draw(int, int,int);			//�`��
	void DrawNormal(int, int, int);			//�`��(�t�F�[�h�A�E�g�Ȃ�)

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int);	//�G�t�F�N�g�ǉ�

	void SetSize();				//�T�C�Y�ݒ�

};

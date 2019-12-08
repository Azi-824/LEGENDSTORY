/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
/* ANIMATION.hpp     																			�@ */
/* �A�j���[�V�����N���X 																		�@ */

#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"
#include <string>
#include <vector>

#include "FPS.hpp"

//########## �}�N����`�F�摜�̃t�@�C���p�X�Ɩ��O ##########
#define MY_ANIME_DIR_PLAYER		R"(.\MY_ANIME\walk\)"			//�v���C���[�̉摜�t�@�C���̏ꏊ
#define MY_ANIME_DIR_ATKEFECT	R"(.\MY_ANIME\atack\)"			//�U���G�t�F�N�g�̉摜�t�@�C���̏ꏊ
#define MY_ANIME_DIR_MAGIC		R"(.\MY_ANIME\magic\)"			//���@�G�t�F�N�g�̉摜�t�@�C���̏ꏊ

#define MY_ANIME_NAME_PLAYER	R"(player_walk.png)"			//�v���C���[�̉摜�̖��O
#define MY_ANIME_NAME_ATKEFECT	R"(atack.png)"					//�U���G�t�F�N�g�̉摜�̖��O
#define MY_ANIME_NAME_MAGIC		R"(magic.png)"					//���@�G�t�F�N�g�̉摜�̖��O
#define MY_ANIME_NAME_MAGIC2	R"(magic2.png)"					//���@�G�t�F�N�g2�̉摜�̖��O

#define PLAYER_WIDTH	45	//�������镝�̑傫��
#define PLAYER_HEIGHT	45	//�������鍂���̑傫��
#define ATK_WIDTH		120	//�������镝�̑傫��
#define ATK_HEIGHT		120	//�������鍂���̑傫��
#define MAGIC_WIDTH		640	//�������镝�̑傫��
#define MAGIC_HEIGHT	480	//�������鍂���̑傫��

#define PLAYER_YOKO_CNT	3
#define PLAYER_TATE_CNT	4
#define ATK_YOKO_CNT	9
#define ATK_TATE_CNT	1
#define MAGIC_YOKO_CNT	1
#define MAGIC_TATE_CNT	12
#define MAGIC2_YOKO_CNT	5
#define MAGIC2_TATE_CNT	5

#define PLAYER_ALL_CNT	PLAYER_YOKO_CNT * PLAYER_TATE_CNT
#define ATK_ALL_CNT	ATK_YOKO_CNT * ATK_TATE_CNT
#define MAGIC_ALL_CNT MAGIC_YOKO_CNT * MAGIC_TATE_CNT
#define MAGIC2_ALL_CNT	MAGIC2_YOKO_CNT * MAGIC2_TATE_CNT

#define PLAYER_ANI_SPEED 1.0
#define ATK_SPEED		 0.02
#define MAGICN_SPEED	 0.05

//########## �}�N����`�F�G���[���b�Z�[�W##########
#define ANIMATION_ERROR_TTILE	"ANIMATION_ERROR"						//�G���[�^�C�g��
#define ANIMATION_ERROR_MSG		"�A�j���[�V�������ǂݍ��߂܂���ł���"	//�G���[���b�Z�[�W

//########## �񋓌^ ############
enum DIST {
	FLONT=0,	//�O����
	LEFT=3,		//������
	RIGHT=6,	//�E����
	BACK=9		//������
};

//########## �N���X�̒�` ##########
class ANIMATION
{
private:
	std::string FilePath;	//�p�X
	std::string FileName;	//���O

	std::vector<int> Handle;				//�n���h��
	std::vector<int>::iterator Handle_itr;	//�n���h���̃C�e���[�^(�|�C���^)

	int Width;					//��
	int Height;					//����

	double NextChangeSpeed;		//�A�j���[�V������ύX���鑬��(�b)
	int ChangeMaxCnt;			//�A�j���[�V��������t���[���̍ő�l
	int ChangeCnt;				//�A�j���[�V��������t���[���̃J�E���g
	int ChangeCntNow;			//�`�F���W�J�E���g
	int ChangeCntMax;			//�`�F���W�J�E���g�ő�l

	double EffectNextChangeSpeed;	//�A�j���[�V������ύX���鑬��(�b)
	int EffectChangeCnt;			//�A�j���[�V��������t���[���̃J�E���g
	int EffectChangeMaxCnt;			//�A�j���[�V��������t���[���̍ő�l

	bool IsAnimeLoop;			//�A�j���[�V�����̓��[�v����H
	bool IsAnimeStop;			//�A�j���[�V�����̓X�g�b�v�������H

	bool IsLoad;				//�ǂݍ��߂����H
	
public:
	ANIMATION(const char *, const char *, int, int, int, int, int, double,bool);	//�R���X�g���N�^
	virtual ~ANIMATION();	//�f�X�g���N�^

	std::string GetFileName(void);	//���O���擾

	int GetWidth(void);				//�����擾
	int GetHeight(void);			//�������擾

	bool GetIsLoad(void);			//�ǂݍ��߂��H

	bool GetIsAnimeStop(void);		//�A�j���[�V�����̓X�g�b�v���������擾

	void ResetIsAnime(void);		//�A�j���[�V�������X�g�b�v�����������Z�b�g

	void Draw(int,int,int,bool);	//�摜��`��

	void DrawEffect(int, int);		//�G�t�F�N�g��`��
};


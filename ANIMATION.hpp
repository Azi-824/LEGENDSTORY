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
#define TXT_POSE_DIR			R"(.\MY_ANIME\Ui\)"				//UI�̉摜�t�@�C���̏ꏊ

#define MY_ANIME_NAME_PLAYER	R"(player_walk.png)"			//�v���C���[�̉摜�̖��O
#define TXT_POSE_NAME			R"(txtpose.png)"				//�e�L�X�g�|�[�Y�̉摜�̖��O

#define PLAYER_WIDTH	45	//�������镝�̑傫��
#define PLAYER_HEIGHT	45	//�������鍂���̑傫��

#define TXT_POSE_WIDTH	30	//��������
#define TXT_POSE_HEIGHT	16	//������

#define PLAYER_YOKO_CNT	3
#define PLAYER_TATE_CNT	4
#define TXT_POSE_YOKO_CNT	1
#define TXT_POSE_TATE_CNT	6

#define PLAYER_ALL_CNT	PLAYER_YOKO_CNT * PLAYER_TATE_CNT
#define	TXT_POSE_ALL_CNT TXT_POSE_YOKO_CNT * TXT_POSE_TATE_CNT

#define PLAYER_ANI_SPEED 1.0
#define TXT_POSE_SPEED	10.0

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

	std::vector<std::vector<int>> Handle;				//�n���h��
	std::vector<int>::iterator Handle_itr;	//�n���h���̃C�e���[�^(�|�C���^)

	std::vector<int> Width;					//��
	std::vector<int> Height;				//����

	std::vector<double> NextChangeSpeed;	//�A�j���[�V������ύX���鑬��(�b)
	std::vector<int> ChangeMaxCnt;			//�A�j���[�V��������t���[���̍ő�l
	std::vector<int> ChangeCnt;				//�A�j���[�V��������t���[���̃J�E���g
	std::vector<int> ChangeCntNow;			//�`�F���W�J�E���g

	std::vector<bool> IsAnimeLoop;			//�A�j���[�V�����̓��[�v����H
	std::vector<bool> IsAnimeStop;			//�A�j���[�V�����̓X�g�b�v�������H

	bool IsLoad;				//�ǂݍ��߂����H
	
public:
	ANIMATION(const char *, const char *, int, int, int, int, int, double,bool,int size=1);	//�R���X�g���N�^
	virtual ~ANIMATION();	//�f�X�g���N�^

	std::string GetFileName(void);	//���O���擾

	int GetWidth(int=0);				//�����擾
	int GetHeight(int=0);			//�������擾

	bool GetIsLoad();			//�ǂݍ��߂��H

	bool GetIsAnimeStop(int=0);		//�A�j���[�V�����̓X�g�b�v���������擾

	void ResetIsAnime(int=0);		//�A�j���[�V�������X�g�b�v�����������Z�b�g

	void Draw(int,int,int,bool,int=0);	//�摜��`��

	void DrawAnime(int, int,int=0);		//�A�j���[�V�����`��

	bool Add(const char *, const char *, int, int, int, int, int, double, bool, int = 0);	//�A�j���[�V�����ǉ�

};


//MUSIC.hpp
//���y�p�N���X

#pragma once

//##################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include <string>
#include <vector>

//##################### �}�N����`�F�t�@�C���p�X�A���O ###################
#define MY_MUSIC_DIR_BGM	R"(.\MY_MUSIC\BGM)"		//BGM�̃t�@�C����
#define MY_MUSIC_DIR_SE		R"(.\MY_MUSIC\SE)"		//SE�̃t�@�C����

#define MY_MUSIC_NAME_BGM	R"(\bgm_op.mp3)"		//BGM�̖��O
#define MY_SE_NAME_LEVUP	R"(\levelup.mp3)"		//SE�i���x���A�b�v�j�̖��O
#define MY_SE_NAME_SLASH	R"(\slash.mp3)"			//�a��Ƃ��̉��̖��O

//##################### �}�N����`�F�G���[���b�Z�[�W ######################
#define MUSIC_ERROR_TITLE "MUSIC_ERROR"					//�G���[�^�C�g��
#define MUSIC_ERROR_MSG	"�����ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//##################### �}�N����` ##########################
#define BGM_KIND	1	//BGM�̎��
#define BT_SE_KIND	2	//�o�g���Ŏg�p����SE�̎��

//##################### �񋓌^ #########################
enum BGM_TYPE
{
	TITLE_BGM		//�^�C�g����ʂ�BGM
};

enum BT_SE_TYPE
{
	BT_SE_LEVELUP,		//���x���A�b�v��SE
	BT_SE_SLASH			//�a��Ƃ��̉�
};

//##################### �N���X��` ############################
class MUSIC
{
private:

	std::string FilePath;		//�t�@�C���p�X
	std::string FileName;		//���O

	std::vector<int> Handle;	//�n���h��
	int PlayType;				//���̍Đ����@

	bool IsLoad;				//�ǂݍ��߂���
	std::vector<bool> IsPlay;	//�Đ�����

	std::vector<bool>IsPlayed;	//�Đ��ς݂�

public:

	MUSIC(const char *, const char *,int);		//�R���X�g���N�^

	~MUSIC();								//�f�X�g���N�^

	bool GetIsLoad();						//�ǂݍ��߂������擾����
	bool GetIsPlay(int );					//�����Đ�����Ă��邩�擾����

	void ChengePlayType(int);				//���̍Đ����@��ύX����

	void ChengeVolume(int,int);				//���ʂ�ύX����

	void Play(int);							//�����Đ�����

	bool Add(const char*, const char*, int);	//����ǉ�����

	void SetIsPlayed(int,bool);				//�Đ��ς݂��ݒ�

	bool GetIsPlayed(int);					//�Đ��ς݂��擾

	void Reset(void);						//�Đ���ԃ��Z�b�g

};

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
#define MY_SE_NAME_LEVUP	R"(\LevelUp.mp3)"		//SE�i���x���A�b�v�j�̖��O

//##################### �}�N����`�F�G���[���b�Z�[�W ######################
#define MUSIC_ERROR_TITLE "MUSIC_ERROR"					//�G���[�^�C�g��
#define MUSIC_ERROR_MSG	"�����ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//##################### �}�N����` ##########################
#define BGM_KIND	1	//BGM�̎��
#define SE_KIND		1	//SE�̎��

//##################### �񋓌^ #########################
enum BGM_TYPE
{
	TITLE_BGM		//�^�C�g����ʂ�BGM
};

enum SE_TYPE
{
	LEVELUP_SE		//���x���A�b�v��SE
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

public:

	MUSIC(const char *, const char *,int);		//�R���X�g���N�^

	~MUSIC();								//�f�X�g���N�^

	bool GetIsLoad();						//�ǂݍ��߂������擾����
	bool GetIsPlay(int );					//�����Đ�����Ă��邩�擾����

	void ChengePlayType(int);				//���̍Đ����@��ύX����

	void ChengeVolume(int,int);				//���ʂ�ύX����

	void Play(int);							//�����Đ�����

	bool Add(const char*, const char*, int);	//����ǉ�����

};

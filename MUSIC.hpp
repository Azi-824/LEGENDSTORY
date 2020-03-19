//MUSIC.hpp
//���y�p�N���X

#pragma once

//##################### �w�b�_�t�@�C���ǂݍ��� #######################
#include "DxLib.h"
#include <string>
#include <vector>

//##################### �}�N����`�F�t�@�C���p�X�A���O ###################
#define MY_MUSIC_DIR_BGM	R"(.\MY_MUSIC\BGM)"		  //BGM�̃t�@�C����
#define MY_MUSIC_DIR_BT_SE	R"(.\MY_MUSIC\SE\battle)" //�퓬��SE�̃t�@�C����
#define MY_MUSIC_DIR_SYS_SE	R"(.\MY_MUSIC\SE\system)" //�V�X�e����SE�̃t�@�C����
//BGM
#define MY_BGM_NAME_TITLE	R"(\bgm_op.mp3)"		//BGM�̖��O
#define MY_BGM_NAME_FIELD	R"(\field.mp3)"			//�t�B�[���h��BGM�̖��O
#define MY_BGM_NAME_CITY	R"(\city.mp3)"			//�X��BGM�̖��O
#define MY_BGM_NAME_BATTLE	R"(\battle.mp3)"		//�퓬��ʂ�BGM�̖��O
#define MY_BGM_NAME_END		R"(\end.mp3)"			//�G���h��ʂ�BGM�̖��O
//�o�g��SE
#define MY_SE_NAME_LEVUP	R"(\levelup.mp3)"		//SE�i���x���A�b�v�j�̖��O
#define MY_SE_NAME_SLASH	R"(\slash.mp3)"			//�a��Ƃ��̉��̖��O
#define MY_SE_NAME_THUNDER	R"(\thunder.mp3)"		//���̉��̖��O
#define MY_SE_NAME_NIGERU	R"(\nigeru.mp3)"		//������Ƃ��̉��̖��O
#define MY_SE_NAME_DAMEGE	R"(\damege.wav)"		//�_���[�W�̉��̖��O
#define MY_SE_NAME_RECOVERY R"(\bt_recovery.wav)"	//�o�g���ł̉񕜉��̖��O
//�V�X�e��SE
#define MY_SE_NAME_CURSOR	R"(\select.mp3)"		//�J�[�\���̈ړ����̖��O
#define MY_SE_NAME_CANSEL	R"(\cancel.wav)"		//�L�����Z�����̖��O
#define MY_SE_NAME_KETTEI	R"(\kettei.mp3)"		//����̉��̖��O
#define MY_SE_NAME_MENU		R"(\menu.mp3)"			//���j���[���J�������̉�
#define MY_SE_NAME_ENCOUNT	R"(\encount.mp3)"		//�G�Ƒ����������̉�
#define MY_SE_NAME_SAVE		R"(\save.wav)"			//�Z�[�u��
#define MY_SE_NAME_BLIP		R"(\blip.mp3)"			//�I���ł��Ȃ��Ƃ��̉�
#define MY_SE_NAME_ITEM		R"(\item.wav)"			//�A�C�e�����g�p�������̉�
#define MY_SE_NAME_EQUIP	R"(\equip.wav)"			//�����������̉�
#define MY_SE_NAME_LOAD		R"(\load.wav)"			//���[�h�������̉�

//##################### �}�N����`�F�G���[���b�Z�[�W ######################
#define MUSIC_ERROR_TITLE "MUSIC_ERROR"					//�G���[�^�C�g��
#define MUSIC_ERROR_MSG	"�����ǂݍ��߂܂���ł���"		//�G���[���b�Z�[�W

//##################### �}�N����` ##########################

//##################### �񋓌^ #########################
enum BGM_TYPE
{
	BGM_TITLE,		//�^�C�g����ʂ�BGM
	BGM_FIELD,		//�t�B�[���h��BGM
	BGM_CITY,		//�X��BGM
	BGM_BATTLE,		//�퓬��ʂ�BGM
	BGM_END			//�G���h��ʂ�BGM
};

enum BT_SE_TYPE
{
	BT_SE_LEVELUP,		//���x���A�b�v��SE
	BT_SE_SLASH,		//�a��Ƃ��̉�
	BT_SE_THUNDER,		//���̉�
	BT_SE_NIGERU,		//�����鎞�̉�
	BT_SE_DAMEGE,		//�_���[�W��
	BT_SE_RECOVERY		//�o�g���ł̉񕜉�
};

enum SYS_SE_TYPE
{
	SYS_SE_CURSOR,		//�J�[�\���̈ړ���
	SYS_SE_CANSEL,		//�L�����Z����
	SYS_SE_KETTEI,		//���艹
	SYS_SE_MENU,		//���j���[���J�������̉�
	SYS_SE_ENCOUNT,		//�G�Ƒ����������̉�
	SYS_SE_SAVE,		//�Z�[�u��
	SYS_SE_BLIP,		//�I���ł��Ȃ����̉�
	SYS_SE_ITEM,		//�A�C�e�����g�p�������̉�
	SYS_SE_EQUIP,		//�����������̉�
	SYS_SE_LOAD			//���[�h�������̉�
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

	MUSIC(const char *, const char *);		//�R���X�g���N�^

	~MUSIC();								//�f�X�g���N�^

	bool GetIsLoad();						//�ǂݍ��߂������擾����
	bool GetIsPlay(int );					//�����Đ�����Ă��邩�擾����

	void ChengePlayType(int);				//���̍Đ����@��ύX����

	void ChengeVolume(int,int);				//���ʂ�ύX����

	void Play(int);							//�����Đ�����

	void Stop();							//�����~�߂�(�S��)
	void Stop(int);							//�����~�߂�(�w�肳�ꂽ���̂���)

	bool Add(const char*, const char*);//����ǉ�����

	void SetIsPlayed(int,bool);				//�Đ��ς݂��ݒ�

	bool GetIsPlayed(int);					//�Đ��ς݂��擾

	void Reset(void);						//�Đ���ԃ��Z�b�g

};

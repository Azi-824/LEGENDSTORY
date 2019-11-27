//MUSIC.cpp
//���y�p�N���X

//################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "MUSIC.hpp"

//################## �N���X��` ###########################

//�R���X�g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
MUSIC::MUSIC(const char *dir, const char *name)
{
	//�����o�ϐ���������
	this->FilePath = "";	//�p�X
	this->FileName = "";	//���O

	this->Handle = -1;		//�n���h��

	this->IsLoad = false;	//�ǂݍ��߂����H

	//����ǂݍ���
	std::string LoadfilePath;	//���̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle = LoadSoundMem(LoadfilePath.c_str());	//���̓ǂݍ���

	if (this->Handle == -1)	//�����ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErroeMsg(MUSIC_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadfilePath;				//���̃p�X

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(MUSIC_ERROR_TITLE),
			MB_OK);

		return;
	}

	this->FilePath = LoadfilePath;		//���̃p�X��ݒ�
	this->FileName = name;				//���̖��O��ݒ�

	this->PlayType = DX_PLAYTYPE_LOOP;	//�ŏ��͍Đ����@�����[�v�Đ��ɂ���

	this->IsLoad = true;				//�ǂݍ��ݐ���

	return;

}

//�f�X�g���N�^
MUSIC::~MUSIC()
{
	DeleteMusicMem(this->Handle);	//���̃n���h���̍폜
	return;
}

//�ǂݍ��߂����ǂ������擾
bool MUSIC::GetIsLoad()
{
	return this->IsLoad;
}

//�����Đ�����Ă��邩�擾
//�߂�l�F�Đ����Ftrue�@�Đ�������Ȃ��Ffalse
bool MUSIC::GetIsPlay()
{
	if (CheckSoundMem(this->Handle) == 1)	//�Đ����Ȃ�
	{
		this->IsPlay = true;	//�Đ���
	}
	else									//�Đ�������Ȃ����
	{
		this->IsPlay = false;	//�Đ�������Ȃ�
	}
	return this->IsPlay;
}

//�Đ����@��ύX����
void MUSIC::ChengePlayType(int type)
{
	this->PlayType = type;	
	return;
}

//���ʂ�ύX����
void MUSIC::ChengeVolume(int volume)
{
	ChangeVolumeSoundMem(volume, this->Handle);
	return;
}

//�����Đ�����
void MUSIC::Play()
{
	PlaySoundMem(this->Handle, this->PlayType);	//���̍Đ�
	return;
}

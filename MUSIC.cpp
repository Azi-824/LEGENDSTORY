//MUSIC.cpp
//���y�p�N���X

//################### �w�b�_�t�@�C���ǂݍ��� ####################
#include "MUSIC.hpp"

//################## �N���X��` ###########################

//�R���X�g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
//���@���Fint�F���f�ނ̎�ސ�
MUSIC::MUSIC(const char *dir, const char *name,int kind)
{
	//�����o�ϐ���������
	this->FilePath = "";	//�p�X
	this->FileName = "";	//���O

	this->Handle.resize(kind);		//�T�C�Y�ύX
	this->IsPlay.resize(kind);		//�T�C�Y�ύX

	this->IsLoad = false;	//�ǂݍ��߂����H

	//����ǂݍ���
	std::string LoadfilePath;	//���̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle[0] = LoadSoundMem(LoadfilePath.c_str());	//���̓ǂݍ���

	if (this->Handle[0] == -1)	//�����ǂݍ��߂Ȃ������Ƃ�
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

	this->IsPlayEnd = false;			//�Đ��I�����Ă��Ȃ�
	this->IsPlayed = false;				//�Đ��ς݂łȂ�

	return;

}

//�f�X�g���N�^
MUSIC::~MUSIC()
{

	//�͈̓x�[�X�� for ���[�v
	//vector�Ȃǂ̃R���e�i�N���X�Ŏg�p�ł���
	//auto�F�^���_�F�R���p�C���������l���琄�_���Č^�����߂Ă����
	for (int handle : this->Handle)
	{
		DeleteMusicMem(handle);		//���̃n���h���̍폜
	}

	//vector�̃�����������s��
	std::vector<int> v;			//���vector���쐬����
	this->Handle.swap(v);		//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<bool> v2;		//���vector���쐬����
	this->IsPlay.swap(v2);		//��ƒ��g�����ւ���

	return;
}

//�ǂݍ��߂����ǂ������擾
bool MUSIC::GetIsLoad()
{
	return this->IsLoad;
}

//�����Đ�����Ă��邩�擾
//�߂�l�F�Đ����Ftrue�@�Đ�������Ȃ��Ffalse
bool MUSIC::GetIsPlay(int kind)
{
	if (CheckSoundMem(this->Handle[kind]) == 1)	//�Đ����Ȃ�
	{
		this->IsPlay[kind] = true;	//�Đ���
	}
	else									//�Đ�������Ȃ����
	{
		this->IsPlay[kind] = false;	//�Đ�������Ȃ�
	}
	return this->IsPlay[kind];
}

//�Đ����@��ύX����
void MUSIC::ChengePlayType(int type)
{
	this->PlayType = type;	
	return;
}

//���ʂ�ύX����
void MUSIC::ChengeVolume(int volume,int kind)
{
	ChangeVolumeSoundMem(volume, this->Handle[kind]);
	return;
}

//�����Đ�����
void MUSIC::Play(int kind)
{
	PlaySoundMem(this->Handle[kind], this->PlayType);	//���̍Đ�
	return;
}

//����ǉ�����
bool MUSIC::Add(const char *dir, const char *name, int kind)
{

	//����ǂݍ���
	std::string LoadfilePath;	//���̃t�@�C���p�X���쐬
	LoadfilePath += dir;
	LoadfilePath += name;

	this->Handle[kind] = LoadSoundMem(LoadfilePath.c_str());	//���̓ǂݍ���

	if (this->Handle[kind] == -1)	//�����ǂݍ��߂Ȃ������Ƃ�
	{
		std::string ErroeMsg(MUSIC_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadfilePath;				//���̃p�X

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(MUSIC_ERROR_TITLE),
			MB_OK);

		return false;	//�ǂݍ��ݎ��s
	}

	return true;		//�ǂݍ��ݐ���

}

//�Đ��I���������ݒ�
void MUSIC::SetIsPlayEnd(bool isend)
{
	this->IsPlayEnd = isend;
	return;
}

//�Đ��I���������擾
bool MUSIC::GetIsPlayEnd(void)
{
	return this->IsPlayEnd;
}

//�Đ��ς݂��ݒ�
void MUSIC::SetIsPlayed(bool Isplayed)
{
	this->IsPlayed = Isplayed;
	return;
}

//�Đ��ς݂��擾
bool MUSIC::GetIsPlayed(void)
{
	return this->IsPlayed;
}

//�Đ���ԃ��Z�b�g
void MUSIC::Reset(void)
{
	this->IsPlayed = false;	//�Đ��ς݂ł͂Ȃ�
	this->IsPlayEnd = false;	//�Đ��I�����Ă��Ȃ�
	return;
}

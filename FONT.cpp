//FONT.cpp
//�t�H���g�N���X

//############### �w�b�_�t�@�C���ǂݍ��� ####################
#include "FONT.hpp"

//############### �N���X�̒�` #####################

//�R���X�g���N�^
//���@���Fconst char *�F�摜�̃f�B���N�g��
//���@���Fconst char *�F�摜�̖��O
FONT::FONT(const char *dir,const char *name)
{
	//�����o�[�ϐ�������

	this->FileName = "";		//�p�X
	this->FilePath = "";		//���O
	this->Handle = -1;			//�n���h��

								
	//�t�H���g��ǂݍ���
	std::string LoadFilePath;		//�t�H���g�̃p�X���쐬

	LoadFilePath += dir;
	LoadFilePath += name;

	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) < 0)		//�ǂݍ��ݎ��s
	{
		std::string ErroeMsg(FONT_ERROR_MSG);	//�G���[���b�Z�[�W�쐬
		ErroeMsg += TEXT('\n');					//���s
		ErroeMsg += LoadFilePath;				//�t�H���g�̃p�X

		MessageBox(
			NULL,
			ErroeMsg.c_str(),	//char * ��Ԃ�
			TEXT(FONT_ERROR_TITLE),
			MB_OK);

		return;

	}

	this->FilePath = LoadFilePath;
	this->FileName = name;

	this->Isload = true;		//�ǂݍ��߂�

	return;

}

//�f�X�g���N�^	
FONT::~FONT()
{
	std::string LoadfilePath;

	LoadfilePath += this->FilePath;

	if (RemoveFontResourceEx(LoadfilePath.c_str(), FR_PRIVATE, NULL) == 0)	//���s��
	{

		MessageBox(NULL, "remove failure", "", MB_OK);				//�G���[���b�Z�[�W

	}
}

//�ǂݍ��߂���
bool FONT::GetIsLoad()
{
	return this->Isload;
}

//�t�H���g�T�C�Y�ݒ�
void FONT::SetSize(int size)
{

	SetFontSize(size);

	return;
}


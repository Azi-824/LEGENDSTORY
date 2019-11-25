//FONT.cpp
//�t�H���g�N���X

//############### �w�b�_�t�@�C���ǂݍ��� ####################
#include "FONT.hpp"

//############### �N���X�̒�` #####################

//�R���X�g���N�^
//���@���Fconst char *�F�t�H���g�̃f�B���N�g��
//���@���Fconst char *�F�t�H���g�̖��O
//���@���Fconst char *�F�t�H���g�̐�������
FONT::FONT(const char *dir,const char *filename,const char *name)
{
	//�����o�[�ϐ�������

	this->FileName = "";		//�p�X
	this->FilePath = "";		//���O
	this->Handle = -1;			//�n���h��

								
	//�t�H���g��ǂݍ���
	std::string LoadFilePath;		//�t�H���g�̃p�X���쐬

	LoadFilePath += dir;
	LoadFilePath += filename;
	
	if (AddFontResourceEx(LoadFilePath.c_str(), FR_PRIVATE, NULL) <= 0)		//�ǂݍ��ݎ��s
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


	ChangeFont(name, DX_CHARSET_DEFAULT);							//�w�肳�ꂽ�t�H���g�ɕύX
	this->SetSize(DEFAULT_FONTSIZE);								//�t�H���g�T�C�Y���f�t�H���g�̐����ɐݒ�

	this->FilePath = LoadFilePath;
	this->FileName = filename;

	this->Isload = true;		//�ǂݍ��߂�

	return;

}

FONT::FONT()
{
	return;
}

//�f�X�g���N�^	
FONT::~FONT()
{

	if (RemoveFontResourceEx(this->FilePath.c_str(), FR_PRIVATE, NULL) == 0)	//���s��
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

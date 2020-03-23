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
	this->FileName.resize(FONT_KIND);
	this->FilePath.resize(FONT_KIND);
	this->Path_itr = this->FilePath.begin();	//�擪�v�f
	this->Name_itr = this->FileName.begin();	//�擪�v�f
	this->LoadFontNow = 0;	//�ǂݍ��񂾃t�H���g�̐�0
								
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

	*this->Path_itr = LoadFilePath;			//�擪�v�f�֑��
	*this->Name_itr = name;					//�擪�v�f�֑��

	this->Isload = true;		//�ǂݍ��߂�
	this->LoadFontNow++;		//�ǂݍ��񂾃t�H���g�̐���ǉ�

	return;

}

FONT::FONT()
{
	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->FilePath.swap(v);					//��ƒ��g�����ւ���

	//vector�̃�����������s��
	std::vector<std::string> v2;			//���vector���쐬����
	this->FileName.swap(v2);				//��ƒ��g�����ւ���


	return;
}

//�f�X�g���N�^	
FONT::~FONT()
{
	for (int i = 0; i < this->LoadFontNow; ++i)
	{
		if (RemoveFontResourceEx(this->FilePath[i].c_str(), FR_PRIVATE, NULL) == 0)	//���s��
		{

			MessageBox(NULL, "remove failure", "", MB_OK);				//�G���[���b�Z�[�W

		}
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

//�t�H���g�ǉ�
//���@���Fconst char *�F�t�H���g�̃f�B���N�g��
//���@���Fconst char *�F�t�H���g�̖��O
//���@���Fconst char *�F�t�H���g�̐�������
void FONT::AddFont(const char *dir, const char *filename, const char *name)
{

	this->Isload = false;	//�ǂݍ���łȂ�

	this->Name_itr++;	//�i�[����ʒu�����̗v�f��
	this->Path_itr++;	//�i�[����ʒu�����̗v�f��

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

	*this->Path_itr = LoadFilePath;			//���
	*this->Name_itr = name;					//���

	this->Isload = true;		//�ǂݍ��߂�
	this->LoadFontNow++;		//�ǂݍ��񂾃t�H���g�̐���ǉ�

	return;
}

//�t�H���g�ύX
void FONT::ChengFont(int fontType)
{
	ChangeFont(this->FileName[fontType].c_str(), DX_CHARSET_DEFAULT);			//�w�肳�ꂽ�t�H���g�ɕύX
	return;
}

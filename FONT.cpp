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

	ChangeFont("GD-DOTFONT-DQ-OTF", DX_CHARSET_DEFAULT);			//�w�肳�ꂽ�t�H���g�ɕύX
	this->SetSize(32);												//�t�H���g�T�C�Y32�������l�Őݒ�

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

//�����`��
//����1:�`�悷��X�ʒu
//����2:�`�悷��Y�ʒu
//����3:�`�悷�镶����
void FONT::Draw(int x,int y,const char *str)
{

	DrawString(x, y, str, GetColor(255, 255, 255));		//�����`��

	return;
}

//������̉������擾
//����1:�������擾������������
int FONT::GetWidth(const char *str)
{
	int Strlen = 0;		//������̒����擾�p
	
	//������̒������擾
	Strlen = strlen(str);

	this->Width = GetDrawStringWidth(str, Strlen);		//�����擾

	return this->Width;	//������Ԃ�

}


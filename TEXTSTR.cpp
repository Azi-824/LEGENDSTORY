//TEXTSTR.cpp
//������A���͂��Ǘ�����

//###################### �w�b�_�t�@�C���ǂݍ��� ######################
#include "TEXTSTR.hpp"

//###################### �N���X��` ####################

//�R���X�g���N�^
TEXTSTR::TEXTSTR()
{
	return;
}

//�f�X�g���N�^
TEXTSTR::~TEXTSTR()
{
	return;
}

//�����擾����
int TEXTSTR::GetWidth()
{

	int Strlen = 0;		//������̒����擾�p

	//������̒������擾
	Strlen = strlen(this->Str.c_str());

	this->Width = GetDrawStringWidth(this->Str.c_str(), Strlen);		//�����擾

	return this->Width;
}

//��������Z�b�g����
//�����Fconst char *�F�Z�b�g���镶����
//�����Fint			�F�s
void TEXTSTR::SetText(const char *str, int row)
{
	this->Str = str;
	return;
}

//�`��
//�����Fint�FX�ʒu
//�����Fint�FY�ʒu
void TEXTSTR::Draw(int x, int y,int row)
{
	DrawString(x, y, this->Str.c_str(), GetColor(255, 255, 255));
}
//WINDOW.cpp
//�Q�[�����ŕ`�悷��E�B���h�E�̃N���X

//########################## �w�b�_�t�@�C���ǂݍ��� #########################
#include "WINDOW.hpp"

//########################## �N���X��` ##############################

//�R���X�g���N�^
WINDOW::WINDOW()
{
	//�����o�ϐ�������
	this->Str = { "" };	//�������������
	this->Str_itr = this->Str.begin();	//�擪�A�h���X
	this->Num = { 0 };
	this->Num_itr = this->Num.begin();	//�擪�A�h���X

	this->Width = 200;		//����������
	this->Height = 120;		//������������

	this->X = 0;			//X�ʒu��������
	this->Y = 480;			//Y�ʒu��������

	this->StrHeight = GetFontSize();	//�������擾

}

//�f�X�g���N�^
WINDOW::~WINDOW()
{
	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->Str.swap(v);				//��ƒ��g�����ւ���

	std::vector<int> v2;			//���vector���쐬����
	this->Num.swap(v2);				//��ƒ��g�����ւ���

	return;

}

//X�ʒu�ݒ�
void WINDOW::SetX(int x)
{
	this->X = x;
	return;
}

//Y�ʒu�ݒ�
void WINDOW::SetY(int y)
{
	this->Y = y;
	return;
}

//�����ݒ�
void WINDOW::SetWidth(int width)
{
	this->Width = width;
	return;
}

//�����ݒ�
void WINDOW::SetHeight(int height)
{
	this->Height = height;
	return;
}

//X�ʒu�擾
int WINDOW::GetX(void)
{
	return this->X;
}

//Y�ʒu�擾
int WINDOW::GetY(void)
{
	return this->Y;
}

//�����擾
int WINDOW::GetWidth(void)
{
	return this->Width;
}

//�����擾
int WINDOW::GetHeight(void)
{
	return this->Height;
}

//�����񉡕��擾
int WINDOW::GetStrWidth(void)
{
	int Strlen = 0;		//������̒����擾�p

	Strlen = strlen(this->Str_itr->c_str());

	this->StrWidth = GetDrawStringWidth(this->Str_itr->c_str(), Strlen);	//�����擾

	return this->StrWidth;

}

//�����񍂂��擾
int WINDOW::GetStrHeight(void)
{
	this->StrHeight = GetFontSize();	//�����擾

	return this->StrHeight;
}

//������i�����j�A�h���X�̎擾
std::vector<int>::iterator WINDOW::GetNumPos()
{
	return this->Num_itr;
}

//�E�B���h�E���ɕ`�悷�镶�����Z�b�g����
void WINDOW::SetText(const char *text)
{
	*this->Str_itr = text;
	return;
}

//�E�B���h�E���ɕ`�悷�镶���i�����j���Z�b�g����
void WINDOW::SetText(int num)
{
	*this->Num_itr = num;
	return;
}

//�`��
void WINDOW::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * 80 / 100);	//�`�惂�[�h�𓧉߂���ɕύX�A���ߗ�80���ɐݒ�

	DrawBox(this->X, this->Y, this->X + this->Width, this->Y + this->Height, GetColor(255, 0, 0), TRUE);	//�h��Ԃ�����Ŏl�p�`��`��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�`�惂�[�h��ʏ�ɖ߂�

	DrawFormatString(this->X, this->Y, GetColor(255, 255, 255), "%s", this->Str_itr->c_str());	//�����`��

	return;

}

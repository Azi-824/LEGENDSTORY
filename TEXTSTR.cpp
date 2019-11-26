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

	//vector�̃�����������s��
	std::vector<std::string> v;			//���vector���쐬����
	this->Str.swap(v);				//��ƒ��g�����ւ���

	return;
}

//�����擾����
int TEXTSTR::GetWidth()
{

	int Strlen = 0;		//������̒����擾�p
	std::string TotalStr;
	for (unsigned int i = 0; i < this->Str.size(); i++)
	{
		TotalStr += this->Str[i].c_str();		//���������������
	}

	//������̒������擾
	Strlen = strlen(TotalStr.c_str());

	this->Width = GetDrawStringWidth(TotalStr.c_str(), Strlen);		//�����擾

	return this->Width;
}

//��������Z�b�g����
//�����Fvector<string>�F�Z�b�g���镶����
void TEXTSTR::SetText(std::vector<std::string> str)
{
	this->Str.resize(str.size());		//�v�f����ύX
	this->Str.swap(str);				//��������Z�b�g

	this->Pos = this->Str.begin();	//�ŏ��͈�ԍŏ��̗v�f��I����Ԃɂ���	

	return;
}

//�`��
//�����Fint�FX�ʒu
//�����Fint�FY�ʒu
//�����Fint�F�v�f��
void TEXTSTR::Draw(int x, int y,int num)
{

	for (int cnt = 0; cnt < num; cnt++)
	{
		if (*this->Pos==this->Str[cnt])	//�I����Ԃ�������
		{
			DrawString(x + cnt * 100, y - 50, this->Str[cnt].c_str(), GetColor(0, 0, 0));	//��ɂ��炵�ĕ`��
		}
		else				//��I����Ԃ�������
		{
			DrawString(x + cnt * 100, y, this->Str[cnt].c_str(), GetColor(0, 0, 0));	//�`��

		}

	}
	return;
}

//�`��
//�����Fint�FX�ʒu
//�����Fint�FY�ʒu
//�����Fint�F�v�f��
//�����Gunsigned int �F�`��F
void TEXTSTR::Draw(int x, int y, int num ,unsigned int color)
{
	for (int cnt = 0; cnt < num; cnt++)
	{
		if (*this->Pos == this->Str[cnt])	//�I����Ԃ�������
		{
			DrawString(x + cnt * 100, y - 50, this->Str[cnt].c_str(), color);	//��ɂ��炵�ĕ`��
		}
		else								//��I����Ԃ�������
		{
			DrawString(x + cnt * 100, y, this->Str[cnt].c_str(), color);		//�`��

		}
	}

	return;
}

//�I�����Ă��镶��������̗v�f�ɕύX����
void TEXTSTR::Next()
{
	if (this->Pos != this->Str.end()-1)	//�Ō�̗v�f�łȂ����
	{
		this->Pos++;	//���̗v�f��
	}
		return;
}

//�I�����Ă��镶��������̗v�f�ɕύX����
void TEXTSTR::Back()
{
	if (this->Pos != this->Str.begin())	//�ŏ��̗v�f�łȂ����
	{
		this->Pos--;	//�O�̗v�f��
	}
	return;
}
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
	Strlen = strlen(this->Str_2.begin()->c_str());

	this->Width = GetDrawStringWidth(this->Str_2.begin()->c_str(), Strlen);		//�����擾

	return this->Width;
}

//��������Z�b�g����
//�����Fconst char *�F�Z�b�g���镶����
//�����Fint			�F�s
void TEXTSTR::SetText(std::vector<std::string> str, int row)
{
	//this->Str_2.push_back(str.front().c_str());
	//this->Str_2.assign(str.front().c_str(), str.back().c_str());
	this->Str_2.swap(str);
	return;
}

//�`��
//�����Fint�FX�ʒu
//�����Fint�FY�ʒu
void TEXTSTR::Draw(int x, int y,int row)
{

	for (int cnt = 0; cnt < row; cnt++)
	{
		DrawString(x+cnt*100, y, this->Str_2[cnt].c_str(), GetColor(255, 255, 255));
	}
	return;
}
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
	this->Str_2.swap(v);				//��ƒ��g�����ւ���

	return;
}

//�����擾����
int TEXTSTR::GetWidth()
{

	int Strlen = 0;		//������̒����擾�p
	std::string TotalStr;
	for (unsigned int i = 0; i < this->Str_2.size(); i++)
	{
		TotalStr += this->Str_2[i].c_str();		//���������������
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
	this->Str_2.swap(str);

	return;
}

//�`��
//�����Fint�FX�ʒu
//�����Fint�FY�ʒu
//�����Fint�F�s��
//�����Fint�F�v�f��
void TEXTSTR::Draw(int x, int y,int row,int num)
{

	for (int cnt = 0; cnt < num; cnt++)
	{
		DrawString(x + cnt * 100, y, this->Str_2[cnt].c_str(), GetColor(0, 0, 0));	//�`��
	}
	return;
}
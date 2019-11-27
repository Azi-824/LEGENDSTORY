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
	this->Str.swap(v);					//��ƒ��g�����ւ���

	return;
}

//�����擾����
int TEXTSTR::GetWidth()
{

	int Strlen = 0;		//������̒����擾�p

	std::string MaxStr;	//�ł�����������

	MaxStr = this->Str[0].c_str();	//�ł�����������ɍŏ��̕�������Z�b�g

	for (int i = 0; i < this->Str.size(); i++)
	{
		if (MaxStr < this->Str[i].c_str())	//���݂̍ő啶��������傫�����
		{
			MaxStr = this->Str[i].c_str();	//�ő啶������X�V
		}
	}

	//������̒������擾
	Strlen = strlen(MaxStr.c_str());

	this->Width = GetDrawStringWidth(MaxStr.c_str(), Strlen);		//�����擾

	return this->Width;
}

//�������擾����
int TEXTSTR::GetHeight()
{
	this->Height = GetFontSize();	//�t�H���g�T�C�Y�擾
	return this->Height;
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
void TEXTSTR::Draw(int x, int y,int num,bool arrow)
{

	for (int cnt = 0; cnt < num; cnt++)
	{
		if (this->Str.size() == 1)			//�v�f������i�I�����Ȃ��j��������
		{
			DrawFormatString(x, y + cnt * this->GetHeight(), GetColor(0, 0, 0), "%s", this->Str[cnt].c_str());	//�ʏ�`��
		}
		else
		{
			if (*this->Pos == this->Str[cnt])	//�I����Ԃ�������
			{
				if (arrow)					//���t����������
				{
					DrawFormatString(x, y + cnt * this->GetHeight(), GetColor(0, 0, 0), "��%s", this->Str[cnt].c_str());	//���t���ŕ`��
				}
				else
				{
					DrawFormatString(x + 50, y + cnt * this->GetHeight(), GetColor(0, 0, 0), "%s", this->Str[cnt].c_str());	//���Ȃ��ŕ`��
				}
			}
			else				//��I����Ԃ�������
			{
				DrawFormatString(x, y + cnt * this->GetHeight(), GetColor(0, 0, 0), "%s", this->Str[cnt].c_str());	//�`��

			}

		}

	}
	return;
}

//�`��
//�����Fint�FX�ʒu
//�����Fint�FY�ʒu
//�����Fint�F�v�f��
//�����Gunsigned int �F�`��F
void TEXTSTR::Draw(int x, int y, int num ,bool arrow,unsigned int color)
{
	for (int cnt = 0; cnt < num; cnt++)
	{
		if (this->Str.size() == 1)				//�v�f������i�I�����Ȃ��j��������
		{
			DrawFormatString(x, y + cnt * this->GetHeight(), color, "%s", this->Str[cnt].c_str());	//�ʏ�`��
		}
		else
		{
			if (*this->Pos == this->Str[cnt])	//�I����Ԃ�������
			{
				if (arrow)						//���t����������
				{
					DrawFormatString(x, y + cnt * this->GetHeight(), color, "��%s", this->Str[cnt].c_str());	//���t���ŕ`��
				}
				else
				{
					DrawFormatString(x + 50, y + cnt * this->GetHeight(), color, "%s", this->Str[cnt].c_str());	//���Ȃ��ŕ`��
				}
			}
			else								//��I����Ԃ�������
			{
				DrawFormatString(x, y + cnt * this->GetHeight(), color, "%s", this->Str[cnt].c_str());	//�`��
			}

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

//���ݑI�����Ă��镶����̃|�C���^���擾����
std::vector<std::string>::iterator TEXTSTR::GetPos()
{
	return this->Pos;
}
